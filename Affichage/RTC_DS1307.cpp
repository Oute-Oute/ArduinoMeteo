#include "RTC_DS1307.h"




uint8_t DS1307::decToBcd(uint8_t val){
    return ((val / 10 * 16) + (val % 10));
}

uint8_t DS1307::bcdToDec(uint8_t val){
    return ((val / 16 * 10) + (val % 16));
}

Calendrier::horloge DS1307::getDate(Calendrier::horloge horloge){
    // Reset the register pointer
    Wire.beginTransmission(DS1307_I2C_ADDRESS);
    Wire.write((uint8_t)0x00);
    Wire.endTransmission();
    Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
    // A few of these need masks because certain bits are control bits
    horloge.heure.seconde      = bcdToDec(Wire.read() & 0x7f);
    horloge.heure.minute       = bcdToDec(Wire.read());
    horloge.heure.heure        = bcdToDec(Wire.read() & 0x3f);// Need to change this if 12 hour am/pm
    horloge.date.jour_semaine  = bcdToDec(Wire.read());
    horloge.date.jour          = bcdToDec(Wire.read());
    horloge.date.nbr_mois      = bcdToDec(Wire.read());
    horloge.date.annee         = bcdToDec(Wire.read());
    //date_horloge.nom_mois     = nom_mois[bcdToDec(Wire.read())];
    return horloge;

  
}

void DS1307::setDate(Calendrier::horloge horloge){
    Wire.beginTransmission(DS1307_I2C_ADDRESS);
    Wire.write((uint8_t)0x00);
    Wire.write(decToBcd(horloge.heure.seconde));// 0 to bit 7 starts the clock
    Wire.write(decToBcd(horloge.heure.minute));
    Wire.write(decToBcd(horloge.heure.heure));  // If you want 12 hour am/pm you need to set bit 6
    Wire.write(decToBcd(horloge.date.jour_semaine));
    Wire.write(decToBcd(horloge.date.jour));
    Wire.write(decToBcd(horloge.date.nbr_mois));
    Wire.write(decToBcd(horloge.date.annee));
    Wire.endTransmission();

}


int DS1307::jourSemaine(Calendrier::horloge horloge){
  int c = (14-horloge.date.nbr_mois)/12;
  int a = (horloge.date.annee+2000)-c;
  int m = horloge.date.nbr_mois+(12*c)-2;
  return (horloge.date.jour+a+(a/4)-(a/100)+(a/400)+(31*m)/12)%7;
}

void DS1307::printTime(Calendrier::horloge horloge) {
const char* jour_semaine[7] = {"Dimanche","Lundi","Mardi","Mercredi","Jeudi","Vendredi","Samedi"};
const char* nom_mois[12] = {"Janvier","Février","Mars","Avril","Mai","Juin","Juillet","Aout","Septembre","Octobre","Novembre","Décembre"};
//Serial.println("test");
    if (horloge.heure.heure<10){
      Serial.print("0");
    }
    Serial.print(horloge.heure.heure);
    Serial.print(":");
    if (horloge.heure.minute<10){
      Serial.print("0");
    }
    Serial.print(horloge.heure.minute);
    Serial.print(":");
    if (horloge.heure.seconde<10){
      Serial.print("0");
    }
    Serial.print(horloge.heure.seconde);
    Serial.print("  ");
    //Serial.print(date_horloge.nbr_mois);
    //Serial.print("/");
    Serial.print (jour_semaine[jourSemaine(horloge)]);
    Serial.print (" ");
    Serial.print(horloge.date.jour);
    Serial.print(" ");
    Serial.print(nom_mois[horloge.date.nbr_mois-1]);
    Serial.print(" ");
    Serial.print(2000 + horloge.date.annee);
    Serial.println(" ");
}
