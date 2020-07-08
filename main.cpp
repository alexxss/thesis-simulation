#include "src/algorithm.h"

#include <iostream>
#include <stdlib.h> //rand
#include <random> //C++'s random
#include <fstream> //ofstream
#include <chrono> // record time

using namespace std;

/*          init node static member       */
int node::UE_number = 0;
node* node::transmitter[g_AP_number] = {0};
node* node::receiver[g_UE_max] = {0};
double node::channel[g_AP_number][g_UE_max] = {0};
/*          init algorithm static member */
int algorithm::UE_number = 0;
int main()
{
    node::UE_number = 40;
    algorithm::UE_number = node::UE_number;
    algorithm Algorithm;
    Algorithm.fullAlgorithm();
    return 0;
}
