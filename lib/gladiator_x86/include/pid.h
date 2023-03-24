#ifndef PID_H
#define PID_H
/*
 * pid.h
 *
 *  Created on: May 16, 2021
 *      Author: shado
 */

#include <Arduino.h>



class pid {
public:
  pid();
  float getKi(){return Ki;}
  void setKi(float Ki){this->Ki = Ki;}

  float getKd(){return Kd;}
  void setKd(float Kd){this->Kd = Kd;}

  float getKp(){return Kp;}
  void setKp(float Kp){this->Kp = Kp;}

  float getConsign(float Err);
  void reset();
private:
  float Ki, Kp, Kd;
  double integral;
  float last_error;
  long lastTime;
};

#endif /* PID_H_ */
