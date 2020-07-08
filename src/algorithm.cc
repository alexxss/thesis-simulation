#include "algorithm.h"
#include <chrono> // for time taken & rand seed
#include <random> // uniform_real_distribution
#include <fstream>
#include <iostream>

void save_throughputUE(){
    /*--------------save to file for plot------------------
     columns: <x> <y> <throughput>
     run in cmd: `gnuplot -p          .gnu` to view plot
    -------------------------------------------------------*/
    std::ofstream fout("UE_throughput.dat");
    if (fout.is_open()){
        for(node* n : node::receiver){
            if (!n) break;
              fout<<n->location.first<<' '<<n->location.second<<' '<<n->sum_throughput<<'\n';
        }
        fout.close();
    } else std::cout<<"Can\'t open UE_throughput.dat :\(\n";
}

void save_idleNode(){
    /*--------------save to file for plot------------------
     columns: <x> <y>
     run in cmd: `gnuplot -p plot_pairWithOutage.gnu` to view plot
    -------------------------------------------------------*/
    std::ofstream fout("UE_off.dat");
    if (fout.is_open()){
        for(node* n : node::receiver)
            if (!n) break;
            else if (n->get_connected().size()==0)
                fout<<n->location.first<<' '<<n->location.second<<'\n';
        fout.close();
    } else std::cout<<"Can\'t open UE_off.dat :\(\n";

    fout.open("AP_off.dat");
    if (fout.is_open()){
        for(node* n : node::transmitter){
            if (n->get_connected().size()==0)
                fout<<n->location.first<<' '<<n->location.second<<'\n';
        }
        fout.close();
    } else std::cout<<"Can\'t open AP_off.dat :\(\n";
}

void save_finalClusterRelationship(){
    /*--------------save to file for plot------------------
    repeats following output for every line segment
       <AP x> <AP y>
       <UE x> <UE y>
       <empty line>
     run in cmd: `gnuplot -p plot_pairWithOutage.gnu` to view plot
    -------------------------------------------------------*/
    std::ofstream fout("AP_UE_pairFinal.dat");
    if (fout.is_open()){
        for(node* AP : node::transmitter){
            for(int UEid : AP->get_connected()){
                fout<<AP->location.first<<' '<<AP->location.second<<'\n';
                node* UE = node::receiver[UEid];
                fout<<UE->location.first<<' '<<UE->location.second<<"\n\n";
            }
        }
        fout.close();
    } else std::cout<<"Can\'t open AP_UE_pairFinal.dat :\(\n";
}

/**
\brief saves UE & AP location to file for plot
\param receiver array
\param transmitter array
*/
void save_room_data(){
    /*--------------save to file for plot------------------
     columns: <node id> <x> <y>
     run in cmd: `gnuplot -p plot_room.gnu` to view plot
    -------------------------------------------------------*/
    std::ofstream fout("UE_point.dat");
    if(fout.is_open()){
        for(int i=0;i<node::UE_number;i++)
            fout<<i<<' '<<node::receiver[i]->location.first<<' '<<node::receiver[i]->location.second<<'\n';
        fout.close();
    }
    fout.open("AP_point.dat");
    if(fout.is_open()){
        for(int i=0;i<g_AP_number;i++){
            fout<<i<<' '<<node::transmitter[i]->location.first<<' '<<node::transmitter[i]->location.second<<'\n';
        }
        fout.close();
    }

}

void algorithm::fullAlgorithm(){

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    /*-------------initialization----------------*/

    // generate AP node
    for (int i=0; i<g_AP_number; i++){
        node::transmitter[i] = new node(i);
    }
    // generate UE node
    std::uniform_real_distribution<double> unif(0.0, g_room_dim);
    std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
    for (int i=0; i<node::UE_number; i++){
        node::receiver[i] = new node(i,unif(re), unif(re)); // UE
    }

    /*--------------save to file for plot------------------
     run in cmd: `gnuplot -p plot_room.gnu` to view plot
    -------------------------------------------------------*/
    save_room_data();

    /*-----------calculate channel---------------*/
//    double channel[g_AP_number][g_UE_number];
    calculate_all_channel();

    std::cout<<"-----------------CLUSTERING------------------\n";
    /*---- for each UE, send request to APs if channel > threshold ----*/
    std::cout<<"1. UE->AP (channel threshold="<<g_channel_threshold<<")\n";
    for(int i=0;i<node::UE_number;i++){
        // check all APs, if channel > threshold send request
        for(int j=0; j<g_AP_number; j++){
            if (node::channel[j][i]>g_channel_threshold)
                node::transmitter[j]->receiveRequest(i);
        }
    }

    /*---- for each AP, send request to UEs if distance < threshold ----*/
    std::cout<<"2. UE<-AP (distance threshold="<<g_distance_threshold<<")\n";
    for(int i=0; i<g_AP_number; i++){
        // check all UEs, if distance<threshold send request
        for(int j=0; j<node::UE_number; j++){
            if (node::transmitter[i]->euclidean_distance(node::receiver[j])<g_distance_threshold)
                node::receiver[j]->receiveRequest(i);
        }
    }
/*
    cout<<"UE nodes"<<'\n';
    for(int i=0; i<g_UE_number; i++) receiver[i]->printme(0);
    std::cout<<'\n'<<"AP nodes"<<'\n';
    for(int j=0; j<g_AP_number; j++) transmitter[j]->printme(0);
*/
    std::cout<<"3. Confirmation\n";
    both_sides_connect();
/*
    std::cout<<"UE nodes"<<std::endl;
    for(int i=0; i<g_UE_number; i++) receiver[i]->printme(1);
    std::cout<<std::endl<<"AP nodes"<<std::endl;
    for(int j=0; j<g_AP_number; j++) transmitter[j]->printme(1);
*/
    for(node* n : node::transmitter){
        n->NOMA_sort_UE_desc();
    }

    std::cout<<"---------------FREQUENCY REUSE---------------\n";
    frequency_reuse(node::transmitter);

    std::cout<<"-------------------TDMA----------------------\n";
    for(node* n : node::transmitter){
        n->tdma();
    }

    save_idleNode();
    save_finalClusterRelationship();
    save_throughputUE();

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout<<"\nResource Allocation complete. Total time taken = "
             << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms = "
             << (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()/60000 << "min\n";
    double sum_throughput = 0.0;
    for(node* n : node::receiver) if (!n) break; else sum_throughput += n->sum_throughput;
    std::cout<<"System sum throughput = "<<sum_throughput<<"Mbps\n";

    return;
}
