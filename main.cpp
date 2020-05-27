#include <iostream>
#include <stdlib.h> //rand
#include <random> //C++'s random
#include "node.h"
#define NODE
#include "clustering.h"
#define UE_number 10
#define AP_number 20
#define channel_threshold 7.5
#define distance_threshold 5

using namespace std;

int main()
{
    /*-------------initialization----------------*/
    node* transmitter [AP_number]; // AP
    node* receiver [UE_number];    // UE
    for (int i=0; i<AP_number; i++)
        transmitter[i]=new node(i,rand()%20,rand()%20); // AP
    for (int i=0; i<UE_number; i++)
        receiver[i] = new node(i,rand()%20, rand()%20); // UE

    /*-----------generate channel----------------*/
    uniform_real_distribution<double> unif(0.0,15.0);
    default_random_engine re;
    double channel[AP_number][UE_number];
    for(int i=0;i<AP_number;i++)
        for (int j=0;j<UE_number;j++){
            channel[i][j] = unif(re);
        }

    /*---- for each UE, send request to APs if channel > threshold ----*/
    for(int i=0;i<UE_number;i++){
        // check all APs, if channel > threshold send request
        for(int j=0; j<AP_number; j++){
            if (channel[j][i]>channel_threshold)
                transmitter[j]->receiveRequest(i);
        }
    }
    //UE_send_requests(transmitter,receiver,channel,UE_number,AP_number,channel_threshold);

    /*---- for each AP, send request to UEs if distance < threshold ----*/
    for(int i=0; i<AP_number; i++){
        // check all UEs, if distance<threshold send request
        for(int j=0; j<UE_number; j++){
            //if (Euclidean_distance(transmitter[i]->location,receiver[j]->location)<distance_threshold)
            if (transmitter[i]->distance(receiver[j])<distance_threshold)
                receiver[j]->receiveRequest(i);
        }
    }

    cout<<"UE nodes"<<endl;
    for(int i=0; i<UE_number; i++) receiver[i]->printme();
    cout<<endl<<"AP nodes"<<endl;
    for(int j=0; j<AP_number; j++) transmitter[j]->printme();

    both_sides_connect(transmitter,receiver,UE_number,AP_number);

    cout<<"UE nodes"<<endl;
    for(int i=0; i<UE_number; i++) receiver[i]->printme();
    cout<<endl<<"AP nodes"<<endl;
    for(int j=0; j<AP_number; j++) transmitter[j]->printme();

    return 0;
}
