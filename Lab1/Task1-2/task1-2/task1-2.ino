const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

const int buttonPin = 2;
const int potPin = A0;

bool greenOn = false;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(buttonPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  // B：variable resistor
  int val = analogRead(potPin);
  int blueBrightness = map(val, 0, 1023, 0, 255);
  analogWrite(bluePin, blueBrightness);
 
  Serial.print("data is ");
  Serial.println(blueBrightness);
  // R：button
  if (digitalRead(buttonPin) == LOW) {
    analogWrite(redPin, 255);
  } else {
    analogWrite(redPin, 0);
  }

  // G：Serial input
  if (Serial.available() > 0) {
    char input = Serial.read();

    if (input == '1') {
      greenOn = true;
    }

    if (input == '0') {
      greenOn = false;
    }
  }

  if (greenOn) {
    analogWrite(greenPin, 255);
  } else {
    analogWrite(greenPin, 0);
  }
}
