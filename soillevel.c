#include <DHT.h>

// DHT11 Settings
#define DHT_PIN 2
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

// Moisture Sensor Settings
#define MOISTURE_PIN A0
#define MOTOR_LED_PIN 9

// Reference moisture level
#define MOISTURE_THRESHOLD 500

void setup() {
    // Initialize Serial Communication
    Serial.begin(9600);

    // Initialize DHT sensor
    dht.begin();

    // Configure Moisture Sensor and Motor LED
    pinMode(MOISTURE_PIN, INPUT);
    pinMode(MOTOR_LED_PIN, OUTPUT);
    digitalWrite(MOTOR_LED_PIN, LOW); // Ensure motor is OFF initially
}

void loop() {
    // Read DHT11 values
    float temp = dht.readTemperature();
    float humidity = dht.readHumidity();

    // Read Moisture Sensor value
    int moisture = analogRead(MOISTURE_PIN);

    // Print readings
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.print(" °C, Humidity: ");
    Serial.print(humidity);
    Serial.print(" %, Moisture: ");
    Serial.println(moisture);

    // Control Motor LED based on Moisture Level
    if (moisture < MOISTURE_THRESHOLD) {
        digitalWrite(MOTOR_LED_PIN, HIGH); // Motor ON
        Serial.println("Motor ON: Low Moisture");
    } else {
        digitalWrite(MOTOR_LED_PIN, LOW); // Motor OFF
        Serial.println("Motor OFF: Sufficient Moisture");
    }

    delay(2000); // Delay for stability
}
