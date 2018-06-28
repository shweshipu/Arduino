/* dump.ino Example sketch for IRLib2
   Illustrates how to receive an IR signal, decode it and print
   information about it to the serial monitor.
*/
//This includes everything. Not generally recommended.
//It's better to include only the parts of library you really need.
//But for this example it's quick and easy. See "comboDump" example
//for a more efficient way.
#include "IRLibAll.h"

IRrecvPCI myReceiver(2); //create receiver and pass pin number
IRdecode myDecoder;   //create decoder

void setup() {
  Serial.begin(9600);
  delay(2000); while (!Serial); //delay for Leonardo
  myReceiver.enableIRIn(); // Start the receiver
  Serial.println(F("Ready to receive IR signals"));
  int i;
  for(i=0;i<4;i++){
    pinMode(i+3, OUTPUT);//initialize the four pins to be used for output
  }
}

void loop() {
 int i;
 for(i=0;i<4;i++){
  digitalWrite(i+3,LOW);
 }
 if(myReceiver.getResults()) {
    myDecoder.decode();
     if(myDecoder.value==0xA10C2807){Serial.println(" up "); digitalWrite(3,HIGH);
        }
     if(myDecoder.value==0xA10C6807){Serial.println(" down ");digitalWrite(4,HIGH);
        }
     if(myDecoder.value==0xA10CA807){Serial.println(" right ");digitalWrite(5,HIGH);
        }
     if(myDecoder.value==0xA10CE807){Serial.println(" left "); digitalWrite(6,HIGH);
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

