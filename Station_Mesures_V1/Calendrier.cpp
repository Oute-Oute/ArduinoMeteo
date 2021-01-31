#include "Calendrier.h"




Calendrier::horloge Calendrier::Extract_date_heure_from_GPS(char* heure, char* date)
{


  UTC.heure.heure = int((heure[0] - 48) * 10 + heure[1] - 48);
  UTC.heure.minute = int((heure[2] - 48) * 10 + heure[3] - 48);
  UTC.heure.seconde = int((heure[4] - 48) * 10 + heure[5] - 48);
  UTC.date.jour = int((date[0] - 48) * 10 + date[1] - 48);
  UTC.date.nbr_mois = int((date[2] - 48) * 10 + date[3] - 48);
  UTC.date.annee = int((date[4] - 48) * 10 + date[5] - 48);


  return UTC;

}


Calendrier::horloge Calendrier::Correction_Heure_Date(horloge UTC, fuseau decalage, int hiver) {
  Serial.println(decalage.decalage_horaire.heure);
  locale.heure.heure = UTC.heure.heure + decalage.decalage_horaire.heure + hiver;
  locale.heure.minute = UTC.heure.minute + decalage.decalage_horaire.minute;
  locale.heure.seconde = UTC.heure.seconde + decalage.decalage_horaire.seconde;
  locale.date.jour = UTC.date.jour;
  locale.date.nbr_mois = UTC.date.nbr_mois;
  locale.date.annee = UTC.date.annee;
  //changement heure pour cause de décalage des minutes
  if (locale.heure.minute >= 60) {
    locale.heure.minute = locale.heure.minute - 60;
    locale.heure.heure = locale.heure.heure + 1;
  }
  else if (locale.heure.minute <= 0) {
    locale.heure.minute = locale.heure.minute + 60;
    locale.heure.heure = locale.heure.heure - 1;
  }

  //changement jour pour cause de décalage des heures
  if (locale.heure.heure >= 24) {
    locale.heure.heure = locale.heure.heure - 24;
    if (locale.date.jour == 31) {
      locale.date.jour = 1;
      locale.date.nbr_mois = locale.date.nbr_mois + 1;
    }
    else if (locale.date.nbr_mois == 4 || locale.date.nbr_mois == 6 || locale.date.nbr_mois == 9 || locale.date.nbr_mois == 11) {
      if (locale.date.jour == 30) {
        locale.date.jour = 1;
        locale.date.nbr_mois = locale.date.nbr_mois + 1;
      }
    }
    else if (locale.date.nbr_mois == 2) {
      if (locale.date.jour == 29) {
        locale.date.jour = 1;
        locale.date.nbr_mois = locale.date.nbr_mois + 1;
      }
      else if (locale.date.annee % 4 != 0 && locale.date.jour == 28) {
        locale.date.jour = 1;
        locale.date.nbr_mois = locale.date.nbr_mois + 1;
      }
      else if (locale.date.nbr_mois == 12 && locale.date.jour == 31) {
        locale.date.jour = 1;
        locale.date.nbr_mois = 1;
        locale.date.annee = locale.date.annee + 1;
      }
    }
    else {
      locale.date.jour = locale.date.jour + 1;
    }
  }
  if (locale.heure.heure <= 0) {
    if (locale.date.jour == 1) {
      if (locale.date.nbr_mois == 5 || locale.date.nbr_mois == 7 || locale.date.nbr_mois == 10 || locale.date.nbr_mois == 12) { //cas mois normal a 31 jours
        locale.date.jour = 30;
        locale.date.nbr_mois = locale.date.nbr_mois - 1;
      }
      else if (locale.date.nbr_mois == 3) { // cas mois de mars
        if (locale.date.annee % 4 == 0) { //annee bisextile
          locale.date.jour = 29;
        }
        else {
          locale.date.jour = 28; //annee normale
        }
        locale.date.nbr_mois = locale.date.nbr_mois - 1;
      }
      else if (locale.date.nbr_mois == 1) { //cas mois de janvier, on recule d'un an, un mois, un jour
        locale.date.nbr_mois = 12;
        locale.date.annee = locale.date.annee - 1;
        locale.date.jour = 31;
      }
      else if (locale.date.nbr_mois == 2 || locale.date.nbr_mois == 4 || locale.date.nbr_mois == 6 || locale.date.nbr_mois == 8 || locale.date.nbr_mois == 9 || locale.date.nbr_mois == 11) { //cas mois normal a 30 jours
        locale.date.jour = 31;
      }
    }
    else {
      locale.date.jour = locale.date.jour - 1;
    }
    locale.heure.heure = locale.heure.heure + 24;
  }



  return locale;
}

