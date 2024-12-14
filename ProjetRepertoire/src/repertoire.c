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

    do {
        printf("Entrer le nom : ");
        scanf("%39s", personne->nom);
        while (getchar() != '\n');
        if (!estValideNomPrenom(personne->nom)) {
            printf("Le nom doit contenir uniquement des lettres.\n");
            while (getchar() != '\n');
        }
    } while (!estValideNomPrenom(personne->nom));

    do {
        printf("Entrer le prenom : ");
        scanf("%39s", personne->prenom);
        while (getchar() != '\n');
        if (!estValideNomPrenom(personne->prenom)) {
            printf("Le prenom doit contenir uniquement des lettres.\n");
            while (getchar() != '\n');
        }
    } while (!estValideNomPrenom(personne->prenom));

    // Vérification des doublons pour nom/prénom
    while (estDoublonNomPrenom(liste, personne->nom, personne->prenom)) {
        printf("%s %s existe deja dans le repertoire.\n", personne->nom, personne->prenom);
        do {
            printf("Entrer un autre prenom : ");
            scanf("%39s", personne->prenom);
            while (getchar() != '\n');
        } while (!estValideNomPrenom(personne->prenom));
    }

    do {
        printf("Entrer le numero de telephone : ");
        scanf("%39s", personne->numero_telephone);
        if (!verifeNum(personne->numero_telephone)) {
            printf("Le numero de telephone doit contenir 10 chiffres.\n");
        }
    } while (!verifeNum(personne->numero_telephone));

    // Vérification des doublons pour le num de tél
    while (estDoublonNumTel(liste, personne->numero_telephone)) {
        printf("Le numero de telephone %s existe deja dans le repertoire.\n", personne->numero_telephone);
        do {
            printf("Entrer un autre numero de telephone : ");
            scanf("%39s", personne->numero_telephone);
        } while (!verifeNum(personne->numero_telephone));
    }

    do {
        printf("Entrer l'adresse mail : ");
        scanf("%39s", personne->adresse_mail);
        if (!verifMail(personne->adresse_mail)) {
            printf("L'adresse mail doit contenir un @ et un point.\n");
            while (getchar() != '\n');
        }
    } while (!verifMail(personne->adresse_mail));

    // Vérification des doublons pour le mail
    while (estDoublonMail(liste, personne->adresse_mail)) {
        printf("L'adresse mail %s existe deja dans le repertoire.\n", personne->adresse_mail);
        do {
            printf("Entrer une autre adresse mail : ");
            scanf("%39s", personne->adresse_mail);
            while (getchar() != '\n');
        } while (!verifMail(personne->adresse_mail));
    }

    node_t *node = malloc(sizeof(node_t));
    if (node == NULL) {
        printf("Erreur d'allocation de mémoire.\n");
        free(personne);
        return liste;
    }

    node->personne = personne;
    node->next = liste;
    node->prev = NULL;

    if (liste != NULL) {
        liste->prev = node;
    }

    printf("%s %s a bien ete ajoute(e) dans le repertoire !\n", personne->prenom, personne->nom);

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

node_t *trouver_personne(node_t *liste, const char *nom, const char *prenom) {
    node_t *current = liste;
    while (current != NULL) {
        if (strcasecmp(current->personne->nom, nom) == 0 &&
            (prenom == NULL || strcasecmp(current->personne->prenom, prenom) == 0)) {
            return current;
            }
        current = current->next;
    }
    return NULL;
}

void rechercher_personne(node_t *liste) {
    if (liste == NULL) {
        printf("\nLe repertoire est vide.\n");
        return;
    }

    char nom[40], prenom[40];
    printf("\nEntrer le nom que vous voulez chercher : ");
    scanf("%39s", nom);

    node_t *matching = trouver_personne(liste, nom, NULL);
    if (matching == NULL) {
        printf("\nIl n'existe pas de personne avec le nom %s dans le repertoire.\n", nom);
        return;
    }

    node_t *current = liste;
    int count = 0;
    while (current != NULL) {
        if (strcasecmp(current->personne->nom, nom) == 0) {
            count++;
        }
        current = current->next;
    }

    if (count == 1) {
        afficher_personne(matching->personne);
    } else {
        printf("Il existe plusieurs %s. Quel est son prenom ? : ", nom);
        scanf("%39s", prenom);

        matching = trouver_personne(liste, nom, prenom);
        if (matching != NULL) {
            afficher_personne(matching->personne);
        } else {
            printf("\nIl n'y a aucune personne avec le prenom %s et le nom %s dans votre repertoire.\n", prenom, nom);
        }
    }
}

node_t *supprimer_personne(node_t *liste) {
    if (liste == NULL) {
        printf("\nLe repertoire est vide.\n");
        return NULL;
    }

    char nom[40], prenom[40];
    printf("\nEntrez le nom de la personne que vous souhaitez supprimer : ");
    scanf("%39s", nom);

    node_t *matching = trouver_personne(liste, nom, NULL);
    if (matching == NULL) {
        printf("\n%s n'a pas ete trouve(e) dans votre repertoire.\n", nom);
        return liste;
    }

    node_t *current = liste;
    int count = 0;
    while (current != NULL) {
        if (strcasecmp(current->personne->nom, nom) == 0) {
            count++;
        }
        current = current->next;
    }

    if (count == 1) {
        if (matching->prev != NULL) {
            matching->prev->next = matching->next;
        } else {
            liste = matching->next;
        }
        if (matching->next != NULL) {
            matching->next->prev = matching->prev;
        }

        printf("\n%s %s a bien ete supprime(e).\n", matching->personne->prenom, matching->personne->nom);
        free(matching->personne);
        free(matching);
        return liste;
    } else {
        printf("Il existe plusieurs %s. Quel est son prenom ? : ", nom);
        scanf("%39s", prenom);

        matching = trouver_personne(liste, nom, prenom);
        if (matching != NULL) {
            if (matching->prev != NULL) {
                matching->prev->next = matching->next;
            } else {
                liste = matching->next;
            }
            if (matching->next != NULL) {
                matching->next->prev = matching->prev;
            }

            printf("\n%s %s a bien ete supprime(e).\n", matching->personne->prenom, matching->personne->nom);
            free(matching->personne);
            free(matching);
        } else {
            printf("\n%s %s n'a pas ete trouve(e) dans votre repertoire.\n", prenom, nom);
        }
    }

    return liste;
}

void afficher_personne(personne_t *personne) {
    printf("\tNom : %s\n", personne->nom);
    printf("\tPrenom : %s\n", personne->prenom);
    printf("\tNumero de telephone : %s\n", personne->numero_telephone);
    printf("\tAdresse mail : %s\n", personne->adresse_mail);
}