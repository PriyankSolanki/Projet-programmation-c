#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//objet personne
typedef struct personne {
    char nom[40]; // doit etre unique
    char prenom[40];
    char numero_telephone[40];
    char adresse_mail[40];
} personne_t;


//utilisation d'une chaine doublement chainee
typedef struct node {
    personne_t * personne;
    struct node * next;
    struct node * prev;
} node_t;


struct node * ajouter_personne(node_t * liste); //Ajouter une personne au repertoire
void afficher_repertoire(node_t * liste); //Afficher le repertoire
void rechercher_personne(node_t * liste); //Rechercher une personne avec son nom
struct node * supprimer_personne(node_t * liste); //Supprimer une personne du repertoire avec son nom
void afficher_personne(personne_t * personne); //Afficher les attributs d'une personne


void main(){
    int fonctionnalite;
    node_t * repertoire = NULL;
    while(true) {
        printf("\nGestion du repertoire :");
        printf("\n\tAjouter une personne : 1");
        printf("\n\tAfficher le repertoire : 2");
        printf("\n\tRealiser une recherche par nom : 3");
        printf("\n\tSuprimmer une personne par nom : 4");
        printf("\n\tQuitter : 5\n");
        scanf("%d",&fonctionnalite);

        while(fonctionnalite<1 || fonctionnalite>5) {
            printf("\nVotre commande n'est pas valide");
            printf("\nEntrer un nouvelle commande :");
            printf("\n\tAjouter une personne : 1");
            printf("\n\tAfficher le repertoire : 2");
            printf("\n\tRealiser une recherche par nom : 3");
            printf("\n\tSuprimmer une personne par nom : 4");
            printf("\n\tQuitter : 5");
            scanf("%d",&fonctionnalite);
        }
        if(fonctionnalite==5) {
            break;
        }
        switch(fonctionnalite) {
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
    printf("\nLa gestion du repertoire est termine");
}

node_t * ajouter_personne(node_t * liste) {
    personne_t * personne = malloc(sizeof(personne_t));
    if(personne==NULL) {
        printf("\nErreur d'allocation de memoire");
        return NULL;
    }

    printf("\nEntrer le nom (40 caracteres max) :");
    scanf("%s", personne->nom);
    printf("\nEntrer le prenom (40 caracteres max) :");
    scanf("%s", personne->prenom);
    printf("\nEntrer le numero de telephone (40 caracteres max) :");
    scanf("%s", personne->numero_telephone);
    printf("\nEntrer l'adresse mail (40 caracteres max) :");
    scanf("%s", personne->adresse_mail);
    node_t * node = (node_t *) malloc(sizeof(node_t));
    node->personne = personne;
    if (liste == NULL) {
        node->next = NULL;
        node->prev = NULL;
        return node;
    }else {
        liste->prev = node;
        node->next = liste;
        return node;
    }
}

void afficher_repertoire(node_t * liste) {
    if (liste == NULL) {
        printf("\nLe repertoire est vide");
        return;
    }
    int i = 1;
    node_t * current = liste;
    printf("Personne %d", i);
    afficher_personne(current->personne);
    while (current->next != NULL) {
        i++;
        printf("Personne %d", i);
        afficher_personne(current->personne);
        current = current->next;
    }
}

void rechercher_personne(node_t * liste) {
    if (liste == NULL) {
        printf("\nLe repertoire est vide");
        return;
    }
    printf("\nEntrer le nom que vous voulez chercher :");
    char nom[40];
    scanf("%s", &nom);
    node_t * current = liste;
    if(strcmp(current->personne->nom, nom) == 0) {
        afficher_personne(current->personne);
        return;
    }
    while (current->next !=NULL) {
        if(strcmp(current->personne->nom, nom) == 0) {
            afficher_personne(current->personne);
            return;
        }
        current = current->next;
    }
    printf("\nIl n'existe pas de personne avec le nom : %s dans le repertoire", nom);
}

node_t * supprimer_personne(node_t * liste) {
    //TODO
}

void afficher_personne(personne_t * personne) {
    printf("\n\tnom : %s\n", personne->nom);
    printf("\tprenom : %s\n", personne->prenom);
    printf("\tnumero de telephone : %s\n", personne->numero_telephone);
    printf("\tadresse mail : %s\n", personne->adresse_mail);
}
