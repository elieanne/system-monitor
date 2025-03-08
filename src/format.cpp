#include "format.h"

#include <string>

using std::string;

// fonction d'aide pour calculer les heures, les minutes et les secondes à
// partir des secondes ENTRÉE : Long int mesurant les secondes SORTIE : HH:MM:SS
string Format::ElapsedTime(long seconds) {
  string time = "00:00:00";
  long cal = 0;
  if (seconds > 0) {
    // calculer les heures
    cal = seconds / 3600;
    time = TimeValueToString(cal) + ":";
    // calculer les minutes
    cal = (seconds / 60) % 60;
    time += TimeValueToString(cal) + ":";
    // calculer les secondes
    cal = seconds % 60;
    time += TimeValueToString(cal);
  }

  return time;
}

// vérifier si le nombre calculé est inférieur à 10 et retourner la chaîne
// appropriée
std::string Format::TimeValueToString(long time) {
  if (time < 10)
    return "0" + std::to_string(time);
  else
    return std::to_string(time);
}