unsigned char buffer[100];                   // buffer array for data receive over serial port
int count=0;

void setup()
{ 
  Serial.begin(9600);
  Serial1.begin(9600);
}

void clearBufferArray()                     // function to clear buffer array
{
    for (int i=100; i<count;i--)
    {
        buffer[i]=NULL;
    }
}

void GetGPS_msg()
{
                         // call clearBufferArray function to clear the stored data from the array
  count = 0;  
  while(Serial1.available())
  {
    buffer[count++]=Serial1.read();      // writing data into array
    if(count == 100)  clearBufferArray();
  }
    //Serial.write(buffer,count);     // if no data transmission ends, write buffer to hardware serial port

}

bool Test_Synchro_GPS(char* result[]){
  if (result[0]=="$GPRMC"){
    if(result[2]=='A')return true;
    else return false;
  }
  if (result[0]=="$GPGGA"){
    if(result[6]=='0')return false;
    else return true;
}

}
void Choix_Msg_NMEA(char nmea){
  if (nmea=="$GPGGA") Serial1.print("$PMTK314,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n");
  else Serial1.print("$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n");
}

void Parser(unsigned char buffer[100])
{
  char** message;
  char* mot;
  for(int i=0; buffer[i]!='*'; i++)
  {
    if (buffer[i]!=',')
    {
      **message += buffer[i];
    }
    else 
    {
      *mot = **message;
      Serial.println(*mot);
      message++ ;
    }
  }
}

void loop() 
{ 
  GetGPS_msg();
  Serial.write(buffer,count);     // if no data transmission ends, write buffer to hardware serial port
  Parser(buffer);
}
