

bool countUP = true;
int timer = 1000;
int slowBlink = 150;
int fastBlink = 50;
int pinNumber = 13;

void blink(int pin, int timeDelay) {
  digitalWrite(pin, HIGH);
  delay(timeDelay);
  digitalWrite(pin, LOW);
  delay(timeDelay);  
}

void s(int pin) {
  for (int i = 3; i > 0; i--)
  blink(pin, fastBlink);
}

void o(int pin) {
  for (int i = 3; i > 0; i--)
  blink(pin, slowBlink);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(pinNumber, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  s(pinNumber);
  delay(500);
  o(pinNumber);
  delay(500);
  s(pinNumber);
  delay(timer);
}
