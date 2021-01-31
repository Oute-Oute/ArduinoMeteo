#include <Arduino.h>


class GPS {
  private:
    int count;
  public:

    struct TYPE_GPRMC {
      char* type;
      char* heure;
      char* valide;
      char* latitude;
      char* nord_sud;
      char* longitude;
      char* est_ouest;
      char* speed_ground;
      char* corse_ground;
      char* date;
      char* magnetic;
      char* est_ouest_indicator;
      char* mode;
      char* cheksum;
      char* fin_msg;
    };
    TYPE_GPRMC gprmc;


    char* results[16];
    char buffer[100];
    void clearBufferArray(void);
    char *GetGPS_msg(void);
    bool buffer_Synchro_GPS(GPS::TYPE_GPRMC);
    void Choix_Msg_NMEA(int nmea);
    void Parser(char buf[100]);
};
