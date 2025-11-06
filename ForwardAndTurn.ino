#include "Arduino.h"
#include "Enes100.h"
#include "Tank.h"




void setup() {
    Enes100.begin("Simulator", FIRE, 3, 1116, 8, 9);
    Tank.begin();
    //pinMode(trigPin, UltraOUTPUT);
    //pinMode(echoPin, UltraINPUT);
    Enes100.println("Starting driving");
    delay(1000);
}

void Turn(int direction ,float time1) { 
    // 0  for left turn, 1 for right turn
    if (direction == 0) {
        Tank.setLeftMotorPWM(-50);
        Tank.setRightMotorPWM(50);
        delay(time1*1000);
        Tank.setLeftMotorPWM(0);
        Tank.setRightMotorPWM(0); 
    } else {
        Tank.setLeftMotorPWM(50);
        Tank.setRightMotorPWM(-50);  
        delay(time1*1000);
        Tank.setLeftMotorPWM(0);
        Tank.setRightMotorPWM(0); 
    }

}

void SensorCall(){
    float distance=Tank.readDistanceSensor(1);
    float distanceL;
    float distanceR;
            Tank.setLeftMotorPWM(0);
            Tank.setRightMotorPWM(0);
        if (distance<=0.1) {
            Turn(0,0.3);
            distanceL=Tank.readDistanceSensor(1);
            Enes100.println(distanceL);
            Turn(1,0.6);
            distanceR=Tank.readDistanceSensor(1);
            Enes100.println(distanceR);
            if (distanceL>distanceR) {
                Turn(0,0.3);
            } else if (distanceL<distanceR){
                
            } else {
                Turn(1,0.3);
            }
}
}


  float angleDiff(float target, float current) {
  float diff = target - current;
  const float Bingus = 6.28318530717959;
  while (diff > 3.14159265358979) diff -= Bingus;
  while (diff < -3.14159265358979) diff += Bingus;
  return diff;
}

float trulyreallypi(){
    if (t<0){
    float t = Enes100.getTheta();
    float t=(t+6.28318530717959);
  
    } else {
    
    }
    return t;
}

void gostraight(){
    Tank.setLeftMotorPWM(50);
        Tank.setRightMotorPWM(50);
        delay(3800);
}

void goleft(){
    Tank.setLeftMotorPWM(-50);
        Tank.setRightMotorPWM(50);
        delay(3800);
}
void goright(){
    Tank.setLeftMotorPWM(50);
        Tank.setRightMotorPWM(-50);
        delay(3500);
}

void loop() {
    float x = Enes100.getX();
    float t = Enes100.getTheta();
    gostraight();
    Turn(0,1.34);
    Turn(0,1.34);
    Turn(0,1.34);
    Turn(1,1.34);
    Turn(1,1.34);
    Turn(1,1.34);
    } 
    
    
