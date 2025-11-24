
#include <Enes100.h>


void setup() {
  Serial.begin(9600);
  Enes100.begin("Testudo Tamers", FIRE, 459, 1116, 7, 4);
  delay(1000);


}


void loop(){

  //Transmit
  Enes100.print("X coordinate: ");
  Enes100.println(Enes100.getX());
  Enes100.print("Y coordinate: ");
  Enes100.println(Enes100.getY());
  Enes100.print("Theta: ");
  Enes100.println(Enes100.getTheta());
  Enes100.print("Visibility: ");
  Enes100.println(Enes100.isVisible());

  //Receive
  /*float theta = Enes100.getTheta();
  float X = Enes100.getX();
  float Y = Enes100.getY();
  float Vis = Enes100.isVisible();*/
  float theta = Enes100.getTheta();
  float X = Enes100.getX();
  float Y = Enes100.getY();
  float Vis = Enes100.isVisible();
  delay(1000);
  Serial.print("X coordinate: ");
  Serial.println(X);
  Serial.print("Y coordinate: ");
  Serial.println(Y);
  Serial.print("Visibility: ");
  Serial.println(Vis);
  Serial.print("Theta: ");
  Serial.println(theta);
  delay(1000);
}


