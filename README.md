# SYSTEM-MONITOR
# français
Objectifs
L'objectif de ce projet est de montrer que vous avez acquis la logique de programmation et que vous êtes capable de vous adapter à de nouveaux langages.

Le langage de programmation que vous allez utiliser est le C++ . Il ne vous sera pas demandé de créer un projet de A à Z ; vous devrez simplement ajouter des fonctionnalités ou corriger le code d'une application donnée .

L'application que vous allez utiliser est Desktop System Monitor . Elle surveillera les ressources et les performances du système, telles que le processeur, la RAM, le SWAP, le ventilateur, le réseau, etc. Pour l'interface graphique, vous utiliserez la bibliothèque Dear ImGui pour C++.

Instructions
Cher ImGui
Comme indiqué ci-dessus, l'interface graphique que vous allez utiliser est Dear ImGui, il y a quelques notions que vous devez connaître sur cette bibliothèque/API.

Le premier point important à retenir est qu'ImGui est une interface utilisateur graphique en mode immédiat , comme son nom l'indique. Il existe deux types d'interfaces utilisateur : le mode retenu et le mode immédiat .

Mode immédiat : l'état de l'application est séparé de la bibliothèque graphique. L'application est responsable de l'affichage des commandes si nécessaire. Autrement dit, en mode immédiat, le client appelle directement les résultats pour afficher les objets graphiques.

Mode retenu : les appels client ne provoquent pas directement le rendu, mais mettent à jour un modèle interne abstrait, maintenu dans l'espace de données de la bibliothèque. Pour en savoir plus sur ce mode, cliquez ici .

Cette API ne nécessite aucune compilation spécifique ; vous pouvez ajouter les fichiers à votre projet existant. Pour l'intégration Dear ImGui, vous devez utiliser un backend. Ce backend transmet les entrées souris, clavier et manette, ainsi que divers paramètres. Il est chargé du rendu des sommets résultants.

Le backend sera fourni par nos soins, dans un système de fichiers décrit dans le paragraphe suivant. Vous devrez l'installer sdlen exécutant la commande apt install libsdl2-dev.

Système de fichiers
Le système de fichiers fourni ici contiendra tous les fichiers ImGui IPA. Pour une meilleure compréhension, voir ci-dessous une représentation du système de fichiers.

$ tree system-monitor
├── header.h
├── imgui                                 // <-- ImGui APIs
│   └── lib
│       ├── backend                       // <-- ImGui backend
│       │   ├── imgui_impl_opengl3.cpp
│       │   ├── imgui_impl_opengl3.h
│       │   ├── imgui_impl_sdl.cpp
│       │   └── imgui_impl_sdl.h
│       ├── gl3w
│       │   └── GL
│       │       ├── gl3w.c
│       │       ├── gl3w.h
│       │       └── glcorearb.h
│       ├── imconfig.h
│       ├── imgui.cpp
│       ├── imgui_demo.cpp
│       ├── imgui_draw.cpp
│       ├── imgui.h
│       ├── imgui_internal.h
│       ├── imgui_tables.cpp
│       ├── imgui_widgets.cpp
│       ├── imstb_rectpack.h
│       ├── imstb_textedit.h
│       └── imstb_truetype.h
├── main.cpp                             // <-- main file, where the application will
├── Makefile                             //     render (main loop)
├── mem.cpp                              // <-- memory resources and processes information
├── network.cpp                          // <-- network resources
└── system.cpp                           // <-- all system resources

5 directories, 28 files
Linux et Proc
Pour surveiller les ressources et les performances du système informatique, vous devrez utiliser le /procsystème de fichiers.

Le /procsystème de fichiers est un système virtuel qui n'existe pas sur le disque. Ce système est créé par le noyau au démarrage du système et détruit par celui-ci à son arrêt.

Ce système de fichiers contient des informations sur le système, du processeur à la mémoire, en passant par les processus actifs et bien plus encore. De ce fait, il peut être considéré comme un centre de contrôle et d'information pour le noyau. De fait, de nombreux utilitaires système sont de simples appels aux fichiers de ce répertoire.

Vous pouvez acquérir plus de connaissances sur ce système de fichiers en consultant la procpage de manuel ( man proc).

surveillance
Pour ce projet, vous devez présenter le suivi suivant :

Moniteur système , qui contiendra :

Le type de système d'exploitation (OS).

