#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string s);

int main(int argc, string argv[])
{
    string ptext;
    int converted_char;
    char *ctext;

    if (argc == 2 && only_digits(argv[1]))
    {
        ptext = get_string("plaintext: ");
        ctext = malloc((strlen(ptext) + 1) * sizeof(char));
    }
    else if (argc != 2 || !only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    int key = atoi(argv[1]);

    for (int i = 0, n = strlen(ptext); i < n; i++)
    {
        if (isupper(ptext[i]))
        {
            converted_char = (ptext[i] - 'A' + key) % 26 + 'A';
            ctext[i] = converted_char;
        }
        else if (islower(ptext[i]))
        {
            converted_char = (ptext[i] - 'a' + key) % 26 + 'a';
            ctext[i] = converted_char;
        }
        else if (ispunct(ptext[i]) || ptext[i] == ' ')
        {
            ctext[i] = ptext[i];
        }
    }
    ctext[strlen(ptext)] = '\0';
    printf("ciphertext: %s\n", ctext);
}

bool only_digits(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
        if (!isdigit(s[i]))
        {
            return false;
        }
    return true;
}
