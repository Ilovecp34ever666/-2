/*
   ~2 

   Yifu Liu

   Neopixels, 2 windsensors, 

*/
//==========================================================================
#include <FastLED.h>
//==========================================================================
// Defines are bad (i.e. annoying)
#define analogPinForRV  1   // change to pins you the analog pins are using
#define analogPinForRV2 3   // change to pins you the analog pins are using
#define analogPinForTMP 0
//==========================================================================
// LED Variables
const uint8_t DATA_PIN = 6;
const uint8_t NUM_LEDS = 10;
CRGB leds[NUM_LEDS];
uint8_t hue = 255;
uint8_t sat = 255;
uint8_t bri = 0;
const uint8_t fadeSteps = 255;
const uint8_t fadeStepSize = 255 / fadeSteps;
const uint8_t fadeIntervalTime = 10;
//==========================================================================
// Wind Sensor Variables
const float zeroWindAdjustment =  .2; // negative numbers yield smaller wind speeds and vice versa.
int TMP_Therm_ADunits;    //temp termistor value from wind sensor
float RV_Wind_ADunits;    //RV output from wind sensor
float RV_Wind_ADunits2;   //RV output from wind sensor
float RV_Wind_Volts;
float RV_Wind_Volts2;
const unsigned long windReadInterval = 200;
long bothBlowingTimer = 0;
unsigned long previousBlowingTime = 0;
bool wereBothBlowing = false;
uint8_t blowingThreshold = 4;
//==========================================================================
// Time/Threading Variables
unsigned long lastMillis;
int TempCtimes100;
float zeroWind_ADunits;
float zeroWind_volts;
float WindSpeed_MPH, WindSpeed_MPH2;
bool lightsAreOn = false;
unsigned long startMillis = 0L;  //some global variables available anywhere in the program
unsigned long currentMillis = 0L;
const unsigned long period = 1000;  //the value is a number of milliseconds
//==========================================================================
void setup()
{
  Serial.begin(57600);   // faster printing to get a bit better throughput on extended info
  Serial.println("start");
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
  FastLED.show();
}

void loop()
{
  unsigned long currentTime = millis();
  //------------------------------------------------------------------------
  calculateWindSpeeds(currentTime);
  //------------------------------------------------------------------------
  bool bothBlowing = ( WindSpeed_MPH > blowingThreshold) && (WindSpeed_MPH2 > blowingThreshold);
  //------------------------------------------------------------------------
  if (bothBlowing)
  {    
    turnUpLights(currentTime);
    if (wereBothBlowing)
    {
      bothBlowingTimer += currentTime - previousBlowingTime; // increment both-blowing-timer
      previousBlowingTime = currentTime;
    }
    else
    {
      wereBothBlowing = true;
      bothBlowingTimer = 0;
      previousBlowingTime = currentTime;
    }
  }

  if (!bothBlowing)
  {
    wereBothBlowing = false;
    if (bothBlowingTimer <= 0)
    {
      turnDownLights(currentTime);
    }
    else // de-increment blowing timer
    {
      bothBlowingTimer -= currentTime - previousBlowingTime; // increment both-blowing-timer
      previousBlowingTime = currentTime;
    }
  }
  //------------------------------------------------------------------------

}
