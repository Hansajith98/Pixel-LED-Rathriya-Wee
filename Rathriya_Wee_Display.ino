#include <FastLED.h>

#define LED_PIN     3
#define COLOR_ORDER RGB
#define CHIPSET     WS2811
#define NUM_LEDS    150

CRGB leds[NUM_LEDS];

int brightness=255;

void setup() {
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS); 
  Serial.begin(9600);
}

void loop() {

  change_fade(0); //ok
  HSV_brightness(20,5);  //ok
  hue_patterns();  //ok
}


void change_fade(int hue){

   for(byte color=0; color<3; color++){     
      for(int led=0; led<NUM_LEDS+6; led++){
        if(led>=0 && led<NUM_LEDS)    leds[led][color]   = brightness;
        if(led>=1 && led<NUM_LEDS+1)  leds[led-1][color] = brightness-75; 
        if(led>=2 && led<NUM_LEDS+2)  leds[led-2][color] = brightness-125; 
        if(led>=3 && led<NUM_LEDS+3)  leds[led-3][color] = brightness-175;
        if(led>=4 && led<NUM_LEDS+4)  leds[led-4][color] = brightness-215;
        if(led>=5 && led<NUM_LEDS+5)  leds[led-5][color] = brightness-235;
        if(led>=6 && led<NUM_LEDS+6)  leds[led-6] = CHSV(hue++,255,255);     
        FastLED.show();
        delay(20);
        if(hue>=255)  hue=0;
      }
   }

   for(byte color=0; color<3; color++){     
      for(int led=NUM_LEDS-1; led>=-6; led--){
        if(led>=0 && led<NUM_LEDS)    leds[led][color]   = brightness;
        if(led>=-1 && led<NUM_LEDS-1)  leds[led+1][color] = brightness-75; 
        if(led>=-2 && led<NUM_LEDS-2)  leds[led+2][color] = brightness-125; 
        if(led>=-3 && led<NUM_LEDS-3)  leds[led+3][color] = brightness-175;
        if(led>=-4 && led<NUM_LEDS-4)  leds[led+4][color] = brightness-215;
        if(led>=-5 && led<NUM_LEDS-5)  leds[led+5][color] = brightness-235;
        if(led>=-6 && led<NUM_LEDS-6)  leds[led+6] = CHSV(hue++,255,255);     
        FastLED.show();
        delay(20);
        if(hue>=255)  hue=0;
      }
   }  
}

void hue_patterns(){
      FastLED.setBrightness(brightness);
  for(int hue=0; hue<256; hue+=5){
    for(int led=0; led<NUM_LEDS; led++){
      leds[led] = CHSV(hue,255,255);
      FastLED.show();
      delay(10);
    }
  }
}

void HSV_brightness(int speed_,int brightness_){

  for(int hue=0; hue<256; hue+=5){      
    for(brightness_=5; brightness_<=255; brightness_+=5){
        FastLED.setBrightness(brightness_);
      for(int led=0; led<NUM_LEDS; led++){
        leds[led] = CHSV(hue,255,255);
      }
        FastLED.show();
        delay(speed_);
    }
    for(brightness_=255; brightness_>=5; brightness_-=5){
        FastLED.setBrightness(brightness_);
      for(int led=0; led<NUM_LEDS; led++){
        leds[led] = CHSV(hue,255,255);
      }
        FastLED.show();
        delay(speed_);
    }
  }  
}

void all_leds(byte state, int light){
    if(state==0){
        for(int led=0; led<NUM_LEDS; led++){
            leds[led].r = light;
            leds[led].g = light;
            leds[led].b = light;
        }
            FastLED.show();
    }
    if(state==1){
        for(int led=0; led<NUM_LEDS; led++){
            leds[led].r = light;
            leds[led].g = light;
            leds[led].b = light;
        }
            FastLED.show();
    }
}
