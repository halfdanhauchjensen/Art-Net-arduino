#include <FastLED.h>
#define NUM_LEDS 10
#define DATA_PIN 2
CRGB leds[NUM_LEDS];

int incomingByte;      // a variable to read incoming serial data into
byte bytes[10];

void setup() {
  // initialize serial communication:
  Serial.begin(115200);
  // initialize the LED pin as an output:
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  
}

void loop() {
  /*
  leds[0] = CRGB::Red;
  FastLED.show();
  delay(1000);
  leds[0] = CRGB::Blue;
  FastLED.show();
  delay(1000);
  */

  
  if (Serial.available() == 10){
    for(int n=0; n < 10; n++) {
      bytes[n] = Serial.read(); // Then: Get them.
    }
       for (int p = 0; p < 10; p++){
        leds[p] = CRGB(bytes[p], 0, 0);
      }
      FastLED.show();    
    
  }
  
}