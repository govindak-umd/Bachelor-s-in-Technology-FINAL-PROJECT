#include <Servo.h>
#include <Stepper.h>
Servo SR;
Servo SL;
const byte A1 = ;
const byte A2=;
const byte B2=;
const byte B1=;
Stepper myStepper(200, A2, A1, B1, B2);
const byte RServo =3;  //Right Servo signal pin    
const byte LServo =6;  //Left Servo signal pin   ~
const byte LMotorS=5;  //Rigth wheel motor signal pin    ~
const byte LMotorA=8;  //Right motor inA
const byte RMotorA=7;  //Left motor inA
const byte LMotorB=12;  //Right motor inB
const byte RMotorB=11;  //Left motor inB
const byte RMotorS=10;  //Left wheel motor signal pin
//Hydraulic DC Motor
const byte DCmotor = 2 ;  //initializing pin 2 as pwm
const byte firstpin = 8 ;
const byte secondpin = 9 ;
const int servorestR=88;    //Servo resting angle,  when upside down, to turn the LEFT WHEEL Clockwise, we need to ADD angles
const int servorestL=95;    //Servo resting angle. when upside down, to turn the RIGHT WHEEL Clockwise, we need to SUBSTRACT angles
int pos =0;
void DCmove(int k){
      digitalWrite(RMotorA, HIGH); 
      digitalWrite(RMotorB, LOW);
      digitalWrite(LMotorA, LOW);
      digitalWrite(LMotorB, HIGH);
      analogWrite(RMotorS, 120);
      analogWrite(LMotorS, 120);
      delay(1000*k);
      digitalWrite(RMotorA, LOW); 
      digitalWrite(RMotorB, LOW);
      digitalWrite(LMotorA, LOW);
      digitalWrite(LMotorB, LOW);
}
 void StepperTurnSteps( int x){
  myStepper.step(x);
  delay(500);
  pos=pos+x;
}


void ServoStraightAhead(){
  SR.write(servorestR);
  SL.write(servorestL);
}
void StepperCenter(){
  myStepper.step(-x);
  delay(500);
  pos=0;
}
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

 SR.attach(RServo);
 SL.attach(LServo); 
 SR.write(servorestR);
 SL.write(servorestL);

  pinMode(DCmotor,OUTPUT) ;   
  pinMode(firstpin,OUTPUT) ; 
  pinMode(secondpin,OUTPUT) ;
 myStepper.setSpeed(60);
}
void loop() {
      DCmove(3);//making the rear DC motors move forward for 3 seconds 
      SR.write(servorestL-45);//turning the rear servos
      SL.write(servorestR+23);
      StepperTurnSteps(68);//turning the front stepper motors
      DCmove(3);
      ServoStraightAhead();//resting the servos                          
      StepperCenter();//centering the stepper moto
      DCmove(3);  
      StepperTurnSteps(68); 
      DCmove(4);  
      StepperCenter ();//centering the stepper motor
      DCmove(4);
      SR.write(servorestL+23);//Left turn 4 wheel until a 90 degree change in path using FOUR WHEEL STEERING SYSTEM
      SL.write(servorestR-45);
      StepperTurnSteps(-68); //stepper turning
      delay (1000);//TIME BASED ON OUR EXPERIMENT TO ATTAIN THE TCR WE WANT 
      DCmove(4); 
      ServoStraightAhead();
      StepperCenter ();//centering the stepper motor
      DCmove(4) ;
      StepperTurnSteps(-68); 
      DCmove(4);  
      StepperCenter();//centering the stepper motor
      delay (1000);
      DCmove(4); 
      StepperTurnSteps(-68) ;
      DCmove(3);
      StepperCenter();//centering the stepper motor
        //crab steer to left side
        SR.write(servorestL-45); //have to measure the servo rest angle and then edit this
        SL.write(servorestR+23);//have to measure the servo rest angle and then edit this
        StepperTurnSteps(25);  //have to calculate the angle here as per the gear ratios and change 
        DCmove(3); 
        StepperCenter ();//centering the stepper motor
        ServoStraightAhead();
        DCmove(3);
        //crab steer to the right side
       SR.write(servorestL+23);//have to measure the servo rest angle and then edit this
       SL.write(servorestR-45);//have to measure the servo rest angle and then edit this
       StepperTurnSteps(25);    //have to calculate the angle here as per the gear ratios and change 
       delay(1000);
       DCmove(3);
       ServoStraightAhead();
       StepperCenter();//centering the stepper motor                    
       delay(1000);//for moving straight ahead
       DCmove(3);
            
      //ZERO STEERING
      
      SR.write(servorestL+23);//servo turn angle must fix
      SL.write(servorestR+23);
      digitalWrite(firstpin,HIGH) ;//HYDRAULIC making the small dc motor clockwise to push the fluid in
      digitalWrite(secondpin,LOW) ;
      analogWrite(DCmotor,255);
      digitalWrite(RMotorA, LOW);  //Moving anti-clockwise
      digitalWrite(RMotorB, HIGH);
      digitalWrite(LMotorA, LOW);//should move anticlockwise???
      digitalWrite(LMotorB, HIGH);  
      delay(1000);//time based on the time it takes to rotate how much ever we want it t    
      analogWrite(RMotorS,0);//stop the dc motor 
      analogWrite(LMotorS,0);
      delay(1000) ; //just a bit of delay given here to pull the wheels back by the DC motor.
      ServoStraightAhead(); 
      digitalWrite(firstpin,LOW) ;//HYDRAULIC dc motor anti-clockwise to pull the fluid back in and to centre the front wheels
      digitalWrite(secondpin,HIGH) ;
      analogWrite(DCmotor,255) ;   
}
