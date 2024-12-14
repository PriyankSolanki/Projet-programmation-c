/**
* @file repertoire.c
 * @brief Implémentation des fonctions de gestion du répertoire de contacts.
 *
 * Ce fichier contient les fonctions pour ajouter, afficher, rechercher et supprimer des contacts
 * dans un répertoire implémenté sous forme de liste doublement chaînée.
 */

#include "../include/repertoire.h"

#include <ctype.h>

#include "inputChecker.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void vider_tampon() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Ajoute une personne au répertoire.
 *
 * Cette fonction demande à l'utilisateur de saisir les informations d'une personne (nom, prénom,
 * numéro de téléphone, adresse mail) et vérifie qu'elles sont valides et uniques avant de l'ajouter
 * au début de la liste chaînée.
 *
 * @param liste Pointeur vers la tête de la liste des contacts.
 * @return node_t* Pointeur vers la nouvelle tête de la liste après ajout.
 */
node_t *ajouter_personne(node_t *liste) {
    personne_t *personne = malloc(sizeof(personne_t));
    if (personne == NULL) {
        printf("Erreur d'allocation de memoire.\n");
        return liste;
    }

    do {
        printf("Entrer le nom : ");
        fgets(personne->nom, sizeof(personne->nom), stdin);
        personne->nom[strcspn(personne->nom, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

        if (!estValideNomPrenom(personne->nom)) {
            printf("Le nom doit contenir uniquement des lettres, des tirets ou des espaces.\n");
        }
    } while (!estValideNomPrenom(personne->nom));

    do {
        printf("Entrer le prenom : ");
        fgets(personne->prenom, sizeof(personne->prenom), stdin);
        personne->prenom[strcspn(personne->prenom, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

        if (!estValideNomPrenom(personne->prenom)) {
            printf("Le prenom doit contenir uniquement des lettres, des tirets ou des espaces.\n");
        }
    } while (!estValideNomPrenom(personne->prenom));

    // Vérification des doublons pour nom/prénom
    while (estDoublonNomPrenom(liste, personne->nom, personne->prenom)) {
        printf("%s %s existe deja dans le repertoire.\n", personne->nom, personne->prenom);
        do {
            printf("Entrer un autre prenom : ");
            scanf("%39s", personne->prenom);
            vider_tampon();
        } while (!estValideNomPrenom(personne->prenom));
    }

    do {
        printf("Entrer le numero de telephone : ");
        scanf("%39s", personne->numero_telephone);
        vider_tampon();
        if (!verifNum(personne->numero_telephone)) {
            printf("Le numero de telephone doit contenir 10 chiffres.\n");
        }
    } while (!verifNum(personne->numero_telephone));

    // Vérification des doublons pour le num de tél
    while (estDoublonNumTel(liste, personne->numero_telephone)) {
        printf("Le numero de telephone %s existe deja dans le repertoire.\n", personne->numero_telephone);
        do {
            printf("Entrer un autre numero de telephone : ");
            scanf("%39s", personne->numero_telephone);
            vider_tampon();
        } while (!verifNum(personne->numero_telephone));
    }

    do {
        printf("Entrer l'adresse mail : ");
        scanf("%39s", personne->adresse_mail);
        vider_tampon();
        if (!verifMail(personne->adresse_mail)) {
            printf("L'adresse mail doit contenir un @ et un point.\n");
        }
    } while (!verifMail(personne->adresse_mail));

    // Vérification des doublons pour le mail
    while (estDoublonMail(liste, personne->adresse_mail)) {
        printf("L'adresse mail %s existe deja dans le repertoire.\n", personne->adresse_mail);
        do {
            printf("Entrer une autre adresse mail : ");
            scanf("%39s", personne->adresse_mail);
            vider_tampon();
        } while (!verifMail(personne->adresse_mail));
    }

    // Création et insertion du nouveau noeud
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

    printf("%s %s a bien ete ajoute(e) dans le repertoire !\n", personne->prenom, personne->nom);

    return node;
}

/**
 * @brief Affiche tous les contacts du répertoire.
 *
 * Cette fonction parcourt la liste chaînée et affiche les informations de chaque contact.
 *
 * @param liste Pointeur vers la tête de la liste des contacts.
 */
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

/**
 * @brief Recherche une personne dans le répertoire.
 *
 * Cette fonction parcourt la liste chaînée des contacts et cherche une personne en fonction du nom
 * et, si fourni, du prénom. Elle compare les noms de manière insensible à la casse. Si un prénom est
 * spécifié, il est également comparé de manière insensible à la casse. Si la personne est trouvée,
 * la fonction retourne le pointeur vers le noeud correspondant. Sinon, elle retourne NULL.
 *
 * @param liste Pointeur vers la tête de la liste des contacts.
 * @param nom Le nom de la personne à rechercher.
 * @param prenom Le prénom de la personne à rechercher (peut être NULL si non utilisé).
 * @return node_t* Pointeur vers le noeud contenant la personne recherchée, ou NULL si non trouvée.
 */
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

/**
 * @brief Recherche une personne dans le répertoire.
 *
 * Cette fonction cherche un contact par nom et éventuellement par prénom.
 * Elle accepte les noms avec des espaces, des tirets et des caractères spéciaux valides.
 *
 * @param liste Pointeur vers la tête de la liste des contacts.
 */
void rechercher_personne(node_t *liste) {
    if (liste == NULL) {
        printf("\nLe repertoire est vide.\n");
        return;
    }

    char nom[40], prenom[40];
    printf("\nEntrez le nom que vous voulez chercher : ");
    fgets(nom, sizeof(nom), stdin);
    nom[strcspn(nom, "\n")] = '\0';

    node_t *matching = trouver_personne(liste, nom, NULL);
    if (matching == NULL) {
        printf("\n%s n'a ete trouve(e) dans le repertoire.\n", nom);
        return;
    }

    int count = 0;
    node_t *current = liste;
    while (current != NULL) {
        if (strcasecmp(current->personne->nom, nom) == 0) {
            count++;
        }
        current = current->next;
    }

    if (count == 1) {
        printf("\nContact trouve :\n");
        afficher_personne(matching->personne);
    } else {
        printf("Il existe plusieurs personnes avec le nom %s. Quel est son prenom ? : ", nom);
        fgets(prenom, sizeof(prenom), stdin);
        prenom[strcspn(prenom, "\n")] = '\0';

        matching = trouver_personne(liste, nom, prenom);
        if (matching != NULL) {
            printf("\nContact trouve :\n");
            afficher_personne(matching->personne);
        } else {
            printf("\nAucun contact avec le nom '%s' et le prenom '%s' n'a ete trouve.\n", nom, prenom);
        }
    }
}

/**
 * @brief Supprime une personne du répertoire.
 *
 * Cette fonction supprime un contact par nom et éventuellement par prénom si plusieurs contacts
 * partagent le même nom. Elle accepte les noms avec des espaces, des tirets et des caractères spéciaux valides.
 *
 * @param liste Pointeur vers la tête de la liste des contacts.
 * @return node_t* Pointeur vers la nouvelle tête de la liste après suppression.
 */
node_t *supprimer_personne(node_t *liste) {
    if (liste == NULL) {
        printf("\nLe repertoire est vide.\n");
        return NULL;
    }

    char nom[40], prenom[40];
    printf("\nEntrez le nom de la personne que vous souhaitez supprimer : ");
    fgets(nom, sizeof(nom), stdin);
    nom[strcspn(nom, "\n")] = '\0';

    node_t *matching = trouver_personne(liste, nom, NULL);
    if (matching == NULL) {
        printf("\n%s n'a pas ete trouve(e) dans votre repertoire.\n", nom);
        return liste;
    }

    int count = 0;
    node_t *current = liste;
    while (current != NULL) {
        if (strcasecmp(current->personne->nom, nom) == 0) {
            count++;
        }
        current = current->next;
    }

    if (count > 1) {
        printf("Il existe plusieurs personnes avec le nom '%s'. Quel est son prenom ? : ", nom);
        fgets(prenom, sizeof(prenom), stdin);
        prenom[strcspn(prenom, "\n")] = '\0';

        matching = trouver_personne(liste, nom, prenom);
        if (matching == NULL) {
            printf("\n%s %s n'a pas ete trouve(e) dans votre repertoire.\n", prenom, nom);
            return liste;
        }
    } else {
        strncpy(prenom, matching->personne->prenom, sizeof(prenom) - 1);
        prenom[sizeof(prenom) - 1] = '\0';
    }

    char confirmation;
    printf("\nVoulez-vous vraiment supprimer %s %s ? (o/n) : ", prenom, nom);
    scanf(" %c", &confirmation);
    vider_tampon();
    if (tolower(confirmation) != 'o') {
        printf("Suppression annulee.\n");
        return liste;
    }

    if (matching->prev != NULL) {
        matching->prev->next = matching->next;
    } else {
        liste = matching->next;
    }
    if (matching->next != NULL) {
        matching->next->prev = matching->prev;
    }

    printf("\n%s %s a bien ete supprime(e).\n", prenom, nom);
    free(matching->personne);
    free(matching);

    return liste;
}

/**
 * @brief Affiche les informations d'une personne.
 *
 * @param personne Pointeur vers la structure contenant les informations de la personne.
 */
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
        fprintf(fichier, "%s;%s;%s;%s\n",
                current->personne->nom,
                current->personne->prenom,
                current->personne->numero_telephone,
                current->personne->adresse_mail);
        current = current->next;
    }

    fclose(fichier);
}


node_t* charger_repertoire(const char *filename) {
    FILE *fichier = fopen(filename, "r");
    if (fichier == NULL) {
        printf("Fichier '%s' introuvable. Creation d'un nouveau repertoire.\n", filename);
        fichier = fopen(filename, "w, ccs=UTF-8");
        if (fichier == NULL) {
            printf("Impossible de creer le fichier '%s'.", filename);
            return NULL;
        }
        fclose(fichier);
        return NULL;
    }

    node_t *repertoire = NULL;
    node_t *dernier = NULL;
    char ligne[200];

    while (fgets(ligne, sizeof(ligne), fichier)) {
        ligne[strcspn(ligne, "\n")] = '\0';

        char *nom = strtok(ligne, ";");
        char *prenom = strtok(NULL, ";");
        char *numero_telephone = strtok(NULL, ";");
        char *adresse_mail = strtok(NULL, ";");

        if (nom && prenom && numero_telephone && adresse_mail) {
            personne_t *nouvelle_personne = malloc(sizeof(personne_t));
            if (nouvelle_personne == NULL) {
                printf("Erreur d'allocation de memoire.\n");
                fclose(fichier);
                return repertoire;
            }

            strncpy(nouvelle_personne->nom, nom, sizeof(nouvelle_personne->nom) - 1);
            nouvelle_personne->nom[sizeof(nouvelle_personne->nom) - 1] = '\0';

            strncpy(nouvelle_personne->prenom, prenom, sizeof(nouvelle_personne->prenom) - 1);
            nouvelle_personne->prenom[sizeof(nouvelle_personne->prenom) - 1] = '\0';

            strncpy(nouvelle_personne->numero_telephone, numero_telephone, sizeof(nouvelle_personne->numero_telephone) - 1);
            nouvelle_personne->numero_telephone[sizeof(nouvelle_personne->numero_telephone) - 1] = '\0';

            strncpy(nouvelle_personne->adresse_mail, adresse_mail, sizeof(nouvelle_personne->adresse_mail) - 1);
            nouvelle_personne->adresse_mail[sizeof(nouvelle_personne->adresse_mail) - 1] = '\0';

            node_t *nouveau_noeud = malloc(sizeof(node_t));
            if (nouveau_noeud == NULL) {
                printf("Erreur d'allocation de memoire.\n");
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
        } else {
            printf("Ligne invalide dans le fichier : %s\n", ligne);
        }
    }

    fclose(fichier);
    return repertoire;
}