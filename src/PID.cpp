#include "PID.h"

#include <iostream>
#include <numeric>
#include <vector>
#include <cmath>



/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_,  double Kd_, double Ki_) {
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
  Kp = Kp_;
  Ki = Ki_;
  Kd = Kd_;

  p_error = i_error = d_error = 0.0;

  twiddle = true;

  err = 0.0;

  step = 1;

  // the step to ajust and evaluate total error
  //about bit more than 1 cycle
  n = 1600; 

  best_err = 10000000000000;

  p = {Kp, Kd, Ki};

  dp = {0.1*Kp, 0.1*Kd, 0.1*Ki};

  index = 2; // (2+1)%3 = 0, will start ajust param with p[0]

}

void PID::UpdateError(double cte) {
  /**
   * TODO: Update PID errors based on cte.
   */
  if (step == 1){
    p_error =  cte; //take care of the first step, to calaculate d_error
  }

  d_error = cte - p_error;
  p_error = cte;
  i_error += cte;

  // the first n step for ajust, the sencond n step for evaluate error.
  if( step % (2*n) > n){
    err += pow(cte, 2);
  }

  // twiddle process
  double sum_dp = dp[0] + dp[1] + dp[2];

  // each small cycle includes: first n step to adjust cte, sencond n step to evaluate error
  // when each small cycle finished, compare the error to best error, and twiddle parameters. 
  if(twiddle && sum_dp > 0.0001 && step%(2*n) == 0 ){

    if (err < best_err){
      best_err = err;
      dp[index] *= 1.1;
      index = (index+1)%3;
      tried_adding = tried_subtracting = false;
    }

    if (!tried_adding && !tried_subtracting){
      p[index] += dp[index];
      tried_adding= true;
    }

    else if (tried_adding && !tried_subtracting){
      p[index] -= 2*dp[index];
      tried_subtracting = true;
    }

    else{

      p[index] += dp[index];
      dp[index] *= 0.9;
      index = (index + 1)% 3;
      tried_subtracting =  tried_adding = false;
    }

    err = 0;
  }

  step++;
  
}

double PID::TotalError( ) {
  /**
   * TODO: Calculate and return the total error
   */
  return -p[0]*p_error - p[1]*d_error - p[2]*i_error;  // TODO: Add your total error calc here!
}