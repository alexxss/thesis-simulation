#ifndef NODE
#include "node.h"
#endif // NODE
#ifndef ENVIRONMENT
#include "global_environment.h"
#endif // ENVIRONMENT

#include <iostream>
#include <math.h>

node::node(int id){
    this->id = id;
    double x = ((id%g_AP_per_row)+1)*(g_room_dim/(g_AP_per_row+1));
    double y = (g_AP_per_row-(id/g_AP_per_row))*(g_room_dim/(g_AP_per_row+1));
    this->location = std::pair<double,double>(x,y);
}

    /**
    * \brief initializer for node
    * \param id Node id
    * \param x,y Location for node
    */
node::node(int id, double x, double y){
    this->id = id;
    this->location = std::pair<double,double>(x,y);
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


bool node::hasRequest(const int srcNodeId){
    auto it = this->receivedRequests.begin();
    while(it != this->receivedRequests.end())
        if (*it++ == srcNodeId) return true;
    return false;
}

void node::connect(const int srcNode){
    this->receivedRequests.remove(srcNode);
    this->connected.push_back(srcNode);
}

void node::fakesend(node* destNode){
    std::cout<<this->id<<" send to "<<destNode->id<<std::endl;
    destNode->fakereceive(this);
}

void node::fakereceive(node* srcNodeId){
    std::cout<<this->id<<" received from "<<srcNodeId->id<<std::endl;
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
