#include "node.h"
#include <iostream>
#include <math.h>

node::node(int id, int x, int y){
    this->id = id;
    this->location = std::pair<int,int>(x,y);
}

void node::receiveRequest(int srcNodeId){
    this->receivedRequests.push_back(srcNodeId);
}

double node::distance(const node* nodeB){
    double x = this->location.first - nodeB->location.first;
    double y = this->location.second - nodeB->location.second;
    double dist = std::pow(x,2) + std::pow(y,2);
    dist = std::sqrt(dist);
    return dist;
}

void node::printme(){
    if (this->connected.empty()==true) {
        std::cout<<"node "<<this->id<<" received: ";
        auto it = this->receivedRequests.begin();
        while(it!=this->receivedRequests.end())
            std::cout<<*it++<<" ";
        std::cout<<std::endl;
    }else{
        std::cout<<"node "<<this->id<<" connected: ";
        auto it = this->connected.begin();
        while(it!=this->connected.end())
            std::cout<<*it++<<" ";
        std::cout<<std::endl;
    }
}

bool node::hasRequest(const int srcNodeId){
    auto it = this->receivedRequests.begin();
    while(it != this->receivedRequests.end())
        if (*it++ == srcNodeId) return true;
    return false;
}

void node::connect(const int srcNodeId){
    this->receivedRequests.remove(srcNodeId);
    this->connected.push_back(srcNodeId);
}
