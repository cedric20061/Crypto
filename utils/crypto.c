#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crypto.h"
#include "global.h"
#include <ctype.h>
#include <math.h>
#include "test.h"

#define SIZE 25
typedef struct {
    int x;
    int y;
} Couple;

/**
 * getCorrespondChar - Calculates the corresponding character after a shift.
 * 
 * @c: Input character (must be an uppercase letter).
 * @a: Shift value to apply.
 * @op: Operation to perform (1 for positive shift, other values for negative shift).
 * 
 * Returns:
 * - The shifted character if c is an uppercase letter.
 * - The unchanged character otherwise.
 */
char getCorrespondChar(char c, int a, int op) {
    if ((c >= 'A' && c <= 'Z')) {
        return op == 1 
            ? (c + a - 'A') % 26 + 'A' 
            : ((c - a - 'A') % 26 >= 0 
                ? (c - a - 'A') % 26 + 'A' 
                : (c - a - 'A') % 26 + 26 + 'A');
    } else {
        return c;
    }
}

/**
 * crypto_v1: Caesar cipher encryption algorithm.
 * 
 * @str: String to encrypt.
 * @key: Integer shift key.
 * 
 * Returns: Encrypted string and modifies the input string.
 */
char* crypto_v1(char *str, int key){
    toUpperCase(str);
    for (int i =0; i<strlen(str); i++){
        if((str[i]>='A' && str[i]<= 'Z')){
            str[i] = getCorrespondChar(str[i], key, 1);
        };
    }
     return str;
}

/**
 * decrypto_v1: Caesar cipher decryption algorithm.
 * 
 * @str: String to decrypt.
 * @key: Integer shift key.
 * 
 * Returns: Decrypted string and modifies the input string.
 */
char* decrypto_v1(char *str, int key){
    toUpperCase(str);
    for (int i =0; i<strlen(str); i++){
        if((str[i]>='A' && str[i]<= 'Z')){
            str[i] = getCorrespondChar(str[i], key, 0);
        };
    }
     return str;
}

/**
 * isValidKey - Validates if the key contains only uppercase letters.
 * 
 * @str: Key string to validate.
 * 
 * Returns:
 * - 1 if the key is valid.
 * - 0 otherwise.
 */
int isValidKey(char *str){
    for(int i=0; str[i]!='\0'; i++){
        if(str[i]<'A' || str[i]>'Z'){
            return 0;
        }
    }
    return 1;
}

/**
 * crypto_v2: Keyword-based encryption algorithm.
 * 
 * @str: String to encrypt.
 * @key: Encryption keyword.
 * 
 * Returns: Encrypted string and modifies the input string.
 */
char* crypto_v2(char *str, char *key){
    toUpperCase(str);
    toUpperCase(key);
    int key_numb[strlen(key)];
    for (int i=0; key[i]!='\0'; i++){
        if((key[i]>='A' && key[i]<='Z')){
            key_numb[i] = key[i]-'A';
        }
    }
    printf("\n");
    int j =0;
    for(int i=0; str[i]!='\0'; i++){
        if((str[i]>='A' && str[i]<='Z') || (str[i]>='a' && str[i]<='z')){
            int index = j % strlen(key);
            str[i] = getCorrespondChar(str[i],key_numb[index], 1);
            j++;
        }   
    }
    return str;
}

/**
 * decrypto_v2: Keyword-based decryption algorithm.
 * 
 * @str: String to decrypt.
 * @key: Decryption keyword.
 * 
 * Returns: Decrypted string and modifies the input string.
 */
char* decrypto_v2(char *str, char *key){
    toUpperCase(str);
    toUpperCase(key);
    int key_numb[strlen(key)];
    for (int i=0; key[i]!='\0'; i++){
        if((key[i]>='A' && key[i]<='Z')){
            key_numb[i] = key[i]-'A';
        }
    }
    int j =0;
    for(int i=0; str[i]!='\0'; i++){
        if((str[i]>='A' && str[i]<='Z') || (str[i]>='a' && str[i]<='z')){
            int index = j % strlen(key);
            str[i] = getCorrespondChar(str[i],key_numb[index], 0);
            j++;
        }   
    }
    return str;
}

/**
 * bruteForce: Attempts to decrypt a Caesar cipher encrypted message using brute force.
 * 
 * @str: Encrypted string.
 * @op: Operation flag (1 to display results, 0 otherwise).
 * 
 * Returns: The three most probable keys.
 */
