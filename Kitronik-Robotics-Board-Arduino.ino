// see README.md

#include "PicoRobotics.h"

#define PCA9685_ENABLE_DEBUG_OUTPUT 1

PicoRobotics board;

byte loopNb = 0;

void setup() {
  Serial.begin(115200);               // Begin Serial and Wire interfaces
  pinMode(LED_BUILTIN, OUTPUT);       // initialize digital pin LED_BUILTIN as an output.
    
  Wire.begin();                       // Use I2C interface as a controller device
  
  board.i2cWire_begin();              // set clock frequency for I2C communication 
  
  board.initPCA();                    // initialize PCA9685 chip
  
  //Serial.println(board.getChannelPWM(0)); // Should output 2048, which is 128 << 4
}

void loop() {
  board.motorOn(leftMotor, FORWARD, 20);
  board.motorOn(rightMotor, FORWARD, 20);
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  Serial.println("motor On Forward");
  delay(1000);    // 1 second
  board.motorOff(leftMotor);
  board.motorOff(rightMotor);
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  Serial.println("motor Off");
  delay(1000);
  board.motorOn(leftMotor, REVERSE, 20);
  board.motorOn(rightMotor, REVERSE, 20);
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  Serial.println("motor On Reverse");
  delay(1000);    // 1 second
  board.motorOff(leftMotor);
  board.motorOff(rightMotor);
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  Serial.println("motor Off");
  delay(1000);
}