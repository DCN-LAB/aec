#include <Servo.h>

// Define IR sensor pins
#define IR_SENSOR1 2
#define IR_SENSOR2 3
#define IR_SENSOR3 4

// Define Servo Motor pin
#define SERVO_PIN 9

Servo servo;

void setup() {
    // Initialize Serial Communication
    Serial.begin(9600);

    // Initialize IR sensors as input
    pinMode(IR_SENSOR1, INPUT);
    pinMode(IR_SENSOR2, INPUT);
    pinMode(IR_SENSOR3, INPUT);

    // Initialize Servo Motor
    servo.attach(SERVO_PIN);
    servo.write(0); // Keep gate closed initially

    Serial.println("Parking Slot System Initialized");
}

void loop() {
    // Read IR sensors
    int slot1 = digitalRead(IR_SENSOR1);
    int slot2 = digitalRead(IR_SENSOR2);
    int slot3 = digitalRead(IR_SENSOR3);

    // Print parking slot status
    Serial.print("Slot 1: ");
    Serial.print(slot1 ? "Occupied" : "Free");
    Serial.print(", Slot 2: ");
    Serial.print(slot2 ? "Occupied" : "Free");
    Serial.print(", Slot 3: ");
    Serial.println(slot3 ? "Occupied" : "Free");

    // Check if any slot is free
    if (!slot1 || !slot2 || !slot3) {
        Serial.println("Free Slot Found! Opening Gate...");
        servo.write(90); // Open gate
        delay(5000);     // Wait for 5 seconds
        servo.write(0);  // Close gate
    } else {
        Serial.println("All Slots Occupied.");
    }

    delay(1000); // Check every second
}
