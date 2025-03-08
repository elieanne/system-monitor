#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Processor {
 public:
  float Utilization();

  // constructeur
  Processor();

  // Déclare les membres privés nécessaires
 private:
  // les valeurs du CPU qui ont été déterminées précédemment
  // temps total CPU précédent depuis le démarrage =
  // utilisateur + nice + système + inactif + attente d'E/S + irq + softirq +
  // vol
  float prevTotalCpuTime;
  // temps inactif précédent depuis le démarrage = inactif + attente d'E/S
  float prevIdleCpuTime;

  // convertit le vecteur de chaînes donné en un vecteur de longs
  vector<long> convertToLong(vector<string> values);
};

#endif