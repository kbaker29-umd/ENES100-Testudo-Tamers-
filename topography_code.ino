
const int irSensorPin1 = 7; // Digital pin connected to the IR sensor's OUT pin
const int irSensorPin2 = 6;


/* A --- SL = 2 and SR = 4
B ------ SL = 1 and SR = 3
C ------ SL = 2 and 2
*/
void setup() {
  Serial.begin(9600); // Start serial communication
   pinMode(irSensorPin1, INPUT);
   pinMode(irSensorPin2, INPUT);
}




void loop() {

  int sensorValue1 = digitalRead(irSensorPin1);
  int sensorValue2 = digitalRead(irSensorPin2);
  

  float currentMillis = (unsigned)millis(); // Get the current time in milliseconds
  currentSeconds = currentMillis/1000; //Seconds

  int RC;
  int LC; 


  //LC = 1 means left corner must be side B, as this is the tallest corner and the one that will be recognized soonest
  //LC = 2 means left corner is the medium height... this can either be the corner C if both right is same height, or A is the righ corner is shorter
  //LC = 1 means right corner is medium height, could be right of side B or C
  //LC = 2 means right corner must be side c, as this is the shortest corner

  if (sensorValue1 <= 100){
    if (currentSeconds < 2){
      LC = 1;
    } else if(currentSeconds > 4){
      LC = 2;
      sensorValue1 = 3000;
    }
  }
  if (sensorValue2 <= 100){
    if (currentSeconds < 4){
      RC = 1;
    } else if(currentSeconds > 6){
      RC = 2;
      sensorValue2 = 3000;
    }
  }
  

  Serial.println(LS);
  Serial.println(RS);

  if (LC == 1 && RC == 2) {
    Serial.println("Side B");
  }
  if (LC == 2 && RC == 1) {
    Serial.println("Side C");
  }
  if (LC == 2 && RC == 2) {
    Serial.println("Side A");
  }
  /*if (sensorValue1 == 3000 && sensorValue2 == 3000){
  Serial.println(sensorValue1);
  Serial.println(sensorValue2);
  if (LS == 1 && RS == 2){
    Serial.println("Side A");
  } else if (LS == 3 && RS == 1){
    Serial.println("Side C");
  }else if (LS == 4 and RS == 3){
    Serial.println("Side B");
  }*/
  sensorValue1 = 3001; // ? not sure why this was in original code... might be for ending loop...?
  sensorValue2 = 3001;
  delay (10);
}

