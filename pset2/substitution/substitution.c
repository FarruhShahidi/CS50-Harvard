#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

int main(int argc, string argv[])

{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }


    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

     for (int i = 0; i < 26; i++)
    {
        if (!islower(argv[1][i]) && !isupper(argv[1][i]))
        {
            printf("Must be letters only\n");
            return 1;
        }
    }
    //int letter_count = 0;

    for (int i = 0; i < 26; i++)
    {

        for (int j = 0; j < i; j++)
        {
            if (argv[1][j] == argv[1][i])
            {
                printf("Letters must be distinct \n");
                return 1;
            }
        }

    }
    /*
    if (letter_count !=26)
    {
        printf("You must enter 26 distinct letters");
        return 1;
    }
    */
    // stores the letters from 0 to 25.
    char cipher[26];

    for (int i = 0; i< 26; i++)
    {

        cipher[i] = 65 + i - toupper(argv[1][i]) ;


    }

    string plaintext = get_string("Plaintext: \n");

    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (plaintext[i] >= 65 && plaintext[i] <= 90)
        {
            plaintext[i] = plaintext[i] - cipher[plaintext[i] - 65];

        }
        else if (plaintext[i] >= 97 && plaintext[i] <= 122)
        {
            plaintext[i] = plaintext[i] - cipher[plaintext[i] - 97];

        }
    }

    printf("ciphertext: %s\n", plaintext);
    return 0;
}