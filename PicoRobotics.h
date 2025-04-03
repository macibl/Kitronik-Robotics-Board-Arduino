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

#define MOT_REG_BASE = 0x28 // Address of first register used to control motors : LED8_OFF_L register 
#define REG_OFFSET = 4      // register offset for same type of register

/* setup the prescale to have 20mS pulse repetition - this is dictated by the servos (even if currently not used)
set PWM Frequency Pre Scale.  The prescale value is determined with the formunla:
prescale value = round(osc clock / (4096 * update rate))
Where update rate is the output modulation frequency required.
External clock (EXTCLOCK pin) is not used.  
The output frequency of 50Hz (20ms) for the servo, with the internal oscillator 
clock frequency of 25 Mhz is as follows (see § 7.3.5 PWM frequency PRE-SCALE on PCA9685 datasheet):
prescale value = round( 25MHZ / (4096 * 50Hz) ) - 1 
prescale value = round (25000000 / (4096 * 50)) - 1 
presscale value = 121 = 79h = 0x79 */
#define PRESCALE_VAL        (byte)0x79    // prescaler value for common PWM output frequency

class PicoRobotics
{
  public:
    /* class constructor, see __init__() in PicoRobotics.py
       called during class instantiation, before setup()
       adress must be 7 bits only when using Wire I2C library
       If I2C pins are not the default one, adjust Wire to perhaps Wire1 or Wire2 
       remember to use no more than 32 byte buffer, else extra byte will be dropped 
       clock frequency for I2C communication is 100kHz, however PCA9685 supports Fast-mode (400kHz) 
       and Fast-mode Plus (1000kHz) 
    */
    PicoRobotics(byte I2CAddress = CHIP_ADDRESS, TwoWire& i2cWire = Wire, uint32_t i2cSpeed = 100000);  

    void initPCA();

    // Resets modules. called in initPCA(), before any init()'s, but public, can be called anytime 
    // Calling will perform a software reset of PCA9685 device on the Wire instance
    void resetDevices();

    // using Wire library, write the byte value in I2C device at register adress regAddress
    void writeRegister(byte regAddress, byte value);

    /* drive motor at speed between 0 and 100 % of power supply voltage (function will convert pourcentage 
       in a 12 bit value 0-4095) and initialise corresponding LEDx registers
       for each motor, two LEDx output are used to control H-bridge motor driver DRV8833
       for each LEDx output, LEDx_ON register stay in default value 0, and LEDx_OFF register define the PWM value 
    */  
    void motorOn(byte motor, byte direction, byte speed);

    void motorOff(byte motor);

    #ifdef PCA9685_ENABLE_DEBUG_OUTPUT
      void checkForErrors();
    #endif

  protected:
    byte _i2cAddress;                                       // Module's i2c address (default: B000000)
    #ifndef PCA9685_USE_SOFTWARE_I2C
      TwoWire* _i2cWire;                                      // Wire class instance (unowned) (default: Wire)
      uint32_t _i2cSpeed;                                     // Module's i2c clock speed (default: 400000)
    #endif
    
    byte _lastI2CError;                                     // Last module i2c error

};
#endif  // ifndef PicoRobotics_H
