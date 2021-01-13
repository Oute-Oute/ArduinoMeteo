// Fichier Synchro_IT_Timer.ino
// Exemple de mise en oeuvre de gestion temporelle d'événements
//  en utilisant les IT Timer3

#include "Evenement1.h"
#include "Evenement2.h"

#define T_EVNT1 4 // Période de gestion de l'événémént 1
#define T_EVNT2 8 // Période de gestion de l'événémént 2
#define TCNT3_TIMER3 61630U // Période entre 2 IT Timer3 sur Overflow registre de comptage (environ 0.25s)

volatile int T_Time_Out_Evenement1 = 0;
volatile int T_Time_Out_Evenement2 = 0;
int Id_instance_Evnt1 = 0, Id_instance_Evnt2 = 0;
unsigned long myTime = 0;

/*--------------------------------------------------------------------------------------------*/
// Routine d'IT TImer3 sur Overflow registre de comptage
ISR(TIMER3_OVF_vect)
{
  TIMSK3 &= B11111110; // Bloquer les IT Timer 3
  
  T_Time_Out_Evenement1 --;
  T_Time_Out_Evenement2 --;
  
  TIFR3 |= B00000001; // Réarmer à 1 le flag TOV1 de l'IT Timer 3
  TCNT3 = TCNT3_TIMER3; // Recharger le registre de comptage du Timer 3 
  TIMSK3 |= B0000001; // Autoriser les IT Timer 3
  SREG |= B10000000; // Autoriser toutes les IT/
}
/*--------------------------------------------------------------------------------------------*/

void setup ()
{
  Serial.begin (115200);
  
	// Initialisation des registres du Timer3
  //  - Définition d'une base de temps de 0.25s
  //  - Utilisation Timer3 avec IT sur débordement du registre de comptage
  noInterrupts(); // Bloquer toutes les interruptions
  TCCR3A = B00000000; // TCCR3A = Ox00 Mode normal
  TCCR3B = B00000000; // Mode normal, Timer 3 arrété
  TCCR3C = 0B00000000;
  TIFR3 |= B00000001; // Pour que les IT Timer 3 puissent être prises en compte; Mise à 1 du bit TOV1
  TIMSK3 |= B00000001; // Pour autoriser les IT sur débordement Timer 3; Mise à 1 du bit TOEI1
  TCNT3 = TCNT3_TIMER3; // Charger le contenu du registre de comptage du Timer 3
  interrupts (); // Autoriser toutes les interruptions
  TCCR3B |= B00000101; // Pour définir valeur de prescaler Timer 3 à 1024 et démarrer le compteur

  myTime = millis();
  Serial.print ("myTime : ");
  Serial.println (myTime);
  Serial.println ("Fin setup");
}

void loop ()
{
	if (T_Time_Out_Evenement1 <= 0)
	{
	  Tache1 ();
    T_Time_Out_Evenement1 = T_EVNT1;
	}

  if (T_Time_Out_Evenement2 <= 0)
  {
    Tache2 ();
    T_Time_Out_Evenement2 = T_EVNT2;
  }
}
