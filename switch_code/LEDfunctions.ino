void fadeDown()
{
  uint8_t fadeBrightness = bri;
  if (fadeBrightness >= fadeStepSize)
  {
    fadeBrightness -= fadeStepSize;
  }
  else
  {
    fadeBrightness = 0;
    lightsAreOn = false;
  }

  fill_solid(leds, NUM_LEDS, CHSV(50, 50, fadeBrightness));
  FastLED.show();
  bri = fadeBrightness;
}

//==========================================================================

void turnDownLights(unsigned long currentTime)
{
  static unsigned long previousTime = 0;
  if (currentTime - previousTime  >= fadeIntervalTime)
  {
    fadeDown();
    previousTime = currentTime;
  }
}

//==========================================================================

void turnUpLights(unsigned long currentTime)
{
  static unsigned long previousTime = 0;
  if (currentTime - previousTime  >= fadeIntervalTime)
  {
    fadeUp();
    previousTime = currentTime;
  }
}
//==========================================================================

void fadeUp()
{
  uint16_t fadeBrightness = bri;
  fadeBrightness += fadeStepSize;
  if (fadeBrightness >= 255)
  {
    fadeBrightness = 255;
  }
  fill_solid(leds, NUM_LEDS, CHSV(50, 50, fadeBrightness));
  FastLED.show();
  bri = fadeBrightness;
}
