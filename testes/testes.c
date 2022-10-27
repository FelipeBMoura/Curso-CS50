#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // string argv = "VCHPRZGJNTLSKFBDQWAXEUYMOI";

    int argvlen = strlen(argv[1]);

    char alphabet[2][26];

    for (int i = 0; i < argvlen; i++)
    {
        alphabet[0][i] = 'A' + i;
        alphabet[1][i] = argv[1][i];
    }

    for (int i = 0; i < argvlen; i++)
    {
        int j = 0;
        for (int k = 0; k < argvlen; k++)
        {
            if (toupper(alphabet[1][k]) == toupper(alphabet[1][i]))
            {
                j++;
                if (j == 2)
                {
                    printf("Valor repetido, verificar a chave.\n");
                    return 1;
                }
            }
        }
    }
    printf("%s\n", alphabet[0]);
    printf("%s\n", alphabet[1]);
}