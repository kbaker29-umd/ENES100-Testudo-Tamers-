#include "Enes100.h"
int led = 13; // define the LED pin
int digitalPin = 2; // KY-026 digital interface
int analogPin = A0; // KY-026 analog interface
int digitalVal; // digital readings
int analogVal; // analog readings

void setup() {
    // Initialize Enes100 Library
    // Team Name, Mission Type, Marker ID, Room Number, Wifi Module TX Pin, Wifi Module RX Pin
    Enes100.begin("It's Lit", FIRE, 205, 1116, 3, 2);
    //Setup Distance Sensors 
    Serial.begin (9600);
    pinMode(digitalPin, INPUT);
    pinMode(analogPin, OUTPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(trigPin2, OUTPUT2);
    pinMode(echoPin2, INPUT2);
    // At this point we know we are connected.
    Enes100.println("Connected...");
}

void ultrasonic_ping() { // The sensor is triggered by a HIGH pulse of 10 or more microseconds 
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
// sends to both sensors
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin2, HIGH);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  pinMode(echoPin2, INPUT);
  duration2 = pulseIn(echoPin2, HIGH);
}

bool thermal_response(int sensor) { // The sensor is triggered by a HIGH pulse of 10 or more microseconds 
    switch (sensor) {
      case 1:
        fireint = digitalRead(digitalPin);
        break;
      case 2:
        fireint = digitalRead(digitalPin);
        break;
      case 3:
        fireint = digitalRead(digitalPin);
        break;
      case 4:
        fireint = digitalRead(digitalPin);
        break;
    }
    if (fireint >= 100){
        return true;
    }
    else {
        return false;
    }
  
}

int flamenum(){
    flamenum=1;
    if thermal_response(1)==true{
        flamenum+=1;
    } if thermal_response(2)==true{
        flamenum+=1;
    } if thermal_response(3)==true{
        flamenum+=1;
    } if thermal_response(4)==true{
        flamenum+=1;
    }
    return flamenum;
}

float ultrasonic_response(int sensor) { 
    if sensor == 1 {
    cm = (duration/2) / 29.1;    
    } else {
    duration = pulseIn(echoPin2, HIGH);
    cm = (duration/2) / 29.1; 
    }
    return cm
}




void loop() {
    float x, y, t; bool v; // Declare variables to hold the data
    //Enes100.getX will make sure you get the latest data available to you about your OTV's location.
    //The first time getX is called, X, Y, theta and visibility are queried and cached.
    //Subsequent calls return from the cache, so there is no performance gain to saving the function response to a variable.

    x = Enes100.getX();  // Your X coordinate! 0-4, in meters, -1 if no aruco is not visibility (but you should use Enes100.isVisible to check that instead)
    y = Enes100.getY();  // Your Y coordinate! 0-2, in meters, also -1 if your aruco is not visible.
    t = Enes100.getTheta();  //Your theta! -pi to +pi, in radians, -1 if your aruco is not visible.
    v = Enes100.isVisible(); // Is your aruco visible? True or False.

    if (v) // If the ArUco marker is visible
    {
        Enes100.print(x); // print out the location
        Enes100.print(",");
        Enes100.print(y);
        Enes100.print(",");
        Enes100.println(t);
    }
    else { // otherwise
        Enes100.println("Not visible"); // print not visible
    }

    // Transmit the number of candles that are lit
    Enes100.mission(NUM_CANDLES, 4);
    // Transmit the topography of the fire mission (TOP_A for topography A)
    Enes100.mission(TOPOGRAPHY, TOP_A);
    delay(1000);
}
