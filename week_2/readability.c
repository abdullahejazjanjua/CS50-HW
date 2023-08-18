#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)

{
    string text = get_string("Text: ");
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    float L = (float) letters / words * 100.0;
    float S = (float) sentences / words * 100.0;
    float index = 0.0588 * L - 0.296 * S - 15.8;

    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %d\n", (int) round(index));
    }
}

int count_letters(string text)
{
    int letters = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (islower(text[i]))
        {
            letters++;
        }
        else if (isupper(text[i]))
        {
            letters++;
        }
    }
    return letters;
}

int count_words(string text)
{
    int words = 0;
    for (int j = 0, n = strlen(text); j < n; j++)
    {
        if (isblank(text[j]))
        {
            words++;
        }
    }

    return words + 1;
}

int count_sentences(string text)
{
    int sentences = 0;
    for (int k = 0, n = strlen(text); k < n; k++)
    {
        if (text[k] == '.' || text[k] == '?' || text[k] == '!')
        {
            sentences++;
        }
    }

    return sentences;
}