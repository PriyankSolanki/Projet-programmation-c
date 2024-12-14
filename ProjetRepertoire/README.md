# Projet - Gestion de Répertoire en C

![SAT SOL SAS Répo](interface/static/images/logo.png)

## Description
Ce projet est une application en C avec une interface Python. Il est conçu pour ajouter des informations personnelles des personnes notamment le nom, prénom, numéro de téléphone et adresse mail. .

## Prérequis

### Logiciels nécessaires
- **CMake** (pour la configuration et la génération des fichiers de compilation)
- **Make** (pour la compilation du projet)
- **Python** 
- **Un compilateur C** (par exemple, GCC ou Clang)

### Dépendances Python 
Le projet inclut une interface Python (`app.py`), vous aurez besoin de Python et des bibliothèques spécifiques.

1. Assurez-vous que Python est installé sur votre machine. Vous pouvez vérifier cela en exécutant :

   ```bash
   python --version
   ```

## Installation

1. **Décompresser le fichier `.rar`** :
    - Décompressez le fichier `.rar` contenant le projet dans un répertoire de votre choix.

2. **Configurer le projet avec CMake** :
    - Ouvrez un terminal ou sur CLion, un éditeur avec CMake qui détectera les configurations tout seul.
    - Accédez au répertoire où vous avez décompressé le projet.
    - Créez un répertoire de compilation :

      ```bash
      mkdir cmake-build-debug
      cd cmake-build-debug
      ```

    - Exécutez CMake pour générer les fichiers nécessaires à la compilation :

      ```bash
      cmake ..
      ```

3. **Compiler le projet** :
    - Une fois que CMake a généré les fichiers nécessaires, vous pouvez compiler le projet avec la commande `make` :

      ```bash
      make
      ```

    - Cela générera les fichiers exécutables dans le répertoire de compilation.

4. **Exécuter le programme** :
    - Après la compilation, vous pouvez exécuter le programme généré. Le nom de l'exécutable est dans `CMakeLists.txt` ou dans `Makefile`.

      ```bash
      ./projetRepertoire
      ```

    - Pour l'interface Python (via `app.py`), vous pouvez l'exécuter en utilisant :

      ```bash
      python app.py
      ```

## Structure du projet

Voici l'arborescence des fichiers de notre projet sur l'éditeur CLion:

```
Projet-programmation-c/
│
├── ProjetRepertoire/
│   ├── .idea/
│   ├── cmake-build-debug/       # Répertoire de compilation
│   ├── include/                 # Fichiers d'en-tête
│   │   ├── inputChecker.h
│   │   └── repertoire.h
│   ├── interface/               # Interface (Python, HTML...)
│   │   ├── static/
│   │   ├── templates/
│   │   └── app.py               # Interface Python
│   ├── src/                     # Code source C
│   │   ├── inputChecker.c
│   │   ├── main.c
│   │   ├── repertoire.c
│   │   CMakeLists.txt       # Fichier de configuration CMake
│   │   Makefile             # Fichier Makefile (pour Mac)
│   └── README.md                # Ce fichier
```

## Auteurs
### SOLANKI Priyank, SATKUNARAJAH Sarusman, SASIKUMAR Sahkana - LSI1


