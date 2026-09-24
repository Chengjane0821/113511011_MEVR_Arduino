const int PIN_1A = 8;
const int PIN_2A = 9;

void setup() {
  pinMode(PIN_1A, OUTPUT);
  pinMode(PIN_2A, OUTPUT);
}

void loop() {
  digitalWrite(PIN_1A, HIGH);
  digitalWrite(PIN_2A, LOW);
}
