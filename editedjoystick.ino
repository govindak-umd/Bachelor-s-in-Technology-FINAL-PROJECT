#include <Stepper.h>//importing stepper library
#include <Servo.h>//importing servo library
Servo SR;//declaring the right servo
Servo SL;//declaring the left servo

Stepper myStepper(200, 7,8,9,10); //decaring stepper speed and pins
const byte LServo =6;  //Right Servo signal pin    
const byte RServo =5;  //Left Servo signal pin  
const byte stepperEN1=3; //stepper enabler pins 3 and 11
const byte stepperEN2=11;
const int xAxis = A0;   //analogue pin number for joystick
const int steerbuttonpin=A1 ;//steering button pin
const int hydbuttonpin=A2 ;//hydraulic button pin


int steerButtonState; //steering button ON/OFF state
int hydButtonState;//hydraulic button steering button ON/OFF state
int innerangle=0; //variable for the inner angle turned by the servo
int outerangle=0; //variable for the outer angle turned by the servo                                       
int x_pos; // corrected X-position of the slider
int x_pos_raw;  //Raw X position

const int servorestL=90; //Left servo rest position (0 angle)
const int servorestR=90; //Right servo rest position (0 angle)
int wantedPos; //Desired position of the joystick
int pos =0;  //actual position of the joystick


int CorVal( int z){
  // Function corrects potentiometer output to make it more linear
      int RET;
      if (z<60){
            RET=z*4.65;
            }
      else if (z<977){
           RET=(0.50708*z)+248.5741;
            } 
      else{
            RET=(6.0652*z)-5181.718;
            } 
      return (RET);
  }

void ServoStraightAhead(){ 
  //function that brings the servo straight ahead to rest position
  SR.write(servorestR);
  SL.write(servorestL);

}

void StepperTurnSteps( int x){ 
  //function to turn steps by the desired amount
  digitalWrite(stepperEN1,HIGH); 
  digitalWrite(stepperEN2,HIGH);
  //HIGH signal to the stepper enabler pin
  myStepper.step(-x);
  delay(5*abs(x));
  digitalWrite(stepperEN1,LOW); 
  digitalWrite(stepperEN2,LOW);
  //LOW signal to the stepper enabler pin
  pos=pos+x;
}

int InnerAngleArray[]={0,3,6,9,12,15,18,21,24,27,30,33,36,39,42,45};
//Array of values for inner wheel angles
int OuterAngleArray[]={0,3,5,7,9,11,13,14,16,17,18,19,20,21,22,23}; 
//Array of values for outer wheel angles

int ChangeAngle(int q){
  //Function to get OuterAngle from InnerAngle
	int res;
	for (int i=0; i<16; i=i+1){
		 if (q <= InnerAngleArray[i]){
			 res = OuterAngleArray[i];
			 break;
		 }
	 }	
	 return res;
}
void setup() {
  //OUPUT PINS
  pinMode(stepperEN1, OUTPUT);
  pinMode(stepperEN2, OUTPUT);
  //INPUT PINS
  pinMode(xAxis,INPUT);
  pinMode(hydbuttonpin, INPUT); 
  pinMode(steerbuttonpin, INPUT); 
  
  SR.attach(RServo);
  SL.attach(LServo); 
  SR.write(servorestR);//brings Rservo to home upon switch on
  SL.write(servorestL);//brings Lservo to home upon switch on
  myStepper.setSpeed(60);
  Serial.begin(9600); 
  //to be able to use the serial monitor display for debugging
  analogWrite(stepperEN1,0);
  analogWrite(stepperEN2,0);
  delay(2000);
}
void loop(){
 x_pos_raw =  analogRead(xAxis);
 x_pos=CorVal(x_pos_raw);
 x_pos=(1023-x_pos);
 //Getting the slider valuue, then correcting it
   steerButtonState = digitalRead(steerbuttonpin); 
   hydButtonState = digitalRead(hydbuttonpin);
   //taking the current input of the hydraulic & steer button
if (hydButtonState == LOW){
if (steerButtonState==HIGH ) {		 //4wheelsteering
      //getting inner angle  
    if (x_pos < 512) {
     innerangle = (((512-x_pos)*45)/512);
     outerangle = ChangeAngle(innerangle);
     SL.write(servorestL + outerangle); //Settign left servo
     SR.write(servorestR + innerangle);//Setting right servo
     }
    if (x_pos > 513) {
     innerangle = (((x_pos-513)*45)/512);
     outerangle = ChangeAngle(innerangle);
     SL.write(servorestL - innerangle);
     SR.write(servorestR - outerangle);
	}
}
wantedPos=map(x_pos,0,1023,90,-90); 
//mapping the desired position using map function
if (abs(wantedPos-pos)>=10){
  if (pos > wantedPos){
    StepperTurnSteps(-5);}
  if (pos < wantedPos){
  StepperTurnSteps(5);}
  //Turnign stepper based on diff. b/w pos and wantedPos
}
}
if (hydButtonState==HIGH){
  //HydraulicMode, servos set to fixed angles, stepper centered
  StepperTurnSteps(-pos);
  delay(1000);
  SL.write(servorestL+30);
  delay(1000);
  SR.write(servorestR-30);
}
}
