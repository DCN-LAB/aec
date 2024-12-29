#include <Wire.h>
#include <MPU6050.h>

// Create MPU6050 object
MPU6050 mpu;

// Collision Thresholds
#define ACCEL_THRESHOLD 3.0 // Change in g-forces

void setup() {
    Serial.begin(115200);
    Wire.begin();

    // Initialize MPU6050
    Serial.println("Initializing MPU6050...");
    if (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_16G)) {
        Serial.println("Could not initialize MPU6050");
        while (1);
    }

    Serial.println("MPU6050 Initialized!");
    mpu.calibrateGyro();
    mpu.setThreshold(3); // Set motion detection threshold
}

void loop() {
    // Read accelerometer data
    Vector rawAccel = mpu.readRawAccel();
    float ax = rawAccel.XAxis / 16384.0; // Convert to g
    float ay = rawAccel.YAxis / 16384.0; // Convert to g
    float az = rawAccel.ZAxis / 16384.0; // Convert to g

    // Compute magnitude of acceleration
    float accelMagnitude = sqrt(ax * ax + ay * ay + az * az);

    // Print accelerometer data
    Serial.print("Acceleration Magnitude: ");
    Serial.println(accelMagnitude);

    // Detect collision
    if (accelMagnitude > ACCEL_THRESHOLD) {
        Serial.println("Collision Detected!");
    }

    delay(100); // Adjust sampling rate
}
