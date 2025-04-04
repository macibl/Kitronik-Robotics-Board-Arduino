// see README.md

#include "PicoRobotics.h"

PicoRobotics board;

#define PCA9685_ENABLE_DEBUG_OUTPUT 1

void setup() {
  Serial.begin(115200);               // Begin Serial and Wire interfaces
  Wire.begin();

  //Serial.println(board.getChannelPWM(0)); // Should output 2048, which is 128 << 4

  board.motorOn(leftMotor, FORWARD, 10);
  delay(1);
  board.motorOff(leftMotor);
}

void loop() {
}