#include <QTRSensors.h>
const int m11Pin = 7;
const int m12Pin = 6;
const int m21Pin = 5;
const int m22Pin = 4;
const int m1Enable = 11;
const int m2Enable = 10;

int m1Speed = 0;
int m2Speed = 0;

float kp = 11;
float ki = 0;
float kd = 1;

int p = 1;
int i = 0;
int d = 0;

int error = 0;
int lastErrorCalibration = 0;
int lastError = 0;

const int maxSpeed = 225;
const int minSpeed = -225;

const int baseSpeed = 195;
const int calibrationSpeed = 135;

QTRSensors qtr;

const int sensorCount = 6;
int sensorValues[sensorCount];
int sensors[sensorCount] = { 0, 0, 0, 0, 0, 0 };

byte isReach = 0;

void setup() {
  pinMode(m11Pin, OUTPUT);
  pinMode(m12Pin, OUTPUT);
  pinMode(m21Pin, OUTPUT);
  pinMode(m22Pin, OUTPUT);
  pinMode(m1Enable, OUTPUT);
  pinMode(m2Enable, OUTPUT);

  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){ A0, A1, A2, A3, A4, A5 }, sensorCount);

  delay(100);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); 

  m1Speed = calibrationSpeed;
  m2Speed = -calibrationSpeed;

  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(9600);
}

void calibration1() {

  qtr.calibrate();

  int error = map(qtr.readLineBlack(sensorValues), 0, 5000, -30, 30);

  if ((error == 30 || error == -30) && lastErrorCalibration != error) {
    m1Speed = -m1Speed;
    m2Speed = -m2Speed;
  }

  lastErrorCalibration = error;

  setMotorSpeed(m1Speed, m2Speed);
}

void reachLine() {

  int error = map(qtr.readLineBlack(sensorValues), 0, 5000, -30, 30);

  if (error == 0) {
    setMotorSpeed(0, 0);
    isReach = 1;
  }
  if (error < 1) {
    setMotorSpeed(-200, 200);
  }
  if (error > 1) {
    setMotorSpeed(200, -200);
  }
}


void loop() {

  if (millis() < 5000) {
    calibration1();
  }
   else if (isReach == 0) {
    reachLine();
  } 
  else {
    int error = map(qtr.readLineBlack(sensorValues), 0, 5000, -30, 30);

    p = error;
    i = i + error;
    d = error - lastError;
    lastError = error;

    int motorSpeed = kp * p + ki * i + kd * d; 

    m1Speed = baseSpeed;
    m2Speed = baseSpeed;


    if (error < 0) {
      m1Speed += motorSpeed;
    } else if (error > 0) {
      m2Speed -= motorSpeed;
    }

    m1Speed = constrain(m1Speed, minSpeed, maxSpeed);
    m2Speed = constrain(m2Speed, minSpeed, maxSpeed);

    setMotorSpeed(m1Speed, m2Speed);
  }
}


void setMotorSpeed(int motor1Speed, int motor2Speed) {
  motor2Speed = -motor2Speed;
  if (motor1Speed == 0) {
    digitalWrite(m11Pin, LOW);
    digitalWrite(m12Pin, LOW);
    analogWrite(m1Enable, motor1Speed);
  } else {
    if (motor1Speed > 0) {
      digitalWrite(m11Pin, HIGH);
      digitalWrite(m12Pin, LOW);
      analogWrite(m1Enable, motor1Speed);
    }
    if (motor1Speed < 0) {
      digitalWrite(m11Pin, LOW);
      digitalWrite(m12Pin, HIGH);
      analogWrite(m1Enable, -motor1Speed);
    }
  }
  if (motor2Speed == 0) {
    digitalWrite(m21Pin, LOW);
    digitalWrite(m22Pin, LOW);
    analogWrite(m2Enable, motor2Speed);
  } else {
    if (motor2Speed > 0) {
      digitalWrite(m21Pin, HIGH);
      digitalWrite(m22Pin, LOW);
      analogWrite(m2Enable, motor2Speed);
    }
    if (motor2Speed < 0) {
      digitalWrite(m21Pin, LOW);
      digitalWrite(m22Pin, HIGH);
      analogWrite(m2Enable, -motor2Speed);
    }
  }
}