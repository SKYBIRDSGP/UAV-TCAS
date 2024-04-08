#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<vector>
#include<math.h>
#include<ctime>
#include <unistd.h> 

using namespace std;
float x_pred, x_est;
const float α = 0.08;
const float β = 0.002;

int main(){
    //------------------ α_β_filter_algorithm--------------------------------------------------
    // STEP0 : Initialization
    float x̂;      // Estimated Position
    float x̃ = 0;  // Predicted Position
    float v̂_prev = 0.0 ;
    float v̂_curr = 0.0 ;
    float x_mes = 50 ;
    float dT = 0.2;
    float r̂ ;
    float x = 10;

    while(1){
        // STEP1 : State Prediction
        x̃ = x̂ + dT*v̂_prev ;
        v̂_curr = v̂_prev ;
        // STEP2 : Calculation of a Residual position
        r̂ = x - x̃;
        // STEP3: Measurement update (correction):
        x̂ = x̃ + α *r̂;
        v̂_curr = v̂_prev + β*r̂/dT ;
 
        cout<<"The predicted position in the next 0.2 seconds is : "<<x̃<<endl;
        cout<<"The estimated position in the next 0.2 seconds is : "<<x̂<<endl;


    }
    
    
}

