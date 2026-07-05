/*
Project : PWM Fading Night Light
Author  : Akash Babu
*/

const int ledPin = 9;
const int buttonPin = 2;

int mode = 0;
bool lastButtonState = HIGH;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.println("Mode 1: Slow Breathing");
}

void loop() {

  bool buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && lastButtonState == HIGH) {
    mode++;
    if (mode > 2) mode = 0;

    if (mode == 0)
      Serial.println("Mode 1: Slow Breathing");

    if (mode == 1)
      Serial.println("Mode 2: Fast Pulse");

    if (mode == 2)
      Serial.println("Mode 3: SOS Pattern");

    delay(200);
  }

  lastButtonState = buttonState;

  if (mode == 0)
    slowBreathing();

  else if (mode == 1)
    fastPulse();

  else
    sosPattern();
}

void slowBreathing() {

  for (int i = 0; i <= 255; i++) {
    analogWrite(ledPin, i);
    delay(6);
  }

  for (int i = 255; i >= 0; i--) {
    analogWrite(ledPin, i);
    delay(6);
  }
}

void fastPulse() {

  for (int i = 0; i <= 255; i++) {
    analogWrite(ledPin, i);
    delay(1);
  }

  for (int i = 255; i >= 0; i--) {
    analogWrite(ledPin, i);
    delay(1);
  }
}

void dot() {
  digitalWrite(ledPin, HIGH);
  delay(200);
  digitalWrite(ledPin, LOW);
  delay(200);
}

void dash() {
  digitalWrite(ledPin, HIGH);
  delay(600);
  digitalWrite(ledPin, LOW);
  delay(200);
}

void sosPattern() {

  dot();
  dot();
  dot();

  dash();
  dash();
  dash();

  dot();
  dot();
  dot();

  delay(1000);
}
