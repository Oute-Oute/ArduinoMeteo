unsigned char buffer[100];                   // bufferfer array for data receive over serial port
int count = 0;
char test[100] = "$GPRMC,100245.000,A,4723.0089,N,00041.3693,E,0.00,7.04,171220,,,A*61";
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
      if (count == 64)break;
    }
    //Serial.write(buffer,count);
    //Parser(buffer);
    //clearBufferArray();
    count = 0;
  }
}
char *ptr;
//char result[64];
//int nbr;

void Parser(char buf[100]) {
  char newtest[100];
  strcpy(newtest,buf);
  Serial.println(newtest);
  delay(10);

//  nbr = 0;
  ptr = strtok (newtest, ",");
  //for (int i=0;i<14;i++){
  while (ptr != NULL) {
    //result[nbr] = ptr;
    Serial.println(ptr);
    ptr = strtok(NULL, ",");
    
//    nbr++;
//    for (int i = 0; i < 15; i++) {
//      Serial.println(result[i]);
//      delay(10);
//    }
  }

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
  GetGPS_msg();
  //Serial.println(buffer);     // if no data transmission ends, write bufferfer to hardware serial port
  Parser(buffer);
}
