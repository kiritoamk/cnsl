#include<stdio.h>  
#include<stdlib.h>  
#include<math.h>  
#include<string.h>  

long int p, q, n, totient, flag, public_key[100], private_key[100], temp[100], key_index, plaintext[100], ciphertext[100], i;  
char message[100];  

int is_prime(long int);  
void generate_keys();  
long int compute_modular_inverse(long int);  
void encrypt();  
void decrypt();  

int main()  
{  
    printf("ENTER FIRST PRIME NUMBER: ");  
    scanf("%ld", &p);  
    flag = is_prime(p);  
    if (flag == 0 || p == 1)  
    {  
        printf("WRONG INPUT\n");  
        exit(1);  
    }  

    printf("ENTER ANOTHER PRIME NUMBER: ");  
    scanf("%ld", &q);  
    flag = is_prime(q);  
    if (flag == 0 || q == 1 || p == q)  
    {  
        printf("WRONG INPUT\n");  
        exit(1);  
    }  

    printf("ENTER MESSAGE: ");  
    scanf(" %[^\n]s", message);  
    for (i = 0; i < strlen(message); i++)  
        plaintext[i] = message[i];  

    n = p * q;  
    totient = (p - 1) * (q - 1);  

    generate_keys();  

    printf("\nPOSSIBLE VALUES OF PUBLIC KEY AND PRIVATE KEY ARE:\n");  
    for (i = 0; i < key_index - 1; i++)  
        printf("%ld\t%ld\n", public_key[i], private_key[i]);  

    encrypt();  
    decrypt();  

    return 0;  
}  

int is_prime(long int pr)  
{  
    int i;  
    if (pr == 1)  
        return 0;  

    for (i = 2; i <= sqrt(pr); i++)  
    {  
        if (pr % i == 0)  
            return 0;  
    }  
    return 1;  
}  

void generate_keys()  
{  
    int k;  
    k = 0;  
    for (i = 2; i < totient; i++)  
    {  
        if (totient % i == 0)  
            continue;  
        flag = is_prime(i);  
        if (flag == 1 && i != p && i != q)  
        {  
            public_key[k] = i;  
            flag = compute_modular_inverse(public_key[k]);  
            if (flag > 0)  
            {  
                private_key[k] = flag;  
                k++;  
            }  
            if (k == 99)  
                break;  
        }  
    }  
    key_index = k;  
}  

long int compute_modular_inverse(long int x)  
{  
    long int k = 1;  
    while (1)  
    {  
        k = k + totient;  
        if (k % x == 0)  
            return (k / x);  
    }  
}  

void encrypt()  
{  
    long int pt, ct, key = public_key[0], k, len;  
    i = 0;  
    len = strlen(message);  
    while (i < len)  
    {  
        pt = plaintext[i];  
        k = 1;  
        for (int j = 0; j < key; j++)  
        {  
            k = k * pt;  
            k = k % n;  
        }  
        temp[i] = k;  
        ct = k;  
        ciphertext[i] = ct;  
        i++;  
    }  
    ciphertext[i] = -1;  
    printf("\nTHE ENCRYPTED MESSAGE IS:\n");  
    for (i = 0; ciphertext[i] != -1; i++)  
        printf("%ld ", ciphertext[i]);  
}  

void decrypt()  
{  
    long int pt, ct, key = private_key[0], k;  
    i = 0;  
    while (ciphertext[i] != -1)  
    {  
        ct = temp[i];  
        k = 1;  
        for (int j = 0; j < key; j++)  
        {  
            k = k * ct;  
            k = k % n;  
        }  
        pt = k;  
        plaintext[i] = pt;  
        i++;  
    }  
    plaintext[i] = -1;  
    printf("\nTHE DECRYPTED MESSAGE IS:\n");  
    for (i = 0; plaintext[i] != -1; i++)  
        printf("%c", (char)plaintext[i]);  
}
