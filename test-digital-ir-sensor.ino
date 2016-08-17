//Code for the QRE1113 Digital board
//Outputs via the serial terminal - Lower numbers mean more reflected
//3000 or more means nothing was reflected.

int IR_DATA_IN = 2; //connected to digital 2

void setup(){
  Serial.begin(9600);
}


void loop(){

  int irValue = readQD();
  Serial.println(irValue);

}


int readQD(){
  //Returns value from the QRE1113
  //Lower numbers mean more refleacive
  //More than 3000 means nothing was reflected.
  pinMode( IR_DATA_IN, OUTPUT );
  digitalWrite( IR_DATA_IN, HIGH );
  delayMicroseconds(10);
  pinMode( IR_DATA_IN, INPUT );

  long time = micros();

  //time how long the input is HIGH, but quit after 3ms as nothing happens after that
  while (digitalRead(IR_DATA_IN) == HIGH && micros() - time < 3000);
  int diff = micros() - time;

  return diff;
}
