#define TRIG 8
#define ECHO 9
#define TURBIDITY_PIN A0
#define LED_PIN 10
#define BUZZER_PIN 11
#define DIST_THRESHOLD 20
#define TURB_THRESHOLD 400

void setup() {
    Serial.begin(9600);
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
    pinMode(TURBIDITY_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
    // Ultrasonic sensor distance
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
    long duration = pulseIn(ECHO, HIGH);
    float distance = (duration * 0.034) / 2;

    // Turbidity sensor value
    int turbidity = analogRead(TURBIDITY_PIN);

    // Print data
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    Serial.print("Turbidity: ");
    Serial.println(turbidity);

    // Monitor water quality and create alerts
    if (distance > DIST_THRESHOLD || turbidity > TURB_THRESHOLD) {
        digitalWrite(LED_PIN, HIGH);
        digitalWrite(BUZZER_PIN, HIGH);
    } else {
        digitalWrite(LED_PIN, LOW);
        digitalWrite(BUZZER_PIN, LOW);
    }

    delay(2000);
}
