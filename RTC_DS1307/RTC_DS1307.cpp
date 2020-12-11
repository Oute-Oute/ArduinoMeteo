#include "RTC_DS1307.h"


const char* jour_semaine[7] = {"Dimanche","Lundi","Mardi","Mercredi","Jeudi","Vendredi","Samedi"};
const char* nom_mois[12] = {"Janvier","Février","Mars","Avril","Mai","Juin","Juillet","Aout","Septembre","Octobre","Novembre","Décembre"};

uint8_t DS1307::decToBcd(uint8_t val){
    return ((val / 10 * 16) + (val % 10));
}

uint8_t DS1307::bcdToDec(uint8_t val){
    return ((val / 16 * 10) + (val % 16));
}

void DS1307::getDate(){
    // Reset the register pointer
    Wire.beginTransmission(DS1307_I2C_ADDRESS);
    Wire.write((uint8_t)0x00);
    Wire.endTransmission();
    Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
    // A few of these need masks because certain bits are control bits
    second     = bcdToDec(Wire.read() & 0x7f);
    minute     = bcdToDec(Wire.read());
    hour       = bcdToDec(Wire.read() & 0x3f);// Need to change this if 12 hour am/pm
    dayOfWeek  = bcdToDec(Wire.read());
    dayOfMonth = bcdToDec(Wire.read());
    month      = bcdToDec(Wire.read());
    year       = bcdToDec(Wire.read());
    remplissage_heure(second,minute,hour);
    remplissage_date(dayOfWeek,dayOfMonth,month,year);
    //date_horloge.nom_mois     = nom_mois[bcdToDec(Wire.read())];

  
}

void DS1307::setDate(){
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


int DS1307::jourSemaine(){
  int c = (14-horloge.date.nbr_mois)/12;
  int a = (horloge.date.annee+2000)-c;
  int m = horloge.date.nbr_mois+(12*c)-2;
  return (horloge.date.jour+a+(a/4)-(a/100)+(a/400)+(31*m)/12)%7;
}

void DS1307::printTime() {
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
    Serial.print (jour_semaine[jourSemaine()]);
    Serial.print (" ");
    Serial.print(horloge.date.jour);
    Serial.print(" ");
    Serial.print(nom_mois[horloge.date.nbr_mois-1]);
    Serial.print(" ");
    Serial.print(2000 + horloge.date.annee);
    Serial.println(" ");
}

void DS1307::remplissage_heure(uint8_t seconde, uint8_t minute, uint8_t heure){
    horloge.heure.seconde=seconde;
    horloge.heure.minute=minute; 
    horloge.heure.heure=heure;

}

void DS1307::remplissage_date(uint8_t jour_semaine, uint8_t jour, uint8_t mois, uint8_t annee){
    //date={jour_semaine,jour,mois,annee};
    horloge.date.jour_semaine=jour_semaine;
    horloge.date.jour=jour;
    horloge.date.nbr_mois=mois;
    horloge.date.annee=annee;
}
