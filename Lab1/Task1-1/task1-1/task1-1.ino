const int ledPin = 11;
const int potPin = A0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int val = analogRead(potPin);        // 0 ~ 1023

  int brightness = map(val, 0, 1023, 0, 255);

  analogWrite(ledPin, brightness);    // 0 ~ 255

  Serial.print("Data is ");
  Serial.println(val);

  delay(1000);
}
