#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    string message = get_string("Message: ");
    for (int i = 0, n = strlen(message); i < n; i++)
    {
        int ascii_value = message[i];
    }
    for (int j = 0, n = strlen(message); j < n; j++)
    {
        int ascii_value = message[j];
        int number, quotient, k = 0, binary[8] = {0}, temp = ascii_value;

        while (temp != 0 && k < 8)
        {
            number = temp % 2;
            quotient = temp / 2;
            temp = quotient;
            binary[k] = number;
            k++;
        }
        for (int f = BITS_IN_BYTE - 1; f >= 0; f--)
        {

            print_bulb(binary[f]);
        }
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
