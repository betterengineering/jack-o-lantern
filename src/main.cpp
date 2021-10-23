#include <Adafruit_NeoPixel.h>

// The pin Din is connected to.
int pin = 12;

// The number of pixels in the strip.
int numPixels = 30;

// NeoPixel color format & data rate.
int pixelFormat = NEO_GRB + NEO_KHZ800;

// NeoPixel object.
Adafruit_NeoPixel *pixels;

// The maximum brightness to use for "breathing"
int maximumBrightness = 255;

// The time to wait until the next intesity.
int stepDelay = 5;

// The speed of the sine wave.
float speedFactor = 0.008;

// Gamma correction for NeoPixles.
const uint8_t PROGMEM gamma8[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2,
    2, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5,
    5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10,
    10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
    17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
    25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
    37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
    51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
    69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
    90, 92, 93, 95, 96, 98, 99, 101, 102, 104, 105, 107, 109, 110, 112, 114,
    115, 117, 119, 120, 122, 124, 126, 127, 129, 131, 133, 135, 137, 138, 140, 142,
    144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 167, 169, 171, 173, 175,
    177, 180, 182, 184, 186, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213,
    215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252, 255};

void setup()
{
  // Create a new NeoPixel object dynamically with defined values.
  pixels = new Adafruit_NeoPixel(numPixels, pin, pixelFormat);

  // Initialize NeoPixel strip object.
  pixels->begin();

  // Set all pixel colors to 'off'
  pixels->clear();
}

void setColor(int r, int g, int b)
{
  for (int p = 0; p < numPixels; p++)
  {
    pixels->setPixelColor(
        p,
        pgm_read_byte(&gamma8[r]),
        pgm_read_byte(&gamma8[g]),
        pgm_read_byte(&gamma8[b]));
  }
}

void setOrange(int brightness)
{
  pixels->setBrightness(brightness);
  setColor(255, 150, 0);
  pixels->show();
}

void setPurple(int brightness)
{
  pixels->setBrightness(brightness);
  setColor(210, 0, 255);
  pixels->show();
}

void setGreen(int brightness)
{
  pixels->setBrightness(brightness);
  setColor(0, 207, 62);
  pixels->show();
}

void setPumpkinColor(int c, int brightness)
{
  int color = c % 3;
  if (color == 0)
  {
    setOrange(brightness);
  }
  else if (color == 1)
  {
    setPurple(brightness);
  }
  else
  {
    setGreen(brightness);
  }
}

void loop()
{
  int count = 0;
  int color = 0;

  for (int i = 0; i < 65535; i++)
  {
    int brightness = maximumBrightness / 2.0 * (1.0 + sin(speedFactor * i));

    // There's a more elegant way to do this, but this is a pumpkin! Brightness
    // is set at zero for 31-32 steps. So we can change color on brightness zero
    // and step 1.
    if (brightness == 0)
    {
      count++;
    }
    else
    {
      count = 0;
    }

    if (count == 1)
    {
      color++;
    }

    setPumpkinColor(color, brightness);

    delay(stepDelay); // Pause before next pass through loop
  }
}
