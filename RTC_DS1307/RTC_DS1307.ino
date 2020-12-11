#include "RTC_DS1307.h"
#include <Wire.h>

const char* joursemaine[7] = {"Dimanche","Lundi","Mardi","Mercredi","Jeudi","Vendredi","Samedi"};
const char* nommois[12] = {"Janvier","Février","Mars","Avril","Mai","Juin","Juillet","Aout","Septembre","Octobre","Novembre","Décembre"};

DS1307 clock;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
    Wire.begin();
    /*heure_horloge.seconde  = 1;
    heure_horloge.minute   = 1;
    heure_horloge.heure    = 1;
    date_horloge.jour_semaine   = 2;
    date_horloge.jour           = 10;
    date_horloge.nbr_mois      = 12;
    date_horloge.annee          = 20;*/
    clock.remplissage_heure(3,1,2);
    clock.remplissage_date(3,11,12,20);
    clock.printTime();
    clock.setDate();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  clock.getDate();
  clock.printTime();
  delay(1000);

}
