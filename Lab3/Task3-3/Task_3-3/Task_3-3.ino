#include <SoftwareSerial.h>

SoftwareSerial bluetooth(10, 11); 
// RX, TX
// Arduino D10 接 HC-05 TX
// Arduino D11 接 HC-05 RX

const int ledPin = 8;

void setup() {
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);       // 給電腦看 debug
  bluetooth.begin(9600);    // HC-05 通訊
}

void loop() {
  if (bluetooth.available() > 0) {
    char data = bluetooth.read();

    Serial.println(data);

    if (data == '1') {
      digitalWrite(ledPin, HIGH);
    }
    else if (data == '0') {
      digitalWrite(ledPin, LOW);
    }
  }
}
