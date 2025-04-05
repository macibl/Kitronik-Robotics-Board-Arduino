// see README.md

#include "PicoRobotics.h"

#define PCA9685_ENABLE_DEBUG_OUTPUT 1

PicoRobotics board;

byte loopNb = 0;

void setup() {
  Serial.begin(115200);               // Begin Serial and Wire interfaces
  pinMode(LED_BUILTIN, OUTPUT);       // initialize digital pin LED_BUILTIN as an output.
  delay(5000);
  Serial.println("setup - before Wire.begin");
  byte i = 0;
  do {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);          // wait for sensors to stabilize
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    i++;                // increase i by 1
    } while (i < 10);

  Wire.begin();                       // Use I2C interface as a controller device
  Serial.println("setup - after Wire.begin");

  board.i2cWire_begin();              // set clock frequency for I2C communication 
  Serial.println("setup - after i2cWire_begin");

  board.initPCA();                    // initialize PCA9685 chip
  Serial.println("setup - after initPCA");

  //Serial.println(board.getChannelPWM(0)); // Should output 2048, which is 128 << 4
  i = 0;
  do {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);          // wait for sensors to stabilize
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    i++;                // increase i by 1
    } while (i < 10);
}

void loop() {
  Serial.print("loop ");
  Serial.println(loopNb);
  board.motorOn(leftMotor, FORWARD, 20);
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  Serial.println("motor On");
  delay(1000);    // 1 second
  board.motorOff(leftMotor);
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  Serial.println("motor Off");
  delay(1000);
  loopNb++;
}