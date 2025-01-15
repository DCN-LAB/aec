#include <Arduino.h>

// Define pins for Ultrasonic Sensor
#define TRIG_PIN 7
#define ECHO_PIN 6

// Define pins for LEDs
#define LED_LOW 8
#define LED_MEDIUM 9
#define LED_HIGH 10

void setup() {
    // Initialize Serial Monitor
    Serial.begin(9600);

    // Configure Ultrasonic Sensor pins
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    // Configure LED pins
    pinMode(LED_LOW, OUTPUT);
    pinMode(LED_MEDIUM, OUTPUT);
    pinMode(LED_HIGH, OUTPUT);

    // Turn off all LEDs initially
    digitalWrite(LED_LOW, LOW);
    digitalWrite(LED_MEDIUM, LOW);
    digitalWrite(LED_HIGH, LOW);

    Serial.println("Water Level Detection System Initialized");
}

void loop() {
    long duration;
    float distance;

    // Send a 10µs pulse to trigger the Ultrasonic Sensor
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Measure the duration of the echo pulse
    duration = pulseIn(ECHO_PIN, HIGH);

    // Calculate distance in cm
    distance = (duration * 0.034) / 2;

    // Print distance to the Serial Monitor
    Serial.print("Water Level Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Control LEDs based on distance
    if (distance > 20) { // Low water level
        digitalWrite(LED_LOW, HIGH);
        digitalWrite(LED_MEDIUM, LOW);
        digitalWrite(LED_HIGH, LOW);
    } else if (distance <= 20 && distance > 10) { // Medium water level
        digitalWrite(LED_LOW, LOW);
        digitalWrite(LED_MEDIUM, HIGH);
        digitalWrite(LED_HIGH, LOW);
    } else if (distance <= 10) { // High water level
        digitalWrite(LED_LOW, LOW);
        digitalWrite(LED_MEDIUM, LOW);
        digitalWrite(LED_HIGH, HIGH);
    } else { // No valid reading
        digitalWrite(LED_LOW, LOW);
        digitalWrite(LED_MEDIUM, LOW);
        digitalWrite(LED_HIGH, LOW);
    }

    // Delay for stability
    delay(500);
}
