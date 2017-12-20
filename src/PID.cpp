#include "PID.h"
#include <iostream>
using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
    
    // This should be the sum of the previously detected errors
    
    this->p_error = 0; // assume this is the proportional error, which means current time frame
    this->d_error = 0; // assume this is the last CTE , (d means difference)
    this->i_error = 0; // assume this is the total CTE, (i means integral -> sum)
    
    this->initialized = false;
    
    this->counter = 0; // the counter used for twiddle
    this->twiddle_counts = 0; // count how many times it has twiddled
    this->sum_cte = 0; // the cumulative CTE for one twiddle session
    this->previous_sum_cte = -1;
    
    
    // twiddle configurations
    this->twiddle = true; // set to true if we want twiddle
    
    // the twiddle amount is defined manually
    this->Tp = Kp / 5;
    this->Ti = Ki / 50;
    this->Td = Kd / 10;
    this->twiddle_ratio = 1;
    
    this->previous_success = true;
    
}

void PID::UpdateError(double cte) {
    // record previous values
    double pp = p_error;
    double pd = d_error;
    
    // add current CTE to the total error
    i_error += cte;
    
    if(this->initialized){
        // if it is not its first time receive data, difference will be calculated
        d_error = cte - p_error;
    }
    else{
        // if this is the first time it receives data, difference will be 0
        d_error = 0;
        initialized = true;
    }
    
    // update P error for steering angle prediction and next iteration
    p_error = cte;
    
    counter += 1;
    sum_cte += cte;
    
    // if twiddle is disabled, nothing need to be run further
    if(!twiddle){
        return;
    }
    
    // if it has run for 50 timesteps, initiate one twiddle procedure
    if(counter >= 50){
        counter = 0;
        // twiddle_counts += 1; // uncomment this line to twiddle all 3 parameters
        // actual twiddle process
        if(previous_sum_cte != -1){
            // set the twiddle ratio
            // if the twiddle is effective
            if(sum_cte <= previous_sum_cte){
                if(previous_success)
                    twiddle_ratio *= 1.1;
                previous_success = true;
            }
            // if the twiddle is detrimental
            else{
                // try to reverse the direction of twiddle first
                if(previous_success)
                    twiddle_ratio *= -2;
                // if still fails, reverse the direction again and decrease the ratio of twiddle
                // -0.45 = -0.5 (cancel the previous -2) * 0.9
                else
                    twiddle_ratio *= -0.45;
                previous_success = false;
            }
            
            // actual twiddling
            // twiddle P first
            if(twiddle_counts % 3 == 0){
                Kp += Tp * twiddle_ratio;
            }
            // then twiddle I
            else if(twiddle_counts % 3 == 1){
                Ki += Ti * twiddle_ratio;
            }
            // finally, twiddle D
            else{
                Kd += Td * twiddle_ratio;
                
            }
        
        }
        previous_sum_cte = sum_cte;
        sum_cte = 0;
    
        cout << "Kp:" << Kp << endl;
        cout << "Ki:" << Ki << endl;
        cout << "Kd:" << Kd << endl;
        
    }
    
    
 
}

// Use total error to compute steering angle and speed
double PID::TotalError() {
    
    double steer = -this->Kp * this->p_error - this->Kd * this->d_error - this->Ki * this->i_error;
    return steer;
}

