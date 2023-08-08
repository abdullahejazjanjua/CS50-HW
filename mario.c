#include <cs50.h>
#include <stdio.h>
int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for (int i = height; i > 0; i--)
    {

        for (int j = 0; j < i; j++)
        {
            printf(" ");
        }

        for (int a = i; a <= height; a++)
        {

            printf("#");
        }
        printf("\n");
    }
}