L'utilisateur s'est connecté à l'ordinateur.

Le nom de l'ordinateur, c'est-à-dire le nom d'hôte .

Le nombre total de tâches/processus actuellement en cours d'exécution, en veille, ininterrompus, zombies, tracés/arrêtés ou interrompus.

Type de processeur

Une section à onglets contenant CPUdes informations sur les performances Fanet Thermalles sujets, incluant un graphique de performances pour tous ces sujets. Ce graphique doit contenir une case à cocher ou un bouton permettant d'arrêter l'animation à tout moment. Il doit également comporter deux barres de défilement. La première barre permet de contrôler la taille FPSdu graphique, tandis que la seconde contrôle yson échelle.

CPUdevrait présenter ce graphique avec un texte superposé indiquant le pourcentage actuel du processeur.

FanLe tableau doit inclure les informations suivantes : l'état du ventilateur (activé/actif), sa vitesse actuelle et son niveau. Il doit également présenter le graphique ci-dessus.

Thermal, devrait présenter le graphique indiqué ci-dessus avec un texte superposé indiquant la température actuelle de l'ordinateur (généralement le capteur du processeur).

exemple :

image : https://academy.digifemmes.com/media/system.gif

Moniteur de mémoire et de processus , qui contiendra :

La mémoire physique (RAM) étant utilisée, il doit y avoir une sorte d'affichage visuel de cette utilisation.

La mémoire virtuelle (SWAP) étant utilisée, elle devrait également inclure un affichage visuel.

L'utilisation du disque, même ici.

Une barre d'onglets qui devrait contenir un tableau de processus avec les colonnes suivantes :

PID , avec l'identification du processus.
Nom , nom du processus.
État , état actuel du processus.
Utilisation du processeur , quantité de processeur utilisée par le processus en pourcentage.
Utilisation de la mémoire , quantité de mémoire utilisée par le processus en pourcentage.
Une zone de texte qui permet à l'utilisateur de filtrer le tableau.

Les utilisateurs doivent pouvoir sélectionner plusieurs lignes du tableau.
exemple :

image : https://academy.digifemmes.com/media/mem.gif

Réseau , qui contiendra :

Le réseau ipv4, ( lo, wlp5s0et d'autres réseaux que l'ordinateur peut avoir).

Une barre d'onglets qui doit contenir deux tableaux :

RX(récepteur réseau) contenant les données suivantes : octets, paquets, erreurs, drop, fifo, trame, compressé et multicast.
TX(émetteur réseau) contenant les données suivantes : octets, paquets, erreurs, drop, fifo, colls, porteuse et compressées.
Il doit également contenir une section à onglets pour les deux RX, TXqui doit afficher une représentation visuelle (par exemple, une barre de progression) de tous les réseaux présents sur l'ordinateur. Cet affichage doit respecter les règles suivantes :

Chaque réseau doit être converti d' octets en Go , Ko ou Mo selon sa valeur. Les valeurs affichées ne doivent pas être trop grandes ou trop petites. Autrement dit, elles doivent être ajustables.

exemple :

452755738 octets => 431,78 Mo . // parfait
452755738 octets => 0,42 Go . // trop petit
452755738 octets => 442144,28,6 Ko . // trop grand

L'affichage visuel devrait passer de 0 Go à 2 Go

exemple :

image: https://academy.digifemmes.com/media/network.gif

Ce projet vous aidera à en apprendre davantage sur :

langage de programmation C++
Interface utilisateur/expérience utilisateur
Cher ImGui
processeur
Mémoire
ÉCHANGER
BÉLIER
Disque
Réseau
Système de fichiers Linux
procédure
sysfs

# anglais
Objectives
The objective for this project is to show that you have acquired programming logic and that you are able to adapt to new languages.

The programming language you are about to use is C++. Creating a project from scratch will not be asked, instead you will have to add features or fix the code of a given application.

The application you are about to work on is a Desktop System Monitor. The app will monitor the computer system resources and performance, such as CPU, RAM, SWAP, Fan, Network and more. For the GUI you will use the Dear ImGui library for C++.

Instructions
Dear ImGui
As stated above the GUI you are going to use is Dear ImGui there are some notions you should know about this library/API.

The first important point to be aware of is that ImGui is an immediate mode graphic user interface, as the name implies it: "ImGui". There are two types of UIs, retained mode and immediate mode.

