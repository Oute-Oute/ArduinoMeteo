// Fichier Evenement1.c
// Gestion de l'action événement1

#include <Arduino.h>

extern int Id_instance_Evnt1;
extern unsigned long myTime;

void Tache1 (void)
{
  Id_instance_Evnt1 ++;
  myTime = millis();
  Serial.print ("myTime : ");
  Serial.println (myTime);
  Serial.print ("\tInstance evenement 1 : ");
  Serial.println (Id_instance_Evnt1);
}
