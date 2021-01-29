#include "Affichage.h"

// D�finir l'objet tft pour l'�cran TFT
/*#define LCD_CS A3 
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);*/

void Affichage::TFT_affichage(	Calendrier::date_RTC curDate, Calendrier::date_RTC prevDate,
						        Calendrier::heure_RTC curHour, Calendrier::heure_RTC prevHour,
						        int curIndic, int prevIndic,
						        char* curCity, char* prevCity,
						        bool syncState,
						        float curTemp, float prevTemp,
						        float curPres, float prevPres,
						        float curHum, float prevHum,
						        float curQual, float prevQual,
						        uint8_t curAcc, uint8_t prevAcc		)
{
    /*
    à initialiser dans le .ino
    
    tft.fillScreen(WHITE);
    tft.setCursor(0, 0);
    tft.setTextColor(BLACK);  
    tft.setTextSize(2);*/

	TFT_Affiche_Date(curDate, prevDate);
	TFT_Affiche_Heure(curHour, prevHour);
	TFT_Affiche_Indicateur_Ete_Hiver(curIndic, prevIndic);
	TFT_Affiche_ville_ref_fuseau_horaire(curCity, prevCity);
	TFT_Affiche_Etat_Synchro_GPS(syncState);

	TFT_Affiche_Temperature(curTemp, prevTemp);
	TFT_Affiche_Pression(curPres, prevPres);
	TFT_Affiche_Humidite(curHum, prevHum);
	TFT_Affiche_Qualite_Air(curQual, prevQual);
	TFT_Affiche_Precision_Qualite_Air(curAcc, prevAcc);
}

void Affichage::TFT_Affiche_Date(Calendrier::date_RTC curDate, Calendrier::date_RTC prevDate)
{
    if(curDate.jour != prevDate.jour)
    {
        tft.setTextColor(WHITE);
        tft.print(prevDate.jour);
        tft.setTextColor(BLACK);
        tft.println(curDate.jour);
        prevDate = curDate;
    }
}

void Affichage::TFT_Affiche_Heure(Calendrier::heure_RTC curHour, Calendrier::heure_RTC prevHour)
{
    if(curHour.seconde != prevHour.seconde)
    {
        tft.setTextColor(WHITE);
        tft.print(prevHour.heure);
        tft.setTextColor(BLACK);
        tft.println(curHour.heure);
        prevHour = curHour;
    }
}

void Affichage::TFT_Affiche_Indicateur_Ete_Hiver(int curIndic, int prevIndic)
{
    if(curIndic != prevIndic)
    {
        tft.setTextColor(WHITE);
        tft.print(prevIndic);
        tft.setTextColor(BLACK);
        tft.println(curIndic);
        prevIndic = curIndic;
    }
}

void Affichage::TFT_Affiche_ville_ref_fuseau_horaire(char* curCity, char* prevCity)
{
    if(*curCity != *prevCity)
    {
        tft.setTextColor(WHITE);
        tft.print(*prevCity);
        tft.setTextColor(BLACK);
        tft.println(*curCity);
        *prevCity = *curCity;
    }
}

void Affichage::TFT_Affiche_Etat_Synchro_GPS(bool syncState)
{
    if(syncState)
    {
        tft.fillCircle(309, 10, 5, GREEN);
    }
    else {tft.fillCircle(309, 10, 5, RED);}
}

void Affichage::TFT_Affiche_Temperature(float curTemp, float prevTemp)
{
    if(curTemp != prevTemp)
    {
        tft.setTextColor(WHITE);
        tft.print(prevTemp);
        tft.setTextColor(BLACK);
        tft.println(curTemp);
        prevTemp = curTemp;
    }
}

void Affichage::TFT_Affiche_Pression(float curPres, float prevPres)
{
    if(curPres != prevPres)
    {
        tft.setTextColor(WHITE);
        tft.print(prevPres);
        tft.setTextColor(BLACK);
        tft.println(curPres);
        prevPres = curPres;
    }
}

void Affichage::TFT_Affiche_Humidite(float curHum, float prevHum)
{
    if(curHum != prevHum)
    {
        tft.setTextColor(WHITE);
        tft.print(prevHum);
        tft.setTextColor(BLACK);
        tft.println(curHum);
        prevHum = curHum;
    }
}

void Affichage::TFT_Affiche_Qualite_Air(float curQual, float prevQual)
{
    if(curQual != prevQual)
    {
        tft.setTextColor(WHITE);
        tft.print(prevQual);
        tft.setTextColor(BLACK);
        tft.println(curQual);
        prevQual = curQual;
    }
}

void Affichage::TFT_Affiche_Precision_Qualite_Air(uint8_t curAcc, uint8_t prevAcc)
{
    if(curAcc != prevAcc)
    {
        tft.setTextColor(WHITE);
        tft.print(prevAcc);
        tft.setTextColor(BLACK);
        tft.println(curAcc);
        prevAcc = curAcc;
    }
}
