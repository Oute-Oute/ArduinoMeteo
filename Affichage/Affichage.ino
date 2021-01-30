//Page 53 du PDF de projet
#include "Affichage.h"

Affichage ecran;
Bsec sensor;
Calendrier Cal;
//Ecran.prevDate = 

void setup() 
{
   tft.fillScreen(WHITE);
   tft.setCursor(0, 0);
   tft.setTextColor(BLACK);  
   tft.setTextSize(2);
}

void loop() 
{
  TFT_affichage(  Cal.locale.date, Cal.locale.date,
                  Cal.locale.heure, Cal.locale.heure,
                  curIndic, prevIndic,
                  curCity, prevCity,
                  syncState,
                  curTemp, prevTemp,
                  curPres, prevPres,
                  curHum, prevHum,
                  curQual, prevQual,
                  curAcc, prevAcc   );
}
