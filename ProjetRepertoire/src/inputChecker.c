#include "../include/repertoire.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


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

bool verifeNum(const char* str) {
    if (str==NULL) {
        return false;
    }
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
    else if (str[0]=='+' && str[1]=='3' && str[2]=='3') {
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
