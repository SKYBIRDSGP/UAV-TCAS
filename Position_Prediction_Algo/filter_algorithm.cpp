#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<vector>
#include<math.h>
#include<ctime>

using namespace std;
float x_pred, x_est;
const float a = 0.08;
const float β = 0.002;

int main(){
    //------------------ a_β_filter_algorithm--------------------------------------------------
    // STEP0 : Initialization
    float x_est;      // Estimated Position
    float x_pred = 0;  // Predicted Position
    float v_prev = 0.0 ;
    float v_curr = 0.0 ;
    float x_mes = 50 ;
    float dT = 2;
    float r ;
    float x = 10;

    while(1){
        // STEP1 : State Prediction
        v_curr = v_prev ;
        x_pred = x_est + dT*v_prev ;
        // STEP2 : Calculation of a Residual position
        r = x - x_pred;
        // STEP3: Measurement update (correction):
        x_est = x_pred + a *r;
        v_curr = v_prev + β*r/dT ;
        cout<<"-------------------------------------------------------------"<<endl;
        cout<<"The predicted position in the next 2 seconds is : "<<x_pred<<endl;
        cout<<"The estimated position in the next 2 seconds is : "<<x_est<<endl;


    }
    
    
}

