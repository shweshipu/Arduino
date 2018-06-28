/*
 * jumper color key:
 * red-power
 * brown/black/purple-ground
 * orange/green-data out
 * white/blue-data in
 * yellow-?either data in or out idk
 */


/* dump.ino Example sketch for IRLib2
   Illustrates how to receive an IR signal, decode it and print
   information about it to the serial monitor.
*/
//This includes everything. Not generally recommended.
//It's better to include only the parts of library you really need.
//But for this example it's quick and easy. See "comboDump" example
//for a more efficient way.
#include "IRLibAll.h"

#include <Servo.h>

IRrecvPCI myReceiver(2); //create receiver and pass pin number
IRdecode myDecoder;   //create decoder

Servo servo1;
Servo servo2;

int pos = 0;

int trigPin = 3;    //Trig - greed data out Jumper
int echoPin = 4;    //Echo - white data in Jumper
long duration, cm, inches;

bool forward = false;

void setup() {
  Serial.begin(9600);
  delay(2000); while (!Serial); //delay for Leonardo
  myReceiver.enableIRIn(); // Start the receiver
  Serial.println(F("Ready to receive IR signals"));
  int i;
  for(i=0;i<4;i++){
    pinMode(i+3, OUTPUT);//initialize the four pins to be used for output
  }

  servo1.attach(9);  // attaches the servo on pin 9 to the servo object
  servo2.attach(10);

  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
 int i;
 for(i=0;i<4;i++){
  digitalWrite(i+3,LOW);
 }
 if(myReceiver.getResults()) {
    myDecoder.decode();
     if(myDecoder.value==0xA10C2807){
        Serial.println(" up ");
        //digitalWrite(3,HIGH);
        //go forward
        for (pos = 0; pos <= 15; pos += 1) { // goes from 0 degrees to 180 degrees
            // in steps of 1 degree
            servo1.write(180-pos);//why does it go on forever? it should stop at pos, no?
            servo2.write(pos);
            // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
        }
        forward = true;
     }
     if(myDecoder.value==0xA10C6807){
      Serial.println(" down ");
      //digitalWrite(4,HIGH);
      for (pos = 0; pos <= 15; pos += 1) { // goes from 0 degrees to 180 degrees
            // in steps of 1 degree
            servo1.write(pos);
            servo2.write(180-pos);
            // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
        }
        forward = false;
     }
     if(myDecoder.value==0xA10CA807){
      Serial.println(" right ");
      digitalWrite(5,HIGH);
      for (pos = 0; pos <= 15; pos += 1) { // goes from 0 degrees to 180 degrees
            // in steps of 1 degree
            servo1.write(180-pos);
            servo2.write(180-pos);
            // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
      }
      forward = false;
     }
     if(myDecoder.value==0xA10CE807){
      Serial.println(" left ");
      digitalWrite(6,HIGH);
      for (pos = 0; pos <= 15; pos += 1) { // goes from 0 degrees to 180 degrees
            // in steps of 1 degree
            servo1.write(pos);
            servo2.write(pos);
            // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
      }
      forward = false;
     }
     if(myDecoder.value==0xA10CC40B){
      Serial.println(" pause ");
      digitalWrite(7,HIGH);
      servo1.attach(11);  //just moves it to pins were not using, theres probably a better way like servo.pause or something
      servo2.attach(12);
     }
     if(myDecoder.value==0xA10C840B){
      Serial.println(" play ");
      digitalWrite(7,HIGH);
      servo1.attach(9); //puts it back to the right pins
      servo2.attach(10);
     }
      //Serial.println(white);
    
    myDecoder.dumpResults(true);  //Now print results. Use false for less detail
    myReceiver.enableIRIn(); 
  
    if (myReceiver.getResults()) {
      myDecoder.decode();           //Decode it
      myDecoder.dumpResults(true);  //Now print results. Use false for less detail
      myReceiver.enableIRIn();      //Restart receiver
    
    
    }
  }
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // convert the time into a distance
  cm = (duration/2) / 29.1;
  inches = (duration/2) / 74; 
  
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  if(cm>9 && forward){//stop before falling off, hopefully
    Serial.println(" pause ");
      digitalWrite(7,HIGH);
      servo1.attach(11);  
      servo2.attach(12);
  }
  delay(250);
}


