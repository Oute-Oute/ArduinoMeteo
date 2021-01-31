#include "RTC_DS1307.h"
#include "GPS.h"
#include <Wire.h>
#define BASE_TEMPS_TIMER1_1S 49911U
#define BASE_TEMPS_TIMER1_05S 57723U
#define T_RH 1 // Période de gestion de l'événémént 1
#define T_MAJH 40000 //4H=28800s, 6H=43200s donc environ 5h
#define T_SyncGPS 3
#define TCNT3_TIMER3 61630U // Période entre 2 IT Timer3 sur Overflow registre de comptage (environ 0.25s)

volatile int T_Time_Out_Recuperation_Heure = 0;
unsigned int T_Time_Out_MAJ_Heure = 3;
volatile int nb_SyncGPS = 3;

const char* joursemaine[7] = {"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};
const char* nommois[12] = {"Janvier", "Février", "Mars", "Avril", "Mai", "Juin", "Juillet", "Aout", "Septembre", "Octobre", "Novembre", "Décembre"};

DS1307 clock;
GPS donnees_GPS;
Calendrier Cal;


ISR (TIMER1_OVF_vect) //FCT INTERRUPTION
{
  noInterrupts();
  /* PUSH Rn
    LDS Rn, SREG
    PUSH Rn*/
  //TRAITEMENT LED
  T_Time_Out_Recuperation_Heure--;
  T_Time_Out_MAJ_Heure--;
  //FIN TRAITEMENT LED
  /*POP Rn
    STS SREG, Rn
    POP Rn*/
  interrupts();
}

void setup() {
  // put your setup code here, to run once:
  //IT GESTION
  noInterrupts();
  TCCR1A = 0b00000000;  //Mode Normal
  TCCR1B = 0b00000000;  //Timer1 arreté
  TCCR1C = 0b00000000;
  TIFR1 |= 0b00000001;  //Mise a 1 bit TOV1
  TIMSK1 |= 0b00000001; //Mise a 1 bit TOEI1
  TCNT1 = BASE_TEMPS_TIMER1_1S;
  interrupts();
  TCCR1B = 0b00000100; //PRESCALE=1024
  //FIN IT GESTION
  // initialize digital pin LED_BUILTIN as an output.
  //initialize connection with serial monitor
  Serial.begin(9600);
  Serial1.begin(9600);
  Wire.begin();

  /*heure_horloge.seconde  = 1;
    heure_horloge.minute   = 1;
    heure_horloge.heure    = 1;
    date_horloge.jour_semaine   = 2;
    date_horloge.jour           = 10;
    date_horloge.nbr_mois      = 12;
    date_horloge.annee          = 20;*/
  donnees_GPS.Choix_Msg_NMEA(2);
  donnees_GPS.Parser(donnees_GPS.buffer);
  Serial.print(donnees_GPS.gprmc.valide);
  //Serial.print(donnees_GPS.results[1]);
  Cal.Extract_date_heure_from_GPS(donnees_GPS.gprmc.heure, donnees_GPS.gprmc.date);
  Cal.initialiser_fuseaux();
  Cal.Correction_Heure_Date(Cal.UTC, Cal.f16, 0);
  clock.setDate(Cal.UTC);
  Cal.UTC = clock.getDate(Cal.UTC);
  Cal.locale = Cal.Correction_Heure_Date(Cal.UTC, Cal.f16, Cal.indicateur_ete_hiver);
  clock.setDate(Cal.locale);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (T_Time_Out_Recuperation_Heure <= 0)
  {
    Cal.locale = clock.getDate(Cal.locale);
    clock.printTime(Cal.locale);
    Serial.print("Ville du fuseau horaire : ");
    Serial.println(Cal.f16.villes);
    Serial.print("Heure Été ou Hiver? ");
    if (Cal.indicateur_ete_hiver==1){
      Serial.println("Été");
    }
    else Serial.println("Hiver");
    T_Time_Out_Recuperation_Heure = T_RH;
  }

  if (T_Time_Out_MAJ_Heure <= 0 && nb_SyncGPS >= 0)
  { bool test = donnees_GPS.buffer_Synchro_GPS(donnees_GPS.gprmc);

    if (test == false) {
      Serial.println("Message GPS non valide");
      donnees_GPS.GetGPS_msg();
      donnees_GPS.Parser(donnees_GPS.buffer);
      T_Time_Out_MAJ_Heure = T_SyncGPS;
    }
    if (test == true) {
      Serial.println("Message GPS valide!");
      if (donnees_GPS.gprmc.date == 0) {
        Cal.UTC = Cal.Extract_date_heure_from_GPS(donnees_GPS.gprmc.heure, donnees_GPS.gprmc.longitude);//pour regler le soucis du parser qui "efface" les indicateurs nord et sud
      }
      else {
        Cal.UTC = Cal.Extract_date_heure_from_GPS(donnees_GPS.gprmc.heure, donnees_GPS.gprmc.date);
      }
      clock.setDate(Cal.UTC);
      Cal.locale = Cal.Correction_Heure_Date(Cal.UTC, Cal.f16, Cal.indicateur_ete_hiver);
      clock.setDate(Cal.locale);
      if (nb_SyncGPS > 0) {
        T_Time_Out_MAJ_Heure = T_SyncGPS;
        nb_SyncGPS--;
      }
      else {
        T_Time_Out_MAJ_Heure = T_MAJH;
        nb_SyncGPS = 1;
      }
    }
  }
}
