#include "../include/repertoire.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/**
 * @brief Vérifie si une chaîne est un nom ou un prénom valide.
 *
 * Un nom/prénom valide doit contenir uniquement des lettres (aucun chiffre ou caractère spécial).
 *
 * @param str Chaîne à vérifier.
 * @return true si la chaîne est valide, false sinon.
 */
bool estValideNomPrenom(char* str){
	if (strlen(str)<=0){
		return false;
	}
	int i=0;
	while (str[i]!='\0'){
		if (str[i] =='0' || str[i] =='1' || str[i] =='2' || str[i] =='3' || str[i] =='4' || str[i] =='5' || str[i] =='6' || str[i] =='7' || str[i] =='8' || str[i] =='9'){
			return false;
		}
		i++;
	}
	return true;
}

/**
 * @brief Vérifie si un numéro de téléphone est valide.
 *
 * Un numéro valide doit :
 * - Commencer par '0' et contenir exactement 10 chiffres, ou
 * - Commencer par '+33' et contenir exactement 12 caractères (dont le préfixe).
 *
 * @param str Chaîne représentant le numéro de téléphone.
 * @return true si le numéro est valide, false sinon.
 */
bool verifNum(const char* str) {
    if (str==NULL) {
        return false;
    }

    // Format "0XXXXXXXXX"
    if (str[0]=='0') {
        if (strlen(str) != 10) {
            return false;
        }
        for (size_t i=0; i < strlen(str); i++) {
            if (!isdigit((unsigned char)str[i])) {
                return false;
            }
        }
        return true;
    }

    // Format "+33XXXXXXXX"
    if (str[0]=='+' && str[1]=='3' && str[2]=='3') {
        if (strlen(str) != 12) {
            return false;
        }
        for (size_t i=3; i < strlen(str); i++) {
            if (!isdigit((unsigned char)str[i])) {
                return false;
            }
        }
        return true;
    }

    return false;
}

/**
 * @brief Vérifie si une adresse e-mail est valide.
 *
 * Une adresse e-mail valide doit :
 * - Contenir un seul '@'.
 * - Contenir au moins un '.' après le '@'.
 * - Avoir des caractères valides avant et après '@' et '.'.
 *
 * @param str Chaîne représentant l'adresse e-mail.
 * @return true si l'adresse est valide, false sinon.
 */
bool verifMail(char* str) {
    int lft = 0;
    if (strlen(str) <= 0) {
        return false;
    }
    bool aro = false, point = false;
    int aroPos = -1;
    
    while (str[lft] != '\0') {
        if (str[lft] == '@') {
            if (!aro && lft > 0 && lft < strlen(str) - 1) {
                aro = true;
                aroPos = lft;
            } else {
                return false;
            }
        }
        if (aro && str[lft] == '.') {
            if (lft>aroPos+1 && lft < strlen(str)-1) {
                point = true;
            } else {
                return false;
            }
        }
        
        lft++;
    }
    return aro && point;
}

/**
 * @brief Vérifie si une combinaison nom/prénom existe déjà dans le répertoire.
 *
 * Parcourt la liste chaînée pour rechercher un doublon basé sur le nom et le prénom.
 *
 * @param liste Pointeur vers la tête de la liste.
 * @param nom Nom à vérifier.
 * @param prenom Prénom à vérifier.
 * @return true si un doublon est trouvé, false sinon.
 */
bool estDoublonNomPrenom(node_t *liste, const char *nom, const char *prenom) {
    node_t *current = liste;
    while (current != NULL) {
        if (strcasecmp(current->personne->nom, nom) == 0 &&
            strcasecmp(current->personne->prenom, prenom) == 0) {
            return true;
            }
        current = current->next;
    }
    return false;
}

/**
 * @brief Vérifie si un numéro de téléphone existe déjà dans le répertoire.
 *
 * Parcourt la liste chaînée pour rechercher un doublon basé sur le numéro de téléphone.
 *
 * @param liste Pointeur vers la tête de la liste.
 * @param numero Numéro de téléphone à vérifier.
 * @return true si un doublon est trouvé, false sinon.
 */
bool estDoublonNumTel(node_t *liste, const char *numero) {
    node_t *current = liste;
    while (current != NULL) {
        if (strcmp(current->personne->numero_telephone, numero) == 0) {
            return true;
        }
        current = current->next;
    }
    return false;
}


/**
 * @brief Vérifie si une adresse e-mail existe déjà dans le répertoire.
 *
 * Parcourt la liste chaînée pour rechercher un doublon basé sur l'adresse e-mail.
 *
 * @param liste Pointeur vers la tête de la liste.
 * @param mail Adresse e-mail à vérifier.
 * @return true si un doublon est trouvé, false sinon.
 */
bool estDoublonMail(node_t *liste, const char *mail) {
    node_t *current = liste;
    while (current != NULL) {
        if (strcasecmp(current->personne->adresse_mail, mail) == 0) {
            return true;
        }
        current = current->next;
    }
    return false;
}