//Page 53 du PDF de projet
//#ifndef Affichage.h
#include "Affichage.h"
#define BASE_TEMPS_TIMER1_1S 49911U
#define BASE_TEMPS_TIMER1_05S 57723U
#define T_RH 1 // Période de gestion de l'événémént 1
#define T_MAJH 40000 //4H=28800s, 6H=43200s donc environ 5h
#define T_SyncGPS 3
#define TCNT3_TIMER3 61630U // Période entre 2 IT Timer3 sur Overflow registre de comptage (environ 0.25s)
//void checksensorStatus(void);


volatile int T_Time_Out_Recuperation_Heure = 0;
unsigned int T_Time_Out_MAJ_Heure = 3;
volatile int nb_SyncGPS = 3;

Affichage ecran;
Bsec sensor;
Calendrier Cal;
GPS donnees_GPS;
DS1307 clock;


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



void setup()
{

  ecran.TFT_setup();
  Serial.begin(9600);
  Wire.begin();
  sensor.begin(BME680_I2C_ADDR_PRIMARY, Wire);
  //checksensorStatus();

  bsec_virtual_sensor_t sensorList[10] = {
    BSEC_OUTPUT_RAW_TEMPERATURE,
    BSEC_OUTPUT_RAW_PRESSURE,
    BSEC_OUTPUT_RAW_HUMIDITY,
    BSEC_OUTPUT_RAW_GAS,
    BSEC_OUTPUT_IAQ,
    BSEC_OUTPUT_STATIC_IAQ,
    BSEC_OUTPUT_CO2_EQUIVALENT,
    BSEC_OUTPUT_BREATH_VOC_EQUIVALENT,
    BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE,
    BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY,
  };

  sensor.updateSubscription(sensorList, 10, BSEC_SAMPLE_RATE_LP);

  donnees_GPS.Parser(donnees_GPS.buffer);
  Cal.Extract_date_heure_from_GPS(donnees_GPS.results[1], donnees_GPS.results[9]);
  Cal.initialiser_fuseaux();
  Cal.Correction_Heure_Date(Cal.UTC, Cal.f1, 0);
  clock.setDate(Cal.UTC);
  Cal.UTC = clock.getDate(Cal.UTC);
  Cal.locale = Cal.Correction_Heure_Date(Cal.UTC, Cal.f1, Cal.indicateur_ete_hiver);
  clock.setDate(Cal.locale);

  if (sensor.run()) {
    ecran.prevTemp = sensor.rawTemperature;
    ecran.prevPres = sensor.pressure;
    ecran.prevHum = sensor.humidity;
    ecran.prevQual = sensor.iaq;
    ecran.prevAcc = sensor.iaqAccuracy;
  }

  ecran.prevDate.jour_semaine = Cal.locale.date.jour_semaine;
  ecran.prevDate.jour = 32;//Cal.locale.date.jour;
  ecran.prevDate.nbr_mois = Cal.locale.date.nbr_mois;
  ecran.prevDate.annee = Cal.locale.date.annee;

  Serial.print(ecran.prevDate.jour);
  ecran.prevHour = Cal.locale.heure;
  ecran.prevIndic = 3;
  ecran.prevCity = Cal.f1.villes;
  ecran.syncState = donnees_GPS.buffer_Synchro_GPS(donnees_GPS.gprmc);

  ecran.TFT_affichage(   ecran.curDate, ecran.prevDate,
                         ecran.curHour, ecran.prevHour,
                         ecran.curIndic , ecran.prevIndic,
                         ecran.curCity , ecran.prevCity,
                         ecran.syncState,
                         ecran.curTemp, ecran.prevTemp,
                         ecran.curPres, ecran.prevPres,
                         ecran.curHum, ecran.prevHum,
                         ecran.curQual, ecran.prevQual,
                         ecran.curAcc, ecran.prevAcc   );
  //delay(5000);

}

void loop()
{
  if (T_Time_Out_Recuperation_Heure <= 0)
  {
    if (sensor.run()) {
      ecran.curTemp = sensor.rawTemperature;
      ecran.curPres = sensor.pressure;
      ecran.curHum = sensor.humidity;
      ecran.curQual = sensor.iaq;
      ecran.curAcc = sensor.iaqAccuracy;
    }

    ecran.curDate.jour_semaine = Cal.locale.date.jour_semaine;
    ecran.curDate.jour = Cal.locale.date.jour;
    ecran.curDate.nbr_mois = Cal.locale.date.nbr_mois;
    ecran.curDate.annee = Cal.locale.date.annee;
    Serial.print(ecran.curDate.jour);
    ecran.curHour = Cal.locale.heure;
    ecran.curIndic = Cal.indicateur_ete_hiver;
    ecran.curCity = Cal.f1.villes;
    ecran.syncState = donnees_GPS.buffer_Synchro_GPS(donnees_GPS.gprmc);

    //ecran.TFT_fillScreen(WHITE);
    ecran.TFT_setCursor(0, 0);
    ecran.TFT_println(" ");
    ecran.TFT_affichage(   ecran.curDate, ecran.prevDate,
                           ecran.curHour, ecran.prevHour,
                           ecran.curIndic , ecran.prevIndic,
                           ecran.curCity , ecran.prevCity,
                           ecran.syncState,
                           ecran.curTemp, ecran.prevTemp,
                           ecran.curPres, ecran.prevPres,
                           ecran.curHum, ecran.prevHum,
                           ecran.curQual, ecran.prevQual,
                           ecran.curAcc, ecran.prevAcc   );
    ecran.prevTemp = ecran.curTemp;
    ecran.prevPres = ecran.curPres;
    ecran.prevHum = ecran.curHum;
    ecran.prevQual = ecran.curQual;
    ecran.prevAcc = ecran.curAcc;
    *ecran.prevCity = *ecran.curCity;
    ecran.prevDate = ecran.curDate;
    ecran.prevHour = ecran.curHour;
    ecran.prevIndic = ecran.curIndic;
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


  //delay(5000);
}
