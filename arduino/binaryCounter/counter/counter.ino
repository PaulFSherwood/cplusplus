int pin0 = 13;
int pin1 = 12;
int pin2 = 11;
int pin3 = 10;
int speed = 500;
int speed2 = 50;
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
  delay(speed2);
}
void loop() {
  // all outputs should be low
  // loop through the array once if it is a 1 flip it to a 0 and move on
  // if it is a 0 flip it to a 1 and stop
  int arr[] = {0, 0, 0, 0};

  for (int i = 0000; i <= 15; i++) {
    String res = toBinary(i);
    if (res.length() == 3) {
      res = '0' + res;
    }
    if (res.length() == 2) {
      res = "00" + res;
    }
    if (res.length() == 1) {
      res = "000" + res;
    }
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
  }
  delay(speed);
}
