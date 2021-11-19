const int pwmPin = 6;
const int potPin = A3;
int potValue = 0;

void setup() {
  // put your setup code here, to run once:
pinMode(pwmPin, OUTPUT);
}

void loop() {
  potValue = analogRead(potPin)/4;
  
  // put your main code here, to run repeatedly:
analogWrite(pwmPin, potValue);

}
