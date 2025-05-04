# Kitronik-Robotics-Board-Arduino
Arduino library for the Kitronik Robotics Board for Pico

based on Kitronik Robotics Board Pico library in MicroPython language here:
https://github.com/KitronikLtd/Kitronik-Pico-Robotics-Board-MicroPython

based on PCA9685 library for Arduino:
https://github.com/NachtRaveVL/PCA9685-Arduino

Names of functions, constants are mostly those of Kitronik-Pico-Robotics-Board-MicroPython

Restrictions: only the four motors will be controlled in this first version, no stepper motors or servos

Kitronik Robotics board is designed to use a Raspberry Pi Pico module, but any microcontroller module 
with an I2C interface can be used (test done on Arduino Nano 33 BLE).

4 motors, each using two LED outputs from PCA9685, LED8 and LED9 for first motor, until LED14 and LED15 for fourth one.
LEDx_ON register is not used, and default value being 0, LEDx output is ON at beginning of PWM cycle.   

## Examples
### SimpleMotorTest provide a test for two motors connected to Kitronik Board, to check if correctly connected