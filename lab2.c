#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define ALPHABET_SIZE 26

char encryptChar(char c, char key[]) {
    if (isalpha(c)) {
        if (islower(c)) {
            return tolower(key[c - 'a']);
        } else {
            return toupper(key[c - 'A']);
        }
    }
    return c;
}

char decryptChar(char c, char key[]) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (tolower(c) == tolower(key[i])) {
            if (islower(c)) {
                return 'a' + i;
            } else {
                return 'A' + i;
            }
        }
    }
    return c;
}

void encrypt(char plaintext[], char key[]) {
    int length = strlen(plaintext);
    for (int i = 0; i < length; i++) {
        plaintext[i] = encryptChar(plaintext[i], key);
    }
}

void decrypt(char ciphertext[], char key[]) {
    int length = strlen(ciphertext);
    for (int i = 0; i < length; i++) {
        ciphertext[i] = decryptChar(ciphertext[i], key);
    }
}

int main() {
    char key[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
    char plaintext[1000];
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

   
    if (plaintext[strlen(plaintext) - 1] == '\n') {
        plaintext[strlen(plaintext) - 1] = '\0';
    }

    char ciphertext[strlen(plaintext) + 1];
    strcpy(ciphertext, plaintext);

    
    encrypt(ciphertext, key);
    printf("Ciphertext: %s\n", ciphertext);

    
    decrypt(ciphertext, key);
    printf("Decrypted plaintext: %s\n", ciphertext);

    return 0;
}

