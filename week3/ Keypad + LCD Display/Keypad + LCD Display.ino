#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27,16,2);

// Keypad
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS]={
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

byte rowPins[ROWS]={9,8,7,6};
byte colPins[COLS]={5,4,3,2};

Keypad keypad=Keypad(makeKeymap(keys),rowPins,colPins,ROWS,COLS);

const int greenLED=10;
const int redLED=11;
const int buzzer=12;

String password="1234";
String input="";

int attempts=0;

void setup(){

Serial.begin(9600);

pinMode(greenLED,OUTPUT);
pinMode(redLED,OUTPUT);
pinMode(buzzer,OUTPUT);

lcd.init();
lcd.backlight();

lcd.print("ENTER PIN:");
}

void loop(){

char key=keypad.getKey();

if(key){

lcd.setCursor(input.length(),1);
lcd.print("*");

input+=key;

if(input.length()==4){

if(input==password){

lcd.clear();
lcd.print("ACCESS");
lcd.setCursor(0,1);
lcd.print("GRANTED");

digitalWrite(greenLED,HIGH);

Serial.println("ACCESS GRANTED");

delay(3000);

digitalWrite(greenLED,LOW);

attempts=0;

}

else{

lcd.clear();
lcd.print("ACCESS");
lcd.setCursor(0,1);
lcd.print("DENIED");

digitalWrite(redLED,HIGH);

tone(buzzer,1000,500);

Serial.println("ACCESS DENIED");

delay(2000);

digitalWrite(redLED,LOW);

attempts++;

if(attempts>=3){

lcd.clear();
lcd.print("LOCKED");

Serial.println("LOCKED 10 SECONDS");

delay(10000);

attempts=0;

}

}

input="";

lcd.clear();
lcd.print("ENTER PIN:");

}

}

}
