#include <Servo.h>
Servo SR;
Servo SL;

const byte RServo =9;  //Right Servo signal pin    ~
const byte LServo =6;
   
void setup() {
  SR.attach(RServo);
  SL.attach(LServo); 

  // put your setup code here, to run once:

}

void loop() {

   SL.write(95);
   SR.write(85);
  delay(2000);

}
