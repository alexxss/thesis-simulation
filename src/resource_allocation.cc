#include "node.h"
#include <random> // uniform_real_distribution, default_random_engine
#include <list>
#include <vector>
#include <iostream>
#include <chrono> // seed

void ra_first_tier(const int& candidate_id){
    node* node_UE = node::receiver[candidate_id];
    std::cout<<"-- 1st Tier RA for UE "<<node_UE->id<<std::endl;

    /*-- for each l, for each j, calculate max achievable rate and respective mod scheme --*/
    for(int l = 1; l<=g_L; l++){
        /* using l layers: */
        for(int j = 1; j<=g_J; j++){
            /* under rate constraint R_j: */
            for(int m = 1; m<=g_M; m++){
                /* [1] t_m = T_(k,l-1)(R_j-r(m,k,l)) - r(m,k,l) */
                /* [2] save to STL? or just replace t_m with max? */
            }
            /* select max t_m */

            /* save mod scheme using l layers under constraint R_j:
             * mod used for each layer, total achievable rate, total required power */
        }
    }
}

/* this member function should only be called by an AP node */
std::list<int> node::dynamic_resource_allocation(const std::vector<int>& candidate){
    /* first tier RA: generate mod schemes for each UE */
    for(int candidate_id:candidate){
        ra_first_tier(candidate_id);
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

