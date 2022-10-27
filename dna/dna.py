from csv import DictReader
import sys

if len(sys.argv) != 3:
    print('São necessários 3 argumentos: dna, dados, sequencia')
    sys.exit(1)

dados_path = sys.argv[1]
sequencia_path = sys.argv[2]

with open(dados_path, 'r') as arquivo_csv:
    leitor = DictReader(arquivo_csv)
    list_dict = list(leitor)

with open(sequencia_path, 'r') as arquivo:
    sequencia = arquivo.read()

contagem_maxima = []

for i in range(1, len(leitor.fieldnames)):
    STR = leitor.fieldnames[i]
    contagem_maxima.append(0)
    for j in range(len(sequencia)):
        STR_contagem = 0
        if sequencia[j:(j + len(STR))] == STR:
            k = 0
            while sequencia[(j + k):(j + k + len(STR))] == STR:
                STR_contagem += 1
                k += len(STR)
            if STR_contagem > contagem_maxima[i - 1]:
                contagem_maxima[i - 1] = STR_contagem

for i in range(len(list_dict)):
    coincidencias = 0
    for j in range(1, len(leitor.fieldnames)):
        if int(contagem_maxima[j - 1]) == int(list_dict[i][leitor.fieldnames[j]]):
            coincidencias += 1
        if coincidencias == (len(leitor.fieldnames) - 1):
            print(list_dict[i]['name'])
            sys.exit(0)

print('No match')

