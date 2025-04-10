#ifndef GLOBAL_H
#define GLOBAL_H

#define MAX_CHAR_LENGTH 50

// Affiche le menu avec un tableau de chaînes et vérifie que le choix est valide
int displayMenu(char *menu[], int count);
// Récupère de facon sécurisé une chaine de caractère
int getSafeInt(char *prompt);
// Convertie une chaine en majuscule
void toUpperCase(char *str);
// Convertie une chaine en miniscule
void toLowerCase(char *str);
// Trie les éléments d'un tableau d'entier
void sort(int tab[], int n);
#endif
