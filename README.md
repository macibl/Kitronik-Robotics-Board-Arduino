# Kitronik-Robotics-Board-Arduino
 use Kitronik Robotics Board for Pico with Arduino env.

based on Kitronik Robotics Board Pico library in MicroPython language here:
https://github.com/KitronikLtd/Kitronik-Pico-Robotics-Board-MicroPython

based on PCA9685 library for Arduino:
https://github.com/NachtRaveVL/PCA9685-Arduino

Names of functions, constants are mostly those of Kitronik-Pico-Robotics-Board-MicroPython

Restrictions: only motors will be controlled in this first version

Kitronik Robotics board is designed to use a Raspberry Pi Pico module, but any microcontroller module 
with an I2C interface can be used (test done on Arduino Nano 33 BLE).

4 motors, each using two LED output of PCA9685, LED8 and LED9 for first motor, until LED14 and LED15 for fourth one.
LEDx_ON register is not used, and default value being 0, LEDx output is ON at beginning of PWM cycle.   