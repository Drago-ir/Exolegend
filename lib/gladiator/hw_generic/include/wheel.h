#ifndef WHEEL_H
#define WHEEL_H

#include <Arduino.h>
#include "const.h"
namespace hal {
  class Wheel {
    public:
      Wheel(uint8_t enc1, uint8_t enc2, uint8_t motDir1, uint8_t motDir2, uint8_t motSpeed, uint16_t tpr);
      void encTickInt();
      void setPower(double power);
      
      uint16_t counter = 0;
      uint16_t lastCounter = 0;
      uint16_t tpr;
      void goForward(uint16_t intPower);
      void goBackward(uint16_t intPower);
      double getWheelSpeed();
      double deadZoneCompensation(float power);
      double saturate(float power);

      double getSpeedLimit(){return speedLimit;};
      void setSpeedLimit(float value){speedLimit = value;};

      double getCons();
      void setCons(float value){cons = value;};
      
      uint8_t enc1, enc2, motDir1, motDir2, motSpeed;
    private:
      float speedLimit = 5; // 1m/s by default
      double cons = 0;
      long lastTime;
      long measureTime = 0;
      double estimatedSpeed = 0;
      
    
  };
}
#endif
