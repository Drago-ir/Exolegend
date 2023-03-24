#ifndef CLOCK_H
#define CLOCK_H
#include <Arduino.h>

class Clock {
  public:
    Clock();
    void synchronize (long long newStamp);
    void synchronize(long long newStamp, long time);
    long getDt(long long stamp);
    long long getStamp();
    
   private:
    long long gameStamp = 0;
    long robotStamp = 0;

};



#endif
