#ifndef PID_H
#define PID_H
#include <vector>

class PID {
 public:
  /**
   * Constructor
   */
  PID();

  /**
   * Destructor.
   */
  virtual ~PID();

  /**
   * Initialize PID.
   * @param (Kp_, Ki_, Kd_) The initial PID coefficients
   */
  void Init(double Kp_, double Kd_, double Ki_);

  /**
   * Update the PID error variables given cross track error.
   * @param cte The current cross track error
   */
  void UpdateError(double cte);

  /**
   * Calculate the total PID error.s
   * @output The total PID error
   */
  double TotalError();


  double Twiddle(int n);

  int step;

  /**
   * PID Coefficients
   */ 
  double Kp;
  double Ki;
  double Kd;

  std::vector<double> p;


 private:

  //int step;
  std::vector<double> dp;

  

  double err;

  int n;

  int round;

  double best_err;

  /**
   * PID Errors
   */
  double p_error;
  double i_error;
  double d_error;

  //int n_evaluate_step;

  bool twiddle;

  int index;

  bool tried_adding;
  bool tried_subtracting;

};

#endif  // PID_H