Immediate mode: the application state is separated from the graphics library. It is the application responsibility for drawing commands when necessary. In other words, in immediate mode the client calls directly results in the rendering of graphics objects to the display.

Retained mode: the client calls do not directly cause actual rendering, but instead update an abstract internal model, which is maintained within the library's data space. You can see more about this mode here.

For this API there is no need for specific builds, you can add the files to your existing project. To integrate Dear ImGui you must use a backend, this backend passes mouse/keyboard/gamepad inputs and a variety of settings. It is in charge of rendering the resulting vertices.

The backend will be provided by us, in a file system described in the next paragraph. You will have to install sdl by running the command apt install libsdl2-dev.

File System
The file system provided, here, will contain all the ImGui IPA. For easier understanding, see below a representation of the fs.

$ tree system-monitor
├── header.h
├── imgui                                 // <-- ImGui APIs
│   └── lib
│       ├── backend                       // <-- ImGui backend
│       │   ├── imgui_impl_opengl3.cpp
│       │   ├── imgui_impl_opengl3.h
│       │   ├── imgui_impl_sdl.cpp
│       │   └── imgui_impl_sdl.h
│       ├── gl3w
│       │   └── GL
│       │       ├── gl3w.c
│       │       ├── gl3w.h
│       │       └── glcorearb.h
│       ├── imconfig.h
│       ├── imgui.cpp
│       ├── imgui_demo.cpp
│       ├── imgui_draw.cpp
│       ├── imgui.h
│       ├── imgui_internal.h
│       ├── imgui_tables.cpp
│       ├── imgui_widgets.cpp
│       ├── imstb_rectpack.h
│       ├── imstb_textedit.h
│       └── imstb_truetype.h
├── main.cpp                             // <-- main file, where the application will
├── Makefile                             //     render (main loop)
├── mem.cpp                              // <-- memory resources and processes information
├── network.cpp                          // <-- network resources
└── system.cpp                           // <-- all system resources

5 directories, 28 files
Linux and Proc
To monitor the computer system resources and performance you will have to use the /proc filesystem.

The /proc filesystem is a virtual system that does not exist on disk. This system is created by the kernel when the system boots, and destroyed by it when the system shuts down.

This filesystem contains information about the system, from the CPU, to memory, to active processes and much more. For this reason, it can be regarded as a control and information center for the kernel. As a matter of fact, a lot of the system utilities are simple calls to files in this directory.

You can acquire more knowledge about this filesystem by taking a look to the proc manual page (man proc).

Monitorization
For this project you must present the following monitorization:

System monitor, that will contain :

The type of OS (Operating System).

The user logged into the computer.

The computer name, this being the hostname.

The total number of tasks/processes that are currently running, sleeping, uninterruptible, zombie, traced/stopped or interrupted.

Type of CPU

A tabbed section containing CPU, Fan and Thermal information, this information include a performance graphic for all those topics. This graph should contain some kind of checkbox or button to be able to stop the animation whenever the user desires to do so. Additionally, it should also have two slider bars. The first slider bar should be able to control the FPS of the graph, and the second slider bar should control the y scale of the graph.

CPU should present this graph with an overlay text saying the current percentage of the CPU.

Fan, should include the following information, the status of the fan, (enable/active), the current speed and the level. And should also present the graph stated above.

Thermal, should present the graph stated above with an overlay text saying the current temperature of the computer (usually the cpu sensor).

example :

image

Memory and process monitor, that will contain :

The Physic Memory (RAM) being used, it must have some kind of visual display of this usage.

The Virtual Memory (SWAP) being used, it should also include a visual display.

The Disk usage, same here.

A tab bar that should contain a table of processes with the following columns :

PID, with the process identification.
Name, name of the process.
State, current state of the process.
CPU usage, how much CPU the process is using in percentage.
Memory usage, how much memory the process is using in percentage.
A text box that lets the user filter the table.

Users must be able to select multiple rows of the table.
example :

image

Network, that will contain :

The network ipv4, (lo, wlp5s0 and other networks that the computer may have).

A tab bar that should contain two tables :

RX (network receiver) containing the following data : bytes, packets, errs, drop, fifo, frame, compressed and multicast.
TX (network transmitter) containing the following data : bytes, packets, errs, drop, fifo, colls, carrier and compressed.
It should also contain a tabbed section for both RX and TX, those sections should display a visual usage (ex: a progress bar), of all network present on the computer. This visual display should obey the following rules:

