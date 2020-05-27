/*#ifndef NODE
#include "node.h"
#define NODE
#endif // NODE
#ifndef UE_number
#define UE_number 10
#endif // UE_number
*/
#include "clustering.h"

void UE_send_requests(node* transmitter[], node* receiver[], const double channel[][UE_number],const int UE_numbe, const int AP_number, const double channel_threshold){
    for(int i=0;i<UE_number;i++){
        // check all APs, if channel > threshold send request
        for(int j=0; j<AP_number; j++){
            if (channel[j][i]>channel_threshold)
                transmitter[j]->receiveRequest(i);
        }
    }
}

void AP_send_requests();

void both_sides_connect(node* transmitter[], node* receiver[],const int UE_numbe, const int AP_number){
    for(int i=0;i<AP_number;i++){
        for(int j=0; j<UE_number; j++){
            if (transmitter[i]->hasRequest(j) && receiver[j]->hasRequest(i)){
                transmitter[i]->connect(j);
                receiver[j]->connect(i);
            }
        }
    }
}
