#include <iostream>
#include <stdio.h>
#include <cmath>

using namespace std;
# define G  9.81  // Gravity Vector in m/s^2
# define D 10    // Maximum Terrain clearance in m 
# define t_pilot 8 // It is the time taken by the Pilot for deciding a safe manevour, considering it 8 seconds for now.

int main(){
//-------------------------------------------------------------------------------------
//---------------------------LAD-Calculation-------------------------------------------
//--------------------Initialization of the data---------------------------------------

float Vned_h = 50;  // The Velocity vector component in the N-E plane
float phi_esc;      // This is the bank angle at the time of escaping or manevour to avoid terrain
// We generally get the data from the available sensor modules, but here lets take user input for the same
float A = Vned_h * (float)t_pilot ;           // It is the max distance that the Airborne travels while the pilot makes some decision
cout<<"----------------------------------------------------------------------------------------------------------------------------------"<<endl;
cout<<"Enter the Value of Bank angle for escape : ";
cin>>phi_esc;
float R = pow(Vned_h,2)/(G*phi_esc);
float LAD = A +2*R + D ; 
cout<<"The look ahead distance, LAD for velocity component in N-E plane = "<<Vned_h<<", Km/s and bank angle "<<phi_esc<<" radians is : "<<LAD<<" meters."<<endl;
cout<<"----------------------------------------------------------------------------------------------------------------------------------"<<endl;
    
return 0;

}
