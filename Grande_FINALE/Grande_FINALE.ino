#include <FastLED.h>

#define LED_PIN     13
#define NUM_LEDS    450
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
extern const TProgmemPalette16 Idles_p PROGMEM;
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
  pinMode(2,INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
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
  int switch4;
  int state1;
  int state2;
  int no_vid;
  
  // put your main code here, to run repeatedly:
  switch1 = digitalRead(2);
  switch2 = digitalRead(3);
  switch3 = digitalRead(4);
  switch4 = digitalRead(5);
  val_button = digitalRead(sw);


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
  if (switch1 == 0 && switch2 == 0 && switch3 == 0){
    Serial.println("0");
        // LEDS part

    currentPalette = Idles_p;

    static uint8_t startIndex = 0;
    startIndex = startIndex + 19; /* motion speed */
    
    FillLEDsFromPaletteColors_Idle( startIndex);
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);

    Has_Self_Destruct_Run = false;
    counter = 0;
  }


  else if (switch1 == 1 && switch2 == 0 && switch3 == 0) {
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

  
  else if (switch1 == 0 && switch2 == 1 && switch3 == 0){
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

  else if (switch1 == 0 && switch2 == 0 && switch3 == 1){
    Serial.println("3");
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

  if (switch4 == 0) 
  {
    Serial.print("No");
    Serial.print("x");
  }

  else if (switch4 == 1)
  {
    Serial.print("Yes");
    Serial.print("x");
  }


  if (counter_yellow >= 10000){
    counter_yellow = 1;
  }

  
  //Audio print
  int sensorValue2 = analogRead(A1);  
  Serial.print(sensorValue2);
  Serial.print("x");
  
  

  delay(200);
}

// Potentiometer converter
long value_pot;
long value_pot2;
long Convert_bananas(long value_pot) { 
  long value_pot_conv;
  value_pot_conv = 255 *  (value_pot)/1065;
  return round(value_pot_conv);
}

int Convert_audio(int value_pot2) { 
  int value_pot_conv1;
  value_pot_conv1 =  1;
  return (value_pot_conv1);
}



// LEDs palettes functions

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{   
    int brightness;
    int sensorValue = analogRead(A0);  
    brightness = (Convert_bananas(sensorValue));

    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}

void FillLEDsFromPaletteColors_Idle( uint8_t colorIndex)
{
    int brightness;
    int sensorValue = analogRead(A0);  
    brightness = (Convert_bananas(sensorValue));
    for( int i = 0; i < NUM_LEDS/3; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, NOBLEND);
        leds[i + NUM_LEDS/3 ] = ColorFromPalette( currentPalette, colorIndex, brightness, NOBLEND);
        leds[i + 2 * NUM_LEDS/3 ] = ColorFromPalette( currentPalette, colorIndex, brightness, NOBLEND);
        colorIndex += 10;
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
      fill_palette(leds, i, palette_Index, 1, pal_boom, 255, LINEARBLEND); 
      FastLED.show();
      delay(100);
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


const TProgmemPalette16 Idles_p PROGMEM =
{
    CRGB::Red,
    CRGB::Red, // 'white' is too bright compared to red and blue
    CRGB::Red,
    CRGB::Red,
    CRGB::Red,
    
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Blue,
    
    CRGB::Yellow,
    CRGB::Yellow,
    CRGB::Yellow,
    CRGB::Yellow,
    CRGB::Yellow,
    CRGB::Yellow,
  
};





