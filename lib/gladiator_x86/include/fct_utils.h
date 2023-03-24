
#ifndef FCT_UTILS
#define FCT_UTILS
#include <Arduino.h>
void macAddressToIntArray(char addr[], uint8_t output[]);
void macAddressToIntArray(String addr, uint8_t output[]);
String IntArrayToMacAddress(uint8_t input[]);
bool compareAddresses(uint8_t addr1[], uint8_t addr2[]);
double constrainAngle(double x);

#endif