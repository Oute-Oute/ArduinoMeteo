unsigned char buffer[100];                   // bufferfer array for data receive over serial port
int count = 0;
//char test[100] = "$GPRMC,100245.000,A,4723.0089,N,00041.3693,E,0.00,7.04,171220,,,A*61";
void clearBufferArray()
{
  for (int i = 0; i < count; i++)
  {
    buffer[i] = NULL;
  }
}

void GetGPS_msg()
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
}

void Parser(char buf[100]) 
{
  char newtest[100];
  strcpy(newtest,buf);
  Serial.println(newtest);
  //delay(10);

  char* msg1 = strtok (newtest, ",");
  char* msg2 = strtok(NULL, ",");
  char* msg3 = strtok(NULL, ",");
  char* msg4 = strtok(NULL, ",");
  char* msg5 = strtok(NULL, ",");
  char* msg6 = strtok(NULL, ",");
  char* msg7 = strtok(NULL, ",");
  char* msg8 = strtok(NULL, ",");
  char* msg9 = strtok(NULL, ",");
  char* msg10 = strtok(NULL, ",");
  char* msg11 = strtok(NULL, ",");
  char* msg12 = strtok(NULL, ",");
  char* msg13 = strtok(NULL, ",");
  char* msg14 = strtok(NULL, ",");
  char* msg15 = strtok(NULL, ",");
  char* msg16 = strtok(NULL, ",");

  Serial.println(msg1);
  Serial.println(msg2);
  Serial.println(msg3);
  Serial.println(msg4);
  Serial.println(msg5);
  Serial.println(msg6);
  Serial.println(msg7);
  Serial.println(msg8);
  Serial.println(msg9);
  Serial.println(msg10);
  Serial.println(msg11);
  Serial.println(msg12);
  Serial.println(msg13);
  Serial.println(msg14);
  Serial.println(msg15);
  Serial.println(msg16);
}

bool buffer_Synchro_GPS(char* result[]) {
  if (result[0] == "$GPRMC") {
    if (result[2] == 'A')return true;
    else return false;
  }
  if (result[0] == "$GPGGA") {
    if (result[6] == '0')return false;
    else return true;
  }
}

void Choix_Msg_NMEA(int nmea) {
  if (nmea == 1) Serial1.println("$PMTK314,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n");
  else  if (nmea == 2) Serial1.println("$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n");
}

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  Choix_Msg_NMEA(2);
}

void loop()
{
  clearBufferArray();
  GetGPS_msg();
  //Serial.println(buffer);     // if no data transmission ends, write bufferfer to hardware serial port
  Parser(buffer);
}
