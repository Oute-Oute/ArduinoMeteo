#include <Adafruit_GFX.h>

#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_Circuit_Playground.h>

#include <TouchScreen.h>

#include <Adafruit_TFTLCD.h>
#include <pin_magic.h>
#include <registers.h>

#include <TFT.h>

// Color definitions
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

void setup()
{
//  fillScreen(WHITE);
}

void loop()
{
  fillRect(5,5,309,469,BLUE);
}
