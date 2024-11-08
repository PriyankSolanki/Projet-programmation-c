#include <stdbool.h>
#include <stdio.h>
#include <string.h>

//objet personne
typedef struct personne {
    char nom[40];
    char prenom[40];
    char numero_telephone[40];
    char adresse_mail[40];
} personne_t;


//utilisation d'une chaine circulaire
typedef struct node {
    personne_t * personne;
    struct node * next;
    struct node * prev;
} node_t;


struct node * ajouter_personne(struct node * liste);
void afficher_repertoire(struct node * liste);
void afficher_personne(struct node * liste);
struct node * supprimer_personne(struct node * liste);


void main(){
    int fonctionnalite;

    while(true) {

        node_t * repertoire = NULL;
        printf("Que voulez vous faire :\n");
        printf("\tAjouter une personne : 1\n");
        printf("\tAfficher le repertoire : 2\n");
        printf("\tRealiser une recherche par nom : 3\n");
        printf("\tSuprimmer une personne par nom : 4\n");
        printf("\tQuitter : 5\n");
        scanf("%d",&fonctionnalite);

        while(fonctionnalite<1 || fonctionnalite>5) {
            printf("Votre demande n'est pas valid \n");
            printf("Entrer un nouvelle demande :\n");
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
                afficher_personne(repertoire);
            break;
            case 4:
                repertoire = supprimer_personne(repertoire);
            break;
        }
    }
    printf("Le programme est terminer");
}

struct node * ajouter_personne(struct node * liste) {
    //TODO
}

void afficher_repertoire(struct node * liste) {
    if (liste == NULL) {
        printf("La liste est NULL");
    }
    int i = 1;
    node_t * end = liste;
    node_t * current = liste;
    printf("Personne %d :", i);
    printf("\tnom = %s\n", current->personne->nom);
    printf("\tprenom = %s\n", current->personne->prenom);
    printf("\tnumero de telephone = %s\n", current->personne->numero_telephone);
    printf("\tadresse mail = %s\n", current->personne->adresse_mail);
    current = current->next;
    while (current != end) {
        i++;
        printf("Personne %d :", i);
        printf("\tnom = %s\n", current->personne->nom);
        printf("\tprenom = %s\n", current->personne->prenom);
        printf("\tnumero de telephone = %s\n", current->personne->numero_telephone);
        printf("\tadresse mail = %s\n", current->personne->adresse_mail);
    }
}

void afficher_personne(struct node * liste) {
    if (liste == NULL) {
        printf("La liste est NULL");
    }
    printf("Entrer le nom que vous voulez chercher :");
    char nom[40];
    scanf("%s", &nom);
    int trouver = 0;
    node_t * end = liste;
    node_t * current = liste;

    if(strcmp(current->personne->nom, nom) == 0) {
        printf("\tnom = %s\n", current->personne->nom);
        printf("\tprenom = %s\n", current->personne->prenom);
        printf("\tnumero de telephone = %s\n", current->personne->numero_telephone);
        printf("\tadresse mail = %s\n", current->personne->adresse_mail);
    }
    current = current->next;
    while (current != end) {
        if(strcmp(current->personne->nom, nom) == 0) {
            printf("\tnom = %s\n", current->personne->nom);
            printf("\tprenom = %s\n", current->personne->prenom);
            printf("\tnumero de telephone = %s\n", current->personne->numero_telephone);
            printf("\tadresse mail = %s\n", current->personne->adresse_mail);
            trouver = 1;
        }
        current = current->next;
    }
    if(trouver==0) {
        printf("Il n'existe pas de %s dans le repertoire", nom);
    }
}

struct node * supprimer_personne(struct node * liste) {
    //TODO
}
