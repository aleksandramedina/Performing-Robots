//Final project : motors part

#include <Arduino.h>
#include <stdint.h>
#include "Wire.h" // for QWIIC communication

// Button
#include <SparkFun_Qwiic_Button.h>
QwiicButton button;

// Motor controller
#include "SCMD.h"
#include "SCMD_config.h" //Contains #defines for common SCMD register names and values
SCMD myMotorDriver; //This creates the main object of one motor driver and connected slaves.
#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1

//variables
int state = 0;
unsigned long motionStartedAt = 0;
int duration = 200;
int count = 0;
int innerSpeed = 50;
int outerSpeed = 10;
//int repetitions = 7;

void setup()
{
  pinMode(8, INPUT_PULLUP); //Use to halt motor movement (ground)

  Serial.begin(9600);
  Serial.println("Starting sketch.");

  //***** Configure the Motor Driver's Settings *****//
  //  .commInter face is I2C_MODE
  myMotorDriver.settings.commInterface = I2C_MODE;

  //  set address if I2C configuration selected with the config jumpers
  myMotorDriver.settings.I2CAddress = 0x5D; //config pattern is "1000" (default) on board for address 0x5D

  //  set chip select if SPI selected with the config jumpers
  myMotorDriver.settings.chipSelectPin = 10;

  //*****initialize the driver get wait for idle*****//
  while ( myMotorDriver.begin() != 0xA9 ) //Wait until a valid ID word is returned
  {
    Serial.println( "ID mismatch, trying again" );
    delay(500);
  }
  Serial.println( "ID matches 0xA9" );

  //  Check to make sure the driver is done looking for slaves before beginning
  Serial.print("Waiting for enumeration...");
  while ( myMotorDriver.ready() == false );
  Serial.println("Done.");
  Serial.println();

  //*****Set application settings and enable driver*****//

  //Uncomment code for motor 0 inversion
  while( myMotorDriver.busy() );
  myMotorDriver.inversionMode(0, 1); //invert motor 0

  //Uncomment code for motor 1 inversion
  while ( myMotorDriver.busy() ); //Waits until the SCMD is available.
  myMotorDriver.inversionMode(1, 1); //invert motor 1

  while ( myMotorDriver.busy() );
  myMotorDriver.enable(); //Enables the output driver hardware

}

void loop()
{
  unsigned long currentMillis = millis();
//  if (!repetitions) {
//    stopMotors();
//    return;
//  }

 // for debugging
  Serial.print("state = ");
  Serial.print(state);
  Serial.print("\t time = ");
  Serial.print(millis());
//  Serial.print("\t repetitions = ");
//  Serial.print(repetitions);
  Serial.println();

  switch (state) {

    case 0: // initiate wiggle to the left
      leftForward(outerSpeed);
//      rightForward(innerSpeed);
      motionStartedAt = millis();
      state = 1;
      break;

    case 1: //continue wiggling until time expires
      if ((currentMillis - motionStartedAt) > duration) {
        state = 2;
      }
      break;

    case 2: // initiate wiggle to the right
      rightForward(innerSpeed);
//      leftForward(outerSpeed);
      motionStartedAt = millis();
      state = 3;
      break;

    case 3: //continue wiggling until time expires
      if ((currentMillis - motionStartedAt) > duration) {
//        repetitions--;
        state = 0;
      }
      break;

    case 4:
      break;

//    default:
//      stopMotors();
//      break;

  }
}


//defining functions

void stopMotors() {
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 0); //Stop motor
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0); //Stop motor
}

void leftForward(int speed) {
  myMotorDriver.setDrive( LEFT_MOTOR, 0, speed);
}

void rightForward(int speed) {
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, speed);
}
