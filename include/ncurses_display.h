#ifndef NCURSES_DISPLAY_H
#define NCURSES_DISPLAY_H

#include <curses.h>

#include "process.h"
#include "system.h"

namespace NCursesDisplay {
// Affiche le système
void Display(System &system, int n = 10);
// Affiche le système dans une fenêtre
void DisplaySystem(System &system, WINDOW *window);
// Affiche les processus dans une fenêtre
void DisplayProcesses(std::vector<Process> &processes, WINDOW *window, int n);
// Crée une barre de progression en fonction du pourcentage
std::string ProgressBar(float percent);
// Normalise la longueur d'une chaîne de caractères
std::string normalizeStringLength(std::string s, std::size_t length);
};  // namespace NCursesDisplay

#endif