#include<utility> //pair
#include<list> //list

class node{
public:
    int id;
    std::pair<int,int> location;
    node(int,int,int);
    void receiveRequest(int);
    double distance(const node*);
    void connect(const int);
    bool hasRequest(const int);
    void printme();
private:
    std::list<int> connected;
    void sendRequest();
    std::list<int> receivedRequests;
};
