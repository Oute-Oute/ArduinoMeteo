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

// D�finir l'objet tft pour l'�cran TFT
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

class Affichage {
private : 
	int prevIndic;
	char[20] prevCity;
	float prevTemp;
	float prevPres;
	float prevHum;
	float prevQual;
	uint8_t prevAcc;

	void TFT_Affiche_Date(curDate, prevDate);
	void TFT_Affiche_Heure(curHour, prevHour);
	void TFT_Affiche_Indicateur_Ete_Hiver(int curIndic, int prevIndic);
	void TFT_Affiche_ville_ref_fuseau_horaire(char[20] curCity, char[20] prevCity);
	void TFT_Affiche_Etat_Synchro_GPS(bool syncState);

	void TFT_Affiche_Temperature(float curTemp, float prevTemp);
	void TFT_Affiche_Pression(float curPres, float prevPres);
	void TFT_Affiche_Humidite(float curHum, float prevHum);
	void TFT_Affiche_Qualite_Air(float curQual, float prevQual);
	void TFT_Affiche_Precision_Qualite_Air(uint8_t curAcc, uint8_t prevAcc);


public :
	void TFT_affichage(	curDate, prevDate,
						curHour, prevHour,
						int curIndic, int prevIndic,
						char[20] curCity, char[20] prevCity,
						bool syncState,
						float curTemp, float prevTemp,
						float curPres, float prevPres,
						float curHum, float prevHum,
						float curQual, float prevQual,
						uint8_t curAcc, uint8_t prevAcc		);
};