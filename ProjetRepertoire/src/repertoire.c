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
        printf("\nLe repertoires est vide.\n");
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

void sauvegarder_repertoire(node_t *liste, const char *filename) {
    FILE *fichier = fopen(filename, "w");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    node_t *current = liste;
    while (current != NULL) {
        fprintf(fichier, "%s;%s;%s;%s\n", current->personne->nom, current->personne->prenom,
                current->personne->numero_telephone, current->personne->adresse_mail);
        current = current->next;
    }

    fclose(fichier);
}

node_t* charger_repertoire(const char *filename) {
    FILE *fichier = fopen(filename, "r");
    if (fichier == NULL) {
        printf("Fichier '%s' introuvable. Création d'un nouveau répertoire.\n", filename);
        // Tente de créer un fichier vide
        fichier = fopen(filename, "w");
        if (fichier == NULL) {
            printf("Erreur : impossible de créer le fichier '%s'. Vérifiez les permissions.\n", filename);
            return NULL;
        }
        fclose(fichier);
        return NULL; // Retourne un répertoire vide
    }

    node_t *repertoire = NULL;
    node_t *dernier = NULL;
    char ligne[200];

    while (fgets(ligne, sizeof(ligne), fichier)) {
        personne_t *nouvelle_personne = malloc(sizeof(personne_t));
        if (sscanf(ligne, "%39[^;];%39[^;];%39[^;];%39[^\n]", nouvelle_personne->nom, nouvelle_personne->prenom,
                   nouvelle_personne->numero_telephone, nouvelle_personne->adresse_mail) == 4) {
            node_t *nouveau_noeud = malloc(sizeof(node_t));
            if (nouveau_noeud == NULL) {
                printf("Erreur d'allocation de mémoire.\n");
                free(nouvelle_personne);
                fclose(fichier);
                return repertoire;
            }

            nouveau_noeud->personne = nouvelle_personne;
            nouveau_noeud->next = NULL;
            nouveau_noeud->prev = dernier;

            if (dernier != NULL) {
                dernier->next = nouveau_noeud;
            } else {
                repertoire = nouveau_noeud;
            }

            dernier = nouveau_noeud;
                   }
    }

    fclose(fichier);
    return repertoire;
}
