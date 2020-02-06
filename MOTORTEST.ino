#include <Servo.h>
Servo SR;
Servo SL;

const byte RServo =3;  //Right Servo signal pin    
const byte LServo =6;  //Left Servo signal pin   ~
const byte LMotorS=5;  //Rigth wheel motor signal pin    ~
const byte LMotorA=8;  //Right motor inA
const byte RMotorA=7;  //Left motor inA
const byte LMotorB=12;  //Right motor inB
const byte RMotorB=11;  //Left motor inB
const byte RMotorS=10;  //Left wheel motor signal pin ~
const byte DCmotor = 2 ;  //initializing pin 2 as pwm
const byte firstpin = 1 ;
const byte secondpin = 9 ;
const int servorestR=88;    //Servo resting angle,  when upside down, to turn the LEFT WHEEL Clockwise, we need to ADD angles
const int servorestL=95;    //Servo resting angle. when upside down, to turn the RIGHT WHEEL Clockwise, we need to SUBSTRACT angles
int posX;
int posY;
int pos = 0;
const int stepperSpeed=2;
void DCmove(int k){
      digitalWrite(RMotorA, HIGH); 
      digitalWrite(RMotorB, LOW);
      digitalWrite(LMotorA, HIGH);
      digitalWrite(LMotorB, LOW);
      analogWrite(RMotorS, 120);
      analogWrite(LMotorS, 120);
      delay(1000*k);
      digitalWrite(RMotorA, LOW); 
      digitalWrite(RMotorB, LOW);
      digitalWrite(LMotorA, LOW);
      digitalWrite(LMotorB, LOW);
}
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  pinMode(RServo, OUTPUT);
  pinMode(LServo, OUTPUT);
  pinMode(RMotorS, OUTPUT);
  pinMode(RMotorA, OUTPUT);
  pinMode(RMotorB, OUTPUT);
  pinMode(LMotorS, OUTPUT);
  pinMode(LMotorA, OUTPUT);
  pinMode(LMotorB, OUTPUT);

 SR.attach(RServo);
 SL.attach(LServo); 
 SR.write(servorestR);
 SL.write(servorestL);

  pinMode(DCmotor,OUTPUT) ;   
  pinMode(firstpin,OUTPUT) ; 
  pinMode(secondpin,OUTPUT) ;
}

void loop() {
  // put your main code here, to run repeatedly:
DCmove(5);
}
