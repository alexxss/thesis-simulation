#include "node.h"
#include <random> // uniform_real_distribution, default_random_engine
#include <list>
#include <vector>
#include <iostream>
#include <chrono> // seed

std::list<int> node::dynamic_resource_allocation(const std::vector<int>& candidate){
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
