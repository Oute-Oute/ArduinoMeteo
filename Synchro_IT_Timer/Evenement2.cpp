// Fichier Evenement2.c
// Gestion de l'action événement1

#include <Arduino.h>

extern int Id_instance_Evnt2;
extern unsigned long myTime;

void Tache2 (void)
{
  Id_instance_Evnt2 ++;
  myTime = millis();
  Serial.print ("myTime : ");
  Serial.println (myTime);
  Serial.print ("\tInstance evenement 2 : ");
  Serial.println (Id_instance_Evnt2);
}
