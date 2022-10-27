import sys

numero_cartao = input('Insira o número do cartão: ')

len_cartao = len(numero_cartao)

soma_par = 0

soma_impar = 0

soma_total = 0

if len_cartao != 13 and len_cartao != 15 and len_cartao != 16:
    print('INVALID')
    sys.exit()

for _ in range(-2, -len_cartao - 1, -2):

    temp_mult = int(numero_cartao[_]) * 2

    if temp_mult >= 10:
        soma_par = soma_par + temp_mult - 9

    else:
        soma_par = soma_par + temp_mult

for _ in range(-1, -len_cartao - 1, -2):

    temp_impar = int(numero_cartao[_])

    soma_impar = soma_impar + temp_impar

soma_total = soma_par + soma_impar

if soma_total % 2 == 0:

    if int(numero_cartao[0]) == 3 and int(numero_cartao[1]) == 4 or int(numero_cartao[1]) == 7:
        print('AMEX')

    elif int(numero_cartao[0]) == 5 and \
    int(numero_cartao[1]) == 1 or \
    int(numero_cartao[1]) == 2 or \
    int(numero_cartao[1]) == 3 or \
    int(numero_cartao[1]) == 4 or \
    int(numero_cartao[1]) == 5:
        print("MASTERCARD")

    elif int(numero_cartao[0]) == 4:
        print('VISA')

else:
    print('INVALID')