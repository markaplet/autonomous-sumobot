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

// https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home
// NOTE: Due to issues with timers NewPing.h library must be modified
// to disable the TIMMER_ENABLED value on line 153 by setting it to false
// https://bitbucket.org/teckel12/arduino-new-ping/wiki/Multiple%20Definition%20of%20%22__vector_7%22%20Error
#include <NewPing.h>



// -------------------------------
// DEFINE ALL DA TINGS
// -------------------------------
//#define DEBUG
int MOTOR_SPEED             = 150;  // Slow ride...
int ATTACK_SPEED            = 255;  // Fuck that bitch up!
int REVERSE_DELAY           = 300;  // Used for short backups
int SPIN_DELAY              = 500;  // Used for turns
int MIN_ATTACK_DIST         = 20;   // Minimum distance to object in cm

// DC Motors
AF_DCMotor MOTOR_LEFT(1, MOTOR12_64KHZ);  // M1 on shield
AF_DCMotor MOTOR_RIGHT(2, MOTOR12_64KHZ); // M2 on shield

// Ultrasonic Sensor
#define US_TRIGGER            10    // Trigger pin on the ultrasonic sensor => use servo 1 pin on shield
#define US_ECHO               9     // Ultrasonic sensor => Use servo 2 pin on shield
#define US_MAX_DISTANCE       60    // Maximum distance to ping (in centimeters)
NewPing sonar(US_TRIGGER, US_ECHO, US_MAX_DISTANCE);

// IR Line Sensors
#define IR_FRONT_LEFT         A4    // Front left edge IR sensor
#define IR_FRONT_RIGHT        A5    // Front right edge IR sensor
#define IR_BORDER_THRESHOLD   600   // White edge is ~550 while black is ~900



// -------------------------------
// SETUP
// The setup routine runs once when you press reset:
// -------------------------------
void setup()
{
  Serial.begin(9600);
  MOTOR_LEFT.setSpeed(MOTOR_SPEED);
  MOTOR_RIGHT.setSpeed(MOTOR_SPEED);
  stop();
  Serial.println("Setup Complete");
  countDown();
}



// -------------------------------
// THE MAIN PROGRAM LOOP
// -------------------------------
void loop()
{
  #ifdef DEBUG
    delay(1000);  // testing delay
  #endif

  // LEFT EDGE DETECTION
  detectLeft();

  // RIGHT EDGE DETECTION
  detectRight();

  // ULTRASONIC TIME
  aquireTarget();
}



// -------------------------------
// FUNCTIONS
// -------------------------------

void aquireTarget()
{
  int distInCentimeters;  // Store the ultrasonic range distance

  distInCentimeters = sonar.ping_cm();

  #ifdef DEBUG
    Serial.print("    Ping Is: ");
    Serial.println(distInCentimeters);
  #endif

  if(distInCentimeters > MIN_ATTACK_DIST || distInCentimeters == 0)
  {
  #ifdef DEBUG
    Serial.println("Keep Looking");
  #endif
    forward();
  }
  else
  {
  #ifdef DEBUG
    Serial.println("Attack");
  #endif
    attack();
  }
}

void detectLeft()
{
  int frontLeftValue;     // IR edge sensor in the front

  frontLeftValue = analogRead(IR_FRONT_LEFT);

  #ifdef DEBUG
    Serial.print("Left Line Sensor: ");
    Serial.println(frontLeftValue);
  #endif

  if(frontLeftValue < IR_BORDER_THRESHOLD)
  {
  #ifdef DEBUG
    Serial.println("Left Edge Detected");
  #endif
    backward();
    spinRight();
  }
}

void detectRight()
{
  int frontRightValue;    // IR edge sensor in the front

  frontRightValue = analogRead(IR_FRONT_RIGHT);

  #ifdef DEBUG
    Serial.print("Right Line Sensor: ");
    Serial.println(frontRightValue);
  #endif

  if(frontRightValue < IR_BORDER_THRESHOLD)
  {
  #ifdef DEBUG
    Serial.println("Right Edge Detected");
  #endif
    backward();
    spinLeft();
  }
}

void attack()
{
  #ifdef DEBUG
    Serial.println("I'm giving her all she's got captain!");
  #endif

  // Full throttle mother fucker!
  MOTOR_LEFT.setSpeed(ATTACK_SPEED);
  MOTOR_RIGHT.setSpeed(ATTACK_SPEED);

  // Full Speed forward
  MOTOR_LEFT.run(FORWARD);
  MOTOR_RIGHT.run(FORWARD);
}

void forward()
{
  #ifdef DEBUG
    Serial.println("Motor Forward");
  #endif

  // Reset speed to slower speed
  MOTOR_LEFT.setSpeed(MOTOR_SPEED);
  MOTOR_RIGHT.setSpeed(MOTOR_SPEED);

  // Drive forward
  MOTOR_LEFT.run(FORWARD);
  MOTOR_RIGHT.run(FORWARD);
}

void backward()
{
  #ifdef DEBUG
    Serial.println("Motor Backward");
  #endif

  // Be friendly to the motor: stop it before reversing.
  stop();

  // Reset speed to slower speed
  MOTOR_LEFT.setSpeed(MOTOR_SPEED);
  MOTOR_RIGHT.setSpeed(MOTOR_SPEED);

  // Drive backwards then stop
  MOTOR_LEFT.run(BACKWARD);
  MOTOR_RIGHT.run(BACKWARD);
  delay(REVERSE_DELAY);     // Backup just a little bit then stop
  stop();
}

void stop()
{
  #ifdef DEBUG
    Serial.println("Motor Stop");
  #endif

  MOTOR_LEFT.run(RELEASE);
  MOTOR_RIGHT.run(RELEASE);
}

void spinLeft()
{
  #ifdef DEBUG
    Serial.println("Spin Left");
  #endif

  // Be friendly to the motor: stop it before reversing.
  stop();

  // Reset speed to slower turning speed
  MOTOR_LEFT.setSpeed(MOTOR_SPEED);
  MOTOR_RIGHT.setSpeed(MOTOR_SPEED);

  // Turn then stop motors
  MOTOR_LEFT.run(BACKWARD);
  MOTOR_RIGHT.run(FORWARD);
  delay(SPIN_DELAY);
  stop();
}

void spinRight()
{
  #ifdef DEBUG
    Serial.println("Spin Right");
  #endif

  // Be friendly to the motor: stop it before reversing.
  stop();

  // Reset speed to slower turning speed
  MOTOR_LEFT.setSpeed(MOTOR_SPEED);
  MOTOR_RIGHT.setSpeed(MOTOR_SPEED);

  // Turn then stop motors
  MOTOR_LEFT.run(FORWARD);
  MOTOR_RIGHT.run(BACKWARD);
  delay(SPIN_DELAY);
  stop();
}

// -------------------------------
// COUNT DOWN TIMER BEFORE BATTLE
// -------------------------------
void countDown()
{
  delay(4800);   // appox 5 seconds after reset released
}
