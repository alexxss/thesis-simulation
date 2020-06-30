#include <list>
struct mod_scheme{
	double sum_throughput;
	double required_power;
	std::list<int> modes_each_layer;
};

struct mod_scheme_combi{
    double sum_throughput;
    double required_power;
    std::list<mod_scheme*> mod_schemes_each_UE;
};
