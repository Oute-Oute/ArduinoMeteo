#include <Arduino.h>
#include <stdio.h>
#include <string.h>

class GPS {
  private:
    int count;
  public:
    unsigned char buffer[100];
    void clearBufferArray(void);
    unsigned char* GetGPS_msg(void);
    bool buffer_Synchro_GPS(char* result[]);
    void Choix_Msg_NMEA(int nmea);
    void Parser(unsigned char buf[100]);
};
