/* some explanation here */
#ifndef PicoRobotics_H
#define PicoRobotics_H

// assuming sofware i2c protocol is not used

#include <Arduino.h>
#include <Wire.h>

#define CHIP_ADDRESS 0x6C   
#define CHIP_ADDRESS_DEFAULT 0x6C // The default I2C address for the Kitronik Robotics Board
#define CHIP_ADDRESS_ALTERNATE1 0x6D
#define CHIP_ADDRESS_ALTERNATE2 0x6E
#define CHIP_ADDRESS_ALTERNATE3 0x6F

class PicoRobotics
{
  public:
    PicoRobotics();  // class constructor, see __init__() in PicoRobotics.py
}
