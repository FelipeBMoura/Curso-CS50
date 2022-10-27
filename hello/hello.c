#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string nome = get_string("Qual é o seu nome? \n");

    printf("olá, %s\n", nome);
}