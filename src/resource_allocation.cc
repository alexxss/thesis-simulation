#include "node.h"
#include <random> // uniform_real_distribution, default_random_engine
#include <list> // std::list
#include <iostream>
#include <fstream> // ofstream
#include <chrono> // seed
#include <math.h> // log2, power, floor
#include "math.c" // erfinv
#include "resource_allocation.h" // struct mod scheme

/**
* \brief calculate nearest lower rate constraint level
* \return int j_star: nearest lower rate constraint level
*/
int jFloor(double const& rateConstraintForPrevLayer){
    // if R_j - r < 0, t_m = 0
    if (rateConstraintForPrevLayer<0) return 0;
    int j_star = floor(rateConstraintForPrevLayer / g_R_max * g_J);
    /* actually belongs to j_star+1 level, but round down to j_star according to algorithm */
    return j_star;
}

double node::calculate_achievable_rate_single_layer(const int& m, const int& l){
    /* BER(m) -> SINR */
    double SINR = 0.0;
    SINR = g_BER;
    SINR = SINR * m * pow(2,m);
    SINR = SINR / (pow(2,m) - 1);
    SINR = 1 - SINR;
    SINR = erfinv(SINR);
    SINR = pow(SINR,2);
    SINR = SINR / 3 * 2 * ( pow(2,2*m) - 1);

    /* SINR(B,beta_l,SINR) -> rate */
    double rate = 0.0;
    rate = (double)g_bandwidth_per_rb / pow(2,l) * log2(1 + SINR);
    return rate;
}

/**
* First Tier RA of UE <candidate-id>. Logs are saved to `./log/<candidate-id>_first_tier`.
* for each l:1-L
*    for each j:1-J
*       for each m:1-|M|
*          [1] calculate achievable rate using m for layer l: r
*          [2] calculate achievate rate at rate constraint (R_j - r) using layers 1 to (l-1): T
*          [3] t_m = T + r
*       obtain ahievable rate at rate constraint R_j using layers 1 to l: max(t_m)
*
* \return list<mod_scheme*> list of mod schemes that satisfy min rate
*/
std::list<mod_scheme*> ra_first_tier(const int& candidate_id){
    node* node_UE = node::receiver[candidate_id];
    std::list<mod_scheme*> candidate_schemes;
    std::cout<<"-- 1st Tier RA for UE "<<node_UE->id<<std::endl;
    struct mod_scheme* my_mod_schemes[g_L][g_J]; // used to store mod schemes for all l and j

    std::string filepath = "./log/" + std::to_string(node_UE->id) + "_first_tier";
    std::ofstream fout(filepath);
    if(!fout.is_open()) {
        std::cout<<"Can't Open "<<filepath<<", exiting now";
        exit(1);
    }

    /*-- for each l, for each j, calculate max achievable rate and respective mod scheme --*/
    for(int l = 1; l<=g_L; l++){
        /* using l layers: */
        fout<<"l = "<<l<<", "<<std::endl;

        for(int j = 1; j<=g_J; j++){
            /* under rate constraint R_j: */
            fout<<"-- j = "<<j<<", r|t_m for m=1~5:";

            /* initialize mod_scheme */
            my_mod_schemes[l-1][j-1] = new mod_scheme;
            mod_scheme* current_mod_scheme = my_mod_schemes[l-1][j-1];
            current_mod_scheme->sum_throughput = 0.0;

            for(int m = 1; m<=g_M; m++){
                /** [1] t_m = T_(k,l-1)(R_j-r(m,k,l)) + r(m,k,l) **/
                /**     calculate r(m,k,l) */
                double r_m = node_UE->calculate_achievable_rate_single_layer(m,l);
                fout<<"\t"<<r_m;

                /**     calculate t_m = T + r */
                /* initialize mod scheme combination */
                std::list<int> current_mod_combi;
                /* if >1st layer, t_m initialize as T_(k,l-1)(R_j-r) */
                double t_m = 0.0;
                double R_j = (double)g_R_max / g_J * j;
                if (l>1)  {
                    R_j = R_j-r_m;
                    if (R_j < 0) {// if R_j - r < 0, t_m = 0.
                        t_m = 0;
                        current_mod_combi.push_back(-1);// this mod CANNOT be chosen.
                    }
                    else {       // if R_j - r >= 0, can at least afford this layer.
                        t_m = r_m;
                        if (jFloor(R_j)>0) {// remaining Rate enough for prev (l-1) layers
                            t_m = my_mod_schemes[l-2][jFloor(R_j)-1]->sum_throughput + r_m; // l-2 because l starts at 1 but index starts at 0
                            current_mod_combi = my_mod_schemes[l-2][jFloor(R_j)-1]->modes_each_layer;
                        }
                        current_mod_combi.push_back(m);
                    }

                } else { // first layer
                    if (R_j >= r_m){
                        t_m = r_m;
                        current_mod_combi.push_back(m);
                    } else
                        current_mod_combi.push_back(-1);
                }
                fout<<"|"<<t_m;

                /** [2] max t_m **/
                if (t_m >= current_mod_scheme->sum_throughput){
                    current_mod_scheme->sum_throughput = t_m;
                    current_mod_scheme->modes_each_layer = current_mod_combi;
                }
            }

            /** save mod scheme using l layers under constraint R_j:
             *  mod used for each layer, total achievable rate, total required power
             *  struct defined in "resource_allocation.h"
             */
            fout<<"\t=> "<<current_mod_scheme->sum_throughput<<", \t";
            //fout<<"                          \t";
            for(int i:current_mod_scheme->modes_each_layer) fout<<i<<' ';
            fout<<std::endl;

            if (current_mod_scheme->sum_throughput >= node_UE->min_required_rate && current_mod_scheme->sum_throughput < g_R_max){
                candidate_schemes.push_back(current_mod_scheme);
            }
        }
    }
    fout.close();
    return candidate_schemes;
}

