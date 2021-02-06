#include "GPS.h"

// bufferfer array for data receive over serial port
int count = 0;

void GPS::clearBufferArray(void)
{
  for (int i = 0; i < count; i++)
  {
    buffer[i] = 0;
  }
}

char *GPS::GetGPS_msg(void) {

  if (Serial1.available())
  {
    while (Serial1.available())
    {
      buffer[count++] = Serial1.read();
      if (count == 100)break;
    }
    count = 0;
  }
  return buffer;
}

void GPS::Parser(char* buf)
{
  if (buffer[1] == 'G') {
    /*char * morceau[16];
      char * p;
      int n=-1;

      p = strtok(buf, ",");
      while (p != NULL) {
        morceau[++n] = p;
        p = strtok(NULL, ",");
      }
      Serial.println(morceau[0]);
      //for (n=0; n<16; n++)
      //Serial.println(morceau[n]);*/
    gprmc.type = strtok(buf, ",");
    //Serial.println(gprmc.type);
    gprmc.heure = strtok(NULL, ",");
    //Serial.println(gprmc.heure);
    gprmc.valide = strtok(NULL, ",");
    //Serial.println(gprmc.valide);
    gprmc.latitude = strtok(NULL, ",");
    //Serial.println(gprmc.latitude);
    gprmc.nord_sud = strtok(NULL, ",");
    //Serial.println(gprmc.nord_sud);
    gprmc.longitude = strtok(NULL, ",");
    //Serial.println(gprmc.longitude);
    gprmc.est_ouest = strtok(NULL, ",");
    //Serial.println(gprmc.est_ouest);
    gprmc.speed_ground = strtok(NULL, ",");
    //Serial.println(gprmc.speed_ground);
    gprmc.corse_ground = strtok(NULL, ",");
    //Serial.println(gprmc.corse_ground);
    gprmc.date = strtok(NULL, ",");
    //Serial.println(gprmc.date);
    gprmc.magnetic = strtok(NULL, ",");
    //Serial.println(gprmc.magnetic);
    gprmc.est_ouest_indicator = strtok(NULL, ",");
    //Serial.println(gprmc.est_ouest_indicator);
    gprmc.mode = strtok(NULL, ",");
    //Serial.println(gprmc.mode);
    gprmc.cheksum = strtok(NULL, ",");
    //Serial.println(gprmc.cheksum);
    gprmc.fin_msg = strtok(NULL, ",");
    //Serial.println(gprmc.fin_msg);

  }
  /*gprmc.type="$GPRMC";
    gprmc.heure="111456.000";
    gprmc.valide="A";
    gprmc.latitude="4721.8924";
    gprmc.nord_sud="N";
    gprmc.longitude="00041.1105";
    gprmc.est_ouest="E";
    gprmc.speed_ground="0.42";
    gprmc.corse_ground="318.99";
    gprmc.date="311220";
    gprmc.magnetic="";
    gprmc.est_ouest_indicator="";
    gprmc.mode="";
    gprmc.cheksum="D*68";
    gprmc.fin_msg="";
    //return results;*/

}

bool GPS::buffer_Synchro_GPS(GPS::TYPE_GPRMC) {
  if (strcmp(gprmc.type, "$GPRMC")) {
    if (gprmc.valide=='A') {
      return true;
    }
    else {
      return false;
    }
  }
  if (strcmp(gprmc.type, "$GPGGA")) {
    if (gprmc.valide == "0")return false;
    else return true;
  }
}

void GPS::Choix_Msg_NMEA(int nmea) {
  if (nmea == 1) Serial1.println("$PMTK314,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n");
  else  if (nmea == 2) Serial1.println("$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n");
}
