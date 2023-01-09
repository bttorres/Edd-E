# This... is Edd-E

Edd-E is an ESP32 powered, controlled robot. 

**************************** INSERT TIKTOK ****************************

## The code

The code in the "src/" folder is the code that he uses to function. It's in the ESP-IDF structure (regular C language). PlatformIO in Visual Studio Code was used for write it.

## Edd-E's Parts and Their Functions:

In this repository is a PDF of the schematic depicting Edd-E's electronic parts and how they are connected.
* 1 ESP32-WROOM-32D dev board
  * Recieves data from the ESP32-CAM board and controls the sensors and servos
* 1 ultrasonic sensor
  * Only serves an aesthetic purpose
* 1 H-bridge motor driver
  * Drives two DC motors
* 2 DC motors
  * Used as Edd-E's wheels
* 3 180 degree servo motor (SG90)
  * Used to animate Edd-E's head and neck to pan, tilt, and roll
* 1 ball caster
  * Assists with movement
* 5 buck converters
  * Step down the voltages from the batteries to power the, motors, motor driver, servos, and ESP32-WROOM-32D dev board
* 1 2000mAh 11.1V Li-ion batteries


## Edd-E's Web App

[Picture of the app](https://user-images.githubusercontent.com/55719532/191055793-7356e9bd-6d7e-492b-b6b2-d5128efd728e.jpeg)

Once the user connects to Edd-E's Wifi, they can go to the IP address (192.168.4.1) in their web browser. The web app allows the user to control Edd-E. The user can drive him, move his head/neck around, and have him do pre-set actions.


