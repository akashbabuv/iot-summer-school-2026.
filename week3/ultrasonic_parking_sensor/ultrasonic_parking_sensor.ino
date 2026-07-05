/*
Project : Ultrasonic Parking Sensor
Author  : Akash Babu
*/

const int trigPin = 9;
const int echoPin = 10;

const int greenLED = 2;
const int yellowLED = 3;
const int redLED = 4;

const int buzzer = 8;

unsigned long previousMillis = 0;
bool ledState = false;

void setup() {

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);

}

void loop() {

  long duration;
  float distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = (duration * 0.034) / 2;

  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.println(" cm");

  unsigned long currentMillis = millis();

  // SAFE

  if(distance > 50){

    digitalWrite(greenLED,HIGH);
    digitalWrite(yellowLED,LOW);
    digitalWrite(redLED,LOW);

    noTone(buzzer);

    Serial.println("SAFE");

  }

  // WARNING

  else if(distance >20 && distance<=50){

    digitalWrite(greenLED,LOW);
    digitalWrite(yellowLED,HIGH);
    digitalWrite(redLED,LOW);

    if(currentMillis-previousMillis>=500){

      previousMillis=currentMillis;

      ledState=!ledState;

      if(ledState)
        tone(buzzer,1000);
      else
        noTone(buzzer);

    }

  }

  // DANGER

  else if(distance>10 && distance<=20){

    digitalWrite(greenLED,LOW);
    digitalWrite(yellowLED,LOW);
    digitalWrite(redLED,HIGH);

    if(currentMillis-previousMillis>=200){

      previousMillis=currentMillis;

      ledState=!ledState;

      if(ledState)
        tone(buzzer,1200);
      else
        noTone(buzzer);

    }

  }

  // STOP

  else{

    if(currentMillis-previousMillis>=100){

      previousMillis=currentMillis;

      ledState=!ledState;

      digitalWrite(greenLED,ledState);
      digitalWrite(yellowLED,ledState);
      digitalWrite(redLED,ledState);

    }

    tone(buzzer,1500);

  }

}