Each network should be converted from bytes to GB, KB or MB depending on the value. It should not display values that are too big or too small. In other words it should be adjustable.

example :

452755738 bytes => 431.78 MB. // perfect
452755738 bytes => 0.42 GB. // too small
452755738 bytes => 442144.28.6 KB. // too big

The visual display should go from 0GB to 2GB

example :

image

This project will help you learn about:

C++ programming language
UI/UX
Dear ImGui
CPU
Memory
SWAP
RAM
Disk
Network
Linux filesystem
proc
sysfs




# Projet System-Monitor

![Moniteur système](images/moniteur.png)

## Description

Le projet vise à :

Appliquer des concepts de programmation orientée objet (OOP) en C++.
Afficher des informations système telles que l'utilisation du CPU, de la RAM, les processus en cours, etc., dans un format graphique basé sur du texte grâce à la bibliothèque ncurses.

2. Structure du Projet
Principaux Fichiers et Dossiers
src/ : Contient le code source, comme les classes C++ et les fonctions principales.
CMakeLists.txt ou Makefile : Fichier pour automatiser la compilation.
build/ : Répertoire où les fichiers compilés sont placés.
images/monitor.png : Image illustrant l'apparence de l'application.
Les Classes Importantes
System :

Fournit des informations globales sur le système (par exemple, utilisation globale du CPU, mémoire totale).
Rassemble des informations sur tous les processus en cours.
Process :

Représente chaque processus actif sur le système.
Contient des données comme le PID, le nom de l'utilisateur, l'utilisation CPU/RAM, etc.
Processor :

Analyse l'utilisation globale du CPU.
NCursesDisplay :

Utilise la bibliothèque ncurses pour afficher les données dans le terminal.
LinuxParser :

Fournit des fonctions utilitaires pour lire les fichiers du système Linux (par exemple, /proc/).
Analyse les fichiers pour extraire les données nécessaires (CPU, mémoire, processus).

3. Concepts Techniques
Programmation Orientée Objet (OOP) :

Utilisation des classes comme System, Processor, et Process pour organiser et encapsuler les données.
Chaque classe a une responsabilité spécifique (Single Responsibility Principle).
Lecture des Fichiers /proc/ :

Les informations système sur Linux sont disponibles dans le dossier /proc/. Ce projet lit ces fichiers pour extraire les données. Par exemple :
/proc/stat pour l'utilisation du CPU.
/proc/meminfo pour l'utilisation de la mémoire.
/proc/[PID]/stat pour les informations sur un processus spécifique.
Affichage avec ncurses :

La bibliothèque ncurses permet de créer une interface utilisateur en mode texte dans un terminal.
Les données sont mises à jour dynamiquement dans une boucle pour simuler un moniteur en temps réel.


4. Fonctionnement Global
Étape 1 : Initialisation
Le programme initialise les objets système, CPU et processus.
Les fichiers du système Linux sont lus pour récupérer les données initiales.
Étape 2 : Boucle Principale
Une boucle met à jour les données à intervalle régulier.
L'affichage dans le terminal est rafraîchi à chaque itération.
Étape 3 : Extraction des Données
Le code utilise des fonctions pour lire des fichiers spécifiques dans /proc/ et interprète leur contenu pour en extraire les données nécessaires.
Étape 4 : Affichage
Les informations sont affichées sous forme de texte graphique grâce à ncurses.



## Dépendances

### ncurses
[ncurses](https://www.gnu.org/software/ncurses/) est une bibliothèque qui facilite la sortie graphique textuelle dans le terminal. Ce projet s'appuie sur ncurses pour l'affichage des données.

Vous devez installer ncurses dans votre propre environnement Linux : `sudo apt install libncurses5-dev libncursesw5-dev`

## Make
Ce projet utilise [Make](https://www.gnu.org/software/make/). Le fichier Makefile a quatre cibles :
* `build` compile le code source et génère un exécutable
* `format` applique [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) pour styliser le code source
* `debug` compile le code source et génère un exécutable, incluant les symboles de débogage
* `clean` supprime le répertoire `build/`, y compris tous les artefacts de compilation.

## Instructions

1. Cloner le dépôt du projet : `git clone https://github.com/nancyreschka/System-Monitor`

2. Construisez le projet : `make build`

3. Exécutez l'exécutable résultant : `./build/monitor`




