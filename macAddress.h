#include <EEPROM.h>
#include <Arduino.h>

uint8_t* getMacAddress(){
  randomSeed(analogRead(0));

  if(EEPROM.read(0) != 1 && EEPROM.read(1) != 0 && EEPROM.read(2) != 1){
    EEPROM.write(0, 1);
    EEPROM.write(1, 0);
    EEPROM.write(2, 1);

    EEPROM.write(3, (uint8_t) random(0,255));
    EEPROM.write(4, (uint8_t) random(0,255));
  }

  uint8_t *mac = (uint8_t*)malloc(sizeof(uint8_t)*6);
  mac[0] = 0xe8;
  mac[1] = 0x13;
  mac[2] = 0x9e;
  mac[3] = 0x26;
  mac[4] = EEPROM.read(3);
  mac[5] = EEPROM.read(4);

  return mac;
}


void(* resetFunc) (void) = 0; //declare reset function @ address 0

void wipeMacAndReboot(){
  EEPROM.write(0, 0);
  EEPROM.write(1, 1);
  EEPROM.write(2, 0);

  resetFunc();
}