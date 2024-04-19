
/*
 * Created by Surajit Majumdar//12-07-2017
 * Project: Bluetooth Control Car
 */
 
 int outPin1 = 2;     //motor1
 int outPin2 = 3;    //motor1

 int outPin3 = 4;   //motor2
 int outPin4 = 5;   //motor2

 char bt = 0;       //BT 

 #define trigPin 6           // Trig Pin Of HC-SR04
#define echoPin 7
#define light_F 8    //LED Front Right   pin A0 for Arduino Uno
#define light_B 9    //LED Back Right    pin A2 for Arduino Uno
#define horn 10 
 

 void setup()
 {
   Serial.begin(9600);
   
   pinMode(outPin1,OUTPUT);
   pinMode(outPin2,OUTPUT);
   pinMode(outPin3,OUTPUT);
   pinMode(outPin4,OUTPUT);
   pinMode(light_F,OUTPUT);
   pinMode(light_B,OUTPUT);
   pinMode(horn,OUTPUT);

 }
 void loop()
 {
   if (Serial.available() > 0) //save incoming data to variable 'bt'
   {
     bt = Serial.read();

   
     if(bt == 'F')           //move forwards
     {
       digitalWrite(outPin1,LOW);
       digitalWrite(outPin2,HIGH);
       digitalWrite(outPin3,LOW);
       digitalWrite(outPin4,LOW); 
     }
     else if (bt == 'B')      //move backwards
     {
       
       digitalWrite(outPin1,HIGH);
       digitalWrite(outPin2,LOW);
       digitalWrite(outPin3,LOW);
       digitalWrite(outPin4,LOW);
       
     }
     else if (bt == 'S')     //stop!!
     {  

       digitalWrite(outPin1,LOW);
       digitalWrite(outPin2,LOW);
       digitalWrite(outPin3,LOW);
       digitalWrite(outPin4,LOW); 
       for(int i=0;i<3;i++)
       {
         digitalWrite(light_B,HIGH);
         delay(50);
         digitalWrite(light_B,LOW);
         delay(50);
       }
       
     }
     else if (bt == 'R')    // turn wheels right
     {
       digitalWrite(outPin3,LOW);
       digitalWrite(outPin4,HIGH);
       digitalWrite(outPin1,LOW);
       digitalWrite(outPin2,LOW);
     }
     else if (bt == 'L')     //turn wheels left
     {
       digitalWrite(outPin3,HIGH);
       digitalWrite(outPin4,LOW);
       digitalWrite(outPin1,LOW);
       digitalWrite(outPin2,LOW);
     }
     else if (bt== 'G')      //move forward left
     {
      digitalWrite(outPin1,HIGH);
      digitalWrite(outPin2,LOW);
      digitalWrite(outPin3,HIGH);
      digitalWrite(outPin4,LOW);
     }
     else if (bt== 'I')      //move forward right
     {
      digitalWrite(outPin1,HIGH);
      digitalWrite(outPin2,LOW);
      digitalWrite(outPin3,LOW);
      digitalWrite(outPin4,HIGH);
     }
     else if (bt== 'H')      //move backward left
     {
      digitalWrite(outPin1,LOW);
      digitalWrite(outPin2,HIGH);
      digitalWrite(outPin3,HIGH);
      digitalWrite(outPin4,LOW);
     }
     else if (bt=='J')       //move backward right
     {
      digitalWrite(outPin1,LOW);
      digitalWrite(outPin2,HIGH);
      digitalWrite(outPin3,LOW);
      digitalWrite(outPin4,HIGH);
     }
     else if(bt=='W')
     {
       digitalWrite(light_F,HIGH);
     }
     else if(bt=='w')
     {
       digitalWrite(light_F,LOW);
     }
     else if(bt=='U')
     {
       digitalWrite(light_B,HIGH);
     }
     else if(bt=='u')
     {
       digitalWrite(light_B,LOW);
     }
     else if(bt=='V')
     {
       digitalWrite(horn,HIGH);
     }
     else if(bt=='v')
     {
       digitalWrite(horn,LOW);
     }
     else if(bt=='X')
     {
        digitalWrite(horn,HIGH);
        digitalWrite(light_B,HIGH);
        digitalWrite(light_F,HIGH);
     }
      
   }
   
 }

