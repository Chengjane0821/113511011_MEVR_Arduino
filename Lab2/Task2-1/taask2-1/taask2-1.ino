const int POT_PIN = A0;

const int PIN_EN = 5;   // L293D pin 1 (Enable)
const int PIN_1A = 8;   // L293D pin 2
const int PIN_2A = 9;   // L293D pin 7

void setup() {
  pinMode(PIN_EN, OUTPUT);
  pinMode(PIN_1A, OUTPUT);
  pinMode(PIN_2A, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int value = analogRead(POT_PIN);

  int speedValue = 0;

  
  if (value >= 480 && value <= 543) {

    digitalWrite(PIN_1A, LOW);
    digitalWrite(PIN_2A, LOW);

    analogWrite(PIN_EN, 0);
  }


  else if (value < 480) {

    digitalWrite(PIN_1A, LOW);
    digitalWrite(PIN_2A, HIGH);

    speedValue = map(value, 479, 0, 0, 255);

    analogWrite(PIN_EN, speedValue);
  }

 
  else {

    digitalWrite(PIN_1A, HIGH);
    digitalWrite(PIN_2A, LOW);

    speedValue = map(value, 544, 1023, 0, 255);

    analogWrite(PIN_EN, speedValue);
  }

  Serial.print("Potentiometer = ");
  Serial.print(value);

  Serial.print("   Speed = ");
  Serial.println(speedValue);

  delay(20);
}
