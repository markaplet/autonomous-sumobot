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

// https://github.com/z3t0/Arduino-IRremote
#include <IRremote.h>



// -------------------------------
// DEFINE ALL DA TINGS
// -------------------------------
int MOTOR_SPEED             = 150;  // Slow ride...
int ATTACK_SPEED            = 255;  // Fuck that bitch up!
int MOTOR_DELAY             = 300;  // Used for turns and short backups
int MIN_ATTACK_DIST         = 20;   // Minimum distance to object in cm

// DC Motors
AF_DCMotor MOTOR_LEFT(1, MOTOR12_64KHZ);  // M1 on shield
AF_DCMotor MOTOR_RIGHT(2, MOTOR12_64KHZ); // M2 on shield

// Ultrasonic Sensor
#define US_TRIGGER            10    // Trigger pin on the ultrasonic sensor => use servo 1 pin on shield
#define US_ECHO               9     // Ultrasonic sensor => Use servo 2 pin on shield
#define US_MAX_DISTANCE       60    // Maximum distance to ping (in centimeters)
NewPing sonar(US_TRIGGER, US_ECHO, US_MAX_DISTANCE);

// IR Sensors
#define RECV_PIN              A0    // IR Remote sensor
#define IR_FRONT_LEFT         A4    // Front left edge IR sensor
#define IR_FRONT_RIGHT        A5    // Front right edge IR sensor
#define IR_REAR               A3    // Rear edge IR sensor
#define IR_BORDER_THRESHOLD   600   // White edge is ~550 while black is ~900

// IR REMOTE
IRrecv irrecv(RECV_PIN);
decode_results results;
boolean runMode = 0;                // Off by default
long remoteKeyPressed;              // Initialize now but use in checkRunMode() function




// -------------------------------
// SETUP
// The setup routine runs once when you press reset:
// -------------------------------
void setup()
{
	Serial.begin(9600);
	irrecv.enableIRIn();              // Start the ir receiver
	MOTOR_LEFT.setSpeed(MOTOR_SPEED);
	MOTOR_RIGHT.setSpeed(MOTOR_SPEED);
	stop();
	Serial.println("Setup Complete");
}



// -------------------------------
// THE MAIN PROGRAM LOOP
// -------------------------------
void loop()
{

	checkRunMode();         // Is bot able to battle?

	if (runMode == 1)
	{

		//Serial.print("runmode: ");
		//Serial.println(runMode);
		delay(1000);    // testing delay

		// INITIALIZE PLACEHOLDER VARIABLES
		int distInCentimeters;  // Store the ultrasonic range distance
		int frontLeftValue;     // IR edge sensor in the front
		int frontRightValue;    // IR edge sensor in the front
		int rearEdgeValue;      // IR edge sensor in the back

		// LEFT EDGE DETECTION
		frontLeftValue = analogRead(IR_FRONT_LEFT);
		//Serial.println(frontLeftValue);

		if(frontLeftValue < IR_BORDER_THRESHOLD)
		{
			Serial.println("Left Edge Detected");
			backward();
			spinRight();
		}

		// RIGHT EDGE DETECTION
		frontRightValue = analogRead(IR_FRONT_RIGHT);
		//Serial.println(frontRightValue);

		if(frontRightValue < IR_BORDER_THRESHOLD)
		{
			Serial.println("Right Edge Detected");
			backward();
			spinLeft();
		}

		int backEdgeValue = analogRead(IR_REAR);
		if(backEdgeValue > IR_BORDER_THRESHOLD)
		{
			//PLACEHOLDER
		}

		// ULTRASONIC TIME
		distInCentimeters = sonar.ping_cm();
		Serial.print("    Ping Is: ");
		Serial.println(distInCentimeters);

		if(distInCentimeters > MIN_ATTACK_DIST || distInCentimeters == 0)
		{
			Serial.println("Keep Looking");
			forward();
		}
		else
		{
			Serial.println("Attack");
			attack();
		}
	}
}



// -------------------------------
// FUNCTIONS
// -------------------------------

void attack()
{
	//Serial.println("I'm giving her all she's got captain!");
	MOTOR_LEFT.setSpeed(ATTACK_SPEED);
	MOTOR_RIGHT.setSpeed(ATTACK_SPEED);
	MOTOR_LEFT.run(FORWARD);
	MOTOR_RIGHT.run(FORWARD);
	//delay(MOTOR_DELAY);   // Used for troubleshooting.
}

void forward()
{
	//Serial.println("Motor Forward");
	MOTOR_LEFT.run(FORWARD);
	MOTOR_RIGHT.run(FORWARD);
	//delay(MOTOR_DELAY);   // Used for troubleshooting.
}

void backward()
{
	//Serial.println("Motor Backward");
	MOTOR_LEFT.run(BACKWARD);
	MOTOR_RIGHT.run(BACKWARD);
	delay(MOTOR_DELAY);     // Backup just a little bit then stop
	stop();
}

void stop()
{
	//Serial.println("Motor Stop");
	MOTOR_LEFT.run(RELEASE);
	MOTOR_RIGHT.run(RELEASE);
}

void spinLeft()
{
	// Be friendly to the motor: stop it before reverse.
	// Turn left wheel in reverse
	// Turn right wheel forward
	//Serial.println("Spin Left");
	stop();
	MOTOR_LEFT.run(BACKWARD);
	MOTOR_RIGHT.run(FORWARD);
	delay(MOTOR_DELAY);
	stop();
}

void spinRight()
{
	// Be friendly to the motor: stop it before reverse.
	// Turn right wheel in reverse
	// Turn left wheel forward
	//Serial.println("Spin Right");
	stop();
	MOTOR_LEFT.run(FORWARD);
	MOTOR_RIGHT.run(BACKWARD);
	delay(MOTOR_DELAY);
    stop();
}




// -------------------------------
// UTILITY FUNCTIONS FOR STARTING
// AND STOPING BOT WITH IR REMOTE
// -------------------------------
void checkRunMode()
{
	// Before running main loop wait for remote keypress
	// then count down before running hunt()

	if (irrecv.decode(&results))
	{
		//Serial.print("HEX Value: ");
		//Serial.println(results.value, HEX);
		//Serial.print("Remote Key Pressed: ");
		//Serial.println(results.value);

		remoteKeyPressed = results.value;

		if (remoteKeyPressed == 0xD7E84B1B)
		{
			countDown();
			runMode = 1;
		}
		else
		{
			Serial.println("Did I do good master?!");
			runMode = 0;   // Any key other than the start key will stop the bot
		}

		irrecv.resume(); // Receive the next value
	}
}


// -------------------------------
// COUNT DOWN TIMER BEFORE BATTLE
// -------------------------------
void countDown()
{
	int i;
	for( i = 3; i-- > 0; )
	{
		delay(1000);
		Serial.println(i);
	}
}
