#ifndef GAME_PARSER_H
#define GAME_PARSER_H

#include "data_utils.h"
#include "user_utils.h"
#include "fct_utils.h"
#include "clock.h"
#include "debug.h"
#include "com.h"
#include "kalman.h"
#include "memory.h"
#include "const.h"

//#include <ArduinoJson.h>

class GameParser {
  public:
    GameParser(String defaultMacAddress, Clock* clock, Com* com, Kalman* kalman, Debug* debug, Memory* memory);
    void resetRobots();
    void parse(uint8_t* data, uint8_t len);
    void parseRobots(RobotsCom rbts);
    /*void parseCoins(FieldCom coins);*/
    void parseModules(FieldCom modules);
    
    bool isWatchdogTriggered();
    bool isPositionWatchdogTriggered(float vl, float vr);
    void resetPositionWatchdog();
    bool isPositionWatchdogActive(){return positionWatchdogActive;};
    long getPositionWatchdogTime(){return positionWatchdogTime;};

    void resetLastStamp();
    
    bool canReceive(uint8_t* macAddress);
    void resetAntenna();
    void readFromMemory();
    void saveLastParsedTime();
    bool isAntennaActive(){return antennaActive;};
    void sendRegisterResponse();
    
    RobotData getDefaultRobot();
    void setRobotSpeed(double vl, double vr);
    void setRobotPosition(Position position);
    RobotData getRobotByIndex(uint8_t robotIndex);
    RobotData getRobotById(uint8_t id);
    MazeData getMazeData();
    MazeSquare getMazeSquare(uint8_t i, uint8_t j);
    void initSquare(MazeSquare* square);
    void initMazeSquares();
    
    char getGamePhase(){return (gamePhase);};
    RobotList getRobotList();

    bool canStart();



    
   private:
    Clock* clock;
    Kalman* kalman;
    Debug* debug;
    Memory* mem;
    Com* com;
    RobotData robots[4];
    MazeData maze;
    
    bool positionWatchdogActive = false;
    long positionWatchdogTime = 0;
    
    char gamePhase = 'S';
    RobotData defaultRobot{};
    bool antennaActive = false;
    uint8_t antennaMacAddress[6];
    bool isDefault(RobotData robot){return robot.macAddress == defaultRobot.macAddress;};
    long lastParseTime = 0;
    long lastStamp = 0;
    long playStarted = 0;
    MazeSquare mazeSquares[MODULES_LEN][MODULES_LEN];

    bool firstRobotsFrameReceived = false;
    bool firstModulesFrameReceived = false;
    
  
};

#endif
