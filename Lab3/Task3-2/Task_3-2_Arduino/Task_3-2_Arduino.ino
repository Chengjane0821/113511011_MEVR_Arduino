const int ledPin = 8;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    char data = Serial.read();

    if (data == '1') {
      digitalWrite(ledPin, HIGH);
    }

    if (data == '0') {
      digitalWrite(ledPin, LOW);
    }
  }
}
