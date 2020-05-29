#define CHANNEL

#ifndef ENVIRONMENT
#include "global_environment.h"
#endif // ENVIRONMENT
#ifndef NODE
#include "node.h"
#endif // NODE

/**
* \brief calculates channel between an AP and a UE
*/
double calculate_one_channel(node* nodeAP, node* nodeUE);

void calculate_all_channel(node* transmitter[g_AP_number], node* receiver[g_UE_number], double (& channel)[g_AP_number][g_UE_number]);
