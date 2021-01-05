// Fichier Tactile.cpp
// Gestion de la dalle tactile écran Adafruit 2050

#include <Arduino.h>
#include "TouchScreen.h"
#include "Adafruit_TFTLCD.h"
#include "Tactile.h"

#define SERIAL_DEBUG

extern TouchScreen ts;
extern Adafruit_TFTLCD tft;

/*--------------------------------------------------------------------------------------------*/
// Acquisition point d'appui sur la dalle tactile
// La fonction Point_DalleTactile prend en compte les écrans :
// - Adafruit 2050
/*--------------------------------------------------------------------------------------------*/
TSPoint Point_DalleTactile (void)
{
  TSPoint p = {0, 0, 0};

  //Pour dalle tactile shield écran Adafruit_2050_TFT
  p = ts.getPoint();
  #ifdef SERIAL_DEBUG
  Serial.println ("Données de la dalle tactile");
  Serial.print("Xt = "); Serial.print(p.x);
  Serial.print("\tYt = "); Serial.print(p.y);
  Serial.print("\tPressure = "); Serial.println(p.z);
  #endif
  
  // Mise à l'échelle 0->1023 vers tft.width() et tft.height()
  p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width() - 1);
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height() - 1);
  #ifdef SERIAL_DEBUB
  Serial.println ("Mapping ecran TFT");
  Serial.print("\tXe = "); Serial.print(p.x);
  Serial.print("\tYe = "); Serial.println(p.y);
  #endif
  
  return p;
}
/*--------------------------------------------------------------------------------------------*/
