#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

const int pushButton = 3;
const int redLed = 2;
int StartLotto = 0;
int previousStartLotto = 0;
int enable = 0;
int lotto_taulu[6];
long randNumber;
int riveja_arvottu = 0;
int viking_numero = 0;
int plus_numero = 0;

LiquidCrystal_PCF8574 lcd(0x27); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {

  int error;
  Serial.begin(9600);
  Wire.beginTransmission(0x27);
  error = Wire.endTransmission();
  lcd.begin(20, 4); // initialize the lcd

  lcd.setCursor(0, 0);

  for (int i = 0; i < 6; i++) {
    lotto_taulu[i] = 0;
  }

  randomSeed(512);
  pinMode(pushButton, INPUT);
  pinMode(redLed, OUTPUT);

  Wire.begin();

}

void loop() {

  StartLotto = digitalRead(pushButton);
  delay(100);

  if (StartLotto != previousStartLotto) {
    if (StartLotto == HIGH) {
      enable = !enable;

    }
  }

  if (enable == 1) {
    digitalWrite(redLed, HIGH);

    for (int i = 0; i < 6; i++) {
      while (true) {
        randNumber = random(49);
        for (int j = 0; j <= i; j++) {
          while (lotto_taulu[j] == randNumber) { //if muutettu while
            randNumber = random(49);
            // en ole varma toimiiko
          }
        }
        if (randNumber != 0) {
          break;
        }
      }

      lotto_taulu[i] = randNumber;

    }

    for (int i = 0; i < 5; i++) {
      for (int j = i + 1; j < 6; j++) {
        if (lotto_taulu[i] > lotto_taulu[j]) {
          int temp = lotto_taulu[i];
          lotto_taulu[i] = lotto_taulu[j];
          lotto_taulu[j] = temp;
        }
      }
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Viking Lotto:");
    lcd.setCursor(0, 1);

    Serial.print("Numerot: ");

    for (int i = 0; i < 6; i++) {
      if (lotto_taulu[i] < 10) {
        lcd.print(" ");
        Serial.print(" ");
      }
      lcd.print(lotto_taulu[i]);
      lcd.print(" ");
      Serial.print(lotto_taulu[i]);

      if (i < 5)
        Serial.print(", ");
    }
    riveja_arvottu++;

    lcd.setCursor(0, 2);

    while (viking_numero == 0) {
      viking_numero = random(6);
    }

    while (plus_numero == 0) {
      plus_numero = random(49);
    }

    Serial.print(" Viking: ");
    Serial.print(viking_numero);

    Serial.print(" Plus: ");
    if (plus_numero < 10)
      Serial.print(" ");
    Serial.print(plus_numero);

    lcd.print("Viking: ");

    if (viking_numero < 10)
      lcd.print(" ");
    lcd.print(viking_numero);
    lcd.print(", Plus: ");

    if (plus_numero < 10)
      lcd.print(" ");
    lcd.print(plus_numero);

    viking_numero = 0;
    plus_numero = 0;

    lcd.setCursor(0, 3);
    lcd.print("Riveja: ");
    lcd.print(riveja_arvottu);

    Serial.print(" Riveja: ");
    Serial.println(riveja_arvottu);


    //Serial.println("");

  }
  else {
    digitalWrite(redLed, LOW);
  }

  previousStartLotto = StartLotto;


}
