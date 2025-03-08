#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Classe de base pour la représentation d'un processus
Elle contient les attributs pertinents comme indiqué ci-dessous
*/
class Process {
 public:
  // constructeur pour initialiser le processus avec l'ID de processus lu depuis
  // le système de fichiers
  Process(int pid);
  // Retourne l'ID de ce processus
  int Pid();
  // Retourne l'utilisateur (nom) qui a généré ce processus
  std::string User();
  // Retourne la commande qui a généré ce processus
  std::string Command();
  // Retourne l'utilisation CPU de ce processus
  // la valeur est donnée en pourcentage
  float CpuUtilization() const;
  // Retourne l'utilisation de la mémoire de ce processus en Mo
  std::string Ram();
  // Retourne l'âge de ce processus (en secondes)
  long int UpTime();

  // Déclare les membres privés nécessaires
 private:
  // ID du processus
  int processId_;
  // nom de l'utilisateur qui a généré ce processus
  std::string user_;
  // commande qui a généré ce processus
  std::string command_;
  // utilisation CPU du processus
  float cpuUsage_;
  // utilisation de la mémoire du processus
  std::string ram_;
  // âge de ce processus
  long uptime_;
  // valeurs CPU d'un processus
  enum ProcessCPUStates {
    kUtime_ = 0,
    kStime_,
    kCutime_,
    kCstime_,
    kStarttime_
  };

  // calcule l'utilisation CPU de ce processus et l'enregistre dans cpuUsage_
  void calculateCpuUsage();
  // détermine le nom de l'utilisateur qui a généré ce processus et l'enregistre
  // dans user_
  void determineUser();
  // détermine la commande qui a généré ce processus et l'enregistre dans
  // command_
  void determineCommand();
  // détermine l'utilisation de la mémoire de ce processus et l'enregistre dans
  // ram_
  void determineRam();
  // détermine l'âge de ce processus et l'enregistre dans uptime_
  void determineUptime();
};

#endif