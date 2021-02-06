
#include <Arduino.h>
#include <Wire.h>
#include "Calendrier.h"


#define DS1307_I2C_ADDRESS 0x68

class DS1307 {
  private:
    uint8_t decToBcd(uint8_t val);
    uint8_t bcdToDec(uint8_t val);

  public:
    Calendrier::horloge test;

    void setDate(Calendrier::horloge horloge);
    Calendrier::horloge  getDate(Calendrier::horloge horloge);
    int jourSemaine(Calendrier::horloge horloge);
    void printTime(Calendrier::horloge horloge);
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t dayOfWeek;// day of week, 1 = Monday
    uint8_t dayOfMonth;
    uint8_t month;
    uint16_t year;
};
