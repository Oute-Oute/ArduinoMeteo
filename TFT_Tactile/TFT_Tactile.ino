// Fichier TFT_Tactile.ino

// Mise en oeuvre écran TFT Adafruit 2050
// Mise en oeuvre dalle tactile shield écran Adafruit 2050

// Version Environnement Arduino : 1.8.8
// Cible matérielle : Atmega 2560_R3

// Version démo validation fonctionnement écran TFT et dalle tactile: V1.0
// Validé le 16.12.2020

// Fichier d'en tête spécifiques
#include "TFT_Affichage.h"    // Pour affichage sur l'écran TFT
#include "Tactile.h"          // Pour gestion de la dalle tactile

// Inclure les bibliothèques pour gestion de l'écran TFT Adafruit 2050
#include <Adafruit_GFX.h> // Bibliothéque graphique : primitives d'affichage
#include <Adafruit_TFTLCD.h> // Gestion du processeur graphique

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// Assign human-readable names to some common 16-bit color values:
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// Définir l'objet tft pour l'écran TFT
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// Inclure la bibliothéque de gestion de la dalle tactile
#include "TouchScreen.h"

// Définir l'objet ts pour la dalle tactile
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// - Pour la dalle tactile
TSPoint p = {0, 0, 0};

/*--------------------------------------------------------------------------------------------*/
void setup(void)
{
  // Déclaration des variables locales
  uint16_t tft_identifier;

  Serial.begin(9600); // Initialiser les paramètres de la sortie série0, moniteur série par défaut
    Serial.println(F("TFT LCD test"));

#ifdef USE_ADAFRUIT_SHIELD_PINOUT
  Serial.println(F("Using Adafruit 2.8\" TFT Arduino Shield Pinout"));
#else
  Serial.println(F("Using Adafruit 2.8\" TFT Breakout Board Pinout"));
#endif

  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

  tft.reset();

  uint16_t identifier = tft.readID();

  if(identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if(identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if(identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if(identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if(identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Adafruit 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_ADAFRUIT_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Adafruit_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    return;
  }
  // Inititialisation de l'écran TFT
  analogWrite(BACKLITE_PIN,BACKLITE_0); // Rétro éclairage éteint
  tft.reset();
  tft_identifier = tft.readID();
  tft.begin(tft_identifier);
  tft.setRotation(0);
  tft.setTextColor(WHITE);
  tft.setTextSize(1); // Taille de texte : 1
  tft.setCursor(0,10);
  
  tft.fillScreen(BLACK);
  analogWrite(BACKLITE_PIN,BACKLITE_128);  // Rétro éclairage allumé
 
  if(tft_identifier==0x9486) tft.println ("Driver ecran : 0x9486 LCD driver");
    else if(tft_identifier == 0x8357) tft.println ("Driver ecran : HX8357D LCD driver");
      else tft.println ("Driver ecran :Unknown LCD driver chip");
  tft.println ("   Shield ecran Adafruit 2050");
  tft.print ("   TFT size is "); tft.print(tft.width()); tft.print(" x "); tft.println(tft.height());
  tft.println ("Initialisation Ecran TFT done");

  delay(100);  
}
/*--------------------------------------------------------------------------------------------*/
void loop(void) 
{
  p = Point_DalleTactile ();
  if (p.z >= MINPRESSURE && p.z <= MAXPRESSURE)// Appui valide sur la dalle tactile
  {
    Serial.println ("Appui dalle tactile valide");
    delay (500);
  }
} // Fin loop
