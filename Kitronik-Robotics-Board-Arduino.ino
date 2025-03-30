# see README.md
# Note : Kitronik Robotics board is designed to use a Raspberry Pi Pico module, 
#        but any microcontroller module with an I2C interface can be used.


#include "PicoRobotics.h"

PicoRobotics board;

#define PCA9685_ENABLE_DEBUG_OUTPUT 1
#define leftMotor 1
#define rightMotor 2 

void setup() {
  Serial.begin(115200);               // Begin Serial and Wire interfaces
  Wire.begin();

  //Serial.println(board.getChannelPWM(0)); // Should output 2048, which is 128 << 4

  board.motorOn(leftMotor, "f", 10)   OK en arduino ?
  delay(1);
  board.motorOff(leftMotor)
}

void loop() {
}