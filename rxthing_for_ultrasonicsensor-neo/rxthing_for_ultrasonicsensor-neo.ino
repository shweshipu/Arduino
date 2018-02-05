#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
#define NUM_LEDS 16
#define BRIGHTNESS 25
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);




char incomingByte = 0;   // for incoming serial data
int Range [ 2 ];

void setup() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
}

void loop() {
        int inches;


        
        // send data only when you receive data:
        if (Serial.available() > 0) {
                // read the incoming byte:
                incomingByte = Serial.read();

                // say what you got:
                Serial.print("I received: ");
                Serial.println(incomingByte);
               
      int condition=1; //conditionis int type
      if(condition==1){
      int first =Serial.read(); //check for the start of a message, noted by "R"
      if (first=="R"){
      condition=0;
      //recieve the digits that follow the "R"
      Range[0]=Serial.read();
      Range[1]=Serial.read();
      Range[2]=Serial.read();
      int i;
      String inchstr;
      //iterate through Range and concatenate the digits together
         for ( i = 0; i < 3; i++){
      if(Range[i] != "R" && Range[i] != NULL){
        //add the digits gotten by concatenation (ex. 2+2 = 22)
        inchstr = inchstr + Range[i];
        
      }
      }
      //convert the string to an integer
      inches = inchstr.toInt();
      Serial.println(inches);
      set_neopixel(inches);
        }
       }
      }
      
}
void set_neopixel(int inches){
  int i;
  for(i = 0;i<inches && i<16;i++){
    strip.setPixelColor(i, strip.Color(0,0,0,255 ));
  }
}

