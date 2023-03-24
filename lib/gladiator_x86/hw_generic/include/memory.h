#ifndef MEMORY_H
#define MEMORY_H
#ifdef TARGET_ESP32
  #include <EEPROM.h>
#else
  #include <iostream>
  #include <fstream> 
#endif
#include "const.h"
#include "Arduino.h"
namespace hal {
  typedef struct MacAddressMemStruct {
    uint8_t macAddress[6];
    bool active;
    
    
  }MacAddressMemStruct;
  class Memory {
    public:
      Memory();
      void saveAntennaParams(uint8_t* macAddress, bool active);
      void getSavedAntenna(uint8_t* macAddress, bool* active);

      void saveRobotId(uint8_t id);
      uint8_t getRobotId();
      
      uint8_t save(uint8_t index, int value);
      uint8_t save(uint8_t index, uint8_t value);
      uint8_t save(uint8_t index, int16_t value);
      uint8_t save(uint8_t index, char value);
      uint8_t save(uint8_t len, char* value);
      uint8_t save(uint8_t index, float value);
      
      uint8_t get(uint8_t index, int  *value);
      uint8_t get(uint8_t index, uint8_t *value);
      uint8_t get(uint8_t index, int16_t *value);
      uint8_t get(uint8_t index, char *value);
      uint8_t get(uint8_t index, float *value);
      uint8_t getStr(uint8_t len, char* value);
      
      static Memory* instance;
      unsigned char memory[EEPROM_SIZE];
    private:
      void save(uint8_t* data, uint8_t address, uint8_t len);
      void read(uint8_t* data, uint8_t address, uint8_t len);
      uint8_t f_addr[4]  = { FLOAT0_ADDR, FLOAT1_ADDR, FLOAT2_ADDR, FLOAT3_ADDR };
      uint8_t c_addr[4]  = { CHAR0_ADDR,  CHAR1_ADDR,  CHAR2_ADDR,  CHAR3_ADDR  };
      uint8_t b_addr[4]  = { BYTE0_ADDR,  BYTE1_ADDR,  BYTE2_ADDR,  BYTE3_ADDR  };
      uint8_t i_addr[4]  = { INT0_ADDR,   INT1_ADDR,   INT2_ADDR,   INT3_ADDR   };
      uint8_t sh_addr[4] = { SHORT0_ADDR, SHORT1_ADDR, SHORT2_ADDR, SHORT3_ADDR };
    
  };
}
#endif
