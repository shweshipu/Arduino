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
}

void loop() {
 if(myReceiver.getResults()) {
    myDecoder.decode();
     if(myDecoder.value==0x22DDA857){Serial.println(" up "); 
        }
     if(myDecoder.value==0x22DD28D7){Serial.println(" down ");
        }
     if(myDecoder.value==0x22DDC837){Serial.println(" right ");
        }
     if(myDecoder.value==0x22DD9867){Serial.println(" left "); 
        }
      //Serial.println(white);

    myReceiver.enableIRIn(); 
  
  if (myReceiver.getResults()) {
    myDecoder.decode();           //Decode it
    myDecoder.dumpResults(true);  //Now print results. Use false for less detail
    myReceiver.enableIRIn();      //Restart receiver
  
  
  }
}
}

