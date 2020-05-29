#define ENVIRONMENT

/*---------------------------------------------------
                ENVIRONMENT CONSTANTS
room size 15*15*3
+ AP
  - number 8*8=64
  - height 2.5m
+ UE
  - number 10-70 step 10
  - height 0.85m
---------------------------------------------------*/
constexpr double g_room_dim = 15;
constexpr double g_AP_height = 2.5;
constexpr double g_UE_height = 0.85;

constexpr int g_UE_number = 10; // range 10-70 step 10
constexpr int g_AP_number = 64; // should be 8*8=64
constexpr int g_AP_per_row = 8;

constexpr double g_channel_threshold = 0.000001;
constexpr double g_distance_threshold = 5.0;

/*---------------------------------------------------
                CHANNEL CONSTANTS
FOV range 70-130 step 10
semi-angle at half-illumination (phi_1/2) 60
gain of optical filter (g_of(psi))         1
gain of optical concentrator (g_oc(psi))   1
physical area for PD receiver              1   cm^2
reflection efficiency (rho)                0.75
---------------------------------------------------*/
constexpr double g_field_of_view = 70;
constexpr int g_PHI_half = 60;
constexpr int g_filter_gain = 1;
constexpr int g_concentrator_gain = 1;
constexpr int g_receiver_area = 1;
constexpr double g_reflect_efficiency = 0.75;
