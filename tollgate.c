#include <Servo.h>

// Define Ultrasonic Sensor Pins
#define TRIG_PIN 27
#define ECHO_PIN 26

// Define IR Sensor Pin
#define IR_SENSOR_PIN 34

// Define Servo Motor Pin
#define SERVO_PIN 25

Servo servo;

// Vehicle detection threshold for Ultrasonic Sensor
#define DISTANCE_THRESHOLD 10 // in cm

void setup() {
    Serial.begin(115200);

    // Configure IR Sensor
    pinMode(IR_SENSOR_PIN, INPUT);

    // Configure Ultrasonic Sensor
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    // Configure Servo Motor
    servo.attach(SERVO_PIN);
    servo.write(0); // Keep gate closed initially

    Serial.println("Toll Gate System Initialized");
}

void loop() {
    // Vehicle Detection (Choose either IR or Ultrasonic)
    bool vehicleDetected = false;

    // IR Sensor
    if (digitalRead(IR_SENSOR_PIN) == HIGH) {
        vehicleDetected = true;
        Serial.println("Vehicle Detected (IR Sensor)");
    }

    // Ultrasonic Sensor
    long duration;
    float distance;

    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH);
    distance = (duration * 0.034) / 2;

    if (distance > 0 && distance < DISTANCE_THRESHOLD) {
        vehicleDetected = true;
        Serial.println("Vehicle Detected (Ultrasonic Sensor)");
    }

    // Control Servo Motor for Toll Gate
    if (vehicleDetected) {
        Serial.println("Opening Gate...");
        servo.write(90); // Open gate
        delay(5000);     // Wait for vehicle to pass
        servo.write(0);  // Close gate
        Serial.println("Closing Gate...");
    }

    delay(1000); // Check every second
}
