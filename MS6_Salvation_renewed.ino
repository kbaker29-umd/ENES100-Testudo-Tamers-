#include "Arduino.h"
#include "Enes100.h"
#include "String.h"

#define l_motor_for 6
#define l_motor_rev 5
#define r_motor_for 10
#define r_motor_rev 9

#define stamp_up 2
#define stamp_down 3

#define ultra_trig 11
#define ultra_echo_r 8 
#define ultra_echo_l 12

float currentSeconds = 0; // Stores the current count of seconds
float LS;
float RS;
//const int irSensorPin1 = A0; // Digital pin connected to the IR sensor's OUT pin
//const int irSensorPin2 = A1;

String InitPosition = "";

void setup() {
  // put your setup code here, to run once:
  pinMode( l_motor_for, OUTPUT);
  pinMode( l_motor_rev, OUTPUT);
  pinMode( r_motor_for, OUTPUT);
  pinMode( r_motor_rev, OUTPUT);
  pinMode( stamp_up, OUTPUT);
  pinMode( stamp_down, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  Serial.begin(9600);
  //Enes100.begin("Testudo Tamers",FIRE,459,1116,7,4);
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

void extinguish()
{
  Serial.print("Extingushing Flames...");
  digitalWrite(stamp_down, HIGH);
  delay(700);

  delay(10);
  Serial.print("Extingushing Flames...");
  delay(10);
  digitalWrite(stamp_down, LOW);
  delay(10);

  Serial.print("Extingushing Flames...");
  digitalWrite(stamp_up, HIGH);
  delay(1000);
  digitalWrite(stamp_up, LOW);

  Serial.print("Flames Extinguished!");
}
void hump(){
  float x = Enes100.getX();
  while (x<=3.3){
  //forward(100,0.5);
  reverse(100,0.25);
  x = Enes100.getX();
  }
  Serial.println("Done");
}

void init_position(){
   float x = Enes100.getX();
   float y = Enes100.getY();
    float t = Enes100.getTheta();
    //if starting at the bottom position, turn to roughly 90 CCW and output Bottom Position
    if (y<1.0){
    while (t<1.54 || t>1.60){
      analogWrite(l_motor_for, 192);
      analogWrite(r_motor_rev, 192);
        t = Enes100.getTheta();
        Serial.println(t);

        if (t>1.54 && t<1.60){
        analogWrite(l_motor_for, 0);
        analogWrite(r_motor_rev, 0);
        Serial.println("Found it");
        //change when we know exact speed
        forward(50,3);
        InitPosition = ("Bottom Position");
        break;
        }
    }
    //if starting at the Top position, turn to roughly 90 CCW and output Top Position
    } else {
      while (t>-1.54 || t<-1.60){
        analogWrite(l_motor_for, 122);
      analogWrite(r_motor_rev, 122);
        t = Enes100.getTheta();
        Serial.println(t);
        if (t<-1.54 && t>-1.60){
          analogWrite(l_motor_for, 0);
        analogWrite(r_motor_rev, 0);
         Serial.println("Found it");
         //change when we know exact speed
         forward(50,3);
         InitPosition = ("Top Position");
         break;
        }
    }
}
}

char get_geo(){
  float currentMillis = millis(); // Get the current time in milliseconds
    currentSeconds = currentMillis/1000;
//Serial.println(currentSeconds);
    int sensorValue1 = digitalRead(A0); // Read the digital value from the IR sensor
    int sensorValue2 = digitalRead(A1); // Read the digital value from the IR sensor


  // Read the analog value from the sensor's AO pin
  // Print the analog value to the serial monitor
  if (sensorValue1 = LOW){
    if ((currentSeconds > 2.9)&&(currentSeconds < 3.2)){
      LS = 1;
    } else if ((currentSeconds > 5.9)&&(currentSeconds < 6.2)){
      LS = 2;
    }else{
      LS = 3;
    }
    sensorValue1 = 3000;
  }
  if (sensorValue2 = LOW){
 if (currentSeconds < 3){
      RS = 1;
    } else if(currentSeconds > 3){
      RS = 2;
    }else{
      RS = 3;
    }  
        sensorValue2 = 3000;
Serial.println(RS);
  }
  if (sensorValue1 == 3000 && sensorValue2 == 3000){
  Serial.println(sensorValue1);
  Serial.println(sensorValue2);
  if (LS == 1 && RS == 2){
    return("A");
  } else if (LS == 3 && RS == 1){
    return("C");
  }else if (LS == 4 && RS == 3){
    Serial.println("B");
  }
  sensorValue1 = 3001;
  sensorValue2 = 3001;
  }
}

int flame_num(){
  int flameDetected1 = digitalRead(A2);
  int flameDetected2 = digitalRead(A3);
  int flame_num = 1;
  digitalWrite(stamp_down, HIGH);
  delay(400);
  digitalWrite(stamp_down, LOW);

  if (flameDetected1 == LOW) { // Flame detected
   flame_num+=1;
  }
  if (flameDetected2 == LOW) { // Flame detected
   flame_num+=1;
  }
  // Add a small delay to avoid continuous readings and reduce serial output spam
  delay(500);
  forward(67, 0.30);
  delay(500);
  if (flameDetected1 == LOW) { // Flame detected
   flame_num+=1;
  }
  if (flameDetected2 == LOW) { // Flame detected
   flame_num+=1;
  }
  return flame_num;
}






void loop() {
  // put your main code here, to run repeatedly:
 // extinguish();
  init_position();
  //hump();
}
