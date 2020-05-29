#ifndef CLUSTERING
#include "clustering.h"
#endif // CLUSTERING
#ifndef ENVIRONMENT
#include "global_environment.h"
#endif // ENVIRONMENT

#include<iostream>
#include<fstream> // file stream

void UE_send_requests(node* transmitter[], node* receiver[], const double channel[][g_UE_number],const int UE_numbe, const int g_AP_number, const double g_channel_threshold){
    for(int i=0;i<g_UE_number;i++){
        // check all APs, if channel > threshold send request
        for(int j=0; j<g_AP_number; j++){
            if (channel[j][i]>g_channel_threshold)
                transmitter[j]->receiveRequest(i);
        }
    }
}

void AP_send_requests();

void both_sides_connect(node* transmitter[g_AP_number], node* receiver[g_UE_number]){
    std::ofstream fout("AP_UE_pair.dat");
    if (fout.is_open()){
        for(int i=0;i<g_AP_number;i++){
            for(int j=0; j<g_UE_number; j++){
                if (transmitter[i]->hasRequest(j) && receiver[j]->hasRequest(i)){
                    transmitter[i]->connect(j);
                    receiver[j]->connect(i);

                    /*--------------save to file for plot------------------
                    repeats following output for every line segment (AP-centric)
                       <AP id> <x> <y>
                       <UE id> <x> <y>
                       <empty line>
                     run in cmd: `gnuplot -p plot_pair.gnu` to view plot
                    -------------------------------------------------------*/
                    fout<<transmitter[i]->location.first<<' '<<transmitter[i]->location.second<<std::endl;
                    fout<<receiver[j]->location.first<<' '<<receiver[j]->location.second<<std::endl<<std::endl;
                }
            }
        }
        fout.close();
    } else
        std::cout<<"Cant open file \"AP_UE_pair.dat\""<<std::endl;
}
