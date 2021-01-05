// Fichier Tactile.h

#include <Arduino.h>
#include "TouchScreen.h"

// Définition de constantes symboliques
#define YP A6   // must be an analog pin, use "An" notation!
#define XM A5   // must be an analog pin, use "An" notation!
#define YM 45   // can be a digital pin
#define XP 44   // can be a digital pin
// Gestion de la dalle tactile
//Measured ADC values for (0,0) and (320-1,480-1)
//TS_MINX corresponds to ADC value when X = 0
//TS_MINY corresponds to ADC value when Y = 0
//TS_MAXX corresponds to ADC value when X = 320 -1
//TS_MAXY corresponds to ADC value when Y = 480 -1

// Paramètres de calibration de la dalle tactile
#define TS_MINX 110
#define TS_MAXX 910
#define TS_MINY 65
#define TS_MAXY 935

// Valeurs limites d'appui sur dalle tactile
#define MINPRESSURE 10
#define MAXPRESSURE 500

/*----------------------------------------*/
// Fonctions prototypes pour dalle tactile
TSPoint Point_DalleTactile (void);
