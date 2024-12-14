#ifndef INPUTCHECKER_H
#define INPUTCHECKER_H

#include <stdbool.h>

/**
 * @brief Vérifie si une chaîne de caractères est un nom ou un prénom valide.
 *
 * Un nom ou un prénom est considéré valide s'il ne contient que des lettres.
 *
 * @param str La chaîne de caractères à vérifier.
 * @return true si la chaîne est valide, false sinon.
 */
bool estValideNomPrenom(char* str);

/**
 * @brief Vérifie si une chaîne de caractères est un numéro de téléphone valide.
 *
 * Un numéro de téléphone est considéré valide s'il contient exactement 10 chiffres.
 *
 * @param str La chaîne de caractères à vérifier.
 * @return true si le numéro est valide, false sinon.
 */
bool verifNum(char* str);

/**
 * @brief Vérifie si une chaîne de caractères est une adresse e-mail valide.
 *
 * Une adresse e-mail est considérée valide si elle contient un '@' et un '.'.
 *
 * @param str La chaîne de caractères à vérifier.
 * @return true si l'adresse e-mail est valide, false sinon.
 */
bool verifMail(char* str);

/**
 * @brief Vérifie si une combinaison nom/prénom existe déjà dans la liste.
 *
 * Parcourt la liste des personnes pour voir si une personne avec le même nom
 * et prénom existe déjà.
 *
 * @param liste La liste des personnes (liste chaînée).
 * @param nom Le nom à vérifier.
 * @param prenom Le prénom à vérifier.
 * @return true si un doublon est trouvé, false sinon.
 */
bool estDoublonNomPrenom(node_t *liste, const char *nom, const char *prenom);

/**
 * @brief Vérifie si un numéro de téléphone existe déjà dans la liste.
 *
 * Parcourt la liste des personnes pour voir si un numéro de téléphone identique
 * existe déjà.
 *
 * @param liste La liste des personnes (liste chaînée).
 * @param numero Le numéro de téléphone à vérifier.
 * @return true si un doublon est trouvé, false sinon.
 */
bool estDoublonNumTel(node_t *liste, const char *numero);

/**
 * @brief Vérifie si une adresse e-mail existe déjà dans la liste.
 *
 * Parcourt la liste des personnes pour voir si une adresse e-mail identique
 * existe déjà.
 *
 * @param liste La liste des personnes (liste chaînée).
 * @param mail L'adresse e-mail à vérifier.
 * @return true si un doublon est trouvé, false sinon.
 */
bool estDoublonMail(node_t *liste, const char *mail);

#endif // INPUTCHECKER_H