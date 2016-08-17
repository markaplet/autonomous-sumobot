/*
_____ _____ _____ _____
|   __|  |  |     |     |
|__   |  |  | | | |  |  |
|_____|_____|_|_|_|_____|

*/



// -------------------------------
// INCLUDE DA LIBRARIES
// -------------------------------
// https://learn.adafruit.com/adafruit-motor-shield/using-dc-motors
#include <AFMotor.h>



// -------------------------------
// DEFINE ALL DA CONSTANTS
// -------------------------------
int MOTOR_SPEED = 200;
int SPIN_DELAY = 300;

// http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
unsigned long previousMillis = 0;

// DC Motors
AF_DCMotor MOTOR_LEFT(1, MOTOR12_64KHZ);
AF_DCMotor MOTOR_RIGHT(2, MOTOR12_64KHZ);


// IR Sensors
#define IR_FRONT_LEFT         A4    // Front left edge IR sensor
#define IR_FRONT_RIGHT        A5    // Front right edge IR sensor
#define IR_BORDER_THRESHOLD   600   // White edge is ~550 while black is ~900





// -------------------------------
// SETUP
// -------------------------------

// the setup routine runs once when you press reset:
void setup() {
  // serial debug
  Serial.begin(9600);
  //Serial.println("Motor Test!");

  MOTOR_LEFT.setSpeed(MOTOR_SPEED);
  MOTOR_RIGHT.setSpeed(MOTOR_SPEED);
  stop();
}



// -------------------------------
// THE MAIN PROGRAM LOOP
// -------------------------------
void loop() {

  //Serial.println("down with the OPP?");
  //delay(2000);    // testing delay

  // NOTE: May wish to be specific with front left/right
  int distInCentimeters;  // Store the ultrasonic range distance
  int frontLeftValue;     // IR edge sensor in the front
  int frontRightValue;    // IR edge sensor in the front
  int rearEdgeValue;      // IR edge sensor in the back

  // LEFT EDGE DETECTION
  frontLeftValue = analogRead(IR_FRONT_LEFT);
  Serial.println(frontLeftValue);
  if(frontLeftValue < IR_BORDER_THRESHOLD) {
    Serial.println("Left Edge Detected");
    stop();
    spinRight();
  }

  // RIGHT EDGE DETECTION
  frontRightValue = analogRead(IR_FRONT_RIGHT);
  Serial.println(frontRightValue);
  if(frontRightValue < IR_BORDER_THRESHOLD) {
    Serial.println("Right Edge Detected");
    stop();
    spinLeft();
  }
}



// -------------------------------
// FUNCTIONS
// -------------------------------
void detectEdge() {
  // Check analog line sensors for edge of arena.
  // If edge is detected spinX() and hunt()
}

void aquireTarget() {
  Serial.println("Aquiring Le Target");
  // Using ultrasonic sensor, detect position of object.
  // Turn in the direction of object until object is centered
}

void forward() {
  Serial.println("Motor Forward");
  MOTOR_LEFT.run(FORWARD);
  MOTOR_RIGHT.run(FORWARD);
}

void backward() {
  Serial.println("Motor Backward");
  stop();
  MOTOR_LEFT.run(BACKWARD);
  MOTOR_RIGHT.run(BACKWARD);
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
  delay(SPIN_DELAY);
  stop();
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
  delay(SPIN_DELAY);
  stop();
}




// -------------------------------
// UTILITY FUNCTIONS FOR STARTING
// AND STOPING BOT WITH IR REMOTE
// -------------------------------
void matchBegin() {
  // Before running main loop wait for remote keypress
  // then count down before running hunt()
  Serial.println("Sumo Ready, and counting down");
}

void matchOver() {
  Serial.println("Motor Forward");
  // When match is over, IR keypress will stop all
  // processes and return bot to ready state

}
