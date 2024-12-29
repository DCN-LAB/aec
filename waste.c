#include <Servo.h>

// Servo Motor Settings
Servo servo;
#define SERVO_PIN 25

// Ultrasonic Sensor Settings
#define TRIG_PIN 27
#define ECHO_PIN 26

// IR Sensor Settings
#define IR_SENSOR_PIN 33

// Threshold for Full Bin
#define BIN_FULL_THRESHOLD 10 // in cm

void setup() {
    Serial.begin(115200);

    // Initialize Servo Motor
    servo.attach(SERVO_PIN);
    servo.write(0); // Close lid initially

    // Configure Ultrasonic and IR Sensor Pins
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(IR_SENSOR_PIN, INPUT);
}

void loop() {
    // Measure distance using Ultrasonic Sensor
    long duration;
    float distance;

    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH);
    distance = (duration * 0.034) / 2;

    // Read IR Sensor
    int waste_detected = digitalRead(IR_SENSOR_PIN);

    // Print Sensor Readings
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    Serial.print("Waste Detected: ");
    Serial.println(waste_detected);

    // Control Servo Motor
    if (waste_detected == HIGH && distance > BIN_FULL_THRESHOLD) {
        Serial.println("Opening Lid...");
        servo.write(90); // Open lid
        delay(3000); // Keep lid open for 3 seconds
        servo.write(0); // Close lid
        Serial.println("Closing Lid...");
    } else if (distance <= BIN_FULL_THRESHOLD) {
        Serial.println("Bin is Full!");
    }

    delay(500);
}
