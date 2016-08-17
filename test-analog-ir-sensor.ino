// Code for the QRE1113 Analog board
// Outputs via the serial terminal - Lower numbers mean more reflected

int IR_DATA_IN = 4; //connected to analog 0

void setup(){
  Serial.begin(9600);
}


void loop(){

  int irValue = analogRead(IR_DATA_IN);
  Serial.println(irValue);
  delay(250);

}
