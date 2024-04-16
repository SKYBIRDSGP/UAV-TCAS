 #include <iostream>

float G = 9.81;           //Gravity Vector in m/s^2

float R_earth = 6378000;  //Radius of the Earth in meters

float t_pred = 10;        // The Look ahead time, assumed to be 10 seconds for now.

int t_pilot = 8;          // It is the time taken by the Pilot for deciding a safe manevour, considering it 8 seconds for now.

const float a = 0.08;

const float β = 0.002;

float D = 10;             // Maximum Terrain Clearance distance in meters
