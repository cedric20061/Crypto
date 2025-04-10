#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crypto.h"
#include "global.h"
#include <ctype.h>
#include <math.h>
#include "test.h"

// Vérifie la présence du caractère c dans la chaine de caractère str
int char_include(char *str, char c){
    for(int j = 0; str[j]!='\0'; j++){
        if(str[j] == c){
            return 1;
        }
    }
    return 0;
}

// Vérifie la présence de voyelles dans tous les mots de la phrase
int test_1(const char *str) { char voyelles[] = "AEIOUY";
    
    char *str_copy = strdup(str);
    if (!str_copy) return 0; 
    char *mot = strtok(str_copy, " ");
    while (mot != NULL) {
        int contient_voyelle = 0;
        for (int i = 0; mot[i] != '\0'; i++) {
            if (char_include(voyelles, mot[i])) {
                contient_voyelle = 1;
                break;
            }
        }

        if (!contient_voyelle) {
            free(str_copy); return 0;
        }

        mot = strtok(NULL, " ");
    }

    free(str_copy);  // Libérer la mémoire avant de retourner
    return 1;
}

// Vérifie la présence de plus de deux consonnes consécutifs
int test_2(char *str){
    char consonnes[] = "BCDFGHJKLMNPQRSTVWXZ";
    int count = 0;
    for (int i=0; str[i]!='\0'; i++){
        if(char_include(consonnes, str[i])){
            if(char_include(consonnes, str[i+1])){
                if(char_include(consonnes, str[i+2])){
                    return 0;
                }
            }
        }
    }
    return 1;
}

// Présence de digramme courant et de digramme rare LG XGWZ SWG EC OCTEJG FKGW CW EQPVTQNG
int test_3(char *str){
    char *frequent_digrammes[] = {
        "ES", "LE", "DE", "EN", "RE", "ON", "NT", "ER", "TE", "EL", 
        "AN", "SE", "ET", "OU", "AU", "ME", "EM", "AI", "EC", "NE", 
        "CH", "QU", "PE", "AP", "IN", "IT", "IS", "IE", "IL", "CE"
    };
    
    char *rares_digrammes[] = {
        "QG", "QJ", "QK", "QW", "QV", "QY", "XZ", "ZX", "KQ", "WX", 
        "JX", "VQ", "ZQ", "JZ", "WQ", "KZ", "XZ", "JQ", "VZ", "KX"
    };
    
    int freq_dig_count = 0;
    int rar_dig_count = 0;
    for (int i=0; i<30; i++){
        char *word = (frequent_digrammes)[i];
        char *pos = str;
        while ((pos = strstr(pos, word)) != NULL) {
            freq_dig_count++;
            pos++;
        }
    }
    for (int i=0; i<20; i++){
        char *word = rares_digrammes[i];
        char *pos = str;
        while ((pos = strstr(pos, word)) != NULL) {
            rar_dig_count++;
            pos++;
        }
    }
    if (freq_dig_count > rar_dig_count){
        return 1;
    } else if ((freq_dig_count == 0 && rar_dig_count == 0) || (freq_dig_count == rar_dig_count)){
        return 2;
    } else if (freq_dig_count < rar_dig_count){
        return 0;
    } else return 0;

}

int test_4(char *str) {
    float freq_francais[26] = {14.7, 8.1, 3.3, 3.6, 17.7, 1.1, 1.0, 1.1, 7.5, 0.3, 0.1, 5.5, 2.9, 7.1, 5.2, 2.9, 1.2, 6.5, 7.9, 7.2, 6.2, 1.8, 0.1, 0.3, 0.2, 0.1};
    int count[26] = {0};
    int total = 0;
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i])) {
            count[toupper(str[i]) - 'A']++;
            total++;
        }
    }
    
    if (total == 0) return 0; // Texte vide ou invalide
    
    float score = 0.0;
    for (int i = 0; i < 26; i++) {
        float freq_texte = (count[i] / (float)total) * 100;
        score += fabs(freq_texte - freq_francais[i]);
    }
    
    return (score < 20) ? 30 : (score < 40) ? 15 : 0;
}

int test_5(char *str) {
    char *mots_courants[] = {"LE", "LA", "LES", "DE", "DU", "UN", "UNE", "ET", "EST", "EN", "IL", "ELLE", "ON", "AVEC"};
    int count = 0;
    
    for (int i = 0; i < 14; i++) {
        if (strstr(str, mots_courants[i]) != NULL) {
            count++;
        }
    }
    
    if (count >= 3) return 40; // Texte très probable
    if (count >= 1) return 20; // Probable
    return 0; // Peu probable
}

int test_6(char *str) {
    char *mots_debut[] = {"LE", "LA", "UN", "UNE", "JE", "TU", "IL", "ELLE", "DE", "AVEC", "POUR", "DANS"};
    char str_copy[strlen(str) + 1];
    strcpy(str_copy, str);
    
    char *mot = strtok(str_copy, " ");
    if (!mot) return 0;

    for (int i = 0; i < 12; i++) {
        if (strcmp(mot, mots_debut[i]) == 0) {
            return 20; // Texte probable
        }
    }
    
    return 0; // Texte peu probable
}