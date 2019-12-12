#include <FastLED.h>

#define LED_PIN     3
#define LED_FIRST    148
#define BRIGHTNESS  255
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB


#define CAPTION_BRIGHTNESS  150
#define END_CAPTION   26
#define NUM_LEDS   (LED_FIRST + END_CAPTION +1)
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 1000

int count = 0;
int hue=0;

// This example shows several ways to set up and use 'palettes' of colors
// with FastLED.
//
// These compact palettes provide an easy way to re-colorize your
// animation on the fly, quickly, easily, and with low overhead.
//
// USING palettes is MUCH simpler in practice than in theory, so first just
// run this sketch, and watch the pretty lights as you then read through
// the code.  Although this sketch has eight (or more) different color schemes,
// the entire sketch compiles down to about 6.5K on AVR.
//
// FastLED provides a few pre-configured color palettes, and makes it
// extremely easy to make up your own color schemes with palettes.
//
// Some notes on the more abstract 'theory and practice' of
// FastLED compact palettes are at the bottom of this file.



CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;


void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
}


void loop()
{
    ChangePalettePeriodically();
    
    static uint8_t startIndex = 148;
    startIndex = startIndex - 1; /* motion speed */
    
    FillLEDsFromPaletteColors( startIndex);
    
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
    FastLED.setBrightness(  CAPTION_BRIGHTNESS );
    
    count++;
    if(count == 10){count = 0;}
    forCaption();
    FastLED.show();
    //FastLED.setBrightness(  BRIGHTNESS );
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}


// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.  All are shown here.

void ChangePalettePeriodically()
{
    uint8_t secondHand = (millis() / 1000) % 60;
    static uint8_t lastSecond = 99;
    
    if( lastSecond != secondHand) {
        lastSecond = secondHand;
        if( secondHand ==  0)  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; }
        if( secondHand == 10)  { SetupMyPalette1();                         currentBlending = NOBLEND; }
        if( secondHand == 15)  { SetupMyPalette1();                         currentBlending = LINEARBLEND; }
        if( secondHand == 20)  { SetupPurpleAndRedPalette();               currentBlending = LINEARBLEND; }
        if( secondHand == 25)  { SetupTotallyRandomPalette();              currentBlending = LINEARBLEND; }
        if( secondHand == 30)  { SetupBlackAndWhiteStripedPalette();       currentBlending = NOBLEND; }
        if( secondHand == 35)  { SetupBlackAndWhiteStripedPalette();       currentBlending = LINEARBLEND; }
        if( secondHand == 40)  { currentPalette = RainbowColors_p;       currentBlending = LINEARBLEND; }
        if( secondHand == 45)  { currentPalette = PartyColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 50)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = LINEARBLEND;  }
        if( secondHand == 55)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = NOBLEND; }
        if( secondHand == 70)  { currentPalette = RainbowStripeColors_p;   currentBlending = LINEARBLEND; }
    }

}

// This function fills the palette with totally random colors.
void SetupTotallyRandomPalette()
{
    for( int i = 0; i < 16; i++) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
}

void SetupMyPalette1(){
  if(hue>255)hue = 0;
  while(hue < 256) {
    for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(hue++, 255, 255);
      FastLED.show(); 
      delay(30);
      fadeall();
    }
  }
}

void SetupMyPalette2(){
  int x = 200;
  while(x != 1){
    if(hue>255)hue = 0;
    leds[random(NUM_LEDS)] = CHSV(hue++, 255, 255);
    x -= 10;
    delay(x); 
  }
  for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(hue++, 255, 255);
    }
    FastLED.show(); 
    delay(30);
}

void fadeall() {
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i].nscale8(253); 
    }
  }

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndWhiteStripedPalette()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB::White;
    currentPalette[4] = CRGB::White;
    currentPalette[8] = CRGB::White;
    currentPalette[12] = CRGB::White;
    
}

// This function sets up a palette of purple and green stripes.
void SetupPurpleAndRedPalette()
{
    CRGB purple = CHSV( HUE_PURPLE, 255, 255);
    CRGB green  = CHSV( HUE_RED, 255, 255);
    CRGB black  = CRGB::Black;
    
    currentPalette = CRGBPalette16(
                                   green,  green,  black,  black,
                                   purple, purple, black,  black,
                                   green,  green,  black,  black,
                                   purple, purple, black,  black );
}


// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};

void forCaption(){
  //pattern1ForCaption();
  //pattern2ForCaption();
  //pattern3ForCaption();
  
}


void pattern1ForCaption(){
  if(count < 10){
    for(int i = LED_FIRST;i < (LED_FIRST + END_CAPTION +1) ;i++){
      if (hue >= 255) hue=0;
      leds[i] = CHSV(hue++, 255, 255);
      
    }
  }
  
  FastLED.show();
  delay(10);
}

void pattern2ForCaption(){
  if(count > 10 && count < 20){
    for(int i = LED_FIRST;i < (LED_FIRST + END_CAPTION +1) ;i++){
        leds[i] = CHSV( random8(),random8(),255);
    }
  }
}

void pattern3ForCaption(){
  if(count > 20 && count < 30){
    for(int i = LED_FIRST;i < (LED_FIRST + END_CAPTION +1) ;i++){
      if (hue==255) hue=0;
      leds[i] = CHSV(hue, 255, 255);
    }
    hue++;
  }
}
