//Final project : motors part

#include <Arduino.h>
#include <stdint.h>
#include "Wire.h" // for QWIIC communication
#include "SCMD.h"
#include "SCMD_config.h" //Contains #defines for common SCMD register names and values

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
int duration = 800;
int count = 0;
int button_state;

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

  Wire.begin();

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

  //  //Uncomment code for motor 0 inversion
  //  while( myMotorDriver.busy() );
  //  myMotorDriver.inversionMode(0, 1); //invert motor 0

  //Uncomment code for motor 1 inversion
  while ( myMotorDriver.busy() ); //Waits until the SCMD is available.
  myMotorDriver.inversionMode(1, 1); //invert motor 1

  while ( myMotorDriver.busy() );
  myMotorDriver.enable(); //Enables the output driver hardware

  if (button.begin() == false)
  {
    Serial.println("Device has not been detected! Infinite loop");          // Go to infinite loop, if button doesn't work.
    while (1);
  }

  Serial.println("Button is Set");

  button_state = 0;

}

void loop()
{

  if (button_state == 0)
  {
    no_button_press();

  }

  if (button.isPressed() == true)
  {
    button_state = 1;
  }

  if (button_state == 1)
  {


    unsigned long currentMillis = millis();

    // for debugging
    Serial.print("state = ");
    Serial.print(state);
    Serial.print("\t time = ");
    Serial.print(millis());
    Serial.println();




    switch (state) {


      case 0: // doesn't move
        stopMotors();
        motionStartedAt = millis();
        state = 1;
        break;

      case 1: // wait 15 seconds
        if ((currentMillis - motionStartedAt) > 15000) {
          state = 2;
        }
        break;

      case 2: // initiate wiggle
        motionStartedAt = millis();
        //        firstMessage();
        for (int i = 0; i < 10; i++) {
          leftForward();
          delay(400);
          rightForward();
          delay(400);
        }
        state = 3;
        break;

      case 3: // continue wiggle for 13 seconds
        if ((currentMillis - motionStartedAt) > 13000) {
          state = 4;
        }
        break;

      case 4: // stop
        stopMotors();
        motionStartedAt = millis();
        state = 5;
        break;

      case 5: // continue for 10 seconds
        if ((currentMillis - motionStartedAt) > 10000) {
          state = 6;
        }
        break;

      case 6: // goes back for 6 seconds
        backward();
        motionStartedAt = millis();
        state = 7;
        break;

      case 7: // continue for 6 seconds
        if ((currentMillis - motionStartedAt) > 6000) {
          state = 8;
        }
        break;

      case 8: //initiate wiggling
        motionStartedAt = millis();
        for (int i = 0; i < 10; i++) {
          leftForward();
          delay(400);
          rightForward();
          delay(400);
        }
        state = 9;
        break;


      case 9: // continue for 17 seconds
        if ((currentMillis - motionStartedAt) > 17000) {
          state = 10;
        }
        break;

      case 10: //stop for 3 seconds
        stopMotors();
        motionStartedAt = millis();
        state = 11;
        break;

      case 11: // continue for 3 seconds
        if ((currentMillis - motionStartedAt) > 3000) {
          state = 12;
        }
        break;

      case 12: // go backward
        backward();
        motionStartedAt = millis();
        state = 13;
        break;

      case 13: // continue for 5 seconds
        if ((currentMillis - motionStartedAt) > 3000) {
          state = 14;
        }
        break;

      case 14: // stop
        stopMotors();
        break;

    }
  }
}



//defining functions

void stopMotors() {
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 0); //Stop motor
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0); //Stop motor
}

void leftForward() {
  myMotorDriver.setDrive( LEFT_MOTOR, 1, 45); // turns left - double checked
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 5);
}

void rightForward() {
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 5); // turns right - double checked
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 45);
}

void forward() {
  myMotorDriver.setDrive( LEFT_MOTOR, 1, 45);  // forward - double checked
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 45);
}

void backward() {
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 45); // backward - double checked
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 45);
}


void no_button_press(void) {
}
