#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int arg_c, string arg_v[])
{
    if (arg_c == 2)
    {
        string chave = arg_v[1];

        int n_chave = strlen(chave);

        char alphabet[2][26];

        for (int i = 0; i < n_chave; i++)
        {
            alphabet[0][i] = 'A' + i;
            alphabet[1][i] = arg_v[1][i];
        }

        for (int i = 0; i < n_chave; i++)
        {
            int j = 0;

            for (int k = 0; k < n_chave; k++)
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

        for (int i = 0; i < strlen(chave); i++)

            if (isalpha(chave[i] == false))
            {
                printf("Chave deve conter somente caracteres alfabéticos.\n");
                return 1;
            }

        if (strlen(chave) == 26)
        {
            string texto_simples = get_string("plaintext: ");

            int n_texto_simples = strlen(texto_simples);

            printf("ciphertext: ");

            for (int i = 0; i < n_texto_simples; i++)
            {
                if (isalpha(texto_simples[i]))
                {
                    if (islower(texto_simples[i]))
                    {
                        for (int j = 0; j < n_chave; j++)
                        {
                            if (tolower(alphabet[0][j]) == texto_simples[i])
                            {
                                 printf("%c", tolower(alphabet[1][j]));
                            }
                        }

                    }
                    if (isupper(texto_simples[i]))
                    {
                        for (int j = 0; j < n_chave; j++)
                        {
                            if (toupper(alphabet[0][j]) == texto_simples[i])
                            {
                                printf("%c", toupper(alphabet[1][j]));
                            }
                        }
                    }
                }
                else
                {
                    printf("%c", texto_simples[i]);
                }
            }
        }
        else
        {
            printf("Chave de conter extamente 26 caracteres\n");
            return 1;
        }

    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    printf("\n");
    return 0;
}
