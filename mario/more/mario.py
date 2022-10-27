from cs50 import get_int

altura = 0

while altura > 8 or altura < 1:
    altura = get_int('Digite a altura da pirâmide. O valor deve ser de 1 até 8: ')

for i in range(1, altura + 1):
    for j in range(1, altura + 1):
        if j > (altura - i):
            print('#', end='')
        else:
            print(' ', end='')

        if j == altura:
            print(' ', '#' * i, end='')
    print()