int* bruteForce(char *str, int op) {
    toUpperCase(str);
    int* bestKeys = (int*) malloc(3 * sizeof(int));
    int bestPercents[3] = {0, 0, 0}; // Stores the three best scores
    
    for (int i = 0; i < 26; i++) {
        decrypto_v1(str, i);
        
        // Execute all tests
        int test1_score = test_1(str) ? 100 : 0; // Presence of vowels
        int test2_score = test_2(str) ? 100 : 0; // No 3 consecutive consonants
        int test3_score = !test_3(str) ? 0 : (test_3(str) == 2 ? 40 : 100); // Digrams
        int test4_score = test_4(str); // Letter frequency
        int test5_score = test_5(str); // Common words
        int test6_score = test_6(str); // Grammatical structure
        
        // Calculate weighted score
        int result = (0.20 * test1_score) + (0.15 * test2_score) + (0.20 * test3_score) + 
                     (0.25 * test4_score) + (0.10 * test5_score) + (0.10 * test6_score);
        // Update the three best keys
        for (int j = 0; j < 3; j++) {
            if (result > bestPercents[j]) {
                for (int k = 2; k > j; k--) { // Shift values
                    bestPercents[k] = bestPercents[k - 1];
                    bestKeys[k] = bestKeys[k - 1];
                }
                bestPercents[j] = result;
                bestKeys[j] = i;
                break;
            }
        }
        crypto_v1(str, i); // Restore the original string for the next test
    }
    if(op){
        printf("The three most probable results are: \n");
        for(int i=0; i<3; i++){
            printf("\n------------------------------------------------------------Key %d------------------------------------------------------------\n", bestKeys[i]);
            printf("%s\n", decrypto_v1(str, bestKeys[i]));
            crypto_v1(str, bestKeys[i]);
        }
    }
    
    return bestKeys;
}

/**
 * extract_key - Extracts a key from a file starting at a specific position.
 * 
 * @chemin_fichier: Path to the file.
 * @start: Starting position in the file.
 * @size: Size of the key to extract.
 * 
 * Returns: Extracted key as a string.
 */
char* extract_key(const char* chemin_fichier, int start, int size) {
    FILE* fichier = fopen(chemin_fichier, "r");
    if (!fichier) {
        perror("Error opening the file");
        return NULL;
    }

    char* mot = (char*)malloc((size + 1) * sizeof(char));
    if (!mot) {
        perror("Memory allocation error");
        fclose(fichier);
        return NULL;
    }

    if (fseek(fichier, start, SEEK_SET) != 0) {
        perror("Error seeking in the file");
        fclose(fichier);
        free(mot);
        return NULL;
    }

    size_t lus = fread(mot, sizeof(char), size, fichier);
    
    if (lus < size) {
        rewind(fichier);
        size_t restant = size - lus;
        size_t lus_complement = fread(mot + lus, sizeof(char), restant, fichier);
        lus += lus_complement;
    }

    mot[lus] = '\0';

    fclose(fichier);
    return mot;
}

/**
 * crypto_v3: Encrypts a string using a key extracted from a file.
 * 
 * @str: String to encrypt.
 * @pos: Starting position in the key file.
 * 
 * Returns: Encrypted string.
 */
char* crypto_v3(char *str, int pos){
    char *key = extract_key("../data/key.txt", pos, strlen(str));    
    crypto_v2(str, key);
    return str;
}

/**
 * decrypto_v3: Decrypts a string using a key extracted from a file.
 * 
 * @str: String to decrypt.
 * @pos: Starting position in the key file.
 * 
 * Returns: Decrypted string.
 */
char* decrypto_v3(char *str, int pos){
    char *key = extract_key("../data/key.txt", pos, strlen(str));    
    decrypto_v2(str, key);
    return str;
}

/**
 * guessTheKey: Attempts to guess the encryption key of a Vigenère cipher.
 * 
 * @str: Encrypted string.
 * @sizeOfKey: Length of the key to guess.
 * 
 * Returns: The three most probable keys as an array of strings.
 */
char** guessTheKey(char *str, int sizeOfKey) {
    toUpperCase(str);
    int key1[sizeOfKey], key2[sizeOfKey], key3[sizeOfKey];
    char **bestKeys = (char**) malloc(3 * sizeof(char*));
    for (int i = 0; i < 3; i++) {
        bestKeys[i] = (char*) malloc((sizeOfKey + 1) * sizeof(char));
    }
    
    char buffer[MAX_MESSAGE_SIZE];
    int j = 0, count = 0;
    for (int k = 0; k < sizeOfKey; k++) {
        j = 0;
        count = 0;
        for (int i = 0; str[i] != '\0'; i++) {
            if (str[i] >= 'A' && str[i] <= 'Z') {
                if (count % sizeOfKey == k) {
                    buffer[j] = str[i];
                    j++;
                }
                count++;
            }
        }
        buffer[j] = '\0';
        
        int *keys = bruteForce(buffer, 0);
        
        key1[k] = keys[0];
        key2[k] = keys[1];
        key3[k] = keys[2];
        
        bestKeys[0][k] = key1[k] + 'A';
        bestKeys[1][k] = key2[k] + 'A';
        bestKeys[2][k] = key3[k] + 'A';
    }
    
    for (int i = 0; i < 3; i++) {
        bestKeys[i][sizeOfKey] = '\0';
    }
    
    return bestKeys;
}

