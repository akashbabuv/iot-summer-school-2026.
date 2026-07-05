/*
====================================
Project : DC Motor Speed Control
Author  : Akash Babu
====================================

*/

const int ENA = 9;
const int IN1 = 8;
const int IN2 = 7;

const int potPin = A0;

const int dirButton = 2;
const int startButton = 3;

bool motorRunning = true;
bool direction = true;   // true = Forward

bool lastDirState = HIGH;
bool lastStartState = HIGH;

void setup() {

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(dirButton, INPUT_PULLUP);
  pinMode(startButton, INPUT_PULLUP);

  Serial.begin(9600);

  Serial.println("===== DC MOTOR CONTROL =====");
}

void loop() {

  // Read potentiometer
  int potValue = analogRead(potPin);

  int pwm = map(potValue, 0, 1023, 0, 255);

  int speedPercent = map(potValue, 0, 1023, 0, 100);

  // ---------- Direction Button ----------

  bool dirState = digitalRead(dirButton);

  if (dirState == LOW && lastDirState == HIGH) {

    direction = !direction;

    delay(200);
  }

  lastDirState = dirState;

  // ---------- Start/Stop Button ----------

  bool startState = digitalRead(startButton);

  if (startState == LOW && lastStartState == HIGH) {

    motorRunning = !motorRunning;

    delay(200);
  }

  lastStartState = startState;

  // ---------- Motor Control ----------

  if (motorRunning) {

    analogWrite(ENA, pwm);

    if (direction) {

      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);

    } else {

      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);

    }

  } else {

    analogWrite(ENA, 0);

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);

  }

  // ---------- Serial Monitor ----------

  Serial.println("----------------------------");

  Serial.print("Direction : ");

  if (direction)
    Serial.println("Forward");
  else
    Serial.println("Reverse");

  Serial.print("Speed     : ");
  Serial.print(speedPercent);
  Serial.println("%");

  Serial.print("State     : ");

  if (motorRunning)
    Serial.println("RUNNING");
  else
    Serial.println("STOPPED");

  Serial.println("----------------------------");

  delay(500);

}
