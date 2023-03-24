
#ifndef DATA_UTILS_H
#define DATA_UTILS_H

#include <Arduino.h>
#include "const.h"
#include "user_utils.h"


enum GpioPin {
    _M1, _M2, _M3, _AUTO_KILL
};
enum GpioMode {
    _DIGITAL_OUTPUT,
    _DIGITAL_INPUT,
    _PWM_OUTPUT,
    _SERVO,
    _UNUSED,
};


struct FieldCom {
  char type;
  uint8_t field[MODULES_LEN][MODULES_LEN];
};

 struct GeneralCom{
  char type;
  void* data;
};

 struct RobotComData  {
  Position position;
  float speedLimit;
  short score;
  uint8_t lifes, id;
  uint8_t macAddress[6];
  bool stamped, remote;
  uint8_t teamId;
};

 struct RobotsCom{
  char type;
  RobotComData robots[4];
  long long stamp;
};

 struct MessageCom{
  char type;
  unsigned char message[200];
};

 struct RegisterCom{
  char type {};
  long long stamp {};
  uint8_t macAddress[6] = {0,0,0,0,0,0};
  Position beginPosition {};
};

struct RemoteCom{
  char type;
  float speed, vl, vr;
  uint8_t direction;
  bool reset;
};



 struct RegisterResponse {
  char type;
  uint8_t macAddress[6];
  char key[30];
  uint8_t id;
};

 struct Withholding {
  bool value;
  long stamp;

};

 struct MazeData {
  uint8_t modules[MODULES_LEN][MODULES_LEN];
};

struct TrackData {
  char type;
  MazeData maze;

  Position position;
  uint32_t positionStamp;

  float vl, vr, vl_c, vr_c;
  uint32_t speedStamp;

  float traj_x, traj_y;
  uint32_t trajStamp;
  
};



 struct TrackMsg {
  char type;
  char message[100];
  
  
};


#endif
