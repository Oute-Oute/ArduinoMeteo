#include <Arduino.h>


class Calendrier  {
private :

public :
const char* jour_semaine[7] = {"Dimanche","Lundi","Mardi","Mercredi","Jeudi","Vendredi","Samedi"};
const char* nom_mois[12] = {"Janvier","Février","Mars","Avril","Mai","Juin","Juillet","Aout","Septembre","Octobre","Novembre","Décembre"};

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
        //char* pays[25];
        //char* villes[25];
        heure_RTC decalage_horaire;
    };
    horloge locale;
    horloge UTC;
    fuseau fuseaux;

    Calendrier::horloge Extract_date_heure_from_GPS(char *heure,char *date);
    Calendrier::horloge Correction_Heure_Date(horloge UTC,fuseau decalage,int hiver);
    void init_fuseaux(void);

  
};
