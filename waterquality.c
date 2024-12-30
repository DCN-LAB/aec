#define TRIG_PIN 27
#define ECHO_PIN 26
#define ADC_PIN 35
#define BUZZER_PIN 23

// Constants
const int NUM_READINGS = 5;
const float EMPTY_LEVEL = 14.0;
const float FULL_LEVEL = 3.0;
const int CLEAR_THRESHOLD = 50;
const int BLOCKED_THRESHOLD = 4095;

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(ADC_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // Read water level and turbidity
  float distance = getDistance();
  int turbidityValue = analogRead(ADC_PIN);
  int turbidityPercentage = map(turbidityValue, CLEAR_THRESHOLD, BLOCKED_THRESHOLD, 100, 0); // Normalize turbidity value

  // Print status to Serial Monitor
  Serial.print("Water Level: ");
  Serial.print(distance);
  Serial.println(" cm");

  Serial.print("Turbidity: ");
  Serial.print(turbidityPercentage);
  Serial.println(" %");

  // Handle warnings with buzzer
  if (distance > EMPTY_LEVEL || turbidityPercentage > 50) { // Buzzer for high turbidity or empty water level
    tone(BUZZER_PIN, 1000, 250);  
    delay(500);
  } else {
    noTone(BUZZER_PIN);
  }

  delay(500);
}

float getDistance() {
  long totalDuration = 0;

  for (int i = 0; i < NUM_READINGS; i++) {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    totalDuration += pulseIn(ECHO_PIN, HIGH);
    delay(50);
  }

  return (totalDuration / NUM_READINGS) * 0.034 / 2; // Average distance in cm
}
