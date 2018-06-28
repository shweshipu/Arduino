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
        digitalWrite(3,HIGH);
        //go forward
        for (pos = 0; pos <= 15; pos += 1) { // goes from 0 degrees to 180 degrees
            // in steps of 1 degree
            servo1.write(180-pos);//why does it go on forever? it should stop at pos, no?
            servo2.write(pos);
            // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
        }
     }
     if(myDecoder.value==0xA10C6807){
      Serial.println(" down ");
      digitalWrite(4,HIGH);
      for (pos = 0; pos <= 15; pos += 1) { // goes from 0 degrees to 180 degrees
            // in steps of 1 degree
            servo1.write(pos);
            servo2.write(180-pos);
            // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
        }
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
}





/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/


// create servo object to control a servo
// twelve servo objects can be created on most boards
// variable to store the servo position
/*

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo1.write(pos);
    servo2.write(180-pos);
    // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    servo1.write(pos);              // tell servo to go to position in variable 'pos'
    servo2.write(180-pos); 
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

*/
