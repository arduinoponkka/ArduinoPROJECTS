// TEA5767 Example

#include <Keypad.h>
#include <Wire.h>
#include <TEA5767Radio.h>

//char keyA;
//char keyB;
//char keyC;
//char keyD;
//char keyE;

int freqOriginal[4] = {0, 0, 0, 0};
double finalFreq = 0;

//int freqCounter = 0;
char Taajuus[5] = {'0', '8', '7', '0', '\0'};

const int taajuusYlosSwitchStateSwitchPin = 5;
const int taajuusAlasSwitchStateSwitchPin = 7;

double radionTaajuus = 88.0;

int TaajuusYlosSwitchState = 0;
int TaajuusAlasSwitchState = 0;

int edellinenTaajuusYlosSwitchState = 0;
int edellinenTaajuusAlasSwitchState = 0;

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


void setup()
{ 
  Serial.begin(9600);
  pinMode(taajuusYlosSwitchStateSwitchPin, INPUT);
  pinMode(taajuusAlasSwitchStateSwitchPin, INPUT);
  Serial.print("Taajuus: ");
  Serial.print(radionTaajuus);
  Serial.println(" Mhz.");
  
  
  Wire.begin();
  radio.setFrequency(radionTaajuus); // pick your own frequency
}

void loop()
{
  Taajuus[0] = keypad.waitForKey();

  //Serial.print("Taajuus: ");
  Serial.print(Taajuus[0]);
  
  Taajuus[1] = keypad.waitForKey();
  Serial.print(Taajuus[1]);
  
  Taajuus[2] = keypad.waitForKey();
  Serial.print(Taajuus[2]);

  Serial.print('.');
  
  Taajuus[3] = keypad.waitForKey();
  Serial.print(Taajuus[3]);
  Serial.println(" MHz.");
  
  for(int i=0; i < 4; i++) {
    
    switch (Taajuus[i]) {
         case '1':
          freqOriginal[i] = 1;
          break;
    
        case '2':
          freqOriginal[i] = 2;
          break;
    
        case '3':
          freqOriginal[i] = 3;
          break;
    
        case '4':
          freqOriginal[i] = 4;
          break;
    
         case '5':
          freqOriginal[i] = 5;
          break;
    
        case '6':
          freqOriginal[i] = 6;
          break;
    
        case '7':
          freqOriginal[i] = 7;
          break;
    
        case '8':
          freqOriginal[i] = 8;
          break;
    
        case '9':
          freqOriginal[i] = 9;
          break;
    
        case '0':
          freqOriginal[i] = 0;
          break;
    
        default:
          freqOriginal[i] = 0;
        break; 
      }
  }

  finalFreq = 100*freqOriginal[0] + 10*freqOriginal[1] + freqOriginal[2] + 0.1*freqOriginal[3];
  
  

  if(finalFreq >= 87.0 && finalFreq <= 108.0) {
    Serial.print("Taajuus: ");
    Serial.print(finalFreq);
    Serial.println(" Mhz.");
    radio.setFrequency(finalFreq);
  }
  /*
  //------------------------------------------------------------------
  TaajuusYlosSwitchState = digitalRead(taajuusYlosSwitchStateSwitchPin);
  delay(1);

  if(TaajuusYlosSwitchState != edellinenTaajuusYlosSwitchState) {
    if(TaajuusYlosSwitchState == HIGH) {
      if(radionTaajuus < 108.0) {
        radionTaajuus = radionTaajuus + 0.1;
        radio.setFrequency(radionTaajuus);
        Serial.print("Taajuus = ");
        Serial.print(radionTaajuus);
        Serial.println(" Mhz");
      }
    }
  }

  //-------------------------
  TaajuusAlasSwitchState = digitalRead(taajuusAlasSwitchStateSwitchPin);
  delay(1);

  if(TaajuusAlasSwitchState != edellinenTaajuusAlasSwitchState) {
    if(TaajuusAlasSwitchState == HIGH) {
      if(radionTaajuus > 88.0) {
        radionTaajuus = radionTaajuus - 0.1;
        radio.setFrequency(radionTaajuus);
        Serial.print("Taajuus = ");
        Serial.print(radionTaajuus);
        Serial.println(" Mhz");
      }
    }
  }

  edellinenTaajuusYlosSwitchState = TaajuusYlosSwitchState;
  edellinenTaajuusAlasSwitchState = TaajuusAlasSwitchState;
  */
}
  
