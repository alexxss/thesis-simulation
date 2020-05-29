#ifndef CHANNEL
#include "channel.h"
#endif
#ifndef ENVIRONMENT
#include "global_environment.h"
#endif // ENVIRONMENT

#define PI 3.14159265359

#include<math.h> // for math stuff..

double RtoD(const double& radian){
    return radian * 180 / PI;
}

double DtoR(const double& degree){
    return degree * PI / 180;
}

double get_angle_of_incidence(node* nodeAP, node* nodeUE){
    const double height_diff = g_AP_height - g_UE_height;
    const double plane_dist = nodeAP->plane_distance(nodeUE);
    const double hypotenuse = nodeAP->euclidean_distance(nodeUE);

    // angle of incidence = angle between <height diff> and <hypotenuse>
    const double angle = acos((pow(height_diff,2) + pow(hypotenuse,2) - pow(plane_dist,2)) / (2*height_diff*hypotenuse));
    return angle;
}

double calculate_one_channel(node* nodeAP, node* nodeUE){
    const double angle_of_incidence = get_angle_of_incidence(nodeAP,nodeUE); // IMPORTANT: this is in RADIAN
    // no channel if exceeds FOV
    if (RtoD(angle_of_incidence)>=(g_field_of_view/2))
        return 0.0;

    const double alpha = abs(log(2)/log(cos(DtoR(g_PHI_half))));
    const double angle_of_irradiance = angle_of_incidence;// TODO (alex#2#): maybe need to change?
    double ch = (alpha + 1) * g_receiver_area / (2 * PI * pow(nodeAP->euclidean_distance(nodeUE),2)); // first term
    ch = ch * pow(cos(angle_of_irradiance),alpha);// second term
    ch = ch * g_filter_gain * g_concentrator_gain; // third and fourth term
    ch = ch * cos(angle_of_incidence);
    return ch;
}

void calculate_all_channel(node* transmitter[g_AP_number], node* receiver[g_UE_number], double (&channel)[g_AP_number][g_UE_number]){
    for(int i=0; i<g_AP_number;i++){
        for(int j=0; j<g_UE_number;j++){
            channel[i][j]=calculate_one_channel(transmitter[i],receiver[j]);
        }
    }
}

