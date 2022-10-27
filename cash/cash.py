from cs50 import get_float

troco = 0
contador = 0

while troco <= 0:
    troco = get_float('Troco: ')
    centavos = round(troco * 100)

while centavos > 0:

    if centavos >= 25:
        centavos = centavos - 25
        contador += 1

    elif centavos >= 10:
        centavos = centavos - 10
        contador += 1

    elif centavos >= 5:
        centavos = centavos - 5
        contador += 1

    elif centavos >= 1:
        centavos = centavos - 1
        contador += 1

print(contador)