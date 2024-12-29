#include <LiquidCrystal.h>

// Initialize LCD (for standard LCD with 16x2 pins)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // RS, E, D4, D5, D6, D7

// Voltage Sensor Pin
#define VOLTAGE_SENSOR_PIN A0

// LED Pin
#define LED_PIN 9

// Voltage Reference and Divider Ratio
#define VOLTAGE_REF 5.0      // Reference voltage for ADC (5V)
#define ADC_RESOLUTION 1023.0 // ADC resolution for 10-bit ADC
#define VOLTAGE_DIVIDER_RATIO 5.0 // If using a 5:1 voltage divider

void setup() {
    Serial.begin(115200);

    // Initialize LCD
    lcd.begin(16, 2);
    lcd.print("Voltage:");

    // Configure LED pin
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    Serial.println("Voltage Measurement System Initialized");
}

void loop() {
    // Read analog value from voltage sensor
    int analogValue = analogRead(VOLTAGE_SENSOR_PIN);

    // Convert to voltage
    float voltage = (analogValue / ADC_RESOLUTION) * VOLTAGE_REF * VOLTAGE_DIVIDER_RATIO;

    // Print voltage to Serial Monitor
    Serial.print("Voltage: ");
    Serial.print(voltage);
    Serial.println(" V");

    // Display voltage on LCD
    lcd.setCursor(0, 1);
    lcd.print(voltage);
    lcd.print(" V   ");

    // Check if voltage is below 3V
    if (voltage < 3.0) {
        digitalWrite(LED_PIN, HIGH); // Turn ON LED
        Serial.println("Low Voltage Detected! LED ON.");
    } else {
        digitalWrite(LED_PIN, LOW); // Turn OFF LED
        Serial.println("Voltage Normal. LED OFF.");
    }

    delay(1000); // Update every second
}
