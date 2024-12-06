#include "../include/repertoire.h"
#include <stdio.h>

int main() {
    int fonctionnalite;
    node_t *repertoire = NULL;

    printf("Bienvenue a toi !");
    while (true) {
        printf("\nGestion du repertoire :");
        printf("\n\t1. Ajouter une personne");
        printf("\n\t2. Afficher le repertoire");
        printf("\n\t3. Rechercher une personne");
        printf("\n\t4. Supprimer une personne");
        printf("\n\t5. Quitter\n");
        scanf("%d", &fonctionnalite);

        if (fonctionnalite == 5) break;

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
            default:
                printf("Option invalide.\n");
        }
    }

    printf("\nMerci de ta visite !\n");
    return 0;
}
