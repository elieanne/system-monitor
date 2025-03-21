#include <curses.h>
#include <chrono>
#include <string>
#include <thread>
#include <vector>

#include "format.h"
#include "ncurses_display.h"
#include "system.h"

using std::string;
using std::to_string;

// 50 barres affichées uniformément de 0 à 100 %
// 2% correspond à une barre (|)
    std::string
    NCursesDisplay::ProgressBar(float percent) {
  std::string result{"0%"};
  int size{50};
  float bars{percent * size};

  for (int i{0}; i < size; ++i) {
    result += i <= bars ? '|' : ' ';
  }

  string display{to_string(percent * 100).substr(0, 4)};
  if (percent < 0.1 || percent == 1.0)
    display = " " + to_string(percent * 100).substr(0, 3);
  return result + " " + display + "/100%";
}

void NCursesDisplay::DisplaySystem(System &system, WINDOW *window) {
  int row{0};
  mvwprintw(window, ++row, 2, ("OS: " + system.OperatingSystem()).c_str());
  mvwprintw(window, ++row, 2, ("Kernel: " + system.Kernel()).c_str());
  mvwprintw(window, ++row, 2, "CPU: ");
  wattron(window, COLOR_PAIR(1));
  mvwprintw(window, row, 10, "");
  wprintw(window, ProgressBar(system.Cpu().Utilization()).c_str());
  wattroff(window, COLOR_PAIR(1));
  mvwprintw(window, ++row, 2, "Memory: ");
  wattron(window, COLOR_PAIR(1));
  mvwprintw(window, row, 10, "");
  wprintw(window, ProgressBar(system.MemoryUtilization()).c_str());
  wattroff(window, COLOR_PAIR(1));
  mvwprintw(window, ++row, 2,
            ("Total Processes: " + to_string(system.TotalProcesses())).c_str());
  mvwprintw(
      window, ++row, 2,
      ("Running Processes: " + to_string(system.RunningProcesses())).c_str());
  mvwprintw(window, ++row, 2,
            ("Up Time: " + Format::ElapsedTime(system.UpTime())).c_str());
  wrefresh(window);
}

void NCursesDisplay::DisplayProcesses(std::vector<Process> &processes,
                                      WINDOW *window, int n) {
  int row{0};
  int const pid_column{2};
  int const user_column{9};
  int const cpu_column{16};
  int const ram_column{26};
  int const time_column{35};
  int const command_column{46};
  wattron(window, COLOR_PAIR(2));
  mvwprintw(window, ++row, pid_column, "PID");
  mvwprintw(window, row, user_column, "USER");
  mvwprintw(window, row, cpu_column, "CPU[%%]");
  mvwprintw(window, row, ram_column, "RAM[MB]");
  mvwprintw(window, row, time_column, "TIME+");
  mvwprintw(window, row, command_column, "COMMAND");
  wattroff(window, COLOR_PAIR(2));
  for (int i = 0; i < n; ++i) {
    mvwprintw(window, ++row, pid_column,
              normalizeStringLength(to_string(processes[i].Pid()), 7).c_str());
    mvwprintw(window, row, user_column,
              normalizeStringLength(processes[i].User(), 7).c_str());
    float cpu = processes[i].CpuUtilization() * 100;
    mvwprintw(window, row, cpu_column,
              normalizeStringLength(to_string(cpu).substr(0, 4), 10).c_str());
    mvwprintw(window, row, ram_column,
              normalizeStringLength(processes[i].Ram(), 9).c_str());
    mvwprintw(
        window, row, time_column,
        normalizeStringLength(Format::ElapsedTime(processes[i].UpTime()), 9)
            .c_str());
    mvwprintw(window, row, command_column, "");
    mvwprintw(window, row, command_column,
              normalizeStringLength(
                  processes[i].Command().substr(0, window->_maxx - 46).c_str(),
                  window->_maxx - 46)
                  .c_str());
  }
}

std::string NCursesDisplay::normalizeStringLength(string s,
                                                  std::size_t length) {
  std::string norm = "";
  int fillIn = static_cast<int>(length - s.length());
  if (s.length() < length) {
    norm = s;
    for (int i = 0; i < fillIn; i++) {
      norm.append(" ");
    }
  } else
    return s;
  return norm;
}

void NCursesDisplay::Display(System &system, int n) {
  initscr();      // démarrer ncurses
  noecho();       // ne pas afficher les valeurs d'entrée
  cbreak();       // terminer ncurses avec ctrl + c
  start_color();  // activer la couleur

  int x_max{getmaxx(stdscr)};
  WINDOW *system_window = newwin(9, x_max - 1, 0, 0);
  WINDOW *process_window =
      newwin(3 + n, x_max - 1, system_window->_maxy + 1, 0);

  while (1) {
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    box(system_window, 0, 0);
    box(process_window, 0, 0);
    DisplaySystem(system, system_window);
    DisplayProcesses(system.Processes(), process_window, n);
    wrefresh(system_window);
    wrefresh(process_window);
    refresh();
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  endwin();
}