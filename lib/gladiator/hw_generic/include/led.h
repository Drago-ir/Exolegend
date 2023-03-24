#ifndef LED_H
#define LED_H
#include <Arduino.h>
namespace hal {
  typedef struct{
      uint8_t pin;
      uint8_t pwm;
      bool blink;
      int blinkPeriod;
      unsigned long int blinkTime;
      bool off;
    } LedConf;
  class Led {
    public:
      Led(uint8_t red, uint8_t green, uint8_t blue);
      void setup();
      void registerMode();
      void standbyMode();
      void playModeAlive(uint8_t team);
      void playModeKilled();
      void playModeDisconnected();
      void pauseMode();
      void withoutArenaMode();
      
    private:
      void setupLed(LedConf* led);
      void blinkLed(LedConf* led,int period, uint8_t pwm);
      void simpleLed(LedConf* led, uint8_t pwm);
      void InitLed(LedConf* led, uint8_t pin);
      LedConf red, blue, green;
    
  };
}
#endif
