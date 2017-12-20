#ifndef PID_H
#define PID_H

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;
    
    
    int counter;
    double sum_cte;
    double previous_sum_cte;
    
    /*
     *  Twiddle Coefficients
     */
    double Tp;
    double Ti;
    double Td;
    double twiddle_ratio;
    int twiddle_counts;
    bool previous_success;
    
  bool initialized;
    bool twiddle;
    

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();
};

#endif /* PID_H */
