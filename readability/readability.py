from cs50 import get_string

texto = get_string('Insira o texto: ')

quant_palavras = 0
quant_letras = 0
quant_sentencas = 0
i = 0

tamanho = len(texto)

while i < tamanho:

    if texto[i].isalpha():
        quant_letras += 1

    if (i == 0 and texto[i] != " ") or (i != tamanho and texto[i] == " " and texto[i + 1] != " "):
        quant_palavras += 1

    if texto[i] == "." or texto[i] == "?" or texto[i] == "!":
        quant_sentencas += 1

    i += 1

L = (quant_letras / quant_palavras) * 100
S = (quant_sentencas / quant_palavras) * 100
indice = round(0.0588 * L - 0.296 * S - 15.8)

if indice < 1:
    print("Before Grade 1")
elif indice >= 16:
    print("Grade 16+")
else:
    print(f"Grade {indice}")