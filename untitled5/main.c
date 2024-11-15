#include <stdbool.h>
#include <stdio.h>
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

    while(true) {

        node_t * repertoire = NULL;
        printf("Gestion du repertoire :\n");
        printf("\tAjouter une personne : 1\n");
        printf("\tAfficher le repertoire : 2\n");
        printf("\tRealiser une recherche par nom : 3\n");
        printf("\tSuprimmer une personne par nom : 4\n");
        printf("\tQuitter : 5\n");
        scanf("%d",&fonctionnalite);

        while(fonctionnalite<1 || fonctionnalite>5) {
            printf("Votre commande n'est pas valide \n");
            printf("Entrer un nouvelle commande :\n");
            printf("\tAjouter une personne : 1\n");
            printf("\tAfficher le repertoire : 2\n");
            printf("\tRealiser une recherche par nom : 3\n");
            printf("\tSuprimmer une personne par nom : 4\n");
            printf("\tQuitter : 5\n");
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
    printf("La gestion du repertoire est termine");
}

node_t * ajouter_personne(struct node * liste) {
    //TODO
}

void afficher_repertoire(node_t * liste) {
    if (liste == NULL) {
        printf("La liste est NULL");
    }
    int i = 1;
    node_t * current = liste;
    while (current->next != NULL) {
        afficher_personne(current->personne);
        current = current->next;
        i++;
    }
}

void rechercher_personne(node_t * liste) {
    if (liste == NULL) {
        printf("La liste est NULL");
    }
    printf("Entrer le nom que vous voulez chercher :");
    char nom[40];
    scanf("%s", &nom);
    int trouver = 0;
    node_t * current = liste;
    while (current->next !=NULL) {
        if(strcmp(current->personne->nom, nom) == 0) {
            afficher_personne(current->personne);
            trouver = 1;
        }
        current = current->next;
    }
    if(trouver==0) {
        printf("Il n'existe pas de personne avec le nom : %s dans le repertoire", nom);
    }
}

node_t * supprimer_personne(node_t * liste) {
    //TODO
}

void afficher_personne(personne_t * personne) {
    printf("\tnom : %s\n", personne->nom);
    printf("\tprenom : %s\n", personne->prenom);
    printf("\tnumero de telephone : %s\n", personne->numero_telephone);
    printf("\tadresse mail : %s\n", personne->adresse_mail);
    printf("\n");
}
