from utils import DataFiles
from collections import *
from numpy import *
from math import *

dataFiles = DataFiles(__file__)

input = dataFiles.input
inputEX = dataFiles.inputEX

inp = input[:]

mat = [[9 for _ in range(len(inp) + 2)] for y in range(len(inp[0]) + 2)]

for i in range(len(inp)):
    for j in range(len(inp[0])):
        mat[i + 1][j + 1] = int(inp[i][j])


def sc_mn(mat, x, y):
    if (
        mat[x][y] < mat[x + 1][y]
        and mat[x][y] < mat[x - 1][y]
        and mat[x][y] < mat[x][y + 1]
        and mat[x][y] < mat[x][y - 1]
    ):
        return mat[x][y]
    else:
        return -1


ans = 0
for x in range(1, len(inp) + 1):
    for y in range(1, len(inp[0]) + 1):
        ans += 1 + sc_mn(mat, x, y)

print("Part1:", ans)

# part 2
basins = []


def cnt_b(x, y, start=False):
    if mat[x][y] != 9 and mat[x][y] != -1:  # or y < 0 or y >= len(inp) or x < 0 or x >= len(inp[0])
        if start:
            basins.append(0)
        else:
            basins[len(basins) - 1] += 1
            mat[x][y] = -1

        cnt_b(x + 1, y)
        cnt_b(x - 1, y)
        cnt_b(x, y + 1)
        cnt_b(x, y - 1)


for x in range(1, len(inp) + 1):
    for y in range(1, len(inp[0]) + 1):
        cnt_b(x, y, True)

basins.sort(reverse=True)
print("Part2:", basins[0] * basins[1] * basins[2])
