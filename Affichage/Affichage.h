#include "RTC_DS1307.h"
#include "bsec.h"
#include "TFT_Affichage.h"
#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>

#define LCD_CS A3 
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0

#define LCD_RESET A4

// Assign human-readable names to some common 16-bit color values:
#define  BLACK  0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// Définir l'objet tft pour l'écran TFT
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

class Affichage {
private : 
	void TFT_Affiche_Date();
	void TFT_Affiche_Heure();
	void TFT_Affiche_Indicateur_Ete_Hiver();
	void TFT_Affiche_ville_ref_fuseau_horaire();
	void TFT_Affiche_Etat_Synchro_GPS();

public :
	void TFT_affichage();
};