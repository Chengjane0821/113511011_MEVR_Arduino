#include <TimerOne.h>

// ===== Pin assignment =====
// Button A + LED A: Timer Interrupt
const int buttonPinA = 2;
const int ledPinA = 8;

// Button B + LED B: Blocking Delay
const int buttonPinB = 4;
const int ledPinB = 9;

// ===== Timer Interrupt ISR =====
void timerISR() {
  int buttonStateA = digitalRead(buttonPinA);

  if (buttonStateA == HIGH) {
    digitalWrite(ledPinA, HIGH);
  } else {
    digitalWrite(ledPinA, LOW);
  }
}

void setup() {
  pinMode(buttonPinA, INPUT);
  pinMode(ledPinA, OUTPUT);

  pinMode(buttonPinB, INPUT);
  pinMode(ledPinB, OUTPUT);

  // 50 ms = 50,000 microseconds
  Timer1.initialize(50000);
  Timer1.attachInterrupt(timerISR);
}

void loop() {
  // Button B uses normal polling
  int buttonStateB = digitalRead(buttonPinB);

  if (buttonStateB == HIGH) {
    digitalWrite(ledPinB, HIGH);
  } else {
    digitalWrite(ledPinB, LOW);
  }

  // Blocking delay
  delay(1000);
}
