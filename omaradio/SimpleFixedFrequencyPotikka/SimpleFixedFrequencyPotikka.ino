// TEA5767 Example

#include <Wire.h>
#include <TEA5767Radio.h>
//#include <TEA5767.h>

int const potPinKoko = A1;
int const potPinDesi = A0;
int potValKoko;
int potValDesi;

double radionTaajuus = 88.0;
double edellinenTaajuus = 88.1;


TEA5767Radio radio = TEA5767Radio();
//TEA5767 radio = TEA5767();

void setup()
{ 
  Serial.begin(9600);
  Serial.print("Taajuus = ");
  Serial.print(radionTaajuus);
  Serial.println(" Mhz");
  
  Wire.begin();
  radio.setFrequency(radionTaajuus); // pick your own frequency
}

void loop()
{

  potValKoko = analogRead(potPinKoko);
  potValDesi = analogRead(potPinDesi);
  
  

  radionTaajuus = 88.0 + map(potValKoko, 0, 1023, 20, 0) + map(potValDesi, 0, 1023, 9, 0)*0.1;

  if (radionTaajuus != edellinenTaajuus) {
  Serial.print("|"); 
  for(int i = 0; i<=80; i++)
  {
      if((88.0 + i/4) < radionTaajuus)
      {
        Serial.print("#");
      }
      else
      {
        Serial.print("-");  
      }
  }

  Serial.print("|  ");
  Serial.print(radionTaajuus);
  Serial.println(" MHz");
  radio.setFrequency(radionTaajuus);
  /*Serial.print("potValKoko: ");
  Serial.print(potValKoko);

  Serial.print(", potValDesi: ");
  Serial.print(potValDesi);
  
  if(radionTaajuus <= 108.0)
  {
  Serial.print(" , taajuus: ");
  Serial.println(radionTaajuus);
  radio.setFrequency(radionTaajuus);
  }*/
  }
 edellinenTaajuus = radionTaajuus;
  
  delay(100);
 
}
  
