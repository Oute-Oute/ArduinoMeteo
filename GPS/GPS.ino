unsigned char buffer[100];                   // bufferfer array for data receive over serial port
int count = 0;
//char test[100] = "$GPRMC,100245.000,A,4723.0089,N,00041.3693,E,0.00,7.04,171220,,,A*61";

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  Choix_Msg_NMEA(2);
}

void loop()
{
  clearBufferArray(); //Ceci est un nouveau code
  GetGPS_msg();
  //Serial.println(buffer);     // if no data transmission ends, write bufferfer to hardware serial port
  Parser(buffer);
}
