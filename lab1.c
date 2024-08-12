#include <stdio.h>
#include <string.h>


void encrypt(char message[], int  shift) {
    int i;
    for (i = 0; message[i] != '\0'; i++) {
        
        if (message[i] >= 'A' && message[i] <= 'Z') {
            message[i] = ((message[i] - 'A') + shift) % 26 + 'A';
        }
        
        else if (message[i] >= 'a' && message[i] <= 'z') {
            message[i] = ((message[i] - 'a') + shift) % 26 + 'a';
        }
    }
}


void decrypt(char message[], int  shift) {
   
    encrypt(message, 26 - shift);
}

int main() {
    char message[1000];
    int shift=3; 

    printf("Enter message to be Encrypted\n");
    fgets(message,sizeof(message),stdin);
    


    printf("Original message: %s\n", message);

    
    encrypt(message, shift);
    printf("Encrypted message: %s\n", message);


    decrypt(message, shift);
    printf("Decrypted message: %s\n", message);

    return 0;
}