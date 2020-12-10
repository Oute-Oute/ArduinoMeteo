
#include <Arduino.h>

#ifndef __DS1307_H__
#define __DS1307_H__
typedef struct Date_RTC {
	uint8_t jour_semaine;
	uint8_t jour;
	uint8_t nbr_mois;
	uint8_t annee;
};

typedef struct Heure_RTC {
	uint8_t seconde;
	uint8_t minute;
	uint8_t heure;
};

typedef struct Horloge_RTC{
	Heure_RTC hour;
	Date_RTC date;
};

#define DS1307_I2C_ADDRESS 0x68


#endif
