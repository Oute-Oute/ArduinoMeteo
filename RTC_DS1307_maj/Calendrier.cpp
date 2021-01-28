#include "Calendrier.h"




Calendrier::horloge Calendrier::Extract_date_heure_from_GPS(char* heure,char* date)
{

  
    UTC.heure.heure=int((heure[0]-48)*10+heure[1]-48);
    UTC.heure.minute=int((heure[2]-48)*10+heure[3]-48);
    UTC.heure.seconde=int((heure[4]-48)*10+heure[5]-48);
    UTC.date.jour=int((date[0]-48)*10+date[1]-48);
    UTC.date.nbr_mois=int((date[2]-48)*10+date[3]-48);
    UTC.date.annee=int((date[4]-48)*10+date[5]-48);
    
    
    return UTC;
  
}
void Calendrier::init_fuseaux(){
  //fuseaux.pays="123456789012345678901234";
  //fuseaux.ville="123456789012345678901234"
  fuseaux.decalage_horaire.seconde=0;
  fuseaux.decalage_horaire.minute=0;
  fuseaux.decalage_horaire.heure=+12;
}

  Calendrier::horloge Calendrier::Correction_Heure_Date(horloge UTC,fuseau decalage,int hiver){
    
    locale.heure.heure=UTC.heure.heure+decalage.decalage_horaire.heure+hiver;
    locale.heure.minute=UTC.heure.minute+decalage.decalage_horaire.minute;
    locale.heure.seconde=UTC.heure.seconde+decalage.decalage_horaire.seconde;
    locale.date.jour=UTC.date.jour;
    locale.date.nbr_mois=UTC.date.nbr_mois;
    locale.date.annee=UTC.date.annee;
        if (locale.heure.heure>=24){
      locale.heure.heure=locale.heure.heure-24;
      if (locale.date.jour==31){
        locale.date.jour=1;
        locale.date.nbr_mois=locale.date.nbr_mois+1;
      }
      else if (locale.date.nbr_mois==4||locale.date.nbr_mois==6||locale.date.nbr_mois==9||locale.date.nbr_mois==11){
          if (locale.date.jour==30){
          locale.date.jour=1;
          locale.date.nbr_mois=locale.date.nbr_mois+1;
        }
      }
      else if (locale.date.nbr_mois==2){
        if (locale.date.jour==29){
          locale.date.jour=1;
          locale.date.nbr_mois=locale.date.nbr_mois+1;
        }
        else if (locale.date.annee%4!=0&&locale.date.jour==28){
          locale.date.jour=1;
          locale.date.nbr_mois=locale.date.nbr_mois+1;
        }
        else if (locale.date.nbr_mois==12&&locale.date.jour==31){
          locale.date.jour=1;
          locale.date.nbr_mois=1;
          locale.date.annee=locale.date.annee+1;
        }
      }
      else{
      locale.date.jour=locale.date.jour+1;}
    }
        if (locale.heure.heure<=0){
          if (locale.date.jour==1){
            if (locale.date.nbr_mois==5||locale.date.nbr_mois==7||locale.date.nbr_mois==10||locale.date.nbr_mois==12){//cas mois normal a 31 jours
              locale.date.jour=30;
              locale.date.nbr_mois=locale.date.nbr_mois-1;
            }
            else if (locale.date.nbr_mois==3){// cas mois de mars
              if (locale.date.annee%4==0){//annee bisextile
                locale.date.jour=29;
              }
              else {locale.date.jour=28;}//annee normale
              locale.date.nbr_mois=locale.date.nbr_mois-1;
            }
            else if (locale.date.nbr_mois==1){//cas mois de janvier, on recule d'un an, un mois, un jour
              locale.date.nbr_mois=12;
              locale.date.annee=locale.date.annee-1;
              locale.date.jour=31;
            }
            else if(locale.date.nbr_mois==2||locale.date.nbr_mois==4||locale.date.nbr_mois==6||locale.date.nbr_mois==8||locale.date.nbr_mois==9||locale.date.nbr_mois==11){//cas mois normal a 30 jours
              locale.date.jour=31;}
            }
            else { locale.date.jour=locale.date.jour-1;}
      locale.heure.heure=locale.heure.heure+24;
      }

    
    
    return locale;
  
}
