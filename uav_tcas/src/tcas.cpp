/*  
    Author: Sagar Chotalia
    email: sagarchotalia2@gmail.com
*/

#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<vector>
#include<math.h>
using namespace std;
#define R_EARTH 6378137 // Radius of Earth in metres
void straight_flight_predict(float, float, float);
void turning_flight_predict(float, float, float, float);
void search_volume_predict(int);
float dist_to_latlong();
float latlong_to_dist();

//------------------------------------------------------------
// latitude (ϕ), longitude (λ) and altitude (h). The latitude and longitude together define the horizontal position.
double phi_ac = 50, lambda_ac = 50;
// -----------------------------------------------------------
vector<float, float> departure_search_width;
float phi_c = 0;
float dx[100];
vector<float> phi_pred, lambda_pred;
// taking one sample time to be 0.01 seconds
// t_t is the True Track angle, given by TT = arctan(ve/vn), where ve and vn are the aircraft's velocities in the East and North directions resp.
// The true track expresses the direction of the velocity vector with respect to the true (not the magnetic) north direction.
const float del_t_pred = 1, t_t = phi_c;

void straight_flight_predict(const float t_pred, float horizontal_vel, float altitude){
    //t_pred = Look ahead time
    int N = t_pred/del_t_pred;
    int phi_ac=0.5, lambda_ac=30;
    float d_step = del_t_pred*horizontal_vel/(R_EARTH + altitude);
    //initialising the aircraft positions
    phi_pred.push_back(0);
    lambda_pred.push_back(0);
    for(int i=1; i<N; i++){
        //position update for straight flight
        phi_pred.push_back(
            phi_ac + asin(sin(phi_ac)*cos(i*d_step) + cos(phi_ac)*sin(i*d_step)*cos(t_t))
        );
        lambda_pred.push_back(
            lambda_ac + atan(sin(t_t)*sin(i*d_step)*cos(phi_ac)/(cos(i*d_step)-sin(phi_ac)*sin(phi_pred.back())))
        );
    }
    std::cout<<"phi_pred elements:";
    for(const auto& element : phi_pred){
        std::cout<< element<<" ";
        std::cout<<endl;
    }
    std::cout<<"lambda_pred elements:";
    for(const auto& element : lambda_pred){
        std::cout<< element<<" ";
        std::cout<<endl;
    }   
}

//delta_phi->aircraft's yaw rate
void turning_flight_predict(const float t_pred, float delta_phi, float horizontal_vel, float altitude){
    float phi_pred0 = phi_ac, lambda_pred0 = lambda_ac, phi_c = t_t;
    int N = t_pred/del_t_pred;
    vector<float> phi_pred, lambda_pred;
    float alpha; //alpha->centre angle
    float x[2] = {0, 0}; // to store the position vector of the curved path, containing x_n and x_e --> North and East position vector of the aircraft respectively
    int i = 0;
    phi_pred.clear();
    lambda_pred.clear(); // clear out any pre-existing data for now
    phi_pred.push_back(0); // initialize
    lambda_pred.push_back(0);

    for(int i=1; i<N; i++){
        alpha = phi_c - M_PI/2;
        phi_c = phi_c + delta_phi*del_t_pred;

        dx[0] = (horizontal_vel*(-sin(alpha))*del_t_pred) - 0.5*horizontal_vel*delta_phi*cos(alpha)*del_t_pred*del_t_pred; // dx[0] is 'dn'
        dx[1] = (horizontal_vel*(-cos(alpha))*del_t_pred) - 0.5*horizontal_vel*delta_phi*sin(alpha)*del_t_pred*del_t_pred; //dx[1] is 'de'
        float dist_dx = pow(dx[0]*dx[0] + dx[1]*dx[1], 0.5);

        //new predicted position
        float a = dist_dx/(R_EARTH + altitude);
        float b = atan(dx[1]/dx[0]);

        // if(i>0 && i<51){
        phi_pred.push_back(phi_pred[i-1]+asin(phi_pred[i-1]*cos(a) + cos(phi_pred[i-1])*sin(a)*cos(b)));
        lambda_pred.push_back(lambda_pred[i-1]+atan((sin(b)*sin(a)*cos(phi_pred[i-1]))/(cos(a)-sin(phi_pred[i-1]*sin(phi_pred[i])))));
        // }
        // else{
            // phi_pred.erase(phi_pred.begin());
        // }
        std::cout<<phi_pred.back()<<" "<<lambda_pred.back()<<" "<<a<<" "<<b<<endl;
    }
}
// The search volume consists of a computed look ahead distance(LAD), a lateral
// distance on both sides of the airplane’s ight path, and a specified look down
// distance based upon the airplane’s vertical flight path. Search volume
// should vary as a function of: phase of flight, distance from runway,
// required obstacle clearance (ROC).
void search_volume_predict(int flight_phase, float  ){

    // nautical miles = metres*1852
    //Flightphase           Basic Across Track Width        in metres
    // Departure            0.50 NM                         926
    // Enroute              0.75 NM                         1389
    // Approach             0.25 NM                         463
    
    // Figure out the lead angle calculations
    if(flight_phase == 1){
        // The departure phase is dened from power-up of the system until the aircraft 
        // reaches 1500 ft above the departure runway (which is the nearest runway)
        // the protection area begins at the Departure End of Runway (DER) with a total width of
        // 300 m (0.16 NM) centered around the runway center line. It then splays at an angle
        // of 15◦ on each side. This would give a total width of approx. 2.8 NM after 5 NM
        departure_search_width.push_back(phi_ac);
    
    }
    else if(flight_phase == 2){
        // The enroute phase is dened as when the aircraft is more than 15 NM away from the
        // nearest runway or whenever the conditions for the other phases are not met.
    }



}
// This function converts a distance from a particular point to latitude, longitude and altitude measurements.
// Important for calculating the search volume distances as the aircraft moves in real-time. Depends on aircraft headin directiong.
float dist_to_latlong(double latitude, double longitude, float altitude, double required_distance, float heading){

    float desired_directions[2] = {heading+90, heading-90}; // Finding out the two directions perpendicular from the aircraft heading



}

float latlong_to_dist(){}

int main(int argc, char** argv){

    // ros::init(argc, argv, "tcas");
    // ros::NodeHandle node_handle;
    // ros::Publisher publisher = node_handle.advertise<std_msgs::String>("tcas_topic", 10);
    // while(ros::ok()){

    // }
    straight_flight_predict(30,100,10000);
    // turning_flight_predict(100,20, 2000, 10000);

    return 0;
}
