//Page 53 du PDF de projet
//#ifndef Affichage.h
#include "Affichage.h"

//void checksensorStatus(void);

Affichage ecran;
Bsec sensor;
Calendrier Cal;
GPS donnees_GPS;
DS1307 clock;

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

  ecran.prevDate = Cal.locale.date;
  ecran.prevHour = Cal.locale.heure;
  ecran.prevIndic = 3;
  ecran.prevCity = Cal.f1.villes;
  ecran.syncState = donnees_GPS.buffer_Synchro_GPS(donnees_GPS.Parser(donnees_GPS.GetGPS_msg()));

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

  if (sensor.run()) {
    ecran.curTemp = sensor.rawTemperature;
    ecran.curPres = sensor.pressure;
    ecran.curHum = sensor.humidity;
    ecran.curQual = sensor.iaq;
    ecran.curAcc = sensor.iaqAccuracy;
  }

  ecran.curDate = Cal.locale.date;
  ecran.curHour = Cal.locale.heure;
  ecran.curIndic = Cal.indicateur_ete_hiver;
  ecran.curCity = Cal.f1.villes;
  ecran.syncState = donnees_GPS.buffer_Synchro_GPS(donnees_GPS.Parser(donnees_GPS.GetGPS_msg()));

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

//delay(5000);
}
