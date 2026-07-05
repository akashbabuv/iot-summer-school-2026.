#include <Servo.h>

/*
Project : Servo Motor Sweep
Author  : Akash Babu
*/

Servo servoMotor;

const int servoPin = 9;
const int potPin = A0;
const int buttonPin = 2;

bool lastButtonState = HIGH;

void setup() {

  servoMotor.attach(servoPin);

  pinMode(buttonPin, INPUT_PULLUP);

  Serial.begin(9600);

}

void loop() {

  int potValue = analogRead(potPin);

  int angle = map(potValue, 0, 1023, 0, 180);

  servoMotor.write(angle);

  Serial.print("Servo Angle : ");
  Serial.print(angle);
  Serial.println(" degrees");

  bool currentButton = digitalRead(buttonPin);

  if(currentButton == LOW && lastButtonState == HIGH){

    Serial.println("Button Pressed -> Servo Sweep");

    // 0 -> 180
    for(int i=0;i<=180;i++){

      servoMotor.write(i);
      delay(10);

    }

    //180 -> 0
    for(int i=180;i>=0;i--){

      servoMotor.write(i);
      delay(10);

    }

  }

  lastButtonState = currentButton;

  delay(100);

}
