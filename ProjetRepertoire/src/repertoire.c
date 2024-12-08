#include "../include/repertoire.h"
#include "inputChecker.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

node_t *ajouter_personne(node_t *liste) {
    personne_t *personne = malloc(sizeof(personne_t));
    if (personne == NULL) {
        printf("Erreur d'allocation de memoire.\n");
        return liste;
    }

    // Saisie du nom
    do {
        printf("Entrer le nom : ");
        scanf("%39s", personne->nom);
        if (!estValideNomPrenom(personne->nom)) {
            printf("Le nom doit contenir uniquement des lettres.\n");
        }
    } while (!estValideNomPrenom(personne->nom));

    // Saisie du prenom
    do {
        printf("Entrer le prenom : ");
        scanf("%39s", personne->prenom);
        if (!estValideNomPrenom(personne->prenom)) {
            printf("Le prenom doit contenir uniquement des lettres.\n");
        }
    } while (!estValideNomPrenom(personne->prenom));

    // Vérification des doublons
    node_t *current = liste;
    while (current != NULL) {
        if (strcmp(current->personne->nom, personne->nom) == 0) {
            printf("%s existe deja dans le repertoire.\n", personne->nom);
            free(personne);
            return liste;
        }
        current = current->next;
    }

    // Saisie du numero de telephone
    do {
        printf("Entrer le numero de telephone : ");
        scanf("%39s", personne->numero_telephone);
        if (!verifeNum(personne->numero_telephone)) {
            printf("Le numero de telephone doit contenir 10 chiffres.\n");
        }
    } while (!verifeNum(personne->numero_telephone));

    // Saisie de l'adresse mail
    do {
        printf("Entrer l'adresse mail : ");
        scanf("%39s", personne->adresse_mail);
        if (!verifMail(personne->adresse_mail)) {
            printf("L'adresse mail doit contenir un @ et un point.\n");
        }
    } while (!verifMail(personne->adresse_mail));

    // Allocation d'un nouveau noeud
    node_t *node = malloc(sizeof(node_t));
    if (node == NULL) {
        printf("Erreur d'allocation de memoire.\n");
        free(personne);
        return liste;
    }

    node->personne = personne;
    node->next = liste;
    node->prev = NULL;

    if (liste != NULL) {
        liste->prev = node;
    }

    return node;
}

void afficher_repertoire(node_t *liste) {
    if (liste == NULL) {
        printf("\nLe repertoire est vide.\n");
        return;
    }

    int i = 1;
    node_t *current = liste;
    while (current != NULL) {
        printf("\nPersonne %d :\n", i++);
        afficher_personne(current->personne);
        current = current->next;
    }
}

void rechercher_personne(node_t *liste) {
    if (liste == NULL) {
        printf("\nLe repertoire est vide.\n");
        return;
    }

    char nom[40];
    printf("\nEntrer le nom que vous voulez chercher : ");
    scanf("%39s", nom);

    node_t *current = liste;
    while (current != NULL) {
        if (strcasecmp(current->personne->nom, nom) == 0) {
            afficher_personne(current->personne);
            return;
        }
        current = current->next;
    }

    printf("\nIl n'existe pas de personne avec le nom %s dans le repertoire.\n", nom);
}

node_t *supprimer_personne(node_t *liste) {
    if (liste == NULL) {
        printf("\nLe repertoire est vide.\n");
        return NULL;
    }

    char nom[40];
    printf("\nEntrez le nom de la personne que vous souhaitez supprimer : ");
    scanf("%39s", nom);

    node_t *current = liste;
    while (current != NULL) {
        if (strcasecmp(current->personne->nom, nom) == 0) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                liste = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }

            printf("\n%s a bien ete supprimee.\n", nom);
            free(current->personne);
            free(current);
            return liste;
        }
        current = current->next;
    }

    printf("\n%s n'a pas ete trouvee dans votre repertoire.\n", nom);
    return liste;
}

void afficher_personne(personne_t *personne) {
    printf("\tNom : %s\n", personne->nom);
    printf("\tPrenom : %s\n", personne->prenom);
    printf("\tNumero de telephone : %s\n", personne->numero_telephone);
    printf("\tAdresse mail : %s\n", personne->adresse_mail);
}
