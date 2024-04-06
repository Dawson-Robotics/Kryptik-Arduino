#include <FastLED.h>

#define LED_PIN     13
#define NUM_LEDS    23
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define sw 10

#define UPDATES_PER_SECOND 100
DEFINE_GRADIENT_PALETTE (bananas) {
  0,   0,    0,    0, //white
  20, 255, 255, 102, //yellow
  100, 255, 204, 0,  //yellow orange
  170, 255, 153, 0,   // orange
  255, 255, 0,   0
  
};

DEFINE_GRADIENT_PALETTE (black) {
  0,   0,    0,    0, //white
  255, 0, 0, 0
  
};

CRGBPalette16 currentPalette;
CRGBPalette16 pal_boom = bananas;
CRGBPalette16 black_palette = black;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;
long counter_yellow;
long mode_yellow;
CRGB leds[NUM_LEDS];
uint8_t palette_Index = 0;
bool Has_Self_Destruct_Run = false;
int val_button;
int counter = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(9,INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(sw, INPUT);

  // LED setup
  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
    
  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;
 

}

void loop() {
  int switch1;
  int switch2;
  int switch3;
  int state1;
  int state2;
  int no_vid;
  int counter2;
  Serial.println(1);
  
  // put your main code here, to run repeatedly:
  switch1 = digitalRead(7);
  switch2 = digitalRead(3);
  val_button = digitalRead(sw);
  switch1 = 1;
  switch2 = 0;
    if (val_button == 1 )
  {
    Serial.println("10");
    int counter_alert = 0;
    Self_Destruct();
    //for (int i = 0 ; i < 6; i++)
    //{
    //  RedAlert2();
    //  static uint8_t startIndex = 0;
    //  startIndex = startIndex + 1; /* motion speed */
    //  FillLEDsFromPaletteColors( startIndex);
    
    //  FastLED.show();
    //  FastLED.delay(1000 / UPDATES_PER_SECOND);
    //  delay(500);

    //}
  }
  
  if (switch1 == 1 && switch2 == 0) {
    Serial.println("1");
    YellowAlert2();

    // if (Has_Self_Destruct_Run == false) {
    //   Self_Destruct();
    //   currentPalette = RainbowColors_p;
    //   delay(1000);
    //   Has_Self_Destruct_Run = true;
    // }

    // PartyMode();

    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    
    FillLEDsFromPaletteColors( startIndex);
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);

  }

  else if (switch1 == 0 && switch2 == 0){
    Serial.println("0");
        // LEDS part
    PartyMode();

    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    
    FillLEDsFromPaletteColors( startIndex);
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);

    Has_Self_Destruct_Run = false;
    counter = 0;
  }
  
  else if (switch1 == 0 && switch2 == 1){
    Serial.println("2");

    
    // LEDS part
    RedAlert2();

    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    
    FillLEDsFromPaletteColors( startIndex);
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
    Has_Self_Destruct_Run = false;
  }

  else if (switch1 == 1 && switch2 == 1){
    Serial.println("3");
    counter = 1;
    Has_Self_Destruct_Run = false;
    
  }

  if (counter_yellow >= 10000){
    counter_yellow = 1;
  }
  
  delay(100);
}
// Potentiometer converter
long value_pot;
long Convert_bananas(long value_pot) { 
  long value_pot_conv;
  value_pot_conv = 255 *  (value_pot)/1065;
  return round(value_pot_conv);
}




// LEDs palettes functions

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{   
    int brightness;
    int sensorValue = analogRead(A0);  
    brightness = 255;
    counter = 1;
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
        counter = counter + 1;


    }
}

void SetBlack()
{


}

void Self_Destruct()
{ 
  fill_palette(leds, NUM_LEDS, palette_Index, 255/NUM_LEDS, black_palette, 255, LINEARBLEND);
  FastLED.show();

  delay(3000);
  for (int i = 0; i < NUM_LEDS; i++){
      fill_palette(leds, i, palette_Index, 255/NUM_LEDS, pal_boom, 255, LINEARBLEND); 
      FastLED.show();
      delay(300);
      }
  delay(1000);
  
  }


void RedAlert2()
{
  counter_yellow = counter_yellow + 1;
  mode_yellow = counter_yellow % 2;
  if (mode_yellow == 0){
    for( int i = 0; i < 16; i++) {
        currentPalette[i] = CHSV( HUE_RED, 255, 255);
    }
  }
  else if (mode_yellow == 1){
    for( int i = 0; i < 16; i++) {
        currentPalette[i] = CHSV( 0, 0, 0);
    }
  }
    delay(500);
}


void YellowAlert2()
{
  counter_yellow = counter_yellow + 1;
  mode_yellow = counter_yellow % 2;
  if (mode_yellow == 0){
    for( int i = 0; i < 16; i++) {
        currentPalette[i] = CHSV( HUE_YELLOW, 255, 255);
    }
  }
  else if (mode_yellow == 1){
    for( int i = 0; i < 16; i++) {
        currentPalette[i] = CHSV( 0, 0, 0);
    }
  }
    delay(500);
}

// This function fills the palette with totally random colors.
void PartyMode()
{
    for( int i = 0; i < 16; i++) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
    delay(100);
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.


// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
