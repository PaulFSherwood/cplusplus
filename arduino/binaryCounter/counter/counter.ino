int pin0 = 13;
int pin1 = 12;
int pin2 = 11;
int pin3 = 10;
int pin4 = 9;
int pin5 = 8;
int speed = 50;
int speed2 = 50;
int inputPin = A0;
int readVal;
float V2;

String toBinary(int n) {
  if (n==0) return "0";
  else if (n == 1) return "1";
  else if (n%2 == 0) return toBinary(n/2) + "0";
  else if (n%2 != 0) return toBinary(n/2) + "1";
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pin0, OUTPUT);
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(pin5, OUTPUT);
}
void changePin(int pin, int LH) {  
  if (pin == 0) {
    digitalWrite(pin0, LH);
  }
  if (pin == 1) {
    digitalWrite(pin1, LH);
  }
  if (pin == 2) {
    digitalWrite(pin2, LH);
  }
  if (pin == 3) {
    digitalWrite(pin3, LH);
  }
  if (pin == 4) {
    digitalWrite(pin4, LH);
  }
  if (pin == 5) {
    digitalWrite(pin5, LH);
  }
  delay(speed2);
}
void loop() {
  // all outputs should be low
  // loop through the array once if it is a 1 flip it to a 0 and move on
  // if it is a 0 flip it to a 1 and stop
  int arr[] = {0, 0, 0, 0, 0, 0};
  
  readVal = analogRead(inputPin);
  V2 = (5./1023.) * readVal;
  Serial.println(V2);
  for (int i = 000000; i <= 63; i++) {
    String res = toBinary(i);
    if (res.length() == 5) {
      res = '0' + res;
    }
    if (res.length() == 4) {
      res = "00" + res;
    }
    if (res.length() == 3) {
      res = "000" + res;
    }
    if (res.length() == 2) {
      res = "0000" + res;
    }
    if (res.length() == 1) {
      res = "00000" + res;
    }
    // Serial.println(res);
    // delay(speed2);
    // Serial.print(res);    
    // Serial.println();
    if (res[0] == '1') {
      changePin(0, 1);
    } else {
      changePin(0, 0);
    }
    if (res[1] == '1') {
      changePin(1, 1);
    } else {
      changePin(1, 0);
    }
    if (res[2] == '1') {
      changePin(2, 1);
    } else {
      changePin(2, 0);
    }
    if (res[3] == '1') {
      changePin(3, 1);
    } else {
      changePin(3, 0);
    }
    if (res[4] == '1') {
      changePin(4, 1);
    } else {
      changePin(4, 0);
    }
    if (res[5] == '1') {
      changePin(5, 1);
    } else {
      changePin(5, 0);
    }
  }
  delay(speed);
}
