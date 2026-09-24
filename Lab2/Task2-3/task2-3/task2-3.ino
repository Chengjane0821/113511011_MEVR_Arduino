
const int buttonPinA = 2;   // Arduino Uno interrupt pin
const int ledPinA = 13;

volatile bool ledStateA = false;


const int buttonPinB = 4;
const int ledPinB = 12;

bool ledStateB = false;
int lastButtonStateB = HIGH;

void setup() {
  // A
  pinMode(ledPinA, OUTPUT);
  pinMode(buttonPinA, INPUT_PULLUP);

  attachInterrupt(
    digitalPinToInterrupt(buttonPinA),
    buttonISR,
    FALLING
  );

  // B
  pinMode(ledPinB, OUTPUT);
  pinMode(buttonPinB, INPUT_PULLUP);
}

void buttonISR() {
  ledStateA = !ledStateA;
  digitalWrite(ledPinA, ledStateA);
}

void loop() {


  int currentButtonStateB = digitalRead(buttonPinB);

  // 偵測 HIGH -> LOW，代表按下按鈕
  if (lastButtonStateB == HIGH &&
      currentButtonStateB == LOW) {

    ledStateB = !ledStateB;
    digitalWrite(ledPinB, ledStateB);
  }

  // 記住這一次的狀態
  lastButtonStateB = currentButtonStateB;

  // 模擬 Arduino 很忙
  delay(2000);
}
