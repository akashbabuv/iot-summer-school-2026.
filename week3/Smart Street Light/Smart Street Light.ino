/*
Project : Smart Street Light
Author  : Akash Babu
*/

const int ldrPin = A0;
const int pirPin = 2;
const int ledPin = 9;

const int threshold = 500;

unsigned long motionTime = 0;
bool motionDetected = false;

void printEvent(String event) {
  unsigned long seconds = millis() / 1000;
  unsigned int hh = (seconds / 3600) % 24;
  unsigned int mm = (seconds % 3600) / 60;
  unsigned int ss = seconds % 60;

  char timeBuffer[12];
  sprintf(timeBuffer, "%02u:%02u:%02u", hh, mm, ss);

  Serial.print("[");
  Serial.print(timeBuffer);
  Serial.print("] EVENT: ");
  Serial.println(event);
}

void setup() {

  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);

  printEvent("System Started");
}

void loop() {

  int light = analogRead(ldrPin);

  // DAYTIME
  if (light > threshold) {

    analogWrite(ledPin, 0);

    motionDetected = false;

    printEvent("DAYLIGHT - LED OFF");

    delay(1000);

    return;
  }

  // NIGHT
  if (digitalRead(pirPin) == HIGH) {

    motionDetected = true;
    motionTime = millis();

    analogWrite(ledPin, 255);

    printEvent("MOTION DETECTED - LED FULL BRIGHTNESS");
  }

  if (motionDetected) {

    if (millis() - motionTime >= 30000) {

      analogWrite(ledPin, 51);

      motionDetected = false;

      printEvent("NO MOTION - LED DIMMED TO 20%");
    }
  }

  else {

    analogWrite(ledPin, 51);
  }

  delay(100);
}
