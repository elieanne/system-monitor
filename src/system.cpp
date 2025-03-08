#include "system.h"

#include <unistd.h>

#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// Retourne le CPU du système
Processor& System::Cpu() { return cpu_; }

// Retourne un conteneur composé des processus du système
vector<Process>& System::Processes() {
  vector<Process> foundProcesses{};
  // lire les IDs de processus depuis le système de fichiers et générer un
  // vecteur
  vector<int> processIds = LinuxParser::Pids();
  for (int p : processIds) {
    Process pro{p};
    foundProcesses.push_back(pro);
  }

  // trier les processus selon leur utilisation CPU
  sort(foundProcesses.begin(), foundProcesses.end(),
       [](const Process& pa, const Process& pb) {
         return (pb.CpuUtilization() < pa.CpuUtilization());
       });
  // mettre à jour la liste des processus
  processes_ = foundProcesses;

  return processes_;
}

// Retourne l'identifiant du noyau du système (chaîne de caractères)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// Retourne l'utilisation de la mémoire du système
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// Retourne le nom du système d'exploitation
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// Retourne le nombre de processus en cours d'exécution sur le système
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// Retourne le nombre total de processus sur le système
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// Retourne le nombre de secondes depuis le démarrage du système
long int System::UpTime() { return LinuxParser::UpTime(); }