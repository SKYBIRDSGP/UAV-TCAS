/*  Ground Terrain Collision Avoidance 
    things to do:
    1. understand DAIDALUS
    2. read other related papers and form a summary of sorts
    3. code the high-level functions first and sort out the lower-level details later

*/

#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<vector>
// #include<matplot/matplot.h>
// #include<ros/ros.h>
// #include<std_msgs>
#include<math.h>
using namespace std;
#define R_EARTH 6378137 // Radius of Earth in metres
void straight_flight_predict(float, float, float);
void turning_flight_predict(float, float, float, float);
void search_volume_predict();

//------------------------------------------------------------
// phi_ac and lambda_ac = aircraft position
double phi_ac = 50, lambda_ac = 50;
// -----------------------------------------------------------
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
        float a = dist_dx/(R_EARTH+altitude);
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
    //  std::cout<<"phi_pred elements:";
    // for(const auto& element : phi_pred){
    //     std::cout<< element<<" ";
    //     std::cout<<endl;
    // }
    // std::cout<<"lambda_pred elements:";
    // for(const auto& element : lambda_pred){
    //     std::cout<< element<<" ";
    //     std::cout<<endl;
    // } 
}

// void search_volume_predict(){

// }


int main(int argc, char** argv){

    // ros::init(argc, argv, "tcas");
    // ros::NodeHandle node_handle;
    // ros::Publisher publisher = node_handle.advertise<std_msgs::String>("tcas_topic", 10);
    // while(ros::ok()){

    // }
    // straight_flight_predict(30,100,10000);
    turning_flight_predict(100,20, 2000, 10000);

    return 0;
}
