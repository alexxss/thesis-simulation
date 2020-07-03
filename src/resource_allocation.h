#include <list>

struct mod_scheme{
	double sum_throughput;
	double required_power;
	std::list<int> modes_each_layer; // mode 0 means no mod selected for that layer!!
};

struct mod_scheme_combi{
    double sum_throughput;
    double required_power;
    std::list<mod_scheme*> mod_schemes_each_UE;
    mod_scheme_combi(){
        this->sum_throughput = 0.0;
        this->required_power = 0.0;
        this->mod_schemes_each_UE.clear();
    }
};
