#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// Lire et retourner le nom du système d'exploitation
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// Lire et retourner le noyau du système
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS : Mettre à jour cela pour utiliser std::filesystem
// Lire et retourner les identifiants de processus
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Est-ce un répertoire ?
    if (file->d_type == DT_DIR) {
      // Chaque caractère du nom est-il un chiffre ?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// Lire et retourner l'utilisation de la mémoire du système
float LinuxParser::MemoryUtilization() {
  float memTotal = 0.0;
  float memFree = 0.0;
  string line;
  string key;
  string value;

  // lire le fichier /proc/meminfo et chercher MemTotal et MemFree
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      // supprimer ' kB' à la fin, les espaces et :
      std::remove(line.begin(), line.end(), 'kB');
      std::remove(line.begin(), line.end(), ' ');
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        // chercher la clé memTotal
        if (key == "MemTotal") {
          memTotal = std::stof(value);
        }
        // chercher la clé memFree
        else if (key == "MemFree") {
          memFree = std::stof(value);
          break;
        }
      }
    }
  }

  // Mémoire totale utilisée = (memTotal - MemFree) / memTotal
  return ((memTotal - memFree) / memTotal);
}

// Lire et retourner le temps de fonctionnement du système
long LinuxParser::UpTime() {
  string line;
  string wholeTime;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> wholeTime) {
        try {
          return std::stol(wholeTime);
        } catch (const std::invalid_argument& arg) {
          return 0;
        }
      }
    }
  }
  return 0;
}

// TODO : Lire et retourner le nombre de jiffies pour le système
long LinuxParser::Jiffies() { return 0; }

// TODO : Lire et retourner le nombre de jiffies actifs pour un PID
// RETIRER : [[maybe_unused]] une fois que vous avez défini la fonction
long LinuxParser::ActiveJiffies(int pid [[maybe_unused]]) { return 0; }

// TODO : Lire et retourner le nombre de jiffies actifs pour le système
long LinuxParser::ActiveJiffies() { return 0; }

// TODO : Lire et retourner le nombre de jiffies inactifs pour le système