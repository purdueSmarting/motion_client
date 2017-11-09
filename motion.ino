#include <Servo.h>
#define pirPin 2

int calibrationTime = 30; //checking time
long unsigned int lowIn;
long unsigned int pause = 5000;
boolean lockLow = true;
boolean takeLowTime;
int PIRValue = 0;

Servo myservo;

int increase = 150;
int min_angle = 15;
int max_angle = 165;
int pos = min_angle;

void setup() {
   Serial.begin(9600);
   pinMode(pirPin, INPUT);
   myservo.attach(6);
}

void loop() {
   PIRSensor();
}

void PIRSensor() {
   if(digitalRead(pirPin) == HIGH) {
      if(lockLow) {
         PIRValue = 1;
         lockLow = false;
         Serial.println("Motion detected.");
         delay(50);
      }
      takeLowTime = true;
   }
   if(digitalRead(pirPin) == LOW) {
      if(takeLowTime){
         lowIn = millis();takeLowTime = false;
      }
      if(!lockLow && millis() - lowIn > pause) {
         PIRValue = 0;
         lockLow = true;
         Serial.println("Motion ended.");
         delay(50);
         myservo.write(pos);
         pos += increase;
         if(pos <= min_angle || pos >=max_angle)
           increase *=-1;
  
        delay(5000);
   
      }
   }
}
