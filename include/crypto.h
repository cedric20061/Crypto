#ifndef CRYPTO_H
#define CRYPTO_H

#define MAX_MESSAGE_SIZE 1500
#define MAX_LINE_LENGTH 256
#define KEY "XMCKLVGABTKOAGHTCGPNRBOJDBDSCABHUBCZVNINMQAIDNVTAYCGDZ"
char* crypto_v1(char *str, int key);
char* decrypto_v1(char *str, int key);
int isValidKey(char *str);
char* crypto_v2(char *str, char *key);
char* decrypto_v2(char *str, char *key);
char* crypto_v3(char *str, int pos);
char* decrypto_v3(char *str, int pos);
void crypto_v4(char *str, char *key);
void decrypto_v4(char *str, char *key);
int* bruteForce(char *str, int op);
char** guessTheKey(char *str, int sizeOfKey);
#endif
