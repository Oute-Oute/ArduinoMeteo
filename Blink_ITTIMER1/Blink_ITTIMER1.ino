
#define BASE_TEMPS_TIMER1_1S 49911U
#define BASE_TEMPS_TIMER1_05S 57723U
int led_status=0;//led on/off
int nbr_IT=0;//nombre d'interruption timer

ISR (TIMER1_OVF_vect) //FCT INTERRUPTION
{ noInterrupts();
 /* PUSH Rn
  LDS Rn, SREG
  PUSH Rn*/
  //TRAITEMENT LED
  if (led_status==0){
    Serial.println("Led Allumée : 1s");// write into serial monitor
    led_status=1;
    nbr_IT=0;
    }
   else if(led_status==1){
    Serial.println("Led Eteinte : 1s");// write into serial monitor
    led_status=0;
    nbr_IT=0;
    }
  nbr_IT++;
  //FIN TRAITEMENT LED
  /*POP Rn
  STS SREG, Rn
  POP Rn*/
  interrupts();
}

// the setup function runs once when you press reset or power the board
void setup() {
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
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(3000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(3000);                       // wait for a second
}
