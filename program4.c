#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int determinant(int **key, int size) {
    if (size == 1) {
        return key[0][0];
    } else if (size == 2) {
        return key[0][0] * key[1][1] - key[0][1] * key[1][0];
    } else if (size == 3) {
        return key[0][0] * (key[1][1] * key[2][2] - key[1][2] * key[2][1]) -
               key[0][1] * (key[1][0] * key[2][2] - key[1][2] * key[2][0]) +
               key[0][2] * (key[1][0] * key[2][1] - key[1][1] * key[2][0]);
    } else {
        printf("Determinant calculation only supported for 1x1, 2x2, and 3x3 matrices.\n");
        return 0;
    }
}


int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}


void encrypt(char *message, int **key, int size) {
    int len = strlen(message);
    int encrypted[len];
    int k = 0;

    for (int i = 0; i < len; i += size) {
        int parts[size];
        for (int j = 0; j < size; j++) {
            parts[j] = (i + j < len) ? message[i + j] - 'a' : 0;
        }
        for (int j = 0; j < size; j++) {
            int sum = 0;
            for (int l = 0; l < size; l++) {
                sum += key[j][l] * parts[l];
            }
            encrypted[k++] = sum % 26;
        }
    }

    printf("Encrypted message: ");
    for (int i = 0; i < k; i++)
        printf("%c", encrypted[i] + 'a');
    printf("\n");
}

int main() {
    int size;
    printf("Enter the size of the key matrix (2 or 3): ");
    scanf("%d", &size);

    
    int **key = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        key[i] = (int *)malloc(size * sizeof(int));
    }

  
    printf("Enter the %dx%d key matrix:\n", size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            char c;
            scanf(" %c", &c); 
            key[i][j] = tolower(c) - 'a';
        }
    }

    char message[100];

    printf("Enter the message to encrypt: ");
    scanf("%s", message);

    
    for (int i = 0; message[i]; i++)
        message[i] = tolower(message[i]);

    
    if (determinant(key, size) == 0) {
        printf("Invalid key matrix. Determinant is zero.\n");
        return 1;
    }

   
    int det = determinant(key, size);
    int modInv = modInverse(det, 26);
    if (modInv == -1) {
        printf("Invalid key matrix. Modular inverse does not exist.\n");
        return 1;
    }

    encrypt(message, key, size);

    
    for (int i = 0; i < size; i++) {
        free(key[i]);
    }
    free(key);

    return 0;
}

