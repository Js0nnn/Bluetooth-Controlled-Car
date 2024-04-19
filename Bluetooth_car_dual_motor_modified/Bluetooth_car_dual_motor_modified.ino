#define in1 3 //L298n Motor Driver pins.
#define in2 2
#define in3 4
#define in4 5
#define trigPin 6           // Trig Pin Of HC-SR04
#define echoPin 7
#define light_FR  8    //LED Front Right   pin A0 for Arduino Uno
#define light_BR  9    //LED Back Right    pin A2 for Arduino Uno
#define horn_Buzz 10    //Horn Buzzer       pin A4 for Arduino Uno
#define r_led 13
int command; //Int to store app command state.
int Speed = 204; // 0 - 255.
int Speedsec;
int buttonState = 0;
int lastButtonState = 0;
int Turnradius = 0; //Set the radius of a turn, 0 - 255 Note:the robot will malfunction if this is higher than int Speed.
int brakeTime = 45;
int brkonoff = 1; //1 for the electronic braking system, 0 for normal.
boolean lightFront = false;
boolean lightBack = false;
boolean horn = false;

long duration, distance;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
   pinMode(light_FR, OUTPUT);
    pinMode(light_BR, OUTPUT);
    pinMode(horn_Buzz, OUTPUT);
    pinMode(trigPin, OUTPUT);       // Set Trig Pin As O/P To Transmit Waves
  pinMode(echoPin, INPUT);
  pinMode(r_led,OUTPUT);
  Serial.begin(9600);  //Set the baud rate to your Bluetooth module.

  for(int i=0;i<5;i++)
  {
    digitalWrite(r_led,HIGH);
    delay(50);
    digitalWrite(r_led,LOW);
    delay(50);
  }
}

void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);   
  digitalWrite(trigPin, HIGH);       // Transmit Waves For 10us
  delayMicroseconds(10);
  duration = pulseIn(echoPin, HIGH);        // Receive Reflected Waves
  distance = duration / 58.2;                       // Get Distance
  Serial.println(distance);
  delay(10);


   if ((distance < 30)&&(distance > 0))            // Condition For Presence Of Obstacle
  {
    obstacle();
  }


  if (Serial.available() > 0) {
    command = Serial.read();
    Stop(); //Initialize with motors stoped.
    
    
if (lightFront) {digitalWrite(light_FR, HIGH);}
if (!lightFront) {digitalWrite(light_FR, LOW);}
if (lightBack) {digitalWrite(light_BR, HIGH);}
if (!lightBack) {digitalWrite(light_BR, LOW);}
if (horn) {digitalWrite(horn_Buzz, HIGH);}
if (!horn) {digitalWrite(horn_Buzz, LOW);}
    switch (command) {
      case 'F':
        forward();digitalWrite(r_led,HIGH);
        break;
      case 'B':
        back();digitalWrite(r_led,HIGH);
        break;
      case 'L':
        left();digitalWrite(r_led,HIGH);
        break;
      case 'R':
        right();digitalWrite(r_led,HIGH);
        break;
      case 'G':
        forwardleft();digitalWrite(r_led,HIGH);
        break;
      case 'I':
        forwardright();digitalWrite(r_led,HIGH);
        break;
      case 'H':
        backleft();digitalWrite(r_led,HIGH);
        break;
      case 'J':
        backright();digitalWrite(r_led,HIGH);
        break;
      case '0':
        Speed = 100;
        break;
      case '1':
        Speed = 140;
        break;
      case '2':
        Speed = 153;
        break;
      case '3':
        Speed = 165;
        break;
      case '4':
        Speed = 178;
        break;
      case '5':
        Speed = 191;
        break;
      case '6':
        Speed = 204;
        break;
      case '7':
        Speed = 216;
        break;
      case '8':
        Speed = 229;
        break;
      case '9':
        Speed = 242;
        break;
      case 'q':
        Speed = 255;
        break;
      case 'W':lightFront = true;break;
      case 'w':lightFront = false;break;
      case 'U':lightBack = true;break;
      case 'u':lightBack = false;break;
      case 'V':horn = true;digitalWrite(r_led,HIGH);break;
      case 'v':horn = false;digitalWrite(r_led,HIGH);break;
      case 'X':
        lightFront=true;
        lightBack=true;
        horn=true;digitalWrite(r_led,HIGH);
      break;
      case 'x':
        lightFront=false;
        lightBack=false;
        horn=false;digitalWrite(r_led,HIGH);
      break;

    }
    Speedsec = Turnradius;
    if (brkonoff == 1) {
      brakeOn();
    } else {
      brakeOff();
    }
  }
}

void forward() {
  analogWrite(in1, Speed);
  
}

void back() {
  analogWrite(in2, Speed);
  
}

void left() {
  analogWrite(in3, Speed);
  
}

void right() {
  analogWrite(in4, Speed);
  
}
void forwardleft() {
  analogWrite(in1, Speed);
  analogWrite(in3, Speed);
}
void forwardright() {
  analogWrite(in1, Speed);
  analogWrite(in4, Speed);
}
void backright() {
  analogWrite(in2, Speed);
  analogWrite(in4, Speed);
}
void backleft() {
  analogWrite(in2, Speed);
  analogWrite(in3, Speed);
}

void Stop() {
  analogWrite(in1, 0);
  analogWrite(in2, 0);
  analogWrite(in3, 0);
  analogWrite(in4, 0);

}

void obstacle(){
  
  back();
  delay(500);
  Stop();


  for(int i=0;i<3;i++){
  digitalWrite(light_FR, HIGH);
  digitalWrite(light_BR, HIGH);
  delay(100);
  digitalWrite(light_FR, LOW);
  digitalWrite(light_BR, LOW);
  delay(100);}
}

void brakeOn() {
  //Here's the future use: an electronic braking system!
  // read the pushbutton input pin:
  buttonState = command;
  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == 'S') {
      if (lastButtonState != buttonState) {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, HIGH);
        delay(brakeTime);
        Stop();
      }
    }
    // save the current state as the last state,
    //for next time through the loop
    lastButtonState = buttonState;
  }
}
void brakeOff() {

}
