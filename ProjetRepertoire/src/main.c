/**
* @file main.c
 * @brief Programme principal pour la gestion du répertoire de contacts.
 *
 * Ce programme permet à l'utilisateur d'ajouter, afficher, rechercher et supprimer des contacts
 * dans un répertoire, implémenté sous forme de liste chaînée. L'utilisateur
 * interagit avec le programme via un menu.
 *
 * Les fonctionnalités proposées sont :
 * - Ajouter une personne au répertoire
 * - Afficher tous les contacts du répertoire
 * - Rechercher une personne dans le répertoire
 * - Supprimer une personne du répertoire
 * - Quitter le programme
 *
 * Le programme continue de s'exécuter jusqu'à ce que l'utilisateur choisisse de le quitter.
 *
 * @author SATKUNARAJAH Sarusman, SOLAKI Priyank & SASIKUMAR Sahkana
 *
 */

#include "../include/repertoire.h"
#include <stdio.h>


#define FICHIER_REPERTOIRE "repertoire.txt"

int main() {
    int fonctionnalite;
    // node_t *repertoire = NULL;
    node_t *repertoire = charger_repertoire(FICHIER_REPERTOIRE);

    printf("Bienvenue a toi !");
    while (true) {
        printf("\nQue voulez-vous faire ?");
        printf("\n\t1. Ajouter une personne");
        printf("\n\t2. Afficher le repertoire");
        printf("\n\t3. Rechercher une personne");
        printf("\n\t4. Supprimer une personne");
        printf("\n\t5. Quitter\n");
        printf("\nEntrez votre choix : ");

        if (scanf("%d", &fonctionnalite) != 1 || fonctionnalite < 1 || fonctionnalite > 5) {
            printf("Choisissez un chiffre entre 1 et 5.\n");
            while (getchar() != '\n');
            continue;
        }

        if (fonctionnalite == 5) break;

        switch (fonctionnalite) {
            case 1:
                repertoire = ajouter_personne(repertoire);
                sauvegarder_repertoire(repertoire, FICHIER_REPERTOIRE);
            break;
            case 2:
                afficher_repertoire(repertoire);
            break;
            case 3:
                rechercher_personne(repertoire);
            break;
            case 4:
                repertoire = supprimer_personne(repertoire);
                sauvegarder_repertoire(repertoire, FICHIER_REPERTOIRE);
            break;
        }
    }

    printf("\nMerci de votre visite !\n");
    sauvegarder_repertoire(repertoire, FICHIER_REPERTOIRE);
    return 0;
}
