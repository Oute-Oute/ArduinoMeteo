#include "GPS.h"

//unsigned char buffer[100];                   // buffer array for data receive over serial port
//int count = 0;
//char test[100] = "$GPRMC,100245.000,A,4723.0089,N,00041.3693,E,0.00,7.04,171220,,,A*61";
GPS monGPS;
unsigned char* buf=monGPS.buffer;

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  monGPS.Choix_Msg_NMEA(2);
}

void loop()
{
  monGPS.clearBufferArray(); //Ceci est un nouveau code
  monGPS.GetGPS_msg();
  //Serial.println(buffer);     // if no data transmission ends, write bufferfer to hardware serial port
  monGPS.Parser(buf);
}
