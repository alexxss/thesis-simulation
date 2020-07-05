#define NODE

#ifndef ENVIRONMENT
#include "global_environment.h"
#endif // ENVIRONMENT

#include "resource_allocation.h"

#include<utility> //pair
#include<list> //list
#include<vector>

class node{
public:
    int id;
    std::pair<double,double> location;
    double min_required_rate;

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

    /**
    * sort UEs according to channel (h_1 > h_2 > ...),
    * required by NOMA.
    * sorting UE id saved in std::list<int> node::sorted_UE
    * \param channel 2d array of channel [ap][ue]
    */
    void NOMA_sort_UE_desc();

    /**
    * \brief gets UE's sorting order in this AP's cluster
    * \param UE id
    * \return int sorting order [1:|U_n|], -1 if not found
    */
    int get_sorting_order (const int& UE_id) const ;

    void set_resource_block(const int& rb_id);
    int get_resource_block();
    std::list<int> get_connected();

    void tdma();

    /**
    * \brief calculate r of UE k using mod m on layer l
    * \param const int& m: which modulation mode
    * \param const int& l: which layer
    * \return double: the achievable rate
    */
    double calculate_achievable_rate_single_layer(const int& m, const int& l);

    /**
    * \brief calculates ICI imposed by this node (AP) on node UE_id
    * this function should only be called by an AP node!
    */
    double calculate_ICI(const int& UE_id);

    /* currently unused, just two test functions */
    void fakesend(node* destNode);
    void fakereceive(node* srcNode);

    void printme();
    /**
    * \brief prints details of this node
    * \param mode 0,1,2
    * 0= print srcNodeId of received requests
    * 1= print ID of connected node(s)
    * 2= print time slot schedule
    */
    void printme(const int mode);

    /*
        static member to hold instances
        // TODO (alex#3#): replace main.cpp's transmitter and receiver array with these instead
        example usage: `node::transmitter[i]`
    */
    static node* transmitter[g_AP_number];
    static node* receiver[g_UE_number];
    static double channel[g_AP_number][g_UE_number];
private:
    int resource_block_id;
    std::list<int> connected;
    void sendRequest();
    std::list<int> receivedRequests;
    int servedUE_cnt;
    std::list<int> sorted_UE;
    std::list<double> time_allocation;
    void tdma_scheduling();
    void tdma_time_allocation();
    std::list<std::list<int>> time_slot_schedule;
    std::list<int> dynamic_resource_allocation(std::vector<int>& candidate);
    /** second tier resource allocation
    * can only be called by AP node!!
    * \param all_candidate_mod_scheme_set each item in this list is a pair for each UE, pair.first = UE_id, pair.second = all candidate schemes for this UE
    * \return list of accept UEs' id
    */
    mod_scheme_combi ra_second_tier(const std::list<std::pair<int, std::list<mod_scheme*>>>& all_candidate_mod_scheme_set);
};
