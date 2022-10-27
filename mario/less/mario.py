from cs50 import get_int

while True:

    height = get_int('Digite a altura da pirâmide. O valor deve ser de 1 até 8: ')

    if height < 1 or height > 8:
        print('A altura da pirâmide deve ser um número de 1 até 8.')
        height = get_int('Digite a altura da pirâmide. O valor deve ser de 1 até 8: ')

    if height >= 1 or height <= 8:
        break

    else:
        print('A altura da pirâmide deve ser um número de 1 até 8.')
        height = get_int('Digite a altura da pirâmide. O valor deve ser de 1 até 8: ')

for i in range(height):
    print((height - 1 - i) * " ", end="")
    print((1 + i) * "#")
