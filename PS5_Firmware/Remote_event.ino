#include <ps5Controller.h>
#include "HardwareSerial.h"

#define txPin  17
#define rxPin 16
HardwareSerial stm32Serial(1);
void setup() {
  stm32Serial.begin(9600, SERIAL_8N1, rxPin, txPin);
  Serial.begin(9600);
  ps5.begin("24:a6:fa:c7:f9:2d"); //replace with MAC address of your controller
  Serial.println("Ready.");
}

void loop() {
  while (ps5.isConnected() == true) {
    // Check if the controller buttons are pressed
    // Omitted for brevity

    // Read the values of necessary values
    int R2Value = ps5.R2Value();
    int L2Value = ps5.L2Value();
    int LStickXValue = ps5.LStickX();
    int Cross = ps5.Cross() ? 0 : 1;
    int Circle = ps5.Circle() ? 0 : 1;
    int Square = ps5.Square() ? 0 : 1;
    int Triangle = ps5.Triangle() ? 0: 1;
    int PSButton = ps5.PSButton() ? 0 : 1;

    // Format the data string
    char dataString[50];
    
    snprintf(dataString, sizeof(dataString), "%d %d %d %d %d %d %d %d", R2Value, L2Value, LStickXValue, Cross, Circle, Square, Triangle, PSButton);

    // Send the data string over serial
    stm32Serial.println(dataString);
    Serial.print("Sent the data: ");
    Serial.println(dataString);
    // This delay is to make the output more human readable
    // Remove it when you're not trying to see the output
  }
  delay(100);
}
