/*  Arduino Library for the Kitronik Pico Robotics board

*/

#include "PicoRobotics.h"

// Register addresses from data sheet
#define PCA9685_MODE1_REG               (byte)0x00
#define PCA9685_PRESCALE_REG            (byte)0xFE
#define PCA9685_ALLLEDONL_REG           (byte)0xFA
#define PCA9685_ALLLEDONH_REG           (byte)0xFB
#define PCA9685_ALLLEDOFFL_REG           (byte)0xFC
#define PCA9685_ALLLEDOFFH_REG           (byte)0xFD

#define PCA9685_SW_RESET    (byte)0x06    // Sent to address 0x00 to reset all devices on Wire line


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

  /* setup the prescale to have 20mS pulse repetition - this is dictated by the servos.
     set PWM Frequency Pre Scale.  The prescale value is determined with the formunla:
     presscale value = round(osc clock / (4096 * update rate))
     Where update rate is the output modulation frequency required.
     For example, the output frequency of 50Hz (20ms) for the servo, with the internal oscillator 
     clock frequency of 25 Mhz is as follows:
     prescale value = round( 25MHZ / (4096 * 50Hz) ) - 1 
     prescale value = round (25000000 / (4096 * 50)) - 1 
     presscale value = 121 = 79h = 0x79 
     see 7.3.5 "PWM frequency PRE_SCALE" of PCA9685 datasheet
     no need to first read Mode 1 register, it is first access to register, default value is known */
  writeRegister(PCA9685_PRESCALE_REG, PRESCALE_VAL);

  // block write outputs to off
  writeRegister(PCA9685_ALLLEDONL_REG, 0);
  writeRegister(PCA9685_ALLLEDONH_REG, 0);
  writeRegister(PCA9685_ALLLEDOFFL_REG, 0);
  writeRegister(PCA9685_ALLLEDOFFH_REG, 0);

  /* come out of sleep (and Mode1 register init)
     Restart disabled, Use internal clock, Register auto-increment disabled, Normal mode (not sleep), 
     PCA9685 does not respond to I2C-bus subadresses, does not respond to LED All Call I2C-bus address
     see §7.3.1 of PCA9685 datasheet */
  writeRegister(PCA9685_MODE1_REG, 0x00);

  /* It takes 500uS max for the oscillator to be up and running once the SLEEP bit (bit 4) has
     been set to logic 0.  Timings on outputs are not guranteed if the PWM control registers are
     accessed within the 500uS window */
  delayMicroseconds(500);

  /* Mode 2 register does not need an init, default value is enough
     INVRT = 0, OUTDRV = 1 (needed for external N-type driver connecting output of PCA9685 to DRV8833 H-Bridges)
     OCH = 0, OUTNE = 0 (unused, OE* pin = 0)
  */
}

void PicoRobotics::resetDevices() {
  // see §7.6 of PCA9685 datasheet
  #ifdef PCA9685_ENABLE_DEBUG_OUTPUT
      Serial.println("PicoRobotics::resetDevices");
  #endif
  _i2cWire->beginTransmission(0);
  _i2cWire->write(PCA9685_SW_RESET);
  _lastI2CError = _i2cWire->endTransmission();

  delayMicroseconds(10);

  #ifdef PCA9685_ENABLE_DEBUG_OUTPUT
    checkForErrors();
  #endif
}

void PicoRobotics::writeRegister(byte regAddress, byte value) {
#ifdef PCA9685_ENABLE_DEBUG_OUTPUT
  Serial.print("  PicoRobotics::writeRegister regAddress: 0x");
  Serial.print(regAddress, HEX);
  Serial.print(", value: 0x");
  Serial.println(value, HEX);
#endif

_lastI2CError = 0;
_i2cWire->beginTransmission(_i2cAddress);
_i2cWire->write(regAddress);
_i2cWire->write(value);
_lastI2CError = _i2cWire->endTransmission();

#ifdef PCA9685_ENABLE_DEBUG_OUTPUT
    checkForErrors();
#endif
}

#ifdef PCA9685_ENABLE_DEBUG_OUTPUT
#if 0
// Compilation error: invalid conversion from 'const char*' to 'byte {aka unsigned char}' [-fpermissive]
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
#endif

void PicoRobotics::checkForErrors() {
  if (_lastI2CError) {
    Serial.print("  PicoRobotics::checkErrors lastI2CError: ");
    Serial.print(_lastI2CError);
    Serial.print(": ");
    //Serial.println(textForI2CError(_lastI2CError));
    }
}

#endif // /ifdef PCA9685_ENABLE_DEBUG_OUTPUT

/* Driving the motor is simpler than the servo - just convert 0-100% to 0-4095 and push it to the correct registers.
   each motor has 4 writes - low and high bytes for a pair of registers */
void PicoRobotics::motorOn(byte motor, byte direction, byte speed){
  #ifdef PCA9685_ENABLE_DEBUG_OUTPUT
    Serial.println("PicoRobotics::motorOn");
  #endif

  if (speed > 100) {
    speed = 100;
  }
  assert(!((motor < 1) || (motor > 4)));
}

void PicoRobotics::motorOff(byte motor){
  #ifdef PCA9685_ENABLE_DEBUG_OUTPUT
    Serial.println("PicoRobotics::motorOff");
  #endif

}
