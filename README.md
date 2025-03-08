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




