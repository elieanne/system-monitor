#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

class System {
 public:
  // Retourne le CPU du système
  Processor &Cpu();
  // Retourne un conteneur composé des processus du système
  // les processus sont triés par utilisation CPU
  std::vector<Process> &Processes();
  // Retourne l'utilisation de la mémoire du système
  float MemoryUtilization();
  // Retourne le nombre de secondes depuis le démarrage du système
  long UpTime();
  // Retourne le nombre total de processus sur le système
  int TotalProcesses();
  // Retourne le nombre de processus en cours d'exécution sur le système
  int RunningProcesses();
  // Retourne l'identifiant du noyau du système (chaîne)
  std::string Kernel();
  // Retourne le nom du système d'exploitation
  std::string OperatingSystem();

  // Définit les membres privés nécessaires
 private:
  // le processeur du système
  Processor cpu_ = {};
  // conteneur composé des processus du système
  std::vector<Process> processes_;
};

#endif