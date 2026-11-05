
const int ledPin = 9;
const int buzzerPin = 8;
const int armBtn = 10;
const int sensorBtn = 11;
const int potPin = A0;

bool armed = false;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  pinMode(armBtn, INPUT_PULLUP);
  pinMode(sensorBtn, INPUT_PULLUP);
}

void loop() {

  // Arm / Disarm button
  if (digitalRead(armBtn) == LOW) {
    armed = !armed;

    // Confirmation flash
    digitalWrite(ledPin, HIGH);
    delay(150);
    digitalWrite(ledPin, LOW);

    // Wait for button release
    while (digitalRead(armBtn) == LOW) {
      delay(10);
    }
  }

  // Trigger alarm only when armed
  if (armed && digitalRead(sensorBtn) == LOW) {

    // Read potentiometer: 1–10 seconds
    int timeMs = map(analogRead(potPin), 0, 1023, 1000, 10000);

    runAlarm(timeMs);

    // Wait for sensor button release
    while (digitalRead(sensorBtn) == LOW) {
      delay(10);
    }
  }
}

void runAlarm(int duration) {
  unsigned long start = millis();

  while (millis() - start < duration) {

    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(200);

    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(200);
  }

  // Ensure everything is OFF
  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, LOW);
}
