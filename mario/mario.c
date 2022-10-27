#include <cs50.h>
#include <stdio.h>

void pyramid(int height);

int main(void)
{
    int height;

    do
    {
        height = get_int("Digite a altura: ");
    }
    while (height < 1 || height > 8);

    pyramid(height);
}

void pyramid(int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int x = height - i; x > 1; x--)
        {
            printf(" ");
        }
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}