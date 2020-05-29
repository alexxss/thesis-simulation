#ifndef NODE
#include "src/node.h"
#endif // NODE
#ifndef CLUSTERING
#include "src/clustering.h"
#endif // CLUSTERING
#ifndef CHANNEL
#include "src/channel.h"
#endif // CHANNEL

#include <iostream>
#include <stdlib.h> //rand
#include <random> //C++'s random
#include <fstream> //ofstream

using namespace std;

/**
\brief saves UE & AP location to file for plot
\param receiver array
\param transmitter array
*/
void save_room_data(node* receiver[g_UE_number], node* transmitter[g_AP_number]){
    /*--------------save to file for plot------------------
     columns: <node id> <x> <y>
     run in cmd: `gnuplot -p plot_room.gnu` to view plot
    -------------------------------------------------------*/
    ofstream fout("UE_point.dat");
    if(fout.is_open()){
        for(int i=0;i<g_UE_number;i++)
            fout<<i<<' '<<receiver[i]->location.first<<' '<<receiver[i]->location.second<<endl;
        fout.close();
    }
    fout.open("AP_point.dat");
    if(fout.is_open()){
        for(int i=0;i<g_AP_number;i++){
            fout<<i<<' '<<transmitter[i]->location.first<<' '<<transmitter[i]->location.second<<endl;
        }
        fout.close();
    }

}

int main()
{
    /*-------------initialization----------------*/
    node* transmitter [g_AP_number]; // AP
    node* receiver [g_UE_number];    // UE
    // generate AP node
    for (int i=0; i<g_AP_number; i++)
        transmitter[i]=new node(i); // AP
    // generate UE node
    uniform_real_distribution<double> unif(0.0, g_room_dim);
    default_random_engine re;
    for (int i=0; i<g_UE_number; i++)
        receiver[i] = new node(i,unif(re), unif(re)); // UE

    /*--------------save to file for plot------------------
     run in cmd: `gnuplot -p plot_room.gnu` to view plot
    -------------------------------------------------------*/
    save_room_data(receiver, transmitter);

    // TODO (alex#1#): use channel formula
    /*-----------calculate channel---------------*/
    double channel[g_AP_number][g_UE_number];
    calculate_all_channel(transmitter,receiver,channel);

    /*---- for each UE, send request to APs if channel > threshold ----*/
    for(int i=0;i<g_UE_number;i++){
        // check all APs, if channel > threshold send request
        for(int j=0; j<g_AP_number; j++){
            if (channel[j][i]>g_channel_threshold)
                transmitter[j]->receiveRequest(i);
        }
    }

    /*---- for each AP, send request to UEs if distance < threshold ----*/
    for(int i=0; i<g_AP_number; i++){
        // check all UEs, if distance<threshold send request
        for(int j=0; j<g_UE_number; j++){
            if (transmitter[i]->euclidean_distance(receiver[j])<g_distance_threshold)
                receiver[j]->receiveRequest(i);
        }
    }

    cout<<"UE nodes"<<endl;
    for(int i=0; i<g_UE_number; i++) receiver[i]->printme();
    std::cout<<std::endl<<"AP nodes"<<std::endl;
    for(int j=0; j<g_AP_number; j++) transmitter[j]->printme();

    both_sides_connect(transmitter,receiver);

    std::cout<<"UE nodes"<<std::endl;
    for(int i=0; i<g_UE_number; i++) receiver[i]->printme();
    std::cout<<std::endl<<"AP nodes"<<std::endl;
    for(int j=0; j<g_AP_number; j++) transmitter[j]->printme();

    return 0;
}
