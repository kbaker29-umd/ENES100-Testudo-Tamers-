/*
* Testudo Tamers OTV Code
*
* right and left and defined looking at the back of the OTV (the ultrasonics CANNOT detect you).
*/
#include "Arduino.h"
#include "Enes100.h"
#include "String.h"

/*
* Constant definitions 
*/

#define l_motor_for 6
#define l_motor_rev 5
#define r_motor_for 10
#define r_motor_rev 9

#define stamp_up 0
#define stamp_down 1

#define ultra_trig 11
#define ultra_echo_r 8 
#define ultra_echo_l 12

// TODO Distance sensor pins
// TODO Flame sensor pins

/*
* Function Prototypes (definitions)
*/

// Drive Functions: take inputs from 0-100 (percent)
void forward(int speed);
void reverse(int speed);
void left (int speed); //Counter-Clockwise
void right (int speed);// Clockwise

// Mission Specific Functions
int get_flames(); // count # of flames
char get_geo(); // find out geography
void extinguish(); // extinguish flames

// TODO wifi chip functions

void setup() 
{
  // Set Pins
  pinMode( l_motor_for, OUTPUT);
  pinMode( l_motor_rev, OUTPUT);
  pinMode( r_motor_for, OUTPUT);
  pinMode( r_motor_rev, OUTPUT);
  pinMode( stamp_up, OUTPUT);
  pinMode( stamp_down, OUTPUT);
  pinMode( ultra_trig, OUTPUT);
  pinMode( ultra_echo_r,INPUT);
  pinMode( ultra_echo_l, INPUT);

  //serial begin
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  forward(50,1);
  delay(1000);
  forward(0,1);
  delay(1000);

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

int get_flames()
{
  int flames = 0; //# of flames
  //use sensors to read flames
  return flames;
}

char get_geo()
{
  char geo; 
  float dist_diff = 0; 
  float duration1, duration2, distance1, distance2;
  digitalWrite(ultra_trig, LOW);
  delayMicroseconds(10);
  digitalWrite(ultra_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultra_trig, LOW);
duration1 = pulseIn(ultra_echo_l, HIGH);
duration2 = pulseIn(ultra_echo_r, HIGH);
//speed of sound = 340 m/s
//                 0.034c/us
//Total_T = Tx_t + Rx_T
distance1 = (duration1*0.034)/2;
distance2 = (duration2*0.034)/2;
Serial.print("Dist1. = ");
Serial.print(distance1);
Serial.println(" cm");
Serial.print("Dist2. = ");
Serial.print(distance2);
Serial.println(" cm");
delay(150);
dist_diff = distance2-distance1;
  //read distance senors and calculate difference 
   
  if (dist_diff == 0)
  {
    geo = 'A';
  }
  else if (dist_diff == 1)
  {
    geo = 'B';
  }
  else 
  {
    geo = 'C';
  }

  return geo;
}

void extinguish()
{
  Serial.print("Extingushing Flames...");
  digitalWrite(stamp_down, HIGH);
  delay(1000);

  Serial.print("Extingushing Flames...");
  digitalWrite(stamp_down, LOW);
  delay(10);

  Serial.print("Extingushing Flames...");
  digitalWrite(stamp_up, HIGH);
  delay(1000);

  Serial.print("Flames Extinguished!");

}
//Takes robot from intial position to angle straight to objective, returns the starting position, either Top or Bottom Position
String init_position(){
   float x = Enes100.getX();
   float y = Enes100.getY();
    float t = Enes100.getTheta();
    //if starting at the bottom position, turn to roughly 90 CCW and output Bottom Position
    if (y<1.0){
    while (t<1.54 | t>1.63){
      analogWrite(l_motor_for, 50);
      analogWrite(r_motor_rev, 50);
        float t = Enes100.getTheta();
        Serial.println(t);
        if (t>1.54 && t<1.60){
        analogWrite(l_motor_for, 0);
        analogWrite(r_motor_rev, 0);
        Serial.println("Found it");
        //change when we know exact speed
        forward(50,3);
        return ("Bottom Position");
        break;
        }
    }
    //if starting at the Top position, turn to roughly 90 CCW and output Top Position
    } else {
      while (t>-1.54 | t<-1.60){
        analogWrite(l_motor_for, 50);
      analogWrite(r_motor_rev, 50);
        float t = Enes100.getTheta();
        Serial.println(t);
        if (t<-1.54 && t>-1.60){
          analogWrite(l_motor_for, 0);
        analogWrite(r_motor_rev, 0);
         Serial.println("Found it");
         //change when we know exact speed
         forward(50,3);
         return ("Top Position");
         break;
        }
    }
}
}



