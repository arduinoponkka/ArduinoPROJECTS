// TEA5767 Example

#include <Keypad.h>
#include <Wire.h>
#include <TEA5767Radio.h>
#include <LiquidCrystal_PCF8574.h>

int kanavaNum = 1;
//int freqOriginal[4] = {0, 0, 0, 0};
double finalFreq[4] = {97.3, 100.3, 101.0, 104.8};

//char Taajuus[5] = {'0', '8', '7', '0', '\0'};

//double radionTaajuus = 88.0;

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

TEA5767Radio radio = TEA5767Radio();

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

LiquidCrystal_PCF8574 lcd(0x27); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{ 
  int error;
  Serial.begin(9600);
  Wire.beginTransmission(0x27);
  error = Wire.endTransmission();
  lcd.begin(20, 4); // initialize the lcd
  lcd.clear();
  lcd.setCursor(0, 0);
  
  lcd.print("1. Suomi: ");
  lcd.print(finalFreq[0]);
  //lcd.print(" Mhz.");
  
  Serial.print("1. Suomi: ");
  Serial.print(finalFreq[0]);
  Serial.println(" Mhz.");

  lcd.setCursor(0, 1);
  lcd.print("2. Vega: ");
  lcd.print(finalFreq[1]);
  //lcd.print(" Mhz.");
  
  lcd.setCursor(0, 2);
  lcd.print("3. Melodia: ");
  lcd.print(finalFreq[2]);
  //lcd.print(" Mhz.");
  
  lcd.setCursor(0, 3);
  lcd.print("4. Nova: ");
  lcd.print(finalFreq[3]);
  //lcd.print(" Mhz.");
  
  Wire.begin();
  radio.setFrequency(finalFreq[0]); // pick your own frequency
}

void loop()
{
  kanavaNum = keypad.waitForKey();

  switch (kanavaNum) {
        case '1':
          Serial.print("1. Radio Suomi: ");
          Serial.print(finalFreq[0]);
          Serial.println(" Mhz.");
          radio.setFrequency(finalFreq[0]);
          break;
    
        case '2':
          Serial.print("2. Radio Vega: ");
          Serial.print(finalFreq[1]);
          Serial.println(" Mhz.");
          radio.setFrequency(finalFreq[1]);
          break;
    
        case '3':
          Serial.print("3. Radio Melodia: ");
          Serial.print(finalFreq[2]);
          Serial.println(" Mhz.");
          radio.setFrequency(finalFreq[2]);
          break;
    
        case '4':
          Serial.print("4. Radio Nova: ");
          Serial.print(finalFreq[3]);
          Serial.println(" Mhz.");
          radio.setFrequency(finalFreq[3]);
          break;
        default:
          Serial.print("1. Radio Suomi: ");
          Serial.print(finalFreq[0]);
          Serial.println(" Mhz.");
          radio.setFrequency(finalFreq[0]);
          break;
  }
}
  
