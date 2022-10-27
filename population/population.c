#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // TODO: Solicite o valor inicial ao usuário

    int populacao_inicial;

    do
    {
        populacao_inicial = get_int("População Inicial: ");
    }
    while (populacao_inicial < 9);

    // TODO: Solicite o valor final ao usuário

    int populacao_final;

    do
    {
        populacao_final = get_int("População Final: ");
    }
    while (populacao_final < populacao_inicial);

    // TODO: Calcule o número de anos até o limite

    int anos = 0;

    do
    {
        anos++;
        populacao_inicial = populacao_inicial + (populacao_inicial / 3) - (populacao_inicial / 4);
    }
    while (populacao_inicial < populacao_final);


    // TODO: Imprima o número de anos

    printf("Numero de anos: %i\n", anos);

}