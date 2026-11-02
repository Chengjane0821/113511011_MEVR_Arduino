
#include <Servo.h>

Servo servo;

// ==============================
// Pin Settings
// ==============================
#define trig 2
#define echo 3
#define servoPin 5

// ==============================
// PID Parameters
// ==============================
double kp = 1.5;
double ki = 0.0;
double kd = 1.0;

// ==============================
// Target Position
// ==============================
const float setPoint = 8.0;

// ==============================
// Servo Settings
// ==============================
const int baselineAngle = 120;

const int minAngle = 30;
const int maxAngle = 150;

// Larger angle raises sensor end
// Confirmed direction required
const int escapeAngle = 130;

// ==============================
// Safety Settings
// ==============================
const float warningDistance = 12.0;
const float escapeDistance = 9.0;
const float warningSpeed = -1.0;

// ==============================
// Filter Settings
// ==============================
const float filterAlpha = 0.7;
const float velocityAlpha = 0.5;

// ==============================
// Sensor Settings
// ==============================
const float minDistance = 2.0;
const float maxDistance = 35.0;

// ==============================
// PID Variables
// ==============================
double integral = 0.0;

float filteredDistance = 0.0;
float previousDistance = 0.0;
float filteredVelocity = 0.0;

bool firstReading = true;

// ==============================
// Timing
// ==============================
unsigned long previousTime = 0;
const unsigned long controlInterval = 50;

// ==============================
// Setup
// ==============================
void setup() {
  Serial.begin(9600);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(trig, LOW);

  servo.attach(servoPin);
  servo.write(baselineAngle);

  delay(1000);

  previousTime = millis();

  Serial.println("Ball-on-Beam Fast PID Started");
}

// ==============================
// HC-SR04 Distance
// ==============================
float distance() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  unsigned long t =
      pulseIn(echo, HIGH, 10000UL);

  if (t == 0) {
    return -1.0;
  }

  float d = t * 0.0343 / 2.0;

  if (d < minDistance || d > maxDistance) {
    return -1.0;
  }

  return d;
}

// ==============================
// PID Control
// ==============================
void PID() {
  float dis = distance();

  unsigned long currentTime = millis();

  double dt =
      (currentTime - previousTime) / 1000.0;

  previousTime = currentTime;

  // 1. Sensor error
  if (dis < 0) {
    servo.write(baselineAngle);

    firstReading = true;
    integral = 0.0;
    filteredVelocity = 0.0;

    Serial.println("Sensor Error");
    return;
  }

  if (dt <= 0.0) return;

  // 2. Distance filter
  if (firstReading) {
    filteredDistance = dis;
    previousDistance = dis;
    filteredVelocity = 0.0;
    firstReading = false;
  } else {
    filteredDistance =
        filterAlpha * dis +
        (1.0 - filterAlpha) * filteredDistance;
  }

  // 3. Velocity calculation
  float rawVelocity =
      (filteredDistance - previousDistance) / dt;

  filteredVelocity =
      velocityAlpha * rawVelocity +
      (1.0 - velocityAlpha) * filteredVelocity;

  previousDistance = filteredDistance;

  // 4. Emergency escape
  if (filteredDistance <= escapeDistance) {
    servo.write(escapeAngle);

    integral = 0.0;

    Serial.print("EMERGENCY | Distance:");
    Serial.print(filteredDistance);

    Serial.print(" | Servo:");
    Serial.println(escapeAngle);
    return;
  }

  // 5. PID error
  double error = setPoint - filteredDistance;

  // 6. Proportional
  double Pvalue = kp * error;

  // 7. Integral
  integral += error * dt;
  integral = constrain(integral, -20.0, 20.0);

  double Ivalue = ki * integral;

  // 8. Derivative on measurement
  double Dvalue = -kd * filteredVelocity;

  // 9. PID output
  double PIDvalue = Pvalue + Ivalue + Dvalue;

  // 10. Servo angle
  int servoAngle = baselineAngle + PIDvalue;

  servoAngle = constrain(
      servoAngle,
      minAngle,
      maxAngle
  );

  // 11. Early braking
  if (
    filteredDistance <= warningDistance &&
    filteredVelocity < warningSpeed
  ) {
    servoAngle = max(servoAngle, 115);
  }

  // 12. Servo output
  servo.write(servoAngle);

  // 13. Serial Monitor
  Serial.print("Distance:");
  Serial.print(filteredDistance, 2);

  Serial.print(",Target:");
  Serial.print(setPoint, 2);

  Serial.print(",Velocity:");
  Serial.print(filteredVelocity, 2);

  Serial.print(",Error:");
  Serial.print(error, 2);

  Serial.print(",Servo:");
  Serial.println(servoAngle);
}

// ==============================
// Main Loop
// ==============================
void loop() {
  static unsigned long lastControl = 0;

  unsigned long now = millis();

  if (now - lastControl >= controlInterval) {
    lastControl = now;
    PID();
  }
}
