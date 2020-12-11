unsigned char buffer[64];                   // buffer array for data receive over serial port
int count=0;

void setup()
{ 
  Serial.begin(9600);
  Serial1.begin(9600);
  //Serial1.write("$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n");
}

void clearBufferArray()                     // function to clear buffer array
{
    for (int i=0; i<count;i++)
    {
        buffer[i]=NULL;
    }                      // clear all index of array with command NULL
}
void GetGPS_msg()
{

  while(Serial1.available())
  {
    buffer[count++]=Serial1.read();      // writing data into array
    if(count == 64)break;
  }
  Serial.write(buffer,count);                 // if no data transmission ends, write buffer to hardware serial port
  clearBufferArray();                         // call clearBufferArray function to clear the stored data from the array
  count = 0; 
    
  //début : $ et fin : *
  //temps d'aquisition limité
}

void loop() 
{ 
  GetGPS_msg();
}
