const int buttonPin = 2;
const int ledPin = 11;
int buttonState = 1;
void setup() {
pinMode(ledPin, OUTPUT);
pinMode(buttonPin, INPUT);
}
void loop() {
buttonState = digitalRead(buttonPin);
if (buttonState == 0) {
digitalWrite(ledPin, HIGH);
} else {
digitalWrite(ledPin, LOW);
}
}
