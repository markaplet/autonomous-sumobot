// https://learn.adafruit.com/adafruit-motor-shield/using-dc-motors
#include <AFMotor.h>

int MOTOR_SPEED = 150;

// DC Motors
AF_DCMotor MOTOR_LEFT(1, MOTOR12_64KHZ);
AF_DCMotor MOTOR_RIGHT(2, MOTOR12_64KHZ);



void setup() {
  Serial.begin(9600);
  MOTOR_LEFT.setSpeed(MOTOR_SPEED);
  MOTOR_RIGHT.setSpeed(MOTOR_SPEED);
  stop();
}

void loop() {
  delay(2000);    // testing delay

  //forward();
  //backward();
  //spinLeft();
  //spinRight();
  //stop();
}

void forward() {
  Serial.println("Motor Forward");
  MOTOR_LEFT.run(FORWARD);
  MOTOR_RIGHT.run(FORWARD);
}

void stop() {
  Serial.println("Motor Stop");
  MOTOR_LEFT.run(RELEASE);
  MOTOR_RIGHT.run(RELEASE);
}

void spinLeft() {
  // Be friendly to the motor: stop it before reverse.
  // Rotate 60 degrees
  // Turn left wheel in reverse
  // Turn right wheel forward
  Serial.println("Spin Left");
  stop();
  MOTOR_LEFT.run(BACKWARD);
  MOTOR_RIGHT.run(FORWARD);
}

void spinRight() {
  // Be friendly to the motor: stop it before reverse.
  // Rotate 60 degrees
  // Turn right wheel in reverse
  // Turn left wheel forward
  Serial.println("Spin Right");
  stop();
  MOTOR_LEFT.run(FORWARD);
  MOTOR_RIGHT.run(BACKWARD);
}
