/*
  This sketch allows live editing of the matrix pixels using WebSerial
  To test, head to https://ledmatrix-editor.arduino.cc

  The LED Matrix editor is part of Arduino Labs (https://labs.arduino.cc/), and is therefore considered experimental software.

  Don't forget to close any serial monitor already opened.

  See the full documentation here:
  https://docs.arduino.cc/tutorials/uno-r4-wifi/led-matrix  
*/
#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"  // Include the LED_Matrix library
#include "RTC.h"
int Minutes = 0;
int Hours = 0;
int Scroll_Rate = 50;
    ArduinoLEDMatrix matrix;  // Create an instance of the ArduinoLEDMatrix class

void setup() {
  Serial.begin(115200);  // Initialize serial communication at a baud rate of 115200
  RTC.begin();

  matrix.begin();  // Initialize the LED matrix
  RTCTime startTime(3, Month::MARCH, 2024, 2, 32, 0, DayOfWeek::SUNDAY, SaveLight::SAVING_TIME_ACTIVE);

}

// Define an array to hold pixel data for a single frame (4 pixels)
uint32_t frame[] = {
  0, 0, 0, 0xFFFF
};

void loop() {
  RTCTime currentTime;
  RTC.getTime(currentTime);
   Minutes = int(currentTime.getMinutes());
   Hours = int(currentTime.getHour());
  if (Hours > 12) {
    Hours -= 12;
  }
  matrix.beginDraw();
  matrix.textScrollSpeed(Scroll_Rate);
  matrix.textFont(Font_5x7);
  matrix.beginText(0, 1, 1);
  matrix.println();
  matrix.print(Hours);
  matrix.print(":");
  matrix.print(Minutes);
  matrix.print(" ");
  matrix.endText(SCROLL_LEFT);
  matrix.endDraw();
}
