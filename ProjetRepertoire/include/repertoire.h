#ifndef REPERTOIRE_H
#define REPERTOIRE_H

#include <stdbool.h>

// Objet personne
typedef struct personne {
    char nom[40];
    char prenom[40];
    char numero_telephone[40];
    char adresse_mail[40];
} personne_t;

// Chaîne doublement chaînée
typedef struct node {
    personne_t *personne;
    struct node *next;
    struct node *prev;
} node_t;

// Fonctions du répertoire
/**
 * @brief Ajoute une personne au répertoire.
 * @param liste Pointeur vers la liste actuelle.
 * @return Pointeur vers la nouvelle liste.
 */
node_t *ajouter_personne(node_t *liste);

/**
 * @brief Affiche toutes les personnes du répertoire.
 * @param liste Pointeur vers la liste actuelle.
 */
void afficher_repertoire(node_t *liste);

/**
 * @brief Recherche une personne dans le répertoire par nom.
 * @param liste Pointeur vers la liste actuelle.
 */
void rechercher_personne(node_t *liste);

/**
 * @brief Supprime une personne du répertoire par nom.
 * @param liste Pointeur vers la liste actuelle.
 * @return Pointeur vers la nouvelle liste.
 */
node_t *supprimer_personne(node_t *liste);

/**
 * @brief Affiche les détails d'une personne.
 * @param personne Pointeur vers une personne.
 */
void afficher_personne(personne_t *personne);

node_t *trouver_personne(node_t *liste, const char *nom, const char *prenom);

#endif // REPERTOIRE_H
