#include "RTC_DS1307.h"
#include "GPS.h"
#include <Wire.h>
#define BASE_TEMPS_TIMER1_1S 49911U
int time_decrement=20000; //4H=14400s, 6H=21600s

const char* joursemaine[7] = {"Dimanche","Lundi","Mardi","Mercredi","Jeudi","Vendredi","Samedi"};
const char* nommois[12] = {"Janvier","Février","Mars","Avril","Mai","Juin","Juillet","Aout","Septembre","Octobre","Novembre","Décembre"};

DS1307 clock;
GPS donnees_GPS;

ISR (TIMER1_OVF_vect) //FCT INTERRUPTION
{ noInterrupts();
 /* PUSH Rn
  LDS Rn, SREG
  PUSH Rn*/
  //TRAITEMENT IT
  if (time_decrement<0){
    Serial.println("Maj_heure_requise");}
  else{
    //Serial.println("OKLM");
    time_decrement--;
  }

  //FIN TRAITEMENT IT
  /*POP Rn
  STS SREG, Rn
  POP Rn*/
  interrupts();
}

void setup() {
  // put your setup code here, to run once:
    //IT GESTION
  noInterrupts();
  TCCR1A = 0b00000000;  //Mode Normal
  TCCR1B = 0b00000000;  //Timer1 arreté
  TCCR1C = 0b00000000; 
  TIFR1 |= 0b00000001;  //Mise a 1 bit TOV1
  TIMSK1 |= 0b00000001; //Mise a 1 bit TOEI1 
  TCNT1=BASE_TEMPS_TIMER1_1S;
  interrupts();
  TCCR1B=0b00000100; //PRESCALE=1024
  //FIN IT GESTION
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  //initialize connection with serial monitor
  Serial.begin(9600);
    Wire.begin();
    /*heure_horloge.seconde  = 1;
    heure_horloge.minute   = 1;
    heure_horloge.heure    = 1;
    date_horloge.jour_semaine   = 2;
    date_horloge.jour           = 10;
    date_horloge.nbr_mois      = 12;
    date_horloge.annee          = 20;*/
    donnees_GPS.Parser(donnees_GPS.buffer);
    //Serial.print(donnees_GPS.results[1]);
    clock.initialiser_horloge(donnees_GPS.results);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  clock.getDate();
  clock.printTime();
  delay(1000);

}
