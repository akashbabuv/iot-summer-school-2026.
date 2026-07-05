/*
Project : Serial Command Interface
Author  : Akash Babu
*/

const int led = LED_BUILTIN;

bool ledState = false;
int blinkCounter = 0;

void setup() {

  pinMode(led, OUTPUT);

  Serial.begin(9600);

  Serial.println("===== Serial Command Interface =====");
  Serial.println("Commands:");
  Serial.println("LED_ON");
  Serial.println("LED_OFF");
  Serial.println("BLINK_X  (Example: BLINK_5)");
  Serial.println("STATUS");
  Serial.println("RESET");
}

void loop() {

  if (Serial.available()) {

    String command = Serial.readStringUntil('\n');
    command.trim();

    // LED ON
    if (command == "LED_ON") {

      digitalWrite(led, HIGH);
      ledState = true;

      Serial.println("LED Turned ON");
    }

    // LED OFF
    else if (command == "LED_OFF") {

      digitalWrite(led, LOW);
      ledState = false;

      Serial.println("LED Turned OFF");
    }

    // STATUS
    else if (command == "STATUS") {

      Serial.print("LED State : ");

      if (ledState)
        Serial.println("ON");
      else
        Serial.println("OFF");

      Serial.print("Blink Count : ");
      Serial.println(blinkCounter);
    }

    // RESET
    else if (command == "RESET") {

      blinkCounter = 0;

      Serial.println("Blink Counter Reset");
    }

    // BLINK_X
    else if (command.startsWith("BLINK_")) {

      int times = command.substring(6).toInt();

      if (times >= 1 && times <= 9) {

        for (int i = 0; i < times; i++) {

          digitalWrite(led, HIGH);
          delay(300);

          digitalWrite(led, LOW);
          delay(300);

          blinkCounter++;
        }

        Serial.print("LED Blinked ");
        Serial.print(times);
        Serial.println(" Times");
      }

      else {

        Serial.println("ERROR: X must be between 1 and 9");

      }

    }

    // Unknown Command
    else {

      Serial.println("ERROR: Unknown command");

    }

  }

}
