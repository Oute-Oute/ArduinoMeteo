unsigned char buffer[64];                   // buffer array for data receive over serial port
int count=0;

void setup()
{ 
  Serial.begin(9600);
  Serial1.begin(9600);
}

void clearBufferArray()                     // function to clear buffer array
{
    for (int i=0; i<count;i++)
    {
        buffer[i]=NULL;
    }
}

void GetGPS_msg()
{
  clearBufferArray();                         // call clearBufferArray function to clear the stored data from the array
  count = 0;  
  while(Serial1.available())
  {
    buffer[count++]=Serial1.read();      // writing data into array
    if(count == 64)break;
  }
    //Serial.write(buffer,count);     // if no data transmission ends, write buffer to hardware serial port

}

void Parser(unsigned char buffer[64])
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
