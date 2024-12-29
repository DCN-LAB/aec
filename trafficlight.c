// Define LED pins
#define RED_LED 25
#define YELLOW_LED 33
#define GREEN_LED 32

void setup() {
    Serial.begin(115200);

    // Configure LED pins
    pinMode(RED_LED, OUTPUT);
    pinMode(YELLOW_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);

    Serial.println("Traffic Light System Initialized");
}

void loop() {
    // Red Light
    digitalWrite(RED_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    Serial.println("Red Light ON");
    delay(5000); // 5 seconds

    // Yellow Light
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    Serial.println("Yellow Light ON");
    delay(2000); // 2 seconds

    // Green Light
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    Serial.println("Green Light ON");
    delay(3000); // 3 seconds
}
