#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crypto.h"
#include "global.h"
//Commande de compilation: gcc -Iinclude utils/crypto.c utils/global.c main.c -o  output/crypto_v1

int main() {
    char *mainMenuOptions[] = {
        "Cryptage par decalge",
        "Cryptage par cles mot",
        "Cryptage parfait",
        "Cryptage par paire"

    };
    int menuCount = 4;
    char str[MAX_MESSAGE_SIZE];
    printf("--------Methode de cryptage--------\n");
    int meth = displayMenu(mainMenuOptions, menuCount);
    int choice;
    if(meth == 1  || meth == 2 || meth == 4){
        printf("Entrez le message: ");
        fgets(str, MAX_MESSAGE_SIZE, stdin);
        str[strlen(str) - 1] = '\0';
        printf("Voulez vous: \n");
        printf("1. Chiffrer ce message\n");
        printf("2. Dechiffrer ce message\n");
        choice = getSafeInt("Choix: ");
    }
    switch (meth)
    {
        case 1:
            int key = getSafeInt("Entrez la cle de cryptage: ");
            if(choice == 1){
                crypto_v1(str, key);
                printf("Resultat: %s\n", str);
            } else if(choice == 2){
                if(key!=0){
                    decrypto_v1(str, key);
                printf("Resultat: %s\n", str);

                }else{
                    bruteForce(str,1);
                }
            }
            break;
        
        case 2:
            printf("Connaissez-vous la cle ? \n1) Oui\n2) Non\n");
            int choix;
            scanf("%d", &choix);
            getchar();  // Évite les problèmes de buffer
            
            if (choix == 1) {
                char key_word[100];
                printf("Entrez la cle : ");
                scanf("%99s", key_word);
                getchar();
            
                if (!isValidKey(key_word)) {
                    printf("\nCle de cryptage invalide\n");
                    return 0;
                }
            
                if (choice == 1) {
                    crypto_v2(str, key_word);
                } else if (choice == 2) {
                    decrypto_v2(str, key_word);
                }

                printf("Resultat : %s\n", str);
            } else {
                int sizeofKey;
                printf("Entrez la taille de la cle : ");
                scanf("%d", &sizeofKey);
                getchar();

                char **bestKeys = guessTheKey(str, sizeofKey);  // Suppose qu'on retourne 3 clés

                printf("Les trois cles les plus probables sont :\n");
                for (int i = 0; i < 3; i++) {
                    printf("Cle %d : %s\n", i + 1, bestKeys[i]);
                    free(bestKeys[i]);  // Libérer la mémoire allouée
                }
                free(bestKeys);
            }
        
            break;

        case 3:
            printf("----------Conversation----------\n");
            int perso = 1;
            int pos =0;
            while(1){
                char message[MAX_MESSAGE_SIZE];
                printf("Individu %d: ", perso);
                fgets(message, MAX_MESSAGE_SIZE, stdin);
                message[strlen(message)-1] = '\0';
                crypto_v3(message, pos);
                printf("Message cryptee: %s\n", message);
                pos +=strlen(message);
                perso = perso==1?2:1;
            }
        case 4:
            char key_word[100];
            printf("Entrez la cle: ");
            scanf("%99s", key_word);
            getchar();
            crypto_v4(str, key_word);
            printf("Resultats: %s", str);
            break;
        default:
            break;
    }
    

    return 0;
}