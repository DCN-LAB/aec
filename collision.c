#include <Wire.h>
#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 mpu;

// Threshold for detecting a collision
const int collisionThreshold = 15000;  // Adjust based on experimentation

void setup() {
  Serial.begin(9600);  // Start Serial communication
  Wire.begin();        // Initialize I2C
  mpu.initialize();    // Initialize the MPU6050 sensor

  if (mpu.testConnection()) {
    Serial.println("MPU6050 connected successfully.");
  } else {
    Serial.println("MPU6050 connection failed. Check connections.");
    while (1);  // Stop execution if the sensor isn't connected
  }
}

void loop() {
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);  // Get acceleration values
  
  // Calculate total acceleration
  long totalAcceleration = sqrt((long)ax * ax + (long)ay * ay + (long)az * az);
  
  Serial.print("Total Acceleration: ");
  Serial.println(totalAcceleration);

  if (totalAcceleration > collisionThreshold) {
    Serial.println("Collision Detected!");
    delay(500);  // To avoid multiple detections
  }

  delay(100);  // Delay for stability
}
