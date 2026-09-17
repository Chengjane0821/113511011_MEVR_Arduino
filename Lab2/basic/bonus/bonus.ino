#include <Servo.h>

Servo myservo;

void setup() {
  myservo.attach(9);  
  myservo.write(90);     

  Serial.begin(9600);

  Serial.println("Enter angle (0~180):");
}

void loop() {
  if (Serial.available() > 0) {

    int data = Serial.parseInt();

    data = constrain(data, 0, 180);
    myservo.write(data);
    Serial.print("Angle = ");
    Serial.println(data);

    while (Serial.available() > 0) {
      Serial.read();
    }

    Serial.println("Enter angle (0~180):");
  }
}
