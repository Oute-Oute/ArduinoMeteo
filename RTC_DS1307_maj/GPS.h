#include <Arduino.h>


class GPS {
  private:
    int count;
  public:
    char* results[16];
    unsigned char buffer[100];
    void clearBufferArray(void);
    unsigned char* GetGPS_msg(void);
    bool buffer_Synchro_GPS(char* result[]);
    void Choix_Msg_NMEA(int nmea);
    char** Parser(unsigned char buf[100]);
};
