# 2019DSSoftConsole

This project implements a protoype soft console for operator two for the 2019 Deepspace game. It uses a Teensy 3.5
connected to a Gameduino 2 touch screen to implement elevator/arm/vision control buttons and emulates
a HID joystick. The joystick clicks can be read directly by the driver station for easy integration with
OI commands. Up to 16 virtual joystick buttons can be supported (driver station limitation...Teensy can support more).
