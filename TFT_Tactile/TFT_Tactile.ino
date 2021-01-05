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
#include "Adafruit_GFX.h" // Bibliothéque graphique : primitives d'affichage
#include "Adafruit_TFTLCD.h" // Gestion du processeur graphique

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

  delay (5000);
  tft.fillScreen(BLACK);
}
/*--------------------------------------------------------------------------------------------*/
void loop() 
{
  p = Point_DalleTactile ();
  if (p.z >= MINPRESSURE && p.z <= MAXPRESSURE)// Appui valide sur la dalle tactile
  {
    Serial.println ("Appui dalle tactile valide");

    delay (100);
  } 
} // Fin loop
