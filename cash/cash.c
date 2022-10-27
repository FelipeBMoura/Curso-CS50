#include <stdio.h>
#include <math.h>
#include <cs50.h>

float valor(void);
int contagem_moedas(int centavos_de_troco);

int main(void)
{
    float troco = valor();
    int centavos_de_troco = round(troco * 100);

    printf("%d\n", contagem_moedas(centavos_de_troco));

}

int contagem_moedas(int centavos_de_troco)
{
    int contagem = 0;

    while (centavos_de_troco > 0)
    {
        if (centavos_de_troco >= 25)
        {
            centavos_de_troco -= 25;
            contagem++;
        }
        else if (centavos_de_troco >= 10)
        {
            centavos_de_troco -= 10;
            contagem++;
        }
        else if (centavos_de_troco >= 5)
        {
            centavos_de_troco -= 5;
            contagem++;
        }
        else
        {
            centavos_de_troco -= 1;
            contagem++;
        }
    }

    return contagem;
}

float valor(void)
{
    float troco;
    do
    {
        troco = get_float("Troco: ");
    }
    while (troco < 0.00);

    return troco;
}