void Calendrier::initialiser_fuseaux() {
  f1.pays = "USA";
  f1.villes = "Iles Baker & Howland";
  f1.decalage_horaire.heure = -12;
  f1.decalage_horaire.minute = 0;
  f1.decalage_horaire.seconde = 0;


  f2.pays = "Samoas";
  f2.villes = "Fagatogo";
  f2.decalage_horaire.heure = -11;
  f2.decalage_horaire.minute = 0;
  f2.decalage_horaire.seconde = 0;


  f3.pays = "USA";
  f3.villes = "Honolulu";
  f3.decalage_horaire.heure = -10;
  f3.decalage_horaire.minute = 0;
  f3.decalage_horaire.seconde = 0;


  f4.pays = "France";
  f4.villes = "Îles Marquises";
  f4.decalage_horaire.heure = -9;
  f4.decalage_horaire.minute = 30;
  f4.decalage_horaire.seconde = 0;


  f5.pays = "USA";
  f5.villes = "Alaska";
  f5.decalage_horaire.heure = -9;
  f5.decalage_horaire.minute = 0;
  f5.decalage_horaire.seconde = 0;


  f6.pays = "USA";
  f6.villes = "Los Angeles";
  f6.decalage_horaire.heure = -8;
  f6.decalage_horaire.minute = 0;
  f6.decalage_horaire.seconde = 0;


  f7.pays = "USA";
  f7.villes = "Denver";
  f7.decalage_horaire.heure = -7;
  f7.decalage_horaire.minute = 0;
  f7.decalage_horaire.seconde = 0;


  f8.pays = "USA";
  f8.villes = "Houston";
  f8.decalage_horaire.heure = -6;
  f8.decalage_horaire.minute = 0;
  f8.decalage_horaire.seconde = 0;


  f9.pays = "USA";
  f9.villes = "New-York";
  f9.decalage_horaire.heure = -5;
  f9.decalage_horaire.minute = 0;
  f9.decalage_horaire.seconde = 0;


  f10.pays = "Bolivie";
  f10.villes = "La Paz";
  f10.decalage_horaire.heure = -4;
  f10.decalage_horaire.minute = 0;
  f10.decalage_horaire.seconde = 0;


  f11.pays = "Canada";
  f11.villes = "Terre-Neuve";
  f11.decalage_horaire.heure = -3;
  f11.decalage_horaire.minute = 30;
  f11.decalage_horaire.seconde = 0;


  f12.pays = "Brésil";
  f12.villes = "Brasilia";
  f12.decalage_horaire.heure = -3;
  f12.decalage_horaire.minute = 0;
  f12.decalage_horaire.seconde = 0;


  f13.pays = "Royaume Uni";
  f13.villes = "îles Sandwich du Sud";
  f13.decalage_horaire.heure = -2;
  f13.decalage_horaire.minute = 0;
  f13.decalage_horaire.seconde = 0;


  f14.pays = "Cap Vert";
  f14.villes = " Praia";
  f14.decalage_horaire.heure = -1;
  f14.decalage_horaire.minute = 0;
  f14.decalage_horaire.seconde = 0;


  f15.pays = "Heure UTC";
  f15.villes = "Greenwich";
  f15.decalage_horaire.heure = 0;
  f15.decalage_horaire.minute = 0;
  f15.decalage_horaire.seconde = 0;


  f16.pays = "Belgique";
  f16.villes = "Bruxelles";
  f16.decalage_horaire.heure = 1;
  f16.decalage_horaire.minute = 0;
  f16.decalage_horaire.seconde = 0;


  f17.pays = "Afrique du Sud";
  f17.villes = "Pretoria";
  f17.decalage_horaire.heure = 2;
  f17.decalage_horaire.minute = 0;
  f17.decalage_horaire.seconde = 0;


  f18.pays = "Russie";
  f18.villes = "Moscou";
  f18.decalage_horaire.heure = 3;
  f18.decalage_horaire.minute = 0;
  f18.decalage_horaire.seconde = 0;


  f19.pays = "Iran";
  f19.villes = "Téhéran";
  f19.decalage_horaire.heure = 3;
  f19.decalage_horaire.minute = 30;
  f19.decalage_horaire.seconde = 0;


  f20.pays = "Russie";
  f20.villes = "Samara";
  f20.decalage_horaire.heure = 4;
  f20.decalage_horaire.minute = 0;
  f20.decalage_horaire.seconde = 0;


  f21.pays = "Afghanistan";
  f21.villes = "Kaboul";
  f21.decalage_horaire.heure = 4;
  f21.decalage_horaire.minute = 30;
  f21.decalage_horaire.seconde = 0;


  f22.pays = "Pakistan";
  f22.villes = "Islamabad";
  f22.decalage_horaire.heure = 5;
  f22.decalage_horaire.minute = 0;
  f22.decalage_horaire.seconde = 0;


  f23.pays = "Inde";
  f23.villes = "New Delhi";
  f23.decalage_horaire.heure = 5;
  f23.decalage_horaire.minute = 30;
  f23.decalage_horaire.seconde = 0;


  f24.pays = "Népal";
  f24.villes = "Katmandou";
  f24.decalage_horaire.heure = 5;
  f24.decalage_horaire.minute = 45;
  f24.decalage_horaire.seconde = 0;


  f25.pays = "Kazakhstan";
  f25.villes = "Noursoultan";
  f25.decalage_horaire.heure = 6;
  f25.decalage_horaire.minute = 0;
  f25.decalage_horaire.seconde = 0;


  f26.pays = "Birmanie";
  f26.villes = "Naypyidaw";
  f26.decalage_horaire.heure = 6;
  f26.decalage_horaire.minute = 30;
  f26.decalage_horaire.seconde = 0;


  f27.pays = "Cambodge";
  f27.villes = "Phnom Penh";
  f27.decalage_horaire.heure = 7;
  f27.decalage_horaire.minute = 0;
  f27.decalage_horaire.seconde = 0;


  f28.pays = "Chine";
  f28.villes = "Pékin";
  f28.decalage_horaire.heure = 8;
  f28.decalage_horaire.minute = 0;
  f28.decalage_horaire.seconde = 0;


  f29.pays = "Australie";
  f29.villes = "Caiguna";
  f29.decalage_horaire.heure = 8;
  f29.decalage_horaire.minute = 45;
  f29.decalage_horaire.seconde = 0;


  f30.pays = "Japon";
  f30.villes = "Tokyo";
  f30.decalage_horaire.heure = 9;
  f30.decalage_horaire.minute = 30;
  f30.decalage_horaire.seconde = 0;


  f31.pays = "Australie";
  f31.villes = "Sydney";
  f31.decalage_horaire.heure = 9;
  f31.decalage_horaire.minute = 30;
  f31.decalage_horaire.seconde = 0;


  f32.pays = "Australie";
  f32.villes = "Melbourne";
  f32.decalage_horaire.heure = 10;
  f32.decalage_horaire.minute = 0;
  f32.decalage_horaire.seconde = 0;


  f33.pays = "Australie";
  f33.villes = "île Lord Howe";
  f33.decalage_horaire.heure = 10;
  f33.decalage_horaire.minute = 30;
  f33.decalage_horaire.seconde = 0;


  f34.pays = "Iles Salomon";
  f34.villes = "Honiara";
  f34.decalage_horaire.heure = 11;
  f34.decalage_horaire.minute = 0;
  f34.decalage_horaire.seconde = 0;


  f35.pays = "Fidji";
  f35.villes = "Suva";
  f35.decalage_horaire.heure = 12;
  f35.decalage_horaire.minute = 0;
  f35.decalage_horaire.seconde = 0;


  f36.pays = "Nouvelle-Zélande";
  f36.villes = "Îles Chatham";
  f36.decalage_horaire.heure = 12;
  f36.decalage_horaire.minute = 45;
  f36.decalage_horaire.seconde = 0;


  f37.pays = "Tonga";
  f37.villes = "Nukuʻalofa";
  f37.decalage_horaire.heure = 13;
  f37.decalage_horaire.minute = 0;
  f37.decalage_horaire.seconde = 0;


  f38.pays = "Kiribati";
  f38.villes = "Îles de la Ligne";
  f38.decalage_horaire.heure = 14;
  f38.decalage_horaire.minute = 0;
  f38.decalage_horaire.seconde = 0;

}
