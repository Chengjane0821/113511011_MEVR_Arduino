#include <Servo.h>

Servo myservo;

const int trigPin = 7;
const int echoPin = 6;

void setup() {
  myservo.attach(9);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.0343 / 2;
  int angle = map(distance, 5, 50, 0, 180);

  angle = constrain(angle, 0, 180);

  myservo.write(angle);

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm, Angle: ");
  Serial.println(angle);

  delay(100);
}
