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
    randomSeed(analogRead(0));
}

//set up variables
int red,green,blue,white;
//set first led and total leds
int first = 0;
int leds = 16;
int count = 0;

//The event loop  *************************
void loop() {
  if (count == 0){
    //this sets up the leds for the first time through the loop
      red = 0; green = 0; blue = 255; white = 0;
  }
  
    red = 255;
    if(count % 2 == 0) {red = 0;}
 
  //circular(first,leds,red,green,blue,white);
  //if (count ==0) delay(3000);
  count++;
  if(count > 1000) count = 1; //never set count to 0
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
          strip.setPixelColor(s, strip.Color(r,g,b,w ));
          delay(delayVal);
           strip.show();  
            s++; // increase s by 1;
            if (s > (lds -1)) { s = 0;}  
 }
}


 void binadd(int s, int lds, int  r,int g,int b,int w){
  // s:start   lds:the number of leds  r:red  g:green  b:blue  w:white
int delayVal = 100;// change the delayVal to speed things up
Serial.println();//debug

//initialize arrays to hold number
boolean values = [16];
boolean carry = [16];
if (values[0] == NULL){
for(int i = 0; i<16;i++){
  values[i]=false;
  carry[i]=false;
}}

strip.setPixelColor(s, strip.Color(r,g,b,w ));
values[0] = true;
values = compare(values , carry);

   delay(delayVal);
   strip.show();  
   s++; // increase s by 1;
   if (s > (lds -1)) { s = 0;}  
 
 }

 
 boolean compare(boolean values,boolean carry){
  for(int i = 0; i<16; i++){
    //1+1=10
    if(values[i] == true && carry[i] == true){
      values[i]= false;
      carry[i]=false;
      if(i!=15){
        carry[i+1]=true;
      }
    }
    //0+1=1
    if(values[i]== false && carry[i] == true){
      values[i]=true;
      carry[i]=false;
    }
    if(carry[i]==false){
      return(values);
    }
  }
 }
}


