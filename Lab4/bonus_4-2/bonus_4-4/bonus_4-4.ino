
#include <Servo.h>

Servo servo;

#define trig 2
#define echo 3

// ==============================
// PID Parameters
// ==============================
double kp = 1.5;
double ki = 0.0;
double kd = 1.0;

// ==============================
// Target Position
// ==============================
const float setPoint = 15.0;

// ==============================
// Servo Settings
// ==============================
const int baselineAngle = 121;

const int minAngle = 115;
const int maxAngle = 127;

// 125° 時超音波端升高
// 因此增加角度 = 遠離超音波
const int escapeAngle = 127;

// ==============================
// Safety Settings
// ==============================
const float warningDistance = 12.0;
const float escapeDistance = 9.0;

// 朝超音波移動的速度門檻
const float warningSpeed = -1.0;

// ==============================
// Filter Settings
// ==============================
const float filterAlpha = 0.4;

// 速度濾波係數
const float velocityAlpha = 0.3;

// ==============================
// PID Variables
// ==============================
double integral = 0.0;

float filteredDistance = 0.0;
float previousDistance = 0.0;
float filteredVelocity = 0.0;

bool firstReading = true;

unsigned long previousTime = 0;


// ==============================
// Setup
// ==============================
void setup() {

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  servo.attach(5);

  Serial.begin(9600);

  // 啟動時維持水平
  servo.write(baselineAngle);

  delay(1000);

  previousTime = millis();
}


// ==============================
// Main Loop
// ==============================
void loop() {

  PID();

  delay(50);
}


// ==============================
// HC-SR04 Distance
// ==============================
float distance() {

  digitalWrite(trig, LOW);
  delayMicroseconds(4);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);

  digitalWrite(trig, LOW);

  unsigned long t =
      pulseIn(echo, HIGH, 30000);

  if (t == 0) {
    return -1.0;
  }

  return t * 0.0343 / 2.0;
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


  // ==========================
  // 1. Sensor Timeout
  // ==========================
  if (dis < 0) {

    servo.write(baselineAngle);

    firstReading = true;
    integral = 0.0;
    filteredVelocity = 0.0;

    Serial.println("Sensor timeout");

    return;
  }

  if (dt <= 0.0) {
    return;
  }


  // ==========================
  // 2. Distance Filter
  // ==========================
  if (firstReading) {

    filteredDistance = dis;
    previousDistance = dis;

    filteredVelocity = 0.0;

    firstReading = false;
  }

  else {

    filteredDistance =
        filterAlpha * dis +
        (1.0 - filterAlpha) * filteredDistance;
  }


  // ==========================
  // 3. Calculate Ball Velocity
  // ==========================

  float rawVelocity =
      (filteredDistance - previousDistance) / dt;

  filteredVelocity =
      velocityAlpha * rawVelocity +
      (1.0 - velocityAlpha) * filteredVelocity;

  previousDistance = filteredDistance;

  // Velocity:
  // Negative = toward ultrasonic sensor
  // Positive = away from ultrasonic sensor


  // ==========================
  // 4. Emergency Escape
  // ==========================
  if (filteredDistance <= escapeDistance) {

    servo.write(escapeAngle);

    integral = 0.0;

    Serial.print("EMERGENCY | Distance: ");
    Serial.print(filteredDistance);

    Serial.print(" | Velocity: ");
    Serial.println(filteredVelocity);

    return;
  }


  // ==========================
  // 5. PID Error
  // ==========================
  double error =
      setPoint - filteredDistance;


  // ==========================
  // 6. P Control
  // ==========================
  double Pvalue = kp * error;


  // ==========================
  // 7. I Control
  // ==========================
  integral += error * dt;

  integral = constrain(
    integral,
    -20.0,
    20.0
  );

  double Ivalue = ki * integral;


  // ==========================
  // 8. D Control
  // ==========================

  // 使用球的速度計算 D
  // 避免目標變化造成微分突波
  double Dvalue =
      -kd * filteredVelocity;


  // ==========================
  // 9. PID Output
  // ==========================
  double PIDvalue =
      Pvalue + Ivalue + Dvalue;


  // ==========================
  // 10. Servo Angle
  // ==========================
  int servoAngle =
      baselineAngle + PIDvalue;

  servoAngle = constrain(
    servoAngle,
    minAngle,
    maxAngle
  );


  // ==========================
  // 11. Early Braking
  // ==========================
  if (
    filteredDistance <= warningDistance &&
    filteredVelocity < warningSpeed
  ) {

    // 球朝超音波快速移動
    // 提前抬高超音波端
    servoAngle = max(servoAngle, 125);

    Serial.print("EARLY BRAKE | ");
  }


  // ==========================
  // 12. Servo Output
  // ==========================
  servo.write(servoAngle);


  // ==========================
  // 13. Serial Monitor
  // ==========================
  Serial.print("Distance: ");
  Serial.print(filteredDistance);

  Serial.print(" cm");

  Serial.print(" | Target: ");
  Serial.print(setPoint);

  Serial.print(" | Velocity: ");
  Serial.print(filteredVelocity);

  Serial.print(" | Error: ");
  Serial.print(error);

  Serial.print(" | P: ");
  Serial.print(Pvalue);

  Serial.print(" | D: ");
  Serial.print(Dvalue);

  Serial.print(" | Servo: ");
  Serial.println(servoAngle);
}
