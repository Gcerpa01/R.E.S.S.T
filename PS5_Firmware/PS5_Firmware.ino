#include <ps5Controller.h>
#include "HardwareSerial.h"

#define txPin  17
#define rxPin 16
HardwareSerial stm32Serial(1);
void setup() {
  stm32Serial.begin(9600, SERIAL_8N1, rxPin, txPin);
  Serial.begin(9600);
  ps5.begin("88:03:4c:ef:be:54"); //replace with MAC address of your controller
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
    int Triangle = ps5.Triangle() ? 0 : 1;
    int L1Value = ps5.L1() ? 0 : 1;

    // Format the data string
    char dataString[30];

    int formattedLength = snprintf(dataString, sizeof(dataString), "%d:%d:%d:%d:%d:%d:%d:%d", R2Value, L2Value, LStickXValue, Cross, Circle, Square, Triangle, L1Value);

    // Fill remaining characters with ':'
    for (int i = formattedLength; i < sizeof(dataString) - 1; i++) {
      dataString[i] = ':';
    }
    dataString[sizeof(dataString) - 1] = '\0'; // Null-terminate the string

    // Send the data string over serial
    stm32Serial.println(dataString);
    Serial.print("Sent the data: ");
    Serial.println(dataString);
    // This delay is to make the output more human readable
    // Remove it when you're not trying to see the output
    delay(100);
  }
}
