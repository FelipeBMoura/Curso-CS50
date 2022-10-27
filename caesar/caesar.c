#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int arg_c, string arg_v[])

{
    // Verifica se o número de argumentos é válido
    if (arg_c == 2 && isdigit(*arg_v[1]))
    {
        // Verifica se a chave é válida
        int chave = atoi(arg_v[1]);

        if (chave < 0 || chave > 26)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }

        // Pega o texto do usuário
        string texto_simples = get_string("plaintext: ");

        int n = strlen(texto_simples);

        // Criptografa o texto
        for (int i = 0; i < n; i++)
        {
            // Verifica se o caracter é letra
            if (isalpha(texto_simples[i]))
            {
                // Verifica se o caracter é maiúsculo
                if (isupper(texto_simples[i]))
                {
                    // Criptografa o caracter
                    texto_simples[i] = ((texto_simples[i] - 'A' + chave) % 26) + 'A';
                }

                // se o caracter é minúsculo
                else
                {
                    // Criptografa o caracter
                    texto_simples[i] = ((texto_simples[i] - 'a' + chave) % 26) + 'a';
                }
            }
        }

        // Imprime o texto criptografado
        printf("ciphertext: %s\n", texto_simples);

        return 0;
    }

    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}