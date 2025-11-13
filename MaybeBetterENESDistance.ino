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
        Tank.setLeftMotorPWM(-100);
        Tank.setRightMotorPWM(100);
        delay(time1*1000);
        Tank.setLeftMotorPWM(0);
        Tank.setRightMotorPWM(0); 
    } else {
        Tank.setLeftMotorPWM(100);
        Tank.setRightMotorPWM(-100);  
        delay(time1*1000);
        Tank.setLeftMotorPWM(0);
        Tank.setRightMotorPWM(0); 
    }

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
        delay(3800);
}


void loop() {
    float x = Enes100.getX();
    float t = Enes100.getTheta();
    if (x<3.5){
    while (t<1.47 | t>1.63){
        Tank.setLeftMotorPWM(50);
        Tank.setRightMotorPWM(-50);  
        float t = Enes100.getTheta();
        Enes100.println(t);
        if (t>1.5 && t<1.63){
          Tank.turnOffMotors();
         Enes100.println("Found it");
         break;
        }
    }
    
    Tank.turnOffMotors();
    Enes100.println("Found itt");
     float t = Enes100.getTheta();
    Tank.setLeftMotorPWM(50);
    Tank.setRightMotorPWM(50);
    delay(11000);
    Tank.turnOffMotors();
    delay(1000);
    goright();
    Tank.turnOffMotors();
    delay(100);
    Tank.readDistanceSensor(1);
    
   Tank.setLeftMotorPWM(50);
    Tank.setRightMotorPWM(50);
    delay(3000);
    Tank.turnOffMotors();
    delay(1000);
    Tank.turnOffMotors();
    delay(100);
    Tank.readDistanceSensor(1);
    if (-Tank.readDistanceSensor(1)<=0.6){
        Enes100.println("uh oh oh");
        Enes100.println(Tank.readDistanceSensor(1));
        goright();
        gostraight();
        gostraight();
        goleft();
        Tank.turnOffMotors();
        
        if (Tank.readDistanceSensor(1)<=0.6){
        goright();
        gostraight();
        Tank.setLeftMotorPWM(50);
        Tank.setRightMotorPWM(50);
        delay(1000);
        goleft();
        gostraight();
        gostraight();
        Tank.setLeftMotorPWM(50);
        Tank.setRightMotorPWM(50);
        delay(1000);
        
        
         if (Tank.readDistanceSensor(1)<=0.8){
            Tank.setLeftMotorPWM(-50);
            Tank.setRightMotorPWM(50);
            delay(3800);
            gostraight();
            gostraight();
            goright();
            Tank.setLeftMotorPWM(50);
            Tank.setRightMotorPWM(50);
            delay(7000);
            Tank.setLeftMotorPWM(50);
            Tank.setRightMotorPWM(-50);
            delay(3800);
            Tank.setLeftMotorPWM(50);
            Tank.setRightMotorPWM(50);
            delay(6000);
            goleft();
            Tank.setLeftMotorPWM(50);
            Tank.setRightMotorPWM(50);
            delay(6500);
            gostraight();
         }
        
        } else {
            Enes100.println("uh oh");
            gostraight();
            gostraight();
            if (Tank.readDistanceSensor(1)<=0.6){
                goleft();
                Tank.setLeftMotorPWM(50);
                Tank.setRightMotorPWM(50);
                delay(4500);
                goright();
                 gostraight();
                gostraight();
                gostraight();
                goleft();
                Tank.setLeftMotorPWM(50);
                Tank.setRightMotorPWM(50);
                delay(6000);
                
            } else {
            gostraight();
            gostraight();
            gostraight();
            goright();
            Tank.setLeftMotorPWM(50);
            Tank.setRightMotorPWM(50);
            delay(6000);
            Tank.setLeftMotorPWM(50);
            Tank.setRightMotorPWM(-50);
            delay(2700);
            Tank.setLeftMotorPWM(50);
            Tank.setRightMotorPWM(50);
            delay(6000);
            goleft();
            Tank.setLeftMotorPWM(50);
            Tank.setRightMotorPWM(50);
            delay(6000);
            gostraight();
            }
            
        }
        Tank.setLeftMotorPWM(0);
        Tank.setRightMotorPWM(0);
        delay(100);
        //No Top Left Block
    } else {
            Tank.setLeftMotorPWM(50);
            Tank.setRightMotorPWM(50);
            delay(9000);
            //Top Right Block
            if (Tank.readDistanceSensor(1)<=0.6){
            Enes100.println(Tank.readDistanceSensor(1));
            goright();
            Tank.setLeftMotorPWM(50);
            Tank.setRightMotorPWM(50);
            delay(8000);
            goleft();
            //Middle Right Block
            Tank.readDistanceSensor(1);
            if (Tank.readDistanceSensor(1)<=0.6){
                goright();
                Enes100.println(Tank.readDistanceSensor(1));
            Tank.setLeftMotorPWM(50);
            Tank.setRightMotorPWM(50);
            delay(8000);
            goleft();
            Tank.setLeftMotorPWM(50);
            Tank.setRightMotorPWM(50);
            delay(17000);
            } else {
            Tank.setLeftMotorPWM(50);
            Tank.setRightMotorPWM(50);
            delay(6000);
            goleft();
            Tank.setLeftMotorPWM(50);
            Tank.setRightMotorPWM(50);
            delay(6000);
            }
         } else {
            gostraight();
            gostraight();
            goright();
            Tank.setLeftMotorPWM(50);
            Tank.setRightMotorPWM(50);
            delay(10000);
            Tank.setLeftMotorPWM(-50);
            Tank.setRightMotorPWM(50);
            delay(2700);
            Tank.setLeftMotorPWM(50);
            Tank.setRightMotorPWM(50);
            delay(8000);
         }
    }
    //Turn(1,clockwiseDistanceFromPiOver2(t));
   // double desired_time = (abs((t-1.570796)/(1.151)));
  // 2. Compute how much to turn to face UP (90° CCW)
    }else{
        Tank.turnOffMotors();
        Enes100.println("We did it!");
    }
    } 
       
    
     
    //Turn(1,clockwiseDistanceFromPiOver2(t));
   // double desired_time = (abs((t-1.570796)/(1.151)));
  // 2. Compute how much to turn to face UP (90° CCW)
        

    
    

    