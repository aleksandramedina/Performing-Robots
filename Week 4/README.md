### Coding homework

**Notes & questions**
- Since I don't have the kit yet, I was wondering how could I know if my code runs the way I want it to?
- I found different examples on how to write display codes for OLED. Which ones are the correct ones? I based my code off of [this one](https://www.instructables.com/id/Fun-With-OLED-Display-and-Arduino/).
- How much of the #include and #define code from the original example are we supposed to leave?

My code is here:

```javascript
// not sure if this initialization needs to be in every code? Left it from the example sketch.

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels


#include <SparkFun_Qwiic_Button.h>
QwiicButton button;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int buttonPressTimes;

void setup() {
  Serial.begin(9600);

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(35, 30);
  display.println("Ready!");

  display.display();
}


void loop() {
  //check if button is pressed, and tell us if it is!
  if (button.isPressed() == true) {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(35, 30);
    display.println("Pressed!");
    display.display();

    buttonPressTimes++;
  } else {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(35, 30);
    Serial.println(buttonPressTimes);
    display.display();

  }
}



```
