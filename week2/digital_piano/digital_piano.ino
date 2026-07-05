/*
Project : Digital Piano using Passive Buzzer
Author  : Akash Babu
*/

const int buzzer = 8;

const int button1 = 2;
const int button2 = 3;
const int button3 = 4;
const int button4 = 5;
const int modeButton = 6;

bool majorMode = true;
bool previousModeState = HIGH;

void setup() {

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  pinMode(modeButton, INPUT_PULLUP);

  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);

  Serial.println("Digital Piano Started");
}

void loop() {

  // Toggle Major/Minor mode
  bool currentModeState = digitalRead(modeButton);

  if (currentModeState == LOW && previousModeState == HIGH) {

    majorMode = !majorMode;

    if (majorMode)
      Serial.println("Major Mode");
    else
      Serial.println("Minor Mode");

    delay(200);
  }

  previousModeState = currentModeState;

  bool b1 = digitalRead(button1) == LOW;
  bool b2 = digitalRead(button2) == LOW;
  bool b3 = digitalRead(button3) == LOW;
  bool b4 = digitalRead(button4) == LOW;

  // Two buttons together
  if ((b1 && b2) || (b2 && b3) || (b3 && b4)) {

    tone(buzzer, 392);

  }

  else if (b1) {

    tone(buzzer, 262);

  }

  else if (b2) {

    tone(buzzer, 294);

  }

  else if (b3) {

    if (majorMode)
      tone(buzzer, 330);
    else
      tone(buzzer, 311);

  }

  else if (b4) {

    tone(buzzer, 349);

  }

  else {

    noTone(buzzer);

  }

}
