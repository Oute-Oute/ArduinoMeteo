// Fichier TFT_Affichage.h
// Spécifique à l'écran TFT Adafruit 2050

#include <Arduino.h>

// Définition de constantes symboliques
// Définition de la résolution du shield TFT : commune aux shields écran utilisés
#define TFT_X 320 // Axe horizontal
#define TFT_Y 480 // Axe vertical

// Définition de couleurs sur 16 bits
#define BLACK      0x0000     // (0, 0, 0)
#define DARKGREEN  0x0500     // (0, 128, 0) 0x03E0 valeur initiale
#define MAROON     0x7800     // (128, 0, 0)
#define BLUE       0x001F     // (0, 0, 255)
#define RED        0xF800     // (255, 0, 0)
#define GREEN      0x07E0     // (0, 255, 0)
#define CYAN       0x07FF     // (0, 255, 255)
#define MAGENTA    0xF81F     // (255, 0, 255)
#define YELLOW     0xFFE0     // (255, 255, 0)
#define ORANGE     0xFD20     // (255, 165, 0)
#define WHITE      0xFFFF     // (255, 255, 255)

/*--------------------------------------------------------------------------------*/
// Spécifique au shield écran TFT + dalle tactile Adafruit_2050_TFT
// Arduino Mega2560, mode Data parallèle

// Broches de contrôle écran TFT
#define LCD_CS A0
#define LCD_CD A1
#define LCD_WR A2
#define LCD_RD A3
#define LCD_RESET A4 // optional

// Pour mémo
//   D0 connects to digital pin 22
//   D1 connects to digital pin 23
//   D2 connects to digital pin 24
//   D3 connects to digital pin 25
//   D4 connects to digital pin 26
//   D5 connects to digital pin 27
//   D6 connects to digital pin 28
//   D7 connects to digital pin 29

// Gestion du rétroéclairage
#define BACKLITE_PIN 46 // Broche de gestion du rétro éclairage de l'écran TFT
#define BACKLITE_0 0 // Intensité du rétroclairage à 0
#define BACKLITE_128 128 // Intensité du rétroclairage à 128
