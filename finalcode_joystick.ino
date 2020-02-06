#include <Servo.h>
Servo SR;
Servo SL;

const byte RServo =2;  //Right Servo signal pin    ~
const byte LServo =3;  //Left Servo signal pin   ~
const byte RMotorS=4;  //Rigth wheel motor signal pin    ~
const byte RMotorA=30;  //Right motor inA
const byte RMotorB=31;  //Right motor inB
const byte LMotorS=5;  //Left wheel motor signal pin ~
const byte LMotorA=32;  //Left motor inA
const byte LMotorB=33;  //Left motor inB
const byte Jx=A1;         //Joystick X direction
const byte Jy=A2;         //Joystick Y direction
const byte stepPin=;      //Stepper input
const byte stepDir=;      //Stepper direction control (HIGH CW/LOW ACW)
const int stepSleep=;     //Stepper sleep
const int stepReset=;     //Stepper reset

const int servorestR=;    //Servo resting angle
const int servorestL=;    //Servo resting angle
int posX;
int posY;
const int stepperSpeed=2;


void setup() {
  Serial.begin(9600);
  pinMode(RServo, OUTPUT);
  pinMode(LServo, OUTPUT);
  pinMode(RMotorS, OUTPUT);
  pinMode(RMotorA, OUTPUT);
  pinMode(RMotorB, OUTPUT);
  pinMode(LMotorS, OUTPUT);
  pinMode(LMotorA, OUTPUT);
  pinMode(LMotorB, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(stepDir, OUTPUT);
  pinMode(stepSleep, OUTPUT);
  pinMode(stepReset, OUTPUT);

  pinMode (Jx, INPUT) ;                     
  pinMode (Jy, INPUT) ;

 SR.attach(RServo);
 SL.attach(LServo); 
 SR.write(servorestR);
 SL.write(servorestL);

}

void loop() {
  
   posX = analogRead (Jx) ;  
   posY = analogRead (Jy) ; 
   if (posY>=700){
      digitalWrite(RMotorA, HIGH);
      digitalWrite(RMotorB, LOW);
      digitalWrite(LMotorA, HIGH);
      digitalWrite(LMotorB, LOW);  
      analogWrite(RMotorS, 250);
      analogWrite(LMotorS, 250);
    }
   if (posY<=320){
      digitalWrite(RMotorA, LOW);
      digitalWrite(RMotorB, HIGH);
      digitalWrite(LMotorA, LOW);
      digitalWrite(LMotorB, HIGH);  
      analogWrite(RMotorS, 250);
      analogWrite(LMotorS, 250);
    }
    if (posX<=501){   //left turn
      float Alpha=(((511-posX)*45)/511);
      float stepperSteps = (((511-posX)*(68.42))/511); // steps = %ofTotalDistance * steps/fullRev * dist.TravelledInFullRev 
      digitalWrite (stepDir, HIGH);
      float angleLeft = -0.0009*(Alpha^3)-(0.0413*(Alpha^2))+0.9678*Alpha-0.1293;
      float angleRight = 
      SL.write(servorestL-int(angleLeft));
      SR.write(servorestR+int(angleRight));
      for (int x=0; x<stepperSteps; x++){
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(1000/stepperSpeed);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(1000/stepperSpeed);
      }
    }
    if (posX>=521){
      int stepperSteps = ((poxX-511)/511)*200*(0.3421); // steps = %ofTotalDistance * steps/fullRev * dist.TravelledInFullRev 
      digitalWrite (stepDir, LOW);
      for (int x=0; x<stepperSteps; x++){
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(1000/stepperSpeed);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(1000/stepperSpeed);
      }
    }
    
    
   
}
