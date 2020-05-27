#ifndef NODE
#include "node.h"
#define NODE
#endif // NODE
#ifndef UE_number
#define UE_number 10
#endif // UE_number

void UE_send_requests(node*[], node*[], const double[][UE_number],const int, const int, const double);
void AP_send_requests();
void both_sides_connect(node*[], node*[],const int, const int);
