#ifndef RC_SERVOS
#define RC_SERVOS

void setupServos();
void updateServos();
void rotateServos();
void updateMotor();

#include <Servo.h>

Servo rServo;
Servo lServo;
Servo motor;

int rCurrentPos = 90;
int lCurrentPos = 90;
int currentMotor = 1000;

void setupServos() {
  rServo.attach(9);
  lServo.attach(6);
  motor.attach(5, 1000, 2000);

  rotateServos();
  motor.write(1000);
}

void updateServos() {
  int rVal = map(FLIGHT_DIR_CONTROL.r, -100, 100, 0, 180);
  int lVal = map(FLIGHT_DIR_CONTROL.l, 100, -100, 0, 180);

  if (rVal == rCurrentPos && lVal == lCurrentPos) {
    return;
  }

  if (rCurrentPos > rVal) {
    rCurrentPos --;
  } else {
    rCurrentPos ++;
  }

  if (lCurrentPos > lVal) {
    lCurrentPos --;
  } else {
    lCurrentPos ++;
  }

  rotateServos();
}

void rotateServos() {
  rServo.write(rCurrentPos);
  lServo.write(lCurrentPos); 
}

void updateMotor() {
  int motorValue = 1000 + FLIGHT_DIR_CONTROL.t * 10;
  if (currentMotor == motorValue) {
    return;
  }
  currentMotor = motorValue;

  Serial.print("updateMotor: "); 
  Serial.println(motorValue); 

  motor.write(currentMotor);
}

#endif