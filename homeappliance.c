#include "BluetoothSerial.h"

// Initialize Bluetooth
BluetoothSerial SerialBT;

// LED Pins
#define LED1 25
#define LED2 33

void setup() {
    Serial.begin(115200);
    SerialBT.begin("ESP32_Bluetooth"); // Bluetooth device name
    Serial.println("Bluetooth Device is Ready to Pair");

    // Configure LED Pins
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
}

void loop() {
    // Check if data is received
    if (SerialBT.available()) {
        char command = SerialBT.read();

        // Control LEDs based on command
        if (command == '1') {
            digitalWrite(LED1, HIGH);
            SerialBT.println("LED1 ON");
        } else if (command == '2') {
            digitalWrite(LED1, LOW);
            SerialBT.println("LED1 OFF");
        } else if (command == '3') {
            digitalWrite(LED2, HIGH);
            SerialBT.println("LED2 ON");
        } else if (command == '4') {
            digitalWrite(LED2, LOW);
            SerialBT.println("LED2 OFF");
        } else {
            SerialBT.println("Invalid Command");
        }
    }

    delay(100); // Delay for stability
}
