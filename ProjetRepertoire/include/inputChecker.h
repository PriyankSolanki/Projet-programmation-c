#ifndef INPUTCHECKER_H
#define INPUTCHECKER_H

#include <stdbool.h>

bool estValideNomPrenom(char* str);
bool verifeNum(char* str);
bool verifMail(char* str);
bool estDoublonNomPrenom(node_t *liste, const char *nom, const char *prenom);
bool estDoublonNumTel(node_t *liste, const char *numero);
bool estDoublonMail(node_t *liste, const char *mail);

#endif // INPUTCHECKER_H