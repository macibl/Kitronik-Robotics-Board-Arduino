/*  Arduino Library for the Kitronik Pico Robotics board

*/

#include "PicoRobotics.h"

#define PCA9685_SW_RESET  (byte)0x06    // Sent to address 0x00 to reset all devices on Wire line


PicoRobotics::PicoRobotics(byte I2CAddress, TwoWire& i2cWire, uint32_t i2cSpeed) 
    : _i2cAddress(I2CAddress),
      _i2cWire(&i2cWire),
      _i2cSpeed(i2cSpeed),
      _lastI2CError(0)
      
{
  _i2cWire->setClock(_i2cSpeed);

  initPCA();
}

// setup the PCA chip for 50Hz and zero out registers.
void PicoRobotics::initPCA(){

  #ifdef PCA9685_ENABLE_DEBUG_OUTPUT
    Serial.println("PicoRobotics::initPCA");
  #endif 
  
  // Make sure we are in a known position
  // Soft reset of the I2C chip
  resetDevices();


Il faut s'assurer que les étapes d'un exemple comme examples/SimpleExample/SimpleExample.ino
sont dans le code de initPCA() :
    (ok)pwmController.resetDevices();       // Resets all PCA9685 devices on i2c line
    pwmController.init();               // Initializes module using default totem-pole driver mode, and default disabled phase balancer
    pwmController.setPWMFrequency(100); // Set PWM freq to 100Hz (default is 200Hz, supports 24Hz to 1526Hz)
    pwmController.setChannelPWM(0, 128 << 4); // Set PWM to 128/255, shifted into 4096-land


}

void PicoRobotics::resetDevices() {
  #ifdef PCA9685_ENABLE_DEBUG_OUTPUT
      Serial.println("PicoRobotics::resetDevices");
  #endif
  _i2cWire->beginTransmission(0);
  _i2cWire->write(PCA9685_SW_RESET);
  _lastI2CError = _i2cWire->endTransmission()

  delayMicroseconds(10);

  #ifdef PCA9685_ENABLE_DEBUG_OUTPUT
    checkForErrors();
  #endif
}

static const char *textForI2CError(byte errorCode) {
    switch (errorCode) {
    case 0:
        return "Success";
    case 1:
        return "Data too long to fit in transmit buffer";
    case 2:
        return "Received NACK on transmit of address";
    case 3:
        return "Received NACK on transmit of data";
    default:
        return "Other error";
    }
}

void PicoRobotics::checkForErrors() {
  if (_lastI2CError) {
    Serial.print("  PicoRobotics::checkErrors lastI2CError: ");
    Serial.print(_lastI2CError);
    Serial.print(": ");
    Serial.println(textForI2CError(_lastI2CError));
    }
}

void PicoRobotics::motorOn(byte motor, byte direction, byte speed){

}

void PicoRobotics::motorOff(byte motor){

}
