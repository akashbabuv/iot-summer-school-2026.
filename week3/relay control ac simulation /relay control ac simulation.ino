#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

const int relayPin = 8;
const int ledPin = 9;
const int buttonPin = 3;

bool relayState = false;
bool manualMode = false;
bool lastButton = HIGH;

void printStatus(float temp)
{
  Serial.print("Temperature : ");
  Serial.print(temp);
  Serial.print(" C | Relay : ");

  if(relayState)
    Serial.println("ON");
  else
    Serial.println("OFF");
}

void setup()
{
  Serial.begin(9600);

  dht.begin();

  pinMode(relayPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  pinMode(buttonPin, INPUT_PULLUP);

  Serial.println("Relay Control System Started");
}

void loop()
{
  float temp = dht.readTemperature();

  bool button = digitalRead(buttonPin);

  // Manual Override
  if(button == LOW && lastButton == HIGH)
  {
    manualMode = !manualMode;

    relayState = !relayState;

    digitalWrite(relayPin, relayState);
    digitalWrite(ledPin, relayState);

    Serial.println("Manual Override");

    printStatus(temp);

    delay(200);
  }

  lastButton = button;

  // Automatic Mode
  if(!manualMode)
  {

    if(temp > 32 && !relayState)
    {
      relayState = true;

      digitalWrite(relayPin,HIGH);
      digitalWrite(ledPin,HIGH);

      Serial.println("Relay ON");

      printStatus(temp);
    }

    else if(temp < 28 && relayState)
    {
      relayState = false;

      digitalWrite(relayPin,LOW);
      digitalWrite(ledPin,LOW);

      Serial.println("Relay OFF");

      printStatus(temp);
    }

  }

  delay(1000);

}
