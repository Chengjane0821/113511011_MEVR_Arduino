const int buttonPinA = 2;
const int ledPinA = 13;

volatile bool ledStateA = false;

void setup() {
  pinMode(ledPinA, OUTPUT);
  pinMode(buttonPinA, INPUT_PULLUP);

  attachInterrupt(
    digitalPinToInterrupt(buttonPinA),
    buttonISR,
    FALLING
  );
}

void buttonISR() {
  ledStateA = !ledStateA;
  digitalWrite(ledPinA, ledStateA);
}

void loop() {
}
