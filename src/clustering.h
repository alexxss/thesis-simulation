#define CLUSTERING

#ifndef NODE
#include "node.h"
#endif // NODE
#ifndef ENVIRONMENT
#include "global_environment.h"
#endif // ENVIRONMENT

/*

*/
void UE_send_requests(node*[], node*[], const double[][10],const int, const int, const double);
void AP_send_requests();
void both_sides_connect(node* transmitter[g_AP_number], node* receiver[g_UE_number]);
