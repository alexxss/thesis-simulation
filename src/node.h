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
    * \brief initializer for node
    * \param id Node id
    * \param x,y Location for node
    */
    node(int id,double x,double y);

    /**
    * \brief this Node will receive the request from srcNodeId
    * \param srcNodeId the ID of the node to be accepted
    */
    void receiveRequest(int srcNodeId);

    /**
    * \brief calculates plane distance between this node and nodeB
    *
    * "plane distance" refers to the distance when view from 'above'
    *
    * \param nodeB pointer to Node with whom distance will be calculated
    * \return distance(double) between this node and nodeB
    */
    double plane_distance(const node* nodeB);

    /**
    * \brief caclulates euclidean distance between this node and nodeB
    *
    * "euclidean distance" refers to the distance in 3D space
    *
    */
    double euclidean_distance(const node* nodeB);

    /**
    * \param srcNodeId
    * \return bool if this node has received request from srcNodeId
    */
    bool hasRequest(const int srcNodeId);

    /**
    * \brief connect this node and srcNodeId
    * \param srcNodeId the ID of node to whom this node will be connected
    */
    void connect(const int srcNodeId);



    void fakesend(node* destNode);
    void fakereceive(node* srcNode);
    void printme();
    /**
    * \brief prints details of this node
    * \param mode 0=print srcNodeId of received requests, 1=print ID of connected node(s)
    *
    */
    void printme(const int mode);
private:
    std::list<int> connected;
    void sendRequest();
    std::list<int> receivedRequests;
};
