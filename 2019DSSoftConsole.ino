#include <EEPROM.h>
#include <SPI.h>
#include <GD2.h>
#include "enums.h"

ARTIFACT_ENUM artifact = GamePiece;
DIRECTION_ENUM direction = Back;
DESTINATION_ENUM destination = Destination;
HEIGHT_ENUM height = Height;

// Define joystick ids for joystick HID events sent to host
const int hatchJoystickButtonId = 1;
const int ballJoystickButtonId = 2; 
const int mediumHeightJoystickButtonId = 3;
const int activateJoystickButtonId = 4;
const int lowHeightJoystickButtonId = 5;
const int frontJoystickButtonId = 6;
const int backJoystickButtonId = 7;
const int rocketJoystickButtonId = 8;
const int cargoShipJoystickButtonId = 9;
const int highHeightJoystickButtonId = 10;
const int cancelJoystickButtonId = 11;
const int loadingStationJoystickButtonId = 12;
const int AJoystickButtonId = 13;
const int BJoystickButtonId = 14;
const int XJoystickButtonId = 15;
const int leftJoystickHatAngle = 315;
const int centerJoystickHatAngle = 0;
const int rightJoystickHatAngle = 45;

static byte prevtag;

#define TAG_ARTIFACT  200
#define TAG_DIRECTION 201
#define TAG_DESTINATION 202
#define TAG_HEIGHT 203

void setup()
{
  GD.begin();
}

void loop()
{
  
  // Pump the inputs
  GD.get_inputs();

  // We have a new button press
  if (prevtag == 0) {
    // What button?
    switch (GD.inputs.tag) {
      case TAG_ARTIFACT:
        switch(artifact) {
          case GamePiece:
          case Hatch:
            artifact = Ball;
            Joystick.button(ballJoystickButtonId, HIGH);
            break;
          case Ball:
            artifact = Hatch;
            Joystick.button(hatchJoystickButtonId, HIGH);
            break;
        }
        break;
      case TAG_DIRECTION:
        switch(direction) {
          case Back:
            direction = Front;
            Joystick.button(frontJoystickButtonId, HIGH);            
            break;
          case Front:
            direction = Back;
            Joystick.button(backJoystickButtonId, HIGH);
            break;
        }
        break;
      case TAG_DESTINATION:
        switch(destination) {
          case Destination:
          case CargoShip:
            destination = Rocket;
            Joystick.button(rocketJoystickButtonId, HIGH);
            break;
          case Rocket:
            destination = LoadingStation;
            Joystick.button(loadingStationJoystickButtonId, HIGH);
            break;
          case LoadingStation:
            destination = CargoShip;
            Joystick.button(cargoShipJoystickButtonId, HIGH);
            break;            
        }
        break;
      case TAG_HEIGHT:
        switch(height) {
          case Height:
          case Low:
            height = High;
            Joystick.button(highHeightJoystickButtonId, HIGH);
            break;
          case Medium:
            height = Low;
            Joystick.button(lowHeightJoystickButtonId, HIGH);
            break;
          case High:
            height = Medium;
            Joystick.button(mediumHeightJoystickButtonId, HIGH);
            break;
        }
        break;
    }
  } else {
    // There is a button release
    if (GD.inputs.tag == 0) {
      switch (prevtag) {
        case TAG_ARTIFACT:
          switch(artifact) {
            case GamePiece:
            case Ball:
              Joystick.button(ballJoystickButtonId, LOW);
              break;
            case Hatch:
              Joystick.button(hatchJoystickButtonId, LOW);
              break;
          }
          break;
        case TAG_DIRECTION:
          switch(direction) {
            case Back:
              Joystick.button(backJoystickButtonId, LOW);
              break;
            case Front:
              Joystick.button(frontJoystickButtonId, LOW);
              break;
          }
          break;
        case TAG_DESTINATION:
          switch(destination) {
            case Destination:
            case Rocket:
              Joystick.button(rocketJoystickButtonId, LOW);
              break;
            case CargoShip:
              Joystick.button(cargoShipJoystickButtonId, LOW);
              break;
            case LoadingStation:
              Joystick.button(loadingStationJoystickButtonId, LOW);
              break;
          }
          break;
        case TAG_HEIGHT:
          switch(height) {
            case Height:
            case High:
              Joystick.button(highHeightJoystickButtonId, LOW);
              break;
            case Medium:
              Joystick.button(mediumHeightJoystickButtonId, LOW);
              break;
            case Low:
              Joystick.button(lowHeightJoystickButtonId, LOW);
              break;
          }
          break;
      }
    }
  }

  prevtag = GD.inputs.tag;

  GD.cmd_gradient(0, 0,   0x404044,
                  479, 271, 0x606068);
                  
  GD.ColorRGB(0x707070);

  GD.LineWidth(4 * 16);
  GD.Begin(RECTS);

  GD.Vertex2ii(8, 8);
  GD.Vertex2ii(128, 128);

  GD.Tag(TAG_DIRECTION);
  GD.cmd_button(8, 8, 60, 30, 28, 0, DIRECTION_STRING[direction]);

  GD.Tag(TAG_ARTIFACT);
  GD.cmd_button(8, 42, 60, 30, 28, 0, ARTIFACT_STRING[artifact]);

  GD.Tag(TAG_DESTINATION);
  GD.cmd_button(8, 80, 60, 30, 28, 0, DESTINATION_STRING[destination]);

  GD.Tag(TAG_HEIGHT);
  GD.cmd_button(8, 118, 60, 30, 28, 0, HEIGHT_STRING[height]);

  GD.swap();
}