/**
 * getPositionInMatrice - Finds the position of a character in a matrix.
 * 
 * @c: Character to find.
 * @matrice: Matrix to search in.
 * 
 * Returns: A Couple struct containing the row and column of the character.
 */
Couple getPositionInMatrice(char c, char *matrice) {
    Couple result = {-1, -1};
    for (int i = 0; i < SIZE; i++) {
        if (c == matrice[i]) {
            result.x = i / 5;
            result.y = i % 5;
            break;
        }
    }
    return result;
}

/**
 * generateMatrice - Generates a 5x5 matrix for the Playfair cipher.
 * 
 * @matrice: Matrix to populate.
 * @key: Key to use for generating the matrix.
 */
void generateMatrice(char *matrice, char *key) {
    int index = 0;
    for (int i = 0; key[i] && index < SIZE; i++) {
        if (!char_include(matrice, key[i])) {
            matrice[index++] = key[i];
        }
    }
    
    for (char j = 'A'; j <= 'Z' && index < SIZE; j++) {
        if (j != 'W' && !char_include(matrice, j)) {
            matrice[index++] = j;
        }
    }
}

/**
 * deleteCharcatere - Deletes a character from a string at a specific index.
 * 
 * @str: String to modify.
 * @index: Index of the character to delete.
 */
void deleteCharcatere(char  *str, int index) {
    int i;
    for (int i=index; i < strlen(str) - 1; i++){
        str[i] = str[i+1];
    }
}

/**
 * crypto_v4: Playfair cipher encryption algorithm.
 * 
 * @str: String to encrypt.
 * @key: Encryption key.
 */
void crypto_v4(char *str, char *key) {
    toUpperCase(str);
    for(int i=0; i<strlen(str); i++){
        if(str[i] == ' '){
            deleteCharcatere(str, i);
        }
    }
    int len = strlen(str);
    for(int i=0; i<strlen(str)-1; i++){
        if(str[i] == str[i+1]){
            for(int j=len+1; j>=i+2; j--){
                str[j] = str[j-1];
            }
            str[i+1] = 'X';
        }
    }
    if(strlen(str)%2==1){
        str[strlen(str)] = 'X';
        str[strlen(str)+1] = '\0';
    }
    
    char matrice[SIZE] = {0};
    generateMatrice(matrice, key);

    for (int i = 0; i < strlen(str) - 1; i += 2) {
        Couple c1 = getPositionInMatrice(str[i], matrice);
        Couple c2 = getPositionInMatrice(str[i + 1], matrice);
        
        if (c1.x == -1 || c2.x == -1) continue; // Error handling

        if (c1.x == c2.x) {
            str[i] = matrice[c1.x * 5 + (c1.y + 1) % 5];
            str[i + 1] = matrice[c2.x * 5 + (c2.y + 1) % 5];
        } else if (c1.y == c2.y) {
            str[i] = matrice[((c1.x + 1) % 5) * 5 + c1.y];
            str[i + 1] = matrice[((c2.x + 1) % 5) * 5 + c2.y];
        } else {
            str[i] = matrice[c1.x * 5 + c2.y];
            str[i + 1] = matrice[c2.x * 5 + c1.y];
        }
    }
}

/**
 * decrypto_v4: Playfair cipher decryption algorithm.
 * 
 * @str: String to decrypt.
 * @key: Decryption key.
 */
void decrypto_v4(char *str, char *key){
    toUpperCase(str);
    for(int i=0; i<strlen(str); i++){
        if(str[i] == ' '){
            deleteCharcatere(str, i);
        }
    }
    char matrice[SIZE] = {0};
    generateMatrice(matrice, key);

    for (int i = 0; i < strlen(str) - 1; i += 2) {
        Couple c1 = getPositionInMatrice(str[i], matrice);
        Couple c2 = getPositionInMatrice(str[i + 1], matrice);
        
        if (c1.x == -1 || c2.x == -1) continue; // Error handling

        if (c1.x == c2.x) {
            str[i] = matrice[c1.x * 5 + (c1.y + 4) % 5]; // Move left in the same row
            str[i + 1] = matrice[c2.x * 5 + (c2.y + 4) % 5];
        } else if (c1.y == c2.y) {
            str[i] = matrice[((c1.x + 4) % 5) * 5 + c1.y]; // Move up in the same column
            str[i + 1] = matrice[((c2.x + 4) % 5) * 5 + c2.y];
        } else {
            str[i] = matrice[c1.x * 5 + c2.y]; // Swap columns
            str[i + 1] = matrice[c2.x * 5 + c1.y];
        }
    }
}