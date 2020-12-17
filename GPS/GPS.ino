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
    for (int i=0; i<count;i++)
    {
        buffer[i]=NULL;
    }
    int count=0;
}

void GetGPS_msg()
{
  clearBufferArray();                         // call clearBufferArray function to clear the stored data from the array
  count = 0;  
  while(Serial1.available())
  {
    buffer[count++]=Serial1.read();      // writing data into array
    if(count == 100)break;
  }
    //Serial.write(buffer,count);     // if no data transmission ends, write buffer to hardware serial port

}

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
  //Serial.write(buffer,count);     // if no data transmission ends, write buffer to hardware serial port
  Parser(buffer);
}
