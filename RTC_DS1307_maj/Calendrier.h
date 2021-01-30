#include <Arduino.h>


class Calendrier  {
private :

public :
const char* jour_semaine[7] = {"Dimanche","Lundi","Mardi","Mercredi","Jeudi","Vendredi","Samedi"};
const char* nom_mois[12] = {"Janvier","Février","Mars","Avril","Mai","Juin","Juillet","Aout","Septembre","Octobre","Novembre","Décembre"};
int indicateur_ete_hiver=1;

    struct date_RTC{
          uint8_t jour_semaine;
          uint8_t jour;
          uint8_t nbr_mois;
          uint8_t annee;
        };

    struct heure_RTC{
      int seconde;
      int minute;
      int heure;
    };

    struct horloge{
      heure_RTC heure;
      date_RTC date;
    };
    
    struct fuseau{
        char* pays;
        char* villes;
        heure_RTC decalage_horaire;
    };
    
    horloge locale;
    horloge UTC;
    fuseau f1;
    fuseau f2;
    fuseau f3;
    fuseau f4;
    fuseau f5;
    fuseau f6;
    fuseau f7;
    fuseau f8;
    fuseau f9;
    fuseau f10;
    fuseau f11;
    fuseau f12;
    fuseau f13;
    fuseau f14;
    fuseau f15;
    fuseau f16;
    fuseau f17;
    fuseau f18;
    fuseau f19;
    fuseau f20;
    fuseau f21;
    fuseau f22;
    fuseau f23;
    fuseau f24;
    fuseau f25;
    fuseau f26;
    fuseau f27;
    fuseau f28;
    fuseau f29;
    fuseau f30;
    fuseau f31;
    fuseau f32;
    fuseau f33;
    fuseau f34;
    fuseau f35;
    fuseau f36;
    fuseau f37;
    fuseau f38;
    
    Calendrier::horloge Extract_date_heure_from_GPS(char *heure,char *date);
    Calendrier::horloge Correction_Heure_Date(horloge UTC,fuseau decalage,int hiver);
    void initialiser_fuseaux();
    

  

};
