#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<vector>
#include<math.h>
#include<ctime>
#include"config.h"

using namespace std;

int main(){
    //------------------ a_β_filter_algorithm--------------------------------------------------
    // STEP0 : Initialization
    float x_est_prev = 0;       // Previous estimated Velocity
    float x_est_curr = 0;       // Current estimated Velocity
    float x_pred = 0;      // Predicted Position
    float v_est_prev = 0;       // Previous Estimated Velocity
    float v_est_curr = 0;       // Current Estimated Velocity
    float v_pred = 0;
    float x_mes = 50 ;
    float dT = 2;
    float r ;
    int i = 1;

    while(i <=30 ){
        // STEP1 : State Prediction
        x_pred = x_est_prev + dT*v_est_prev ;
        v_pred = v_est_prev ;
        // STEP2 : Calculation of a Residual position
        r = x_mes - x_pred;
        // STEP3: Measurement update (correction):
        x_est_curr = x_pred + a*r;
        v_est_curr = v_pred + β*r/dT ;
        cout<<"-------------------------------------------------------------"<<endl;
        cout<<"The predicted position in the next "<< dT*i<<" seconds is : "<<x_mes+x_pred<<endl;
        cout<<"The estimated position in the next "<< dT*i<<" seconds is : "<<x_mes+x_est_curr<<endl;
        cout<<"The estimated velocity in the next "<< dT*i<<" seconds is : "<<v_est_curr<<endl;

        x_est_prev = x_est_curr;
        v_est_prev = v_est_curr;

        i ++;
    }
    
    
}

