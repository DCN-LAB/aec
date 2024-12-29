// Pin Definitions
#define TRIG_PIN 27
#define ECHO_PIN 26
#define TURBIDITY_PIN 34
#define LED_PIN 25
#define BUZZER_PIN 33

// Thresholds
#define TURBIDITY_THRESHOLD 300 // Adjust based on calibration
#define DISTANCE_THRESHOLD 10   // in cm

void setup() {
    Serial.begin(115200);

    // Ultrasonic Sensor
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    // Turbidity Sensor
    pinMode(TURBIDITY_PIN, INPUT);

    // LED and Buzzer
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
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

    // Read Turbidity Sensor
    int turbidity = analogRead(TURBIDITY_PIN);

    // Print readings
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    Serial.print("Turbidity: ");
    Serial.println(turbidity);

    // Check for alerts
    if (turbidity > TURBIDITY_THRESHOLD || distance < DISTANCE_THRESHOLD) {
        digitalWrite(LED_PIN, HIGH); // Turn on LED
        digitalWrite(BUZZER_PIN, HIGH); // Turn on Buzzer
        Serial.println("ALERT! Quality Issue Detected.");
    } else {
        digitalWrite(LED_PIN, LOW); // Turn off LED
        digitalWrite(BUZZER_PIN, LOW); // Turn off Buzzer
    }

    delay(1000); // Delay for stability
}
