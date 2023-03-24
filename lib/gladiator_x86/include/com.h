#ifndef _COM_H_
#define _COM_H_
#ifdef TARGET_ESP32
  #include <esp_now.h>
#endif

#include "WiFi.h"
#include "data_utils.h"
#include "user_utils.h"
#include "fct_utils.h"



  
  typedef struct ComMessage {
    uint8_t frameId;
    uint8_t frameSize;
    char frameContent[240];
  } ComMessage;

  class Com {
      public:
          Com();
          void initCom();
          void registerPeer(uint8_t address[]);
          void deletePeer(uint8_t address[]);
          void registerPeer(String address);
          void deletePeer(String address);
          void OnDataSent(void (*callBack)(const unsigned char*, esp_now_send_status_t));
          void OnDataRecv(void (*callBack)(const unsigned char*, const unsigned char*, int));
          void send(uint8_t address[], uint8_t* message, uint8_t len);
          void sendAll(ComMessage message);
          void sendAll(uint8_t* message, uint8_t len);
          void sendAll(MessageCom message);
          void sendLongFrameAll(String strFrame) ; //only char array

          void broadcastAll(uint8_t* message, uint8_t len);
          void sendAllData(FieldCom coins, FieldCom modules, RobotsCom robots);
          void sendCoins(FieldCom coins);
          void sendRobots(RobotsCom robots);
          void sendModules(FieldCom modules);
          void sendRemote(RemoteCom remote);
          void sendRemote(RemoteCom remote, uint8_t address[]);
          void sendTrack(TrackMsg msg, uint8_t address[]);
          void sendTrack(TrackData msg, uint8_t address[]);
          void sendRobotMessage(GladiatorMsg msg);
          void sendRegisterResponse(RegisterResponse response);

          void processResponse(ComMessage response); //to use in callback functions
          void getMessage(String* messageBuffer); //to use in callback functions
          bool isNewMessage() {return newMessage;};
          uint8_t getPeerInex() {return peerIndex;};
          String getMyAddress(){return myStrAddress;};
          
          void initWithholding();
          void setWithholding(uint8_t address[], bool value);
          Withholding getWithholding(uint8_t address[]);

          void setup(RobotData robotData);
          
          
      private:
          uint8_t myAdress[6];
          String myStrAddress;
          bool newMessage;
          String buffer;
          //uint8_t bufferIndex;
          //you cann add only 5 peers
          uint8_t peerAdresses[6][6];
          Withholding withholding[5];
          

          uint8_t peerIndex = 0;
          
          
          
  };




#endif
