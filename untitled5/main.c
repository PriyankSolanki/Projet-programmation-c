#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//objet personne
typedef struct personne {
    char nom[40]; // doit être unique
    char prenom[40];
    char numero_telephone[40];
    char adresse_mail[40];
} personne_t;

// Utilisation d'une chaîne doublement chaînée
typedef struct node {
    personne_t *personne;
    struct node *next;
    struct node *prev;
} node_t;

node_t *ajouter_personne(node_t *liste); //Ajouter une personne au répertoire
void afficher_repertoire(node_t *liste); //Afficher le répertoire
void rechercher_personne(node_t *liste); //Rechercher une personne avec son nom
node_t *supprimer_personne(node_t *liste); //Supprimer une personne du répertoire avec son nom
void afficher_personne(personne_t *personne); //Afficher les attributs d'une personne

int main() {
    int fonctionnalite;
    node_t *repertoire = NULL;
    while (true) {
        printf("\nGestion du repertoire :");
        printf("\n\tAjouter une personne : 1");
        printf("\n\tAfficher le repertoire : 2");
        printf("\n\tRealiser une recherche par nom : 3");
        printf("\n\tSupprimer une personne par nom : 4");
        printf("\n\tQuitter : 5\n");
        scanf("%d", &fonctionnalite);

        while (fonctionnalite < 1 || fonctionnalite > 5) {
            printf("\nVotre commande n'est pas valide");
            printf("\nEntrer une nouvelle commande :");
            printf("\n\tAjouter une personne : 1");
            printf("\n\tAfficher le repertoire : 2");
            printf("\n\tRealiser une recherche par nom : 3");
            printf("\n\tSupprimer une personne par nom : 4");
            printf("\n\tQuitter : 5\n");
            scanf("%d", &fonctionnalite);

            // faire vérification d'entrée
        }
        if (fonctionnalite == 5) {
            break;
        }
        switch (fonctionnalite) {
            case 1:
                repertoire = ajouter_personne(repertoire);
                break;
            case 2:
                afficher_repertoire(repertoire);
                break;
            case 3:
                rechercher_personne(repertoire);
                break;
            case 4:
                repertoire = supprimer_personne(repertoire);
                break;
        }
    }
    printf("\nMerci de votre visite !\n");
    return 0;
}

// Faire les vérifications d'entrées (string, numéro de tel, mail @)

node_t *ajouter_personne(node_t *liste) {
    personne_t *personne = malloc(sizeof(personne_t));
    if (personne == NULL) {
        printf("\nErreur d'allocation de memoire\n");
        return liste;
    }

    printf("\nEntrer le nom (40 caracteres max) : ");
    scanf("%39s", personne->nom);
    printf("Entrer le prenom (40 caracteres max) : ");
    scanf("%39s", personne->prenom);

    // Vérification des doublons
    node_t *current = liste;
    while (current != NULL) {
        if (strcmp(current->personne->nom, personne->nom) == 0) {
            printf("\n%s existe daja dans le repertoire.\n", personne->nom);
            free(personne);
            return liste;
        }
        current = current->next;
    }

    printf("Entrer le numero de telephone (40 caracteres max) : ");
    scanf("%39s", personne->numero_telephone);
    printf("Entrer l'adresse mail (40 caracteres max) : ");
    scanf("%39s", personne->adresse_mail);

    node_t *node = malloc(sizeof(node_t));
    if (node == NULL) {
        printf("\nErreur d'allocation de memoire\n");
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
        printf("\nLe repertoire est vide\n");
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

// faire une recherche sans regarder les maj
void rechercher_personne(node_t *liste) {
    if (liste == NULL) {
        printf("\nLe repertoire est vide\n");
        return;
    }

    char nom[40];
    printf("\nEntrer le nom que vous voulez chercher : ");
    scanf("%39s", nom);

    node_t *current = liste;
    while (current != NULL) {
        if (strcmp(current->personne->nom, nom) == 0) {
            afficher_personne(current->personne);
            return;
        }
        current = current->next;
    }

    printf("\nIl n'existe pas de personne avec le nom : %s dans le repertoire\n", nom);
}

// supprimer une personne en demandant son prénom si y'a deux fois le meme nom
node_t *supprimer_personne(node_t *liste) {
    if (liste == NULL) {
        printf("\nLe repertoire est vide\n");
        return NULL;
    }

    char nom[40];
    printf("\nEntrez le nom de la personne que vous souhaitez supprimer : ");
    scanf("%39s", nom);

    node_t *current = liste;
    while (current != NULL) {
        if (strcmp(current->personne->nom, nom) == 0) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                liste = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }

            free(current->personne);
            free(current);
            printf("\n%s a bien ete supprimee.\n", nom);
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
