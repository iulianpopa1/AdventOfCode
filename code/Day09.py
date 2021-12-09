from utils import DataFiles
from collections import *
from math import *
import numpy as np

dataFiles = DataFiles(__file__)

input = dataFiles.input
inputEX = dataFiles.inputEX

inp = input[:]


def get_neigh(x, y):
    neigh = []

    if x > 0:
        neigh.append((x - 1, y, mat[x - 1][y]))
    if x < len(mat) - 1:
        neigh.append((x + 1, y, mat[x + 1][y]))
    if y > 0:
        neigh.append((x, y - 1, mat[x][y - 1]))
    if y < len(mat[x]) - 1:
        neigh.append((x, y + 1, mat[x][y + 1]))

    return neigh


def is_low_point(x, y):
    if all(mat[x][y] < z for _, _, z in get_neigh(x, y)):
        return mat[x][y]
    else:
        return -1


rows = len(inp)
cols = len(inp[0])
mat = np.zeros((rows, cols), dtype=int)

for x in range(len(inp)):
    for y in range(len(inp[0])):
        mat[x][y] = inp[x][y]

ans = 0
for x in range(len(mat)):
    for y in range(len(mat[0])):
        ans += 1 + is_low_point(x, y)

print("Part1:", ans)


def cnt_b(x, y, start=False):

    if mat[x][y] != 9 and mat[x][y] != -1:
        neigh = get_neigh(x, y)

        if start:
            basins.append(0)
        else:
            basins[len(basins) - 1] += 1
            mat[x][y] = -1

        for nx, ny, _ in neigh:
            cnt_b(nx, ny)


basins = []

for x in range(len(inp)):
    for y in range(len(inp[0])):
        cnt_b(x, y, True)

basins.sort(reverse=True)

print("Part2:", basins[0] * basins[1] * basins[2])