/** second tier
* \return list of accept UEs' id
*/
std::list<int> ra_second_tier(const std::list<std::pair<int, std::list<mod_scheme*>>>& all_candidate_mod_scheme_set){
    int UE_number = all_candidate_mod_scheme_set.size();

    for(auto candidate_scheme_set : all_candidate_mod_scheme_set){
        for(int l = 1; l<=g_L; l++){ // l is power constraint level
            double P_l = g_P_max * l / g_L;
            /** determine best scheme under P_l */

            /** save scheme */
            // mod_scheme_combi* mod_scheme_combination = new mod_scheme_combi;
            // mod_scheme_combination->sum_throughput = ??
            // mod_scheme_combination->required_power = ??
            // mod_scheme_combination->mod_schemes_each_UE = ??
        }
    }
}

/** this member function should only be called by an AP node */
std::list<int> node::dynamic_resource_allocation(const std::vector<int>& candidate){
    /* a list of pair<UE_id, list_of_candidate_schemes_of_this_UE> */
    std::list<std::pair<int, std::list<mod_scheme*>>> all_candidate_mod_scheme_set;

    /* first tier RA: generate mod schemes for each UE */
    for(int candidate_id:candidate){
        std::pair<int,std::list<mod_scheme*>> all_candidate_mod_scheme;
        all_candidate_mod_scheme.first = candidate_id;
        all_candidate_mod_scheme.second = ra_first_tier(candidate_id);
    }

    /* second tier RA: select scheme combination */


    std::uniform_real_distribution<double> unif(0,1.0);
    std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());

    std::list<int> accepted;
    for(int i:candidate) accepted.push_back(i);
    //std::cout<<"-- Accepted: "; for(int i:accepted)std::cout<<i<<' '; std::cout<<'\n';
    for(int i : candidate){
        double chance = unif(re);
        //std::cout<<"-- -- Chance="<<chance<<std::endl;
        if(chance<0.5) accepted.remove(i);
    }
    return accepted;
}

