#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char plain[100], cipher[100];
    int key, i, length;

    printf("\n Prakash Koirala \n");
    printf("\n Enter the plain text: ");
    scanf("%s", plain);

    // Validate key input
    printf("\n Enter the key value (integer): ");
    while (scanf("%d", &key) != 1)
    {
        printf("Invalid key! Please enter a valid integer: ");
        while (getchar() != '\n')
            ; // Clear the invalid input
    }

    printf("\n \n \t PLAIN TEXT: %s", plain);
    printf("\n \n \t ENCRYPTED TEXT: ");

    length = strlen(plain);
    for (i = 0; i < length; i++)
    {
        if (isupper(plain[i]))
        {
            // Encrypt uppercase letters
            cipher[i] = ((plain[i] - 'A' + key) % 26) + 'A';
        }
        else if (islower(plain[i]))
        {
            // Encrypt lowercase letters
            cipher[i] = ((plain[i] - 'a' + key) % 26) + 'a';
        }
        else
        {
            // Keep non-alphabetic characters as is
            cipher[i] = plain[i];
        }
        printf("%c", cipher[i]);
    }
    cipher[length] = '\0'; // Null-terminate the cipher string

    printf("\n \n \t AFTER DECRYPTION : ");
    for (i = 0; i < length; i++)
    {
        if (isupper(cipher[i]))
        {
            // Decrypt uppercase letters
            plain[i] = ((cipher[i] - 'A' - key + 26) % 26) + 'A';
        }
        else if (islower(cipher[i]))
        {
            // Decrypt lowercase letters
            plain[i] = ((cipher[i] - 'a' - key + 26) % 26) + 'a';
        }
        else
        {
            // Keep non-alphabetic characters as is
            plain[i] = cipher[i];
        }
        printf("%c", plain[i]);
    }
    plain[length] = '\0'; // Null-terminate the plain string

    printf("\n");
    return 0;
}
