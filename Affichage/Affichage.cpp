#include "Affichage.h"

// D�finir l'objet tft pour l'�cran TFT
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

void Affichage::TFT_affichage(	curDate, prevDate,
						        curhour, prevHour,
						        int curIndic, int prevIndic,
						        char[20] curCity, char[20] prevCity,
						        bool syncState,
						        float curTemp, float prevTemp,
						        float curPres, float prevPres,
						        float curHum, float prevHum,
						        float curQual, float prevQual,
						        uint8_t curAcc, uint8_t prevAcc		)
{
	TFT_Affiche_Date(curDate, prevDate);
	TFT_Affiche_Heure(curHour, prevHour);
	TFT_Affiche_Indicateur_Ete_Hiver(int curIndic, int prevIndic);
	TFT_Affiche_ville_ref_fuseau_horaire(char[20] curCity, char[20] prevCity);
	TFT_Affiche_Etat_Synchro_GPS(bool syncState);

	TFT_Affiche_Temperature(float curTemp, float prevTemp);
	TFT_Affiche_Pression(float curPres, float prevPres);
	TFT_Affiche_Humidite(float curHum, float prevHum);
	TFT_Affiche_Qualite_Air(float curQual, float prevQual);
	TFT_Affiche_Precision_Qualite_Air(uint8_t curAcc, uint8_t prevAcc);
}

void Affichage::TFT_Affiche_Date(curDate, prevDate)
{

}

void Affichage::TFT_Affiche_Heure(curHour, prevHour)
{

}

void Affichage::TFT_Affiche_Indicateur_Ete_Hiver(int curIndic, int prevIndic)
{
    if(curIndic != prevIndic)
    {
        tft.setTextColor(WHITE)
        tft.print(prevIndic);
        tft.setTextColor(BLACK)
        tft.println(curIndic);
        prevIndic = curIndic;
    }
}

void Affichage::TFT_Affiche_ville_ref_fuseau_horaire(char[20] curCity, char[20] prevCity)
{
    if(curCity != prevCity)
    {
        tft.setTextColor(WHITE)
        tft.print(prevCity);
        tft.setTextColor(BLACK)
        tft.println(curCity);
        prevCity = curCity;
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
        tft.setTextColor(WHITE)
        tft.print(prevTemp);
        tft.setTextColor(BLACK)
        tft.println(curTemp);
        prevTemp = curTemp;
    }
}

void Affichage::TFT_Affiche_Pression(float curPres, float prevPres)
{
    if(curPres != prevPress)
    {
        tft.setTextColor(WHITE)
        tft.print(prevPress);
        tft.setTextColor(BLACK)
        tft.println(curPress);
        prevPress = curPres;
    }
}

void Affichage::TFT_Affiche_Humidite(float curHum, float prevHum)
{
    if(curHum != prevHum)
    {
        tft.setTextColor(WHITE)
        tft.print(prevHum);
        tft.setTextColor(BLACK)
        tft.println(curHum);
        prevHum = curHum;
    }
}

void Affichage::TFT_Affiche_Qualite_Air(float curQual, float prevQual)
{
    if(curQual != prevQual)
    {
        tft.setTextColor(WHITE)
        tft.print(prevQual);
        tft.setTextColor(BLACK)
        tft.println(curQual);
        prevQual = curQual;
    }
}

void Affichage::TFT_Affiche_Precision_Qualite_Air(uint8_t curAcc, uint8_t prevAcc)
{
    if(curAcc != prevAcc)
    {
        tft.setTextColor(WHITE)
        tft.print(prevAcc);
        tft.setTextColor(BLACK)
        tft.println(curAcc);
        prevAcc = curAcc;
    }
}