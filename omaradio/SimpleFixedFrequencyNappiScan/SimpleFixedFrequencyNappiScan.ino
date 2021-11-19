// TEA5767 Example

#include <Wire.h>
// #include <TEA5767Radio.h>
#include <TEA5767.h>

const int taajuusYlosSwitchStateSwitchPin = 5;
const int taajuusAlasSwitchStateSwitchPin = 7;

float radionTaajuus = 88.0;

int TaajuusYlosSwitchState = 0;
int TaajuusAlasSwitchState = 0;

int edellinenTaajuusYlosSwitchState = 0;
int edellinenTaajuusAlasSwitchState = 0;

unsigned char buf[5];
unsigned int counter = 0, btn_counter = 0;
unsigned char level = 0;

TEA5767 radio;

// TEA5767Radio radio = TEA5767Radio();

void setup()
{ 
Wire.begin();
  
  Serial.begin(9600);
  pinMode(taajuusYlosSwitchStateSwitchPin, INPUT);
  pinMode(taajuusAlasSwitchStateSwitchPin, INPUT);
  Serial.print("Taajuus = ");
  Serial.print(radionTaajuus);
  Serial.println(" Mhz");
  
  
  radio.init();
  radio.set_frequency(radionTaajuus);
  DispSigStrenght();
 // radio.setFrequency(radionTaajuus); // pick your own frequency
}

void loop()
{
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
  
}
  
