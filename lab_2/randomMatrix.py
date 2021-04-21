from random import randint

n = int(input('Введите размер матрицы: '))

for i in range(n):
    for j in range(n):
        if i == j:
            print('0', end=' ')
        else:
            print(str(randint(0, 1)), end=' ')
    print()
