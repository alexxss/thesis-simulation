#define CHANNEL

#ifndef NODE
#include "node.h"
#endif // NODE

/**
* \brief calculates all the channel between every AP-UE pair
* \param transmitter
* \param receiver
* \param channel passed as reference
*/
void calculate_all_channel(node* transmitter[g_AP_number], node* receiver[g_UE_number], double (&channel)[g_AP_number][g_UE_number]);
