char* buffer_gps="";

char* GetGPS_Msg(){
  buffer_gps=Serial1.read();
  return buffer_gps;
}


void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  Serial.begin(9600);
  Serial1.print("$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n");
}


void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(GetGPS_Msg());
}
