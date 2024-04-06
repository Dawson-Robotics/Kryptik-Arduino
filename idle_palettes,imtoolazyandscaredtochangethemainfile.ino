#include <FastLED.h>

#define LED_PIN     13
#define NUM_LEDS    51
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
uint8_t palette_Index = 0;
uint8_t palette_Index_idle_1 = 0;
uint8_t palette_Index_idle_2 = 0;
uint8_t palette_Index_idle_3 = 0;
CRGB leds[NUM_LEDS];




#define UPDATES_PER_SECOND 100

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

DEFINE_GRADIENT_PALETTE (idleb) {
  0,   255,    0,    0, //white
  75, 255, 0, 0, //yellow
  76, 255, 255, 0,  //yellow orange
  150, 255, 255, 0,
  151, 0, 0, 255,
  255, 0, 0,   255
  
};

CRGBPalette16 currentPalette;
CRGBPalette16 idling = idleb;
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
  
    idles();
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    
    //FillLEDsFromPaletteColors(startIndex);
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS/3; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        leds[i + NUM_LEDS/3 ] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        leds[i + 2 * NUM_LEDS/3 ] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 10;
    }
}

void idles()
{ 
  
  fill_palette(leds, NUM_LEDS, palette_Index_idle_1, 255/(NUM_LEDS/3), idling, 255, NOBLEND);
  FastLED.show();
  delay(10);
  palette_Index_idle_1 = palette_Index_idle_1 + 1;
  palette_Index_idle_2 = palette_Index_idle_2 + 1;
  palette_Index_idle_3 = palette_Index_idle_3 + 1;
}

void FillLEDsFromPaletteColors_idle( uint8_t colorIndex)
{
    uint8_t brightness = 255;

    SetupPurpleAndGreenPalette();
    for( int i = 0; i < NUM_LEDS/3; i++) {
        leds[i] = ColorFromPalette( currentPalette, 0, brightness, currentBlending);
        colorIndex += 3;
    }
    colorIndex = 0;
    SetupPurpleAndGreenPalette();
    for( int i = NUM_LEDS/3; i < 2*NUM_LEDS/3; i++) {
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
    uint8_t secondHand = (millis() / 1000) % 1;
    static uint8_t lastSecond = 99;
    
    if( lastSecond != secondHand) {
        lastSecond = secondHand;
        
       
        if( secondHand == 0)  { SetupPurpleAndGreenPalette();       currentBlending = NOBLEND; }
        
    }
}

// This function fills the palette with totally random colors.
void SetupTotallyRandomPalette()
{
    for( int i = 0; i < 16; i++) {
        currentPalette[i] = CHSV( random8(), 255, random8());
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
void SetupPurpleAndGreenPalette()
{
    CRGB blue = CHSV( HUE_BLUE, 255, 255);
    CRGB yellow  = CHSV( HUE_YELLOW, 255, 255);
    CRGB red  = CHSV( HUE_RED, 255, 255);
    CRGB black  = CRGB::Black;
    
    currentPalette = CRGBPalette16(
                                   red,  red,  red,  red,
                                   red, yellow, yellow,  yellow,
                                   yellow,  yellow,  blue,  blue,
                                   blue, blue, red,  red );
}


// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
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



// Additionl notes on FastLED compact palettes:
//
// Normally, in computer graphics, the palette (or "color lookup table")
// has 256 entries, each containing a specific 24-bit RGB color.  You can then
// index into the color palette using a simple 8-bit (one byte) value.
// A 256-entry color palette takes up 768 bytes of RAM, which on Arduino
// is quite possibly "too many" bytes.
//
// FastLED does offer traditional 256-element palettes, for setups that
// can afford the 768-byte cost in RAM.
//
// However, FastLED also offers a compact alternative.  FastLED offers
// palettes that store 16 distinct entries, but can be accessed AS IF
// they actually have 256 entries; this is accomplished by interpolating
// between the 16 explicit entries to create fifteen intermediate palette
// entries between each pair.
//
// So for example, if you set the first two explicit entries of a compact 
// palette to Green (0,255,0) and Blue (0,0,255), and then retrieved 
// the first sixteen entries from the virtual palette (of 256), you'd get
// Green, followed by a smooth gradient from green-to-bl
