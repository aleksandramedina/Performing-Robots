/*
   Final project - OLED part
*/

#include <Arduino.h>
#include <stdint.h>
#include "SCMD.h"
#include "SCMD_config.h" //Contains #defines for common SCMD register names and values


// Button
#include <SparkFun_Qwiic_Button.h>
QwiicButton button;

// OLED
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//variables
int state = 0;
unsigned long motionStartedAt = 0;
int duration = 2000;
int count = 0;


void setup() {
  Serial.begin(9600);
  Wire.begin(); //Join I2C bus

  //Check if button acknowledges
  if (button.begin() == false) {
    Serial.println("Device did not acknowledge! Freezing.");
    while (1);
  }

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever

  }
  Serial.println("Button acknowledged.");
  Serial.println("OLED acknowledged.");


  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text

}


void loop() {

  //  if (button.isPressed() == true && count == 0) {
  //    count = 1;
  //  } else if (button.isPressed() == false && count == 1) {
  //

  unsigned long currentMillis = millis();

  switch (state) {

    case 0: //display first message
      firstMessage();
      motionStartedAt = millis();
      state = 1;
      break;

    case 1: // keep displaying first message until time expires
      if ((currentMillis - motionStartedAt) > duration) {
        state = 2;
      }
      break;


    case 2: //display second message
      secondMessage();
      motionStartedAt = millis();
      state = 3;
      break;

    case 3: // keep displaying second message until time expires
      if ((currentMillis - motionStartedAt) > duration) {
        state = 4;
      }
      break;

    case 4: //display third message
      thirdMessage();
      motionStartedAt = millis();
      state = 5;
      break;

    case 5: // keep displaying third message until time expires
      if ((currentMillis - motionStartedAt) > duration) {
        state = 6;
      }
      break;

    case 6: //display fourth message
      fourthMessage();
      motionStartedAt = millis();
      state = 7;
      break;

    case 7: // keep displaying fourth message until time expires
      if ((currentMillis - motionStartedAt) > duration) {
        state = 0;
      }
      break;
  }
  //  }
}


//defining functions


void firstMessage() {
  display.clearDisplay();
  display.setCursor(0, 0);            // Start at top-left corner
  display.println("Message: Something seems wrong.");
  display.display();
}

void secondMessage() {
  display.clearDisplay();
  display.setCursor(0, 0);            // Start at top-left corner
  display.println("Message: Can't find safety - abort.");
  display.display();
}

void thirdMessage() {
  display.clearDisplay();
  display.setCursor(0, 0);            // Start at top-left corner
  display.println("Error: Power source seems incompatible.");
  display.display();
}

void fourthMessage() {
  display.clearDisplay();
  display.setCursor(0, 0);            // Start at top-left corner
  display.println("Error: Stuck in an infinite loop.");
  display.display();
}
