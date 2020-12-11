#include "RTC_DS1307.h"
#include <Wire.h>

const char* joursemaine[7] = {"Dimanche","Lundi","Mardi","Mercredi","Jeudi","Vendredi","Samedi"};
const char* nommois[12] = {"Janvier","Février","Mars","Avril","Mai","Juin","Juillet","Aout","Septembre","Octobre","Novembre","Décembre"};

DS1307 clock;

/*uint8_t decToBcd(uint8_t val){
    return ((val / 10 * 16) + (val % 10));
}

uint8_t bcdToDec(uint8_t val){
    return ((val / 16 * 10) + (val % 16));
}

void getDate(){
    // Reset the register pointer
    Wire.beginTransmission(DS1307_I2C_ADDRESS);
    Wire.write((uint8_t)0x00);
    Wire.endTransmission();
    Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
    // A few of these need masks because certain bits are control bits
    heure_horloge.seconde       = bcdToDec(Wire.read() & 0x7f);
    heure_horloge.minute        = bcdToDec(Wire.read());
    heure_horloge.heure         = bcdToDec(Wire.read() & 0x3f);// Need to change this if 12 hour am/pm
    date_horloge.jour_semaine   = jour_semaine[bcdToDec(Wire.read())];
    date_horloge.jour           = bcdToDec(Wire.read());
    date_horloge.nbr_mois       = bcdToDec(Wire.read());
    //date_horloge.nom_mois     = nom_mois[bcdToDec(Wire.read())];
    date_horloge.annee          = bcdToDec(Wire.read());
    horloge.date=date_horloge;
    horloge.hour=heure_horloge;
  
}

void setDate(){
    Wire.beginTransmission(DS1307_I2C_ADDRESS);
    Wire.write((uint8_t)0x00);
    Wire.write(decToBcd(heure_horloge.seconde));// 0 to bit 7 starts the clock
    Wire.write(decToBcd(heure_horloge.minute));
    Wire.write(decToBcd(heure_horloge.heure));  // If you want 12 hour am/pm you need to set bit 6
    Wire.write(decToBcd(date_horloge.jour_semaine));
    Wire.write(decToBcd(date_horloge.jour));
    Wire.write(decToBcd(date_horloge.nbr_mois));
    Wire.write(decToBcd(date_horloge.annee));
    Wire.endTransmission();
}
void startClock() {      // set the ClockHalt bit low to start the rtc
    Wire.beginTransmission(DS1307_I2C_ADDRESS);
    Wire.write((uint8_t)0x00);                      // Register 0x00 holds the oscillator start/stop bit
    Wire.endTransmission();
    Wire.requestFrom(DS1307_I2C_ADDRESS, 1);
    heure_horloge.seconde = Wire.read() & 0x7f;       // save actual seconds and AND sec with bit 7 (sart/stop bit) = clock started
    Wire.beginTransmission(DS1307_I2C_ADDRESS);
    Wire.write((uint8_t)0x00);
    Wire.write((uint8_t)heure_horloge.seconde);                    // write seconds back and start the clock
    Wire.endTransmission();
}

int jourSemaine(){
  int c = (14-date_horloge.nbr_mois)/12;
  int a = (date_horloge.annee+2000)-c;
  int m = date_horloge.nbr_mois+(12*c)-2;
  return (date_horloge.jour+a+(a/4)-(a/100)+(a/400)+(31*m)/12)%7;
}

void printTime() {
    if (heure_horloge.heure<10){
      Serial.print("0");
    }
    Serial.print(heure_horloge.heure);
    Serial.print(":");
    if (heure_horloge.minute<10){
      Serial.print("0");
    }
    Serial.print(heure_horloge.minute);
    Serial.print(":");
    if (heure_horloge.seconde<10){
      Serial.print("0");
    }
    Serial.print(heure_horloge.seconde);
    Serial.print("  ");
    //Serial.print(date_horloge.nbr_mois);
    //Serial.print("/");
    Serial.print (jour_semaine[jourSemaine()]);
    Serial.print (" ");
    Serial.print(date_horloge.jour);
    Serial.print(" ");
    Serial.print(nom_mois[date_horloge.nbr_mois-1]);
    Serial.print(" ");
    Serial.print(2000 + date_horloge.annee);
    Serial.println(" ");
}*/

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
