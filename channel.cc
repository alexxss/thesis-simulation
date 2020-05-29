#ifndef CHANNEL
#include "channel.h"
#endif
#ifndef ENVIRONMENT
#include "global_environment.h"
#endif // ENVIRONMENT

#include<math.h> // for math stuff..

double calculate_one_channel(node* nodeAP, node* nodeUE){
    const double alpha = log(2)/log(cos(g_PHI_half));
    const double pi = 3.14159265359;
    return 0.1;
}

void calculate_all_channel(node* transmitter[g_AP_number], node* receiver[g_UE_number], double (&channel)[g_AP_number][g_UE_number]){
    for(int i=0; i<g_AP_number;i++){
        for(int j=0; j<g_UE_number;j++){
            channel[i][j]=calculate_one_channel(transmitter[i],receiver[j]);
        }
    }
}

