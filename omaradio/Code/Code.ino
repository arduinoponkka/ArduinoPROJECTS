#include <TEA5767.h>
#include <Wire.h>
#include <JC_Button.h>
#include <LiquidCrystal.h>

float frequency = 76.0;
unsigned char buf[5];
unsigned int counter = 0, btn_counter = 0;
unsigned char level = 0;

TEA5767 radio;
const byte RS = 7, EN = 6, D4 = 4, D5 = 5, D6 = 2, D7 = 3;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);


byte L1[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111
};

byte L2[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111
};

byte L3[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111,
  B11111
};

byte L4[] = {
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

byte L5[] = {
  B00000,
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

void setup() {
  Wire.begin();

  lcd.begin(8, 2);
  lcd.createChar(0, L1);
  lcd.createChar(1, L2);
  lcd.createChar(2, L3);
  lcd.createChar(3, L4);
  lcd.createChar(4, L5);
  lcd.clear();

  radio.init();
  radio.set_frequency(frequency);
  DispSigStrenght();
  Freq_Mono_Stereo(frequency);

  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);

}

void loop() {

  if (digitalRead(11) == 0 && frequency < 108.0)
  {
    btn_counter++;
    if (btn_counter == 5000) {
      frequency += 0.1;
      radio.set_frequency(frequency);
      Freq_Mono_Stereo(frequency);
      btn_counter = 0;
    }
  }

  if (digitalRead(12) == 0 && frequency > 76.0)
  {
    btn_counter++;
    if (btn_counter == 5000) {
      frequency -= 0.1;
      radio.set_frequency(frequency);
      Freq_Mono_Stereo(frequency);
      btn_counter = 0;
    }
  }

  if (digitalRead(10) == 0)
  {
    btn_counter++;
    if (btn_counter == 5000) {
      if (frequency >= 108.0)
      {
        frequency = 76.0;
        radio.set_frequency(frequency);
      }
      radio.read_status(buf);
      radio.search_up(buf);
      radio.process_search (buf, TEA5767_SEARCH_DIR_UP);
      frequency =  floor (radio.frequency_available (buf) / 100000 + .5) / 10;
      Freq_Mono_Stereo(frequency);
      btn_counter = 0;
    }

  }

  counter ++;

  if (counter == 15000)
  {
    counter = 0;
    DispSigStrenght();
  }

}


void DispSigStrenght()
{

  lcd.setCursor(0, 1);
  radio.read_status(buf);
  level = radio.signal_level(buf);
  switch (level)
  {

    case 1 ... 3:
      lcd.print("\x08");
      lcd.setCursor(1, 1);
      lcd.print("    ");
      break;

    case 4 ... 6:
      lcd.print("\x08\x01");
      lcd.setCursor(2, 1);
      lcd.print("   ");
      break;

    case 7 ... 9:
      lcd.print("\x08\x01\x02");
      lcd.setCursor(3, 1);
      lcd.print("  ");
      break;

    case 10 ... 12:
      lcd.print("\x08\x01\x02\x03");
      lcd.setCursor(4, 1);
      lcd.print(" ");
      break;

    case 13 ... 15:
      lcd.print("\x08\x01\x02\x03\x04");
      break;
  }
}


void Freq_Mono_Stereo(float freq)
{

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(String(frequency, 1) + "MHz");

  radio.read_status(buf);
  if (radio.stereo(buf))
  {
    lcd.setCursor(6, 1);
    lcd.print("ST");
  }
  else
  {
    lcd.setCursor(6, 1);
    lcd.print("MN");
  }
}
