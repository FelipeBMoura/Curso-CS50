#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)

{
    int letters = 0;

    int words = 1; // não há um espaço vazio após a última palavra

    int sentences = 0;

    string text = get_string("Texto: ");

    int n = strlen(text);

    for (int i = 0; i < n; i++)

        if (text[i] >= 'a' && text[i] <= 'z')

            {
                letters += 1;
            }

        else if (text[i] >= 'A' && text[i] <= 'Z')

            {
                letters += 1;
            }

        else if (text[i] == ' ')

            {
                words += 1;
            }

        else if (text[i] == '.' || text[i] == '?' || text[i] == '!')

            {
                sentences += 1;
            }

    float L = (letters * 100) / (float) words; // número médio de letras por 100 palavras

    float S = (sentences * 100) / (float) words; // número médio de sentenças por 100 palavras

    int col_liau_index = round(0.0588 * L - 0.296 * S - 15.8);

    if (col_liau_index < 1)

        printf("Before Grade 1\n");

    else if (col_liau_index <= 15)

        printf("Grade %i\n", col_liau_index);

    else

        printf("Grade 16+\n");

}