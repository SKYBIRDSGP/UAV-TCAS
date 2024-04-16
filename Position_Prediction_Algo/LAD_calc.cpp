#include <iostream>
#include <stdio.h>
#include <cmath>

using namespace std;
# define G  9.81  // Gravity Vector in m/s^2
# define D 10    // Maximum Terrain clearance in m 
# define t_pilot 8 // It is the time taken by the Pilot for deciding a safe manevour, considering it 8 seconds for now.
# define phi_esc 30

int main(){
//-------------------------------------------------------------------------------------
//---------------------------LAD-Calculation-------------------------------------------
//--------------------Initialization of the data---------------------------------------

float Vned_h = 50;  // The Velocity vector component in the N-E plane

// We generally get the data from the available sensor modules, but here lets take user input for the same
float A = Vned_h * (float)t_pilot ;           // It is the max distance that the Airborne travels while the pilot makes some decision
cout<<"----------------------------------------------------------------------------------------------------------------------------------"<<endl;
float R = pow(Vned_h,2)/(G*tan(phi_esc*3.14/180));
float LAD = A +2*R + D ; 
cout<<"The look ahead distance, LAD for velocity component in N-E plane = "<<Vned_h<<" m/s, and bank angle "<<phi_esc<<" degrees is : "<<LAD<<" meters."<<endl;
cout<<"----------------------------------------------------------------------------------------------------------------------------------"<<endl;
    
return 0;

}
