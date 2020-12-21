unsigned char buffer[100];                   // buffer array for data receive over serial port
int count=0;

void setup()
{ 
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial1.print("$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n");
}

void clearBufferArray()                     // function to clear buffer array
{
    for (int i=100; i<count;i--)
    {
        buffer[i]=NULL;
    }
    int count=0;
}

void GetGPS_msg()
{
                         // call clearBufferArray function to clear the stored data from the array
  count = 0;  
  while(Serial1.available())
  {
    buffer[count++]=Serial1.read();      // writing data into array
<<<<<<< HEAD
    if(count == 100)  clearBufferArray();
=======
    if(count == 100)break;
>>>>>>> a4caa598f8a1c38c46d326fdfef4885a616dc513
  }
    //Serial.write(buffer,count);     // if no data transmission ends, write buffer to hardware serial port

}

<<<<<<< HEAD
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

=======
>>>>>>> a4caa598f8a1c38c46d326fdfef4885a616dc513
void Parser(unsigned char buffer[100])
{
  char *ptr;
  char *result[20];   // Large enough to hold each datum
  int count;
  int i = 0;
  ptr = strtok(buffer,",");   // Look for commas...
  while (ptr != NULL)
  {
    result[i++] = ptr;
    ptr = strtok (NULL, ",");
  }
  count = i;
  for (i = 0; i < count; i++)
  {
    Serial.println(result[i]);   //$GPRMC,100245.000,A,4723.0089,N,00041.3693,E,0.00,7.04,171220,,,A*61
    //Serial.print("     ");
  }
}

void loop() 
{ 
  GetGPS_msg();
<<<<<<< HEAD
  Serial.write(buffer,count);     // if no data transmission ends, write buffer to hardware serial port
  //Parser(buffer);
=======
  //Serial.write(buffer,count);     // if no data transmission ends, write buffer to hardware serial port
  Parser(buffer);
>>>>>>> a4caa598f8a1c38c46d326fdfef4885a616dc513
}
