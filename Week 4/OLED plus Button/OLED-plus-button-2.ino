
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SparkFun_Qwiic_Button.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

QwiicButton button;

//A variable where the amount of times the button was pressed, is stored.
int TimesPressed = 0;

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

  //Start with the message "Ready."
  printonOLED("Ready.");

}

void loop() {
  //If button is pressed, print "Pressed." and increment the count.
  if (button.isPressed()) {
    printonOLED("Pressed.");
    TimesPressed++;
  }
  
  //When button is not pressed, it prints the amount of times the button has been pressed.
  //NumTimesPressed is never zero to avoid overriding the welcome message
  
  if (!(button.isPressed()) && (TimesPressed != 0)) {
    String NumTimesPressed = String(TimesPressed) ;
    printonOLED("Total Button Presses: " + NumTimesPressed);
  }
}

//Printing onto OLDE

void printonOLED(String i) {
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0, 0);            // Start at top-left corner
  display.println(i);
  display.display();
}
