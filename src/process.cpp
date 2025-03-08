#include "process.h"

#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) : processId_(pid) {
  // initialiser toutes les valeurs
  calculateCpuUsage();
  determineCommand();
  determineRam();
  determineUptime();
  determineUser();
}

// Retourne l'ID de ce processus
int Process::Pid() { return processId_; }

// Retourne l'utilisation CPU de ce processus
float Process::CpuUtilization() const { return cpuUsage_; }

// Retourne la commande qui a généré ce processus
string Process::Command() { return command_; }

// Retourne l'utilisation de la mémoire de ce processus
string Process::Ram() { return ram_; }

// Retourne l'utilisateur (nom) qui a généré ce processus
string Process::User() { return user_; }

// Retourne l'âge de ce processus (en secondes)
long int Process::UpTime() { return uptime_; }

// calcule l'utilisation CPU de ce processus et l'enregistre dans cpuUsage_
void Process::calculateCpuUsage() {
  // lire les valeurs du système de fichiers
  long uptime = LinuxParser::UpTime();
  vector<float> val = LinuxParser::CpuUtilization(Pid());
  // seulement si les valeurs ont pu être lues avec succès
  if (val.size() == 5) {
    // ajouter utime, stime, cutime, cstime (ils sont en secondes)
    float totaltime =
        val[kUtime_] + val[kStime_] + val[kCutime_] + val[kCstime_];
    float seconds = uptime - val[kStarttime_];
    // calculer l'utilisation CPU du processus
    cpuUsage_ = totaltime / seconds;
  } else
    cpuUsage_ = 0;
}

// détermine le nom de l'utilisateur qui a généré ce processus et l'enregistre
// dans user_
void Process::determineUser() { user_ = LinuxParser::User(Pid()); }
// détermine la commande qui a généré ce processus et l'enregistre dans command_
void Process::determineCommand() { command_ = LinuxParser::Command(Pid()); }
// détermine l'utilisation de la mémoire de ce processus et l'enregistre dans
// ram_
void Process::determineRam() {
  // lire la valeur en kB depuis le fichier
  string val = LinuxParser::Ram(Pid());
  // convertir en MB
  try {
    long conv = std::stol(val) / 1000;
    ram_ = std::to_string(conv);
  } catch (const std::invalid_argument& arg) {
    ram_ = "0";
  }
}
// détermine l'âge de ce processus et l'enregistre dans uptime_
void Process::determineUptime() {
  // TODO selon la version du noyau, obtenir les jiffies ou les ticks d'horloge
  uptime_ = LinuxParser::UpTime(Pid());
}