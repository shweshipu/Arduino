// cw coleman  neo RGBW circular
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
#define NUM_LEDS 16
#define BRIGHTNESS 10
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
unsigned char values[16];




//The event loop  *************************
void loop() {
  if (count == 0){
    //this sets up the leds for the first time through the loop
      red = 0; green = 0; blue = 255; white = 0;
      for(int i = 0; i<16;i++){
        values[i]=0;
      }
  }

  binadd(count,leds,red,green,blue,white);
  
  count++;
  if(count > 1000) count = 1; //never set count to 0
}

// end of the event loop *************************
/*
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
*/

void binadd(int s, int lds, int  r,int g,int b,int w){
  // s:start   lds:the number of leds  r:red  g:green  b:blue  w:white
  int delayVal = 600;// change the delayVal to speed things up
  Serial.println();//debug

  //initialize arrays to hold number

  unsigned char carry[16];
  int i;
   for(i = 0; i<16;i++){
    carry[i]=0;
  }
  

  //add one to values
  carry[0] = 1;
  compare(carry);
  
  //show the values
  i=0;
  for(i=0;i<16;i++){
    if(values[i]){
      strip.setPixelColor(i, strip.Color(r,g,b,w ));
    }
    else{
      strip.setPixelColor(i, strip.Color(0,0,0,0));
    }
  }
   delay(delayVal);
   strip.show();  
}


 
void compare(unsigned char* carry){
  int i;
  for(i = 0; i<16; i++){
    //1+1=10
    if(values[i] && carry[i]){
      values[i]= 0;
      carry[i]= 0;
      if(i!=15){
        carry[i+1]=1;
      }
    }
    //0+1=1
    if( !values[i] && carry[i]){
      values[i]=1;
      carry[i]=0;
    }
    /*
    if(!carry[i]){
      return;
    }
    //goshdarn it
    */
  }
  
   return;
 }


