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

char** GPS::Parser(unsigned char buf[100])
{
results[0]="$GPRMC";
results[1]="115956.000";
results[2]="A";
results[3]="4721.8924";
results[4]="N";
results[5]="00041.1105";
results[6]="E";
results[7]="0.42";
results[8]="318.99";
results[9]="300420";
results[10]="";
results[11]="";
results[12]="";
results[13]="D*68";
results[14]="";
results[15]="";
return results;

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
