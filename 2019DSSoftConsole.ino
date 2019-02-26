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
const int outakeJoystickButtonId = 11;
const int loadingStationJoystickButtonId = 12;
const int AJoystickButtonId = 13;
const int BJoystickButtonId = 14;
const int XJoystickButtonId = 15;
const int intakeJoystickButtonId = 16;
const int leftJoystickHatAngle = 315;
const int centerJoystickHatAngle = 0;
const int rightJoystickHatAngle = 45;

static byte prevtag;

#define TAG_ARTIFACT  200
#define TAG_DIRECTION 201
#define TAG_DESTINATION 202
#define TAG_HEIGHT 203
#define TAG_ACTIVATE 204
#define TAG_INTAKE 205
#define TAG_OUTAKE 206
#define TAG_TILT 207
#define TAG_PAN 208

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
      case TAG_ACTIVATE:
        Joystick.button(activateJoystickButtonId, HIGH);
        break;
      case TAG_INTAKE:
        Joystick.button(intakeJoystickButtonId, HIGH);
        break;
      case TAG_OUTAKE:
        Joystick.button(outakeJoystickButtonId, HIGH);
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
      case TAG_ACTIVATE:
        Joystick.button(activateJoystickButtonId, LOW);
        break;
      case TAG_INTAKE:
        Joystick.button(intakeJoystickButtonId, LOW);
        break;
      case TAG_OUTAKE:
        Joystick.button(outakeJoystickButtonId, LOW);
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
  GD.Vertex2ii(120, 244);

  GD.Tag(TAG_DIRECTION);
  GD.cmd_button(8, 8, 110, 30, 27, 0, DIRECTION_STRING[direction]);

  GD.Tag(TAG_ARTIFACT);
  GD.cmd_button(8, 42, 110, 30, 27, 0, ARTIFACT_STRING[artifact]);

  GD.Tag(TAG_DESTINATION);
  GD.cmd_button(8, 76, 110, 30, 27, 0, DESTINATION_STRING[destination]);

  GD.Tag(TAG_HEIGHT);
  GD.cmd_button(8, 110, 110, 30, 27, 0, HEIGHT_STRING[height]);

  GD.Tag(TAG_ACTIVATE);
  GD.cmd_button(8, 144, 110, 30, 27, 0, "Activate");

  GD.Tag(TAG_INTAKE);
  GD.cmd_button(8, 178, 110, 30, 27, 0, "Intake");

  GD.Tag(TAG_OUTAKE);
  GD.cmd_button(8, 212, 110, 30, 27, 0, "Outake");

  // Tilt slider
  GD.Tag(TAG_TILT);
  GD.cmd_slider(133, 8, 11, 240, 0, 90, 180);

  // Pan slider
  GD.Tag(TAG_PAN);
  GD.cmd_slider(155, 240, 300, 11, 0, 90, 180);

  // Show buffer
  GD.swap();
}
