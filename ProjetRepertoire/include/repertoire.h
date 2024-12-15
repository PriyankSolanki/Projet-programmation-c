#ifndef REPERTOIRE_H
#define REPERTOIRE_H

#include <stdbool.h>

/**
 * @brief Structure représentant une personne dans le répertoire.
 *
 * Cette structure contient les informations personnelles suivantes :
 * - Nom
 * - Prénom
 * - Numéro de téléphone
 * - Adresse e-mail
 */
typedef struct personne {
    char nom[40];                /**< Nom de la personne (max 39 caractères). */
    char prenom[40];             /**< Prénom de la personne (max 39 caractères). */
    char numero_telephone[40];   /**< Numéro de téléphone de la personne (max 39 caractères). */
    char adresse_mail[40];       /**< Adresse e-mail de la personne (max 39 caractères). */
} personne_t;

/**
 * @brief Structure représentant un nœud dans une liste doublement chaînée.
 *
 * Chaque nœud contient un pointeur vers une structure `personne` et des
 * pointeurs vers les nœuds précédent et suivant dans la liste.
 */
typedef struct node {
    personne_t *personne;        /**< Pointeur vers les informations de la personne. */
    struct node *next;           /**< Pointeur vers le nœud suivant. */
    struct node *prev;           /**< Pointeur vers le nœud précédent. */
} node_t;

// Fonctions du répertoire

/**
 * @brief Ajoute une personne au début du répertoire.
 *
 * Cette fonction permet d'ajouter une nouvelle personne à la liste chaînée
 * représentant le répertoire. Elle vérifie les doublons avant l'ajout.
 *
 * @param liste Pointeur vers la tête de la liste actuelle.
 * @return Pointeur vers la nouvelle tête de la liste.
 */
node_t *ajouter_personne(node_t *liste);

/**
 * @brief Affiche toutes les personnes du répertoire.
 *
 * Parcourt la liste chaînée et affiche les informations de chaque personne
 * présente dans le répertoire.
 *
 * @param liste Pointeur vers la tête de la liste actuelle.
 */
void afficher_repertoire(node_t *liste);

/**
 * @brief Recherche une personne dans le répertoire par nom (et prénom si nécessaire).
 *
 * Cette fonction permet de rechercher une personne dans le répertoire. Si plusieurs
 * personnes portent le même nom, un prénom sera demandé pour désambiguïser.
 *
 * @param liste Pointeur vers la tête de la liste actuelle.
 */
void rechercher_personne(node_t *liste);

/**
 * @brief Supprime une personne du répertoire.
 *
 * Supprime une personne de la liste chaînée en fonction de son nom (et prénom si nécessaire).
 * Libère la mémoire allouée pour cette personne et ajuste les pointeurs dans la liste.
 *
 * @param liste Pointeur vers la tête de la liste actuelle.
 * @return Pointeur vers la nouvelle tête de la liste après suppression.
 */
node_t *supprimer_personne(node_t *liste);

/**
 * @brief Affiche les informations d'une personne.
 *
 * Affiche les détails d'une personne, y compris son nom, prénom, numéro de téléphone,
 * et adresse e-mail.
 *
 * @param personne Pointeur vers la structure `personne_t` contenant les informations.
 */
void afficher_personne(personne_t *personne);

/**
 * @brief Trouve une personne dans le répertoire par nom et prénom.
 *
 * Parcourt la liste chaînée pour localiser une personne correspondant au nom
 * et, si fourni, au prénom. Si le prénom est NULL, la recherche se fait uniquement
 * par nom.
 *
 * @param liste Pointeur vers la tête de la liste actuelle.
 * @param nom Nom de la personne à rechercher.
 * @param prenom Prénom de la personne à rechercher (ou NULL pour ignorer).
 * @return Pointeur vers le nœud contenant la personne, ou NULL si non trouvée.
 */
node_t *trouver_personne(node_t *liste, const char *nom, const char *prenom);

/**
 * @brief Charge un répertoire à partir d'un fichier.
 *
 * Cette fonction charge un répertoire à partir d'un fichier de sauvegarde.
 * Le fichier doit être dans un format spécifique permettant de reconstruire
 * la liste chaînée des personnes.
 *
 * @param filename Nom du fichier contenant les données du répertoire.
 * @return Pointeur vers la tête de la liste contenant les personnes chargées.
 */
node_t* charger_repertoire(const char *filename);

/**
 * @brief Sauvegarde le répertoire dans un fichier.
 *
 * Cette fonction sauvegarde le répertoire (la liste chaînée des personnes)
 * dans un fichier afin de pouvoir le recharger plus tard.
 *
 * @param liste Pointeur vers la tête de la liste à sauvegarder.
 * @param filename Nom du fichier dans lequel sauvegarder les données du répertoire.
 */
void sauvegarder_repertoire(node_t *liste, const char *filename);
#endif // REPERTOIRE_H