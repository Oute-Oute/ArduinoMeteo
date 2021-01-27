#include "GPS.h"

unsigned char buffer[100];                   // bufferfer array for data receive over serial port
int count = 0;

void GPS::clearBufferArray(void)
{
    for (int i = 0; i < count; i++)
    {
        buffer[i] = 0;
    }
}

unsigned char* GPS::GetGPS_msg(void)
{

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

void GPS::Parser(unsigned char buf[100])
{
    //delay(10);

    char * morceau[16];
    char * p;
    int n=-1;

    p = strtok(buf, ",");
    while (p != NULL) {
        morceau[++n] = p;
        p = strtok(NULL, ",");
    }
    Serial.println(morceau[0]);
    //for (n=0; n<16; n++)
        //Serial.println(morceau[n]);
}

bool GPS::buffer_Synchro_GPS(char* result[]) {
    if (result[0] == "$GPRMC") {
        if (result[2] == "A")return true;
        else return false;
    }
    if (result[0] == "$GPGGA") {
        if (result[6] == "0")return false;
        else return true;
    }
}

void GPS::Choix_Msg_NMEA(int nmea) {
    if (nmea == 1) Serial1.println("$PMTK314,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n");
    else  if (nmea == 2) Serial1.println("$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n");
}
