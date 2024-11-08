#include <stdbool.h>
#include <stdio.h>

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
                ajouter_personne();
            break;
            case 2:
                afficher_repertoire();
            break;
            case 3:
                afficher_personne();
            break;
            case 4:
                supprimer_personne();
            break;
        }
    }
    printf("Le programme est terminer");
}

struct node * ajouter_personne(struct node * liste) {
    //TODO
}

void afficher_repertoire(struct node * liste) {
    //TODO
}

void afficher_personne(struct node * liste) {
    //TODO
}

struct node * supprimer_personne(struct node * liste) {
    //TODO
}
