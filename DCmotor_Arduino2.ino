const byte LMotorS=10;  //Right wheel motor signal pin  
const byte RMotorS=11;  //Left wheel motor signal pin~
const byte LMotorA=7;  
const byte LMotorB=2;  
const byte RMotorA=3;  
const byte RMotorB=4;  
const byte HMotorS=5;  //Hydraulic Motor signal pin
const int HMotorA=A4;  
const int HMotorB=A5; 
const int hydbuttonpin=A3; //hydraulic button pin
int yAxis = A0; //analogue input for joystick
int xAxis = A1; //analogue input for linear potentiometer
int x_pos;
int y_pos;
int hydButtonState; //hydraulic button state
void setup() {
  pinMode(RMotorS, OUTPUT);
  pinMode(RMotorA, OUTPUT);
  pinMode(RMotorB, OUTPUT);
  pinMode(LMotorS, OUTPUT);
  pinMode(LMotorA, OUTPUT);
  pinMode(LMotorB, OUTPUT);
  pinMode(HMotorS, OUTPUT);
  pinMode(HMotorA, OUTPUT);
  pinMode(HMotorB, OUTPUT);
  pinMode(hydbuttonpin, INPUT_PULLUP);
  pinMode(yAxis,INPUT);
  pinMode(xAxis,INPUT);
  Serial.begin(9600);
  //used the serial monitor for code debugging
}
void loop() {
  y_pos = analogRead(yAxis); 
  //reading the joystick status
  hydButtonState=digitalRead(hydbuttonpin); 
  //reading the hydraulic button state
  
if (hydButtonState == LOW){
  //Normal steering mode
if (y_pos < 460) {
  //joystick moved backwards, DC motor set reverse
      digitalWrite(RMotorA, HIGH); 
      digitalWrite(RMotorB, LOW);
      digitalWrite(LMotorA, LOW);
      digitalWrite(LMotorB, HIGH);
      analogWrite(RMotorS, 200); 
      analogWrite(LMotorS, 200);
      //declaring the speed at 200/255
  }
  else if (y_pos > 562) { 
    //joystick moved forward, DC motor set forward
      digitalWrite(RMotorA, LOW); 
      digitalWrite(RMotorB, HIGH);
      digitalWrite(LMotorA, HIGH);
      digitalWrite(LMotorB, LOW);
      analogWrite(RMotorS, 200);
      analogWrite(LMotorS, 200);
  }
  else { 
    //joystick deadzone, DC motor stopped
      digitalWrite(RMotorA, LOW); 
      digitalWrite(RMotorB, LOW);
      digitalWrite(LMotorA, LOW);
      digitalWrite(LMotorB, LOW);
  }
}
if (hydButtonState==HIGH){
  //Hyd. mode ON
        analogWrite(RMotorS, 150);
        analogWrite(LMotorS, 150);
        analogWrite(HMotorS, 150);
  while(hydButtonState==HIGH){
    hydButtonState=digitalRead(hydbuttonpin); 
    x_pos=analogRead(xAxis);
    y_pos=analogRead(yAxis);
    //Reading joystick, slider and hyd. button
    if (x_pos > 1000 ){
      
      digitalWrite(HMotorA, HIGH);
      digitalWrite(HMotorB, LOW);
    }
    else if (x_pos < 25){
      //slider is at left end, rack contracting
      digitalWrite(HMotorA, LOW);
      digitalWrite(HMotorB, HIGH);
    }
    else {
      digitalWrite(HMotorA, LOW);
      digitalWrite(HMotorB, LOW);
    }

    if (y_pos > 562){
      //joystick moved forward, CW turn
        digitalWrite(RMotorA, LOW); 
        digitalWrite(RMotorB, HIGH);
        digitalWrite(LMotorA, LOW);
        digitalWrite(LMotorB, HIGH);
    }
    else if (y_pos < 460){
      //joystick moved backwards, ACW turn
        digitalWrite(RMotorA, HIGH); 
        digitalWrite(RMotorB, LOW);
        digitalWrite(LMotorA, HIGH);
        digitalWrite(LMotorB, LOW);
    }
  else {
        digitalWrite(RMotorA, LOW); 
        digitalWrite(RMotorB, LOW);
        digitalWrite(LMotorA, LOW);
        digitalWrite(LMotorB, LOW);
  
  }
  }
  
}
}
