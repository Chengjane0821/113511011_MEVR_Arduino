#include <TimerOne.h>

int timercount = 0;

void timer_int() {
    timercount++;
}

void setup() {
    Serial.begin(9600);

    Timer1.initialize(500000);
    Timer1.attachInterrupt(timer_int);
}

void loop() {
    Serial.println(timercount);
}
