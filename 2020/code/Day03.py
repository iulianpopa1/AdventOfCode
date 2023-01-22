from utils import DataFiles

dataFiles = DataFiles(__file__)

input = dataFiles.get_input()  # inputRaw = dataFiles.input
inputEx = dataFiles.get_inputEX()  # inputRawEX = dataFiles.inputEX


def count_trees(right, down):
    cnt = 0
    x = 0
    y = 0
    while y < len(input):
        if input[y][x] == '#':
            cnt += 1

        x = (x + right) % len(input[0])
        y += down

    return cnt


y = count_trees(3, 1)
print('Part 1: ', y)
y *= count_trees(1, 1)
y *= count_trees(5, 1)
y *= count_trees(7, 1)
y *= count_trees(1, 2)
print('Part 2: ', y)
