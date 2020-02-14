#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Adafruit_NeoPixel.h>
#ifdef _AVR_
#include <avr/power.h>
#endif

char auth[] = "XXXXXXXXXXXXXXXXXXXXXXXX"; // Enter your auth token 
char ssid[] = "XXXXXXXXXXXXXXXXXXXXXXXX"; // Enter your wifi SSID
char pass[] = "XXXXXXXXXXXXXXXXXXXXXXXX"; // Enter your wifi password

int red = 255;
int green = 255;
int blue = 255;

#define PIN 4
#define LED_COUNT 1

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);


void lampOn()
{
  for ( int i = 0; i < LED_COUNT; i++)
  {
    uint32_t high = strip.Color(255, 255, 255);
    strip.setPixelColor(i, high);
    strip.show();
    strip.setBrightness(40);

  }
}

void lampOff()
{
  for ( int i = 0; i < LED_COUNT; i++)
  {
    uint32_t low = strip.Color(0, 0, 0);
    strip.setPixelColor(i, low);
    strip.show();

  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
   red = 255 - WheelPos * 3;
   green = WheelPos * 3;
   blue = 0;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    red = WheelPos * 3;
    green = 0;
    blue = 255 - WheelPos * 3;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    red = 0;
    green = 255 - WheelPos * 3;
    blue = WheelPos * 3;
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
}

BLYNK_WRITE(V1)
{
  int shift = param.asInt();
  for (int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, Wheel(shift & 255));
    // OR: strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + shift) & 255));
  }
  strip.show();
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  strip.begin();
  strip.show();
}

void loop()
{

  Blynk.run();
}
