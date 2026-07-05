#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

const int trigPin = 9;
const int echoPin = 10;
const int ldrPin = A0;

void setup() {

  Serial.begin(9600);

  dht.begin();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void loop() {

  float humidity = dht.readHumidity();
  float tempC = dht.readTemperature();

  int lightRaw = analogRead(ldrPin);

  int lightPercent = map(lightRaw,0,1023,0,100);

  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin,LOW);

  long duration = pulseIn(echoPin,HIGH);

  float distance = (duration*0.034)/2;

  Serial.println("=== SENSOR LOG ===");

  Serial.print("Time      : ");
  Serial.print(millis());
  Serial.println(" ms");

  Serial.print("Temp      : ");
  Serial.print(tempC);
  Serial.print(" C | Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  Serial.print("Light     : ");
  Serial.print(lightPercent);
  Serial.print("% ");

  if(lightPercent>60)
      Serial.println("(Bright)");
  else
      Serial.println("(Dark)");

  Serial.print("Distance  : ");
  Serial.print(distance);
  Serial.println(" cm");

  Serial.println("==================");

  delay(5000);

}
