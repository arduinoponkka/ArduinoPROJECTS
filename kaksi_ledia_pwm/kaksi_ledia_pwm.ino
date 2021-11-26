const int red_led = 5;
const int green_led = 9;
const int potPin = A1;
int potValue = 0;
int ledValue = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  ledValue = 0;

  // Valon sykkiminen while silmukalla

  while (ledValue < 256) {
    potValue = analogRead(potPin);

    analogWrite(red_led, ledValue);
    analogWrite(green_led, (255 - ledValue));
    delay(potValue / 200);
    ledValue++;
    //if(ledValue == 256)
    //  break;
  }

  Serial.print("potValue = ");
  Serial.print(potValue);
  Serial.print(", ledValue = ");
  Serial.println(ledValue);

  ledValue = 255;

  while (ledValue >= 0) {
    potValue = analogRead(potPin);

    analogWrite(red_led, ledValue);
    analogWrite(green_led, (255 - ledValue));
    delay(potValue / 200);
    ledValue--;
    //if(ledValue == 0)
    //  break;
  }

  Serial.print("potValue = ");
  Serial.print(potValue);
  Serial.print(", ledValue = ");
  Serial.println(ledValue);

  // Valon sykkiminen for silmukalla

  /*
    for(int i=0; i<=255; i++){
    potValue = analogRead(potPin);
    analogWrite(red_led, i);
    analogWrite(green_led, (255-i));
    delay(potValue/50);
    }

    for(int i=255; i>=0; i--){
    potValue = analogRead(potPin);
    analogWrite(red_led, i);
    analogWrite(green_led, (255-i));
    delay(potValue/50);
    }
  */
}
