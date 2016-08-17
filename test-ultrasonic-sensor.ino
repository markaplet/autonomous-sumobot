#include <NewPing.h>

#define TRIGGER_PIN 10
#define ECHO_PIN 9
#define MAX_DISTANCE 30

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
   Serial.begin(9600);
}

void loop() {
   delay(200);
   unsigned int uS = sonar.ping_cm();
   Serial.print(uS);
   Serial.println("cm");
}
