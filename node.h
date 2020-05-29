#define NODE

#ifndef ENVIRONMENT
#include "global_environment.h"
#endif // ENVIRONMENT

#include<utility> //pair
#include<list> //list

class node{
public:
    int id;
    std::pair<double,double> location;

    node(int id);

    /**
    \brief initializer for node
    \param id Node id
    \param x,y Location for node
    */
    node(int id,double x,double y);

    /**
    \brief this Node will receive the request from srcNodeId
    \param srcNodeId the ID of the node to be accepted
    */
    void receiveRequest(int srcNodeId);

    /**
    \brief calculates distance between this node and passed Node
    \param nodeB pointer to Node with whom distance will be calculated
    \return distance(double) between this node and nodeB
    */
    double distance(const node* nodeB);

    /**
    \param srcNodeId
    \return bool if this node has received request from srcNodeId
    */
    bool hasRequest(const int srcNodeId);

    /**
    \brief connect this node and srcNodeId
    \param srcNodeId the ID of node to whom this node will be connected
    */
    void connect(const int srcNodeId);



    void fakesend(node* destNode);
    void fakereceive(node* srcNode);
    void printme();
private:
    std::list<int> connected;
    void sendRequest();
    std::list<int> receivedRequests;
};
