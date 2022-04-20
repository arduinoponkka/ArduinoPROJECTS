#include <HCSR04.h>

HCSR04 hc(5, 6); //initialisation class HCSR04 (trig pin , echo pin)
const int RED = 8;
const int YELLOW = 9;
const int GREEN = 10;

const int RED_WALKER = 3;
const int GREEN_WALKER = 4;

const int WALKER_BUTTON = 2;

float distance = 0.0;
int buttonState = 0;

void setup()
{
    pinMode(RED, OUTPUT);
    pinMode(YELLOW, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(RED_WALKER, OUTPUT);
    pinMode(GREEN_WALKER, OUTPUT);
    pinMode(WALKER_BUTTON, INPUT);
    
    digitalWrite(RED, HIGH);
    digitalWrite(YELLOW, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(RED_WALKER, HIGH);
    digitalWrite(GREEN_WALKER, LOW);
    
    Serial.begin(9600);
}

void loop()
{
   
    distance = hc.dist();
    buttonState = digitalRead(WALKER_BUTTON);
    
    Serial.println(hc.dist()); // return curent distance in serial
    delay(60);                 // we suggest to use over 60ms measurement cycle, in order to prevent trigger signal to the echo signal.

    if(buttonState == HIGH) {
      delay(2000);
      digitalWrite(RED_WALKER, LOW);
      digitalWrite(GREEN_WALKER, HIGH);
      delay(5000);
      digitalWrite(RED_WALKER, HIGH);
      digitalWrite(GREEN_WALKER, LOW);
      delay(1000);
    } else
    if(distance <= 30.0) {
      delay(1000);
      digitalWrite(RED, HIGH);
      digitalWrite(YELLOW, HIGH);
      digitalWrite(GREEN, LOW);

      delay(1000);
      
      while(distance <= 30.0) {
      distance = hc.dist();
      digitalWrite(RED, LOW);
      digitalWrite(YELLOW, LOW);
      digitalWrite(GREEN, HIGH);
      delay(100);
      }

      delay(5000);
      digitalWrite(RED, LOW);
      digitalWrite(YELLOW, HIGH);
      digitalWrite(GREEN, LOW);

      delay(1000);
      digitalWrite(RED, HIGH);
      digitalWrite(YELLOW, LOW);
      digitalWrite(GREEN, LOW);
    }
}
