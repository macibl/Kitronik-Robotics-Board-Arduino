/*  */

#ifndef PicoRobotics_H
#define PicoRobotics_H

// assuming sofware i2c protocol is not used

// Uncomment or -D this define to enable debug output.
//#define PCA9685_ENABLE_DEBUG_OUTPUT

#include <Arduino.h>
#include <Wire.h>   // https://docs.arduino.cc/language-reference/en/functions/communication/wire/

#define CHIP_ADDRESS_DEFAULT 0x6C // The default I2C address for the Kitronik Robotics Board
#define CHIP_ADDRESS_ALTERNATE1 0x6D   // other possible address
#define CHIP_ADDRESS_ALTERNATE2 0x6E
#define CHIP_ADDRESS_ALTERNATE3 0x6F
#define CHIP_ADDRESS CHIP_ADDRESS_DEFAULT


class PicoRobotics
{
  public:
    /* class constructor, see __init__() in PicoRobotics.py
       called during class instantiation, before setup()
       adress must be 7 bits only when using Wire I2C library
       If I2C pins are not the default one, adjust Wire to perhaps Wire1 or Wire2 
       remember to use no more than 32 byte buffer, else will be dropped 
       clock frequency for I2C communication is 100kHz, however PCA9685 supports Fast-mode (400kHz) 
       and Fast-mode Plus (1000kHz)
    PicoRobotics(byte I2CAddress = CHIP_ADDRESS, TwoWire& i2cWire = Wire, uint32_t i2cSpeed = 100000);  

  
}
