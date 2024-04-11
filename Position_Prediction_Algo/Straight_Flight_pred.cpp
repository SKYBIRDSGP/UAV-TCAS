#include <iostream>
#include <stdio.h>
#include <cmath>

using namespace std;
# define R_earth 6378000    // Radius of earth in meters along the equator
# define G = 9.81           // Gravity vector in m/s^2
# define phi_ac 3.14/3          // Latitude in radians
# define lambda_ac 3.14/6       // Longitude in radians
# define h_ac 5000              // ALtitude in meters 

int main(){
    //---------------------------INITIALIZATIONS-------------------------------------------
    float Vned_h = 500;   // The component of velocity vector in the N-E plane in m/s
    float Tt = 3.14/3;    // The true track angle in radians
    float t_pred = 10;    // The Look ahead time, assumed to be 10 seconds for now.
    float dt_pred = 0.8;  // Sample time considered to be 0.8 seconds for now.
    float phi_pred;       // The predicted value of phi(Latitude in radians) after an step.
    float lambda_pred;    // The predicted value of lambda(Longitude in radians) after an step.
    //---------------------------CALCULATIONS----------------------------------------------
    float N = t_pred/dt_pred ;
    float d_step = (dt_pred*Vned_h)/(R_earth+h_ac);
    //---------------------------THE_POSITION_PREDICTION-----------------------------------
    //-------------------CALCULATING THE POSITIONS FOR NEXT 30 STEPS-----------------------
    for(int i=0; i<30; i++){
        phi_pred = phi_ac + asin( sin(phi_ac)*cos(i*d_step)+(cos(phi_ac)*sin(i*d_step)*cos(Tt)));
        lambda_pred = lambda_ac + atan(sin(Tt)*sin(i*d_step)*cos(phi_ac)/(cos(i*d_step)-sin(phi_ac)*sin(phi_pred)));
        cout<<"---------------------------------------------------------------------------------"<<endl;
        cout<<"The value of Latitude(phi_pred) for the step : "<<i+1<<" is : "<<phi_pred<<" radians."<<endl;
        cout<<"The value of Longitude(lambda_pred) for the step : "<<i+1<<" is : "<<lambda_pred<<" radians. "<<endl;
        cout<<"---------------------------------------------------------------------------------"<<endl;

    }

    return 0;
}