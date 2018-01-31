// cw coleman  neo RGBW circular
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
#define NUM_LEDS 16
#define BRIGHTNESS 25
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

//set up variables
int red,green,blue,white;
//set first led and total leds
int first = 10;
int leds = 16;
int count = 0;

//The event loop  *************************
void loop() {
  if (count == 0){
    //this sets up the leds for the first time through the loop
      red = 0; green = 255; blue = 0; white = 0;
  }
  count = 1;
  
    green = 255;
 
 
  circular(first,leds,red,green,blue,white);
}

// end of the event loop *************************

//red function
void circular(int s, int lds, int  r,int g,int b,int w){
// s:start   lds:the number of leds  r:red  g:green  b:blue  w:white
int delayVal = 100;// change the delayVal to speed things up
int j;
Serial.println();//debug
for(j = 0; j < 16 ; j++){
    Serial.println (s);//debug
    s = j;
          strip.setPixelColor(s, strip.Color(r,g,b,w ));
          delay(delayVal);
           strip.show();  
 }
}


