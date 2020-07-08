#include <list>
#ifndef RESOURCE_ALLOCATION

struct mod_scheme{
	double sum_throughput;
	double required_power;
	std::list<int> modes_each_layer; // mode 0 means no mod selected for that layer!!
	mod_scheme(){};
	mod_scheme(const mod_scheme* scheme){
	    this->modes_each_layer = scheme->modes_each_layer;
	    this->sum_throughput = scheme->sum_throughput;
	}
};

struct mod_scheme_combi{
    double sum_throughput;
    double required_power;
    std::list<mod_scheme*> mod_schemes_each_UE;
    mod_scheme_combi(){ // init
        this->sum_throughput = 0.0;
        this->required_power = 0.0;
        this->mod_schemes_each_UE.clear();
    }
};

#define RESOURCE_ALLOCATION
#endif // RESOURCE_ALLOCATION
