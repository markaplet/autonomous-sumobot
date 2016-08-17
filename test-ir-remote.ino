#include <IRremote.h>

int RECV_PIN = A0;
IRrecv irrecv(RECV_PIN);
decode_results results;
boolean runMode = false;
int keyPressed;

void setup()
{
	Serial.begin(9600);
	irrecv.enableIRIn(); // Start the receiver
	Serial.println("Setup Complete");
}

void loop()
{
	checkRunMode();

	if (runMode)
	{
		Serial.println("running");
	}
}

void checkRunMode()
{
	// Before running main loop wait for remote keypress
	// then count down before running hunt()

	if (irrecv.decode(&results))
	{
		Serial.print("HEX Value: ");
		Serial.println(results.value, HEX);

		keyPressed = results.value;

		if (runMode == 0 && keyPressed == 765)
		{
			delay(3000);
			runMode = true;
		}
		else
		{
			runMode = false;
		}

		irrecv.resume(); // Receive the next value
	}
}
