const int redLED = 10;
const int yellowLED = 9;
const int greenLED = 8;
const int buttonPin = 7;

void printState(String state) {
  Serial.print("[");
  Serial.print(millis());
  Serial.print(" ms] ");
  Serial.println(state);
}

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  pinMode(buttonPin, INPUT);

  Serial.begin(9600);
}

void loop() {

  // Check pedestrian button
  if (digitalRead(buttonPin) == HIGH) {

    digitalWrite(redLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);

    printState("PEDESTRIAN - RED");

    delay(8000);

    return;
  }

  // RED for 5 seconds
  digitalWrite(redLED, HIGH);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);

  printState("RED");

  delay(5000);

  // YELLOW for 2 seconds
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, HIGH);
  digitalWrite(greenLED, LOW);

  printState("YELLOW");

  delay(2000);

  // GREEN for 4 seconds
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, HIGH);

  printState("GREEN");

  delay(4000);
}
