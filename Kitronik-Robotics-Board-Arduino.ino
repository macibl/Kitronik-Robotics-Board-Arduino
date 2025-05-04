// see README.md

#include "src/PicoRobotics.h"

#define DEBUGSERIAL   // debug information sent on serial Monitor

PicoRobotics board;

void setup() {
  Serial.begin(115200);               // Begin Serial and Wire interfaces
  while (!Serial);

  pinMode(LED_BUILTIN, OUTPUT);       // initialize digital pin LED_BUILTIN as an output.
    
  Wire.begin();                       // Use I2C interface as a controller device
  
  board.begin();                      // set clock frequency for I2C communication 
  
  board.initPCA();                    // initialize PCA9685 chip
  
  #ifdef DEBUGSERIAL
    //Serial.println(board.getChannelPWM(0)); // Should output 2048, which is 128 << 4
  #endif
}

/* just an exemple here, to check if the motors have the intended forward movement
   move 1 second forward, then 1 second backward
*/
void loop() {
  board.motorOn(leftMotor, FORWARD, 20);
  board.motorOn(rightMotor, FORWARD, 20);
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on
  #ifdef DEBUGSERIAL
    Serial.println("motor On Forward");
  #endif

  delay(1000);    // 1 second

  board.motorOff(leftMotor);
  board.motorOff(rightMotor);
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  #ifdef DEBUGSERIAL
    Serial.println("motor Off");
  #endif

  delay(1000);    // 1 second

  board.motorOn(leftMotor, REVERSE, 20);
  board.motorOn(rightMotor, REVERSE, 20);
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  #ifdef DEBUGSERIAL
    Serial.println("motor On Reverse");
  #endif

  delay(1000);    // 1 second

  board.motorOff(leftMotor);
  board.motorOff(rightMotor);
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  #ifdef DEBUGSERIAL
    Serial.println("motor Off");
  #endif
  delay(1000);
}