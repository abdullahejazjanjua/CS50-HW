#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompts for start size
    int start;
    do
    {
        start = get_int("Start size: ");
    }
    while (start < 9);

    // Prompts for end size
    int end;
    do
    {
        end = get_int("End size: ");
    }
    while (end < start);

    // Calculates number of years until we reach threshold
    int years = 0;
    while (start < end)
    {
        int growth = start / 3;
        int loss = start / 4;
        start = start + growth - loss;
        years++;
    }

    // Prints number of years
    printf(" Years: %i\n", years);
}
