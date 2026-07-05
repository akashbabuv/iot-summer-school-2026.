
/*
==============================
VENDING MACHINE STATE DIAGRAM
==============================

IDLE
 |
 | Insert Coin
 V
COIN_INSERTED
 |
 | Select Item
 V
ITEM_SELECTED
 |
 | Dispense
 V
DISPENSING
 |
 | Complete
 V
IDLE

Cancel returns to IDLE.
*/

const int redLED = 10;
const int yellowLED = 9;
const int greenLED = 8;

const int coinButton = 2;
const int selectButton = 3;
const int cancelButton = 4;

enum State {
  IDLE,
  COIN_INSERTED,
  ITEM_SELECTED,
  DISPENSING
};

State currentState = IDLE;

void updateLEDs() {

  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);

  switch(currentState) {

    case IDLE:
      digitalWrite(redLED, HIGH);
      break;

    case COIN_INSERTED:
      digitalWrite(yellowLED, HIGH);
      break;

    case ITEM_SELECTED:
      digitalWrite(greenLED, HIGH);
      break;

    case DISPENSING:
      digitalWrite(redLED, HIGH);
      digitalWrite(greenLED, HIGH);
      break;
  }
}

void printState() {

  switch(currentState) {

    case IDLE:
      Serial.println("State: IDLE");
      break;

    case COIN_INSERTED:
      Serial.println("State: COIN_INSERTED");
      break;

    case ITEM_SELECTED:
      Serial.println("State: ITEM_SELECTED");
      break;

    case DISPENSING:
      Serial.println("State: DISPENSING");
      break;
  }
}

void setup() {

  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  pinMode(coinButton, INPUT_PULLUP);
  pinMode(selectButton, INPUT_PULLUP);
  pinMode(cancelButton, INPUT_PULLUP);

  Serial.begin(9600);

  updateLEDs();
  printState();
}

void loop() {

  if (digitalRead(cancelButton) == LOW) {

    currentState = IDLE;
    updateLEDs();
    printState();
    delay(300);

  }

  switch(currentState) {

    case IDLE:

      if (digitalRead(coinButton) == LOW) {

        currentState = COIN_INSERTED;

        updateLEDs();
        printState();

        delay(300);
      }

      break;

    case COIN_INSERTED:

      if (digitalRead(selectButton) == LOW) {

        currentState = ITEM_SELECTED;

        updateLEDs();
        printState();

        delay(300);
      }

      break;

    case ITEM_SELECTED:

      currentState = DISPENSING;

      updateLEDs();
      printState();

      delay(3000);

      currentState = IDLE;

      updateLEDs();
      printState();

      break;

    case DISPENSING:
      break;
  }

}
