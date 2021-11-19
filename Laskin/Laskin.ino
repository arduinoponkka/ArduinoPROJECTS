/* @file HelloKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates the simplest use of the matrix Keypad library.
|| #
*/
#include <Keypad.h>
#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>

LiquidCrystal_PCF8574 lcd(0x27); // set the LCD address to 0x27 for a 16 chars and 2 line display

int riviNro = 0;
int show = -1;
char keyA;
char keyB;

bool loppuA = false;
bool loppuB = false;
bool loppuC = false;
bool loppuD = false;

char keyTahti;
char keyHastag;

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {7, 2, 3, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 8, 4}; //connect to the column pinouts of the keypad

int lukuA = 0;
int lukuB = 0;
int vastaus = 0;
int vastausA = 0;
int vastausB = 0;
int vastausC = 0;
int vastausD = 0;

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  int error;
  
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(0x27);
  error = Wire.endTransmission();
  lcd.begin(20, 4); // initialize the lcd
}
  
void loop(){
  
  keyA = keypad.waitForKey();
  lcd.setBacklight(255);
  //lcd.home();

  
  if(riviNro == 0) {
  lcd.setCursor(0, 0);
  }

if(riviNro == 1) {
  lcd.setCursor(0, 1);
  }

  if(riviNro == 2) {
  lcd.setCursor(0, 2);
  }

  if(riviNro == 3) {
  lcd.setCursor(0, 3);
  }

  if(riviNro == 4) {

  riviNro = 0;
    
  vastausA=0;
  vastausB=0;
  vastausC=0;
  vastausD=0;

  loppuA = false;
  loppuB = false;
  loppuC = false;
  loppuD = false;
    
  lcd.clear();
  lcd.setCursor(0, 0);
  }
  
  lcd.print(keyA);
  Serial.print(keyA);
  
  switch (keyA) {
    case '1':
      lukuA = 1;
      break;

    case '2':
      lukuA = 2;
      break;

    case '3':
      lukuA = 3;
      break;

    case '4':
      lukuA = 4;
      break;

     case '5':
      lukuA = 5;
      break;

    case '6':
      lukuA = 6;
      break;

    case '7':
      lukuA = 7;
      break;

    case '8':
      lukuA = 8;
      break;

    case '9':
      lukuA = 9;
      break;

    case '0':
      lukuA = 0;
      break;

    default:
      lukuA = 100;
    break;
  }

  
  keyTahti = keypad.waitForKey();

  Serial.print(keyTahti);
  lcd.print(keyTahti);
  keyB = keypad.waitForKey();
  lcd.print(keyB);
  

  Serial.print(keyB);
  
    switch (keyB) {
    case '1':
      lukuB = 1;
      break;

    case '2':
      lukuB = 2;
      break;

    case '3':
      lukuB = 3;
      break;

    case '4':
      lukuB = 4;
      break;

     case '5':
      lukuB = 5;
      break;

    case '6':
      lukuB = 6;
      break;

    case '7':
      lukuB = 7;
      break;

    case '8':
      lukuB = 8;
      break;

    case '9':
      lukuB = 9;
      break;

    case '0':
      lukuB = 0;
      break;

    default:
      lukuB = 100;
    break;
  }

  keyHastag = keypad.waitForKey();
  lcd.print("=");
  Serial.println("=");
  
  if((keyTahti == '*') && (keyHastag == '#')) {

    if(riviNro == 0) {
    vastausA = lukuA*lukuB;
    loppuA = true;
    riviNro = 1;
    } 

    else if(riviNro == 1) {
    vastausB = lukuA*lukuB;
    loppuB = true;
    riviNro = 2;
    } 

    else if(riviNro == 2) {
    vastausC = lukuA*lukuB;
    loppuC = true;
    riviNro = 3;
    } 

    else if(riviNro == 3) {
    vastausD = lukuA*lukuB;
    loppuD = true;
    riviNro = 4;
    }
     
    Serial.print(lukuA);
    Serial.print(" * ");
    Serial.print(lukuB);
    Serial.print(" = ");
    vastaus = lukuA*lukuB;
    Serial.println(vastaus);
    lcd.setCursor(4, 0);
    
    if((vastausA != 0 ) && (loppuA == true))
    
    lcd.print(vastausA);
    
    lcd.setCursor(4, 1);
    
    if((vastausB != 0 ) && (loppuB == true))
    lcd.print(vastausB);
  
    lcd.setCursor(4, 2);
 
    if((vastausC != 0 ) && (loppuC == true))
    lcd.print(vastausC);
    
    lcd.setCursor(4, 3);

    if((vastausD != 0 ) && (loppuD == true)) {
    lcd.print(vastausD);
    
    }
     
  }

}
