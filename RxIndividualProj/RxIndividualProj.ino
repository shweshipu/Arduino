#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
#define NUM_LEDS 16
#define BRIGHTNESS 15
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);




char incomingByte = 0;   // for incoming serial data
int Range [ 2 ];

void setup() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
        #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
    randomSeed(analogRead(0));
}

void loop() {
        int inches;
        String inchstr;

        
        // send data only when you receive data:
        if (Serial.available() > 0) {
              
      int condition=1; //conditionis int type
      if(condition==1){
      int first =Serial.read(); //check for the start of a message, noted by "R"
      
      if (first== 82){
      condition=0;
      //recieve the digits that follow the "R"
      Range[0]=Serial.read();
      Range[1]=Serial.read();
     
      int i;
      
      //iterate through Range and concatenate the digits together
         for ( i = 0; i < 2; i++){
      if(Range[i] != 82 && Range[i] != 0){
        //add the digits gotten by concatenation (ex. 2+2 = 22)
        inchstr = inchstr + (Range[i]-48);
        
        
        //Serial.println(Range[i]);      
      }
      }
      inches = inchstr.toInt();
      Serial.println(inches);
      if(inches >=0){
        
      set_neopixel(inches);
      }
      
      }
      int i;
      inches = 0;
      inchstr = "";
      for(i = 0;i<2;i++){
        Range[i] = 0;
        }
       }
      }
      
}
void set_neopixel(int inches){
  int i;
  for(i = 0;i<16;i++){
    strip.setPixelColor(i, strip.Color(0,0,0,0 ));
  }
  for(i = 0;i<inches && i<16;i++){
    strip.setPixelColor(i, strip.Color(255,0,0,5 ));
        
  
  //delay(50);

  }
    strip.show();
}

