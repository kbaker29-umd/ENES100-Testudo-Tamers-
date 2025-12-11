#include "Arduino.h"
#include "Enes100.h"

#define l_motor_for 6
#define l_motor_rev 5
#define r_motor_for 10
#define r_motor_rev 9

void setup() {
  pinMode( l_motor_for, OUTPUT);
  pinMode( l_motor_rev, OUTPUT);
  pinMode( r_motor_for, OUTPUT);
  pinMode( r_motor_rev, OUTPUT);
  pinMode( 4, INPUT);
  pinMode( 7, OUTPUT);
  delay(1000);
  //Enes100.begin("Testudo Tamers", FIRE, 459, 1116, 7, 4);
  delay(1000);
  Serial.begin(9600);
  //Enes100.println("Connected...");
  //Enes100.isConnected();
}

void forward(int speed, float time)
{
  speed *= 2.55;// convert the percentage to values (0-100) to values of pwm (0-255)
  Serial.print("Moving Forward @ ");
  Serial.println(speed);

  analogWrite(l_motor_for, (int)speed);
  analogWrite(r_motor_for, (int)speed);
  delay(time*1000);
  analogWrite(l_motor_for, 0);
  analogWrite(r_motor_for, 0);
  
}

void reverse(int speed, float time)
{
  speed *= 2.55;
  Serial.print("Moving Backwards @ ");
  Serial.println(speed);

  analogWrite(l_motor_rev, (int)speed);
  analogWrite(r_motor_rev, (int)speed);
  delay(time*1000);
  analogWrite(l_motor_rev, 0);
  analogWrite(r_motor_rev, 0);
}

void left(int speed, float time)
{
  speed *= 2.55;
  Serial.print("Spinning CCW @ ");
  Serial.println(speed);

  analogWrite(l_motor_rev, (int)speed);
  analogWrite(r_motor_for, (int)speed);
  delay(time*1000);
  analogWrite(l_motor_rev, 0);
  analogWrite(r_motor_for, 0);

}

void right(int speed, float time)
{
  speed *= 2.55;
  Serial.print("Spinning CW @ ");
  Serial.println(speed);

  analogWrite(l_motor_for, (int)speed);
  analogWrite(r_motor_rev, (int)speed);
  delay(time*1000);
  analogWrite(l_motor_for, 0);
  analogWrite(r_motor_rev, 0);
}
float get_distance(){
  float ultra1, ultra2, distance;
  digitalWrite(ultra_trig, LOW);
  delayMicroseconds(10);
  digitalWrite(ultra_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultra_trig, LOW);
  ultra1 = pulseIn(ultra_echo_l, HIGH);
  ultra2 = pulseIn(ultra_echo_r, HIGH);
  distance = (ultra1+ultra2)/2;
  return distance;

}

void navigation_path(){
  if (InitPosition == 0){
    right(50, 1);
    float x = Enes100.getX();
    while (x<3.3){
      forward(50,3);
      while (get_distance()<6){
      right(50,1);
      forward(50,3);
      left(50,1);
      }
    }
      float y = Enes100.getY();
      if (y>1.2){
        right(50,1);
      forward(50,3);
      left(50,1);
      forward(50,2);
      } else if (y>0.8){
        right(50,1);
      forward(50,2);
      left(50,1);
      forward(50,2);
      } else { 
      forward(50,3);
      }
  }
    else {
    left(50, 1);
    float x = Enes100.getX();
    while (x<3.3){
      forward(50,3);
      //might be wrong formatting
      while (get_distance()<6){
      left(50,1);
      forward(50,3);
      right(50,1);
      get_distance();
      }
    }
      float y = Enes100.getY();
      //jack fix for endzone
      if (y>1.2){
      right(50,1);
      forward(50,3);
      left(50,1);
      forward(50,2);
      } else if (y>0.8){
      right(50,1);
      forward(50,2);
      left(50,1);
      forward(50,2);
      } else {
      forward(50,3);
      }
    }
    }


void loop() {
  // put your main code here, to run repeatedly:
  //init_position();
  bool v = Enes100.isVisible(); // Is your aruco visible? True or False.
    if (v) // If the ArUco marker is visible
    {
        Enes100.println("I see You"); // print out the location
        
    }
    else { // otherwise
        Enes100.println("Not visible"); // print not visible
        Serial.println("Found it");
    }
    
}