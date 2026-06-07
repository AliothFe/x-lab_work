#define DELAY_TIME 250
const int ledNum = sizeof(ledPins) / sizeof(ledPins[0]);

void setup() {
  for (int i = 0; i < ledNum; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
}

void loop() {
  for (int i = 0; i < ledNum; i++) {
    for (int j = 0; j < ledNum; j++) {
      digitalWrite(ledPins[j], LOW);
    }
    digitalWrite(ledPins[i], HIGH);
    delay(DELAY_TIME);
  }
}