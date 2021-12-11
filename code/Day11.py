from utils import DataFiles
from collections import *
from math import *
from copy import copy, deepcopy


import numpy as np
import re

dataFiles = DataFiles(__file__)

input = dataFiles.input
inputEX = dataFiles.inputEX

inp = input[:]

rows = len(inp)
cols = len(inp[0])
mat = np.zeros((rows, cols), dtype=int)

for x in range(len(inp)):
    for y in range(len(inp[0])):
        mat[x][y] = inp[x][y]


def get_neigh(x, y):
    neigh = []

    if x > 0:
        neigh.append((x - 1, y))
        if y > 0:
            neigh.append((x - 1, y - 1))
    if x < len(mat) - 1:
        neigh.append((x + 1, y))
        if y < len(mat[x]) - 1:
            neigh.append((x + 1, y + 1))
    if y > 0:
        neigh.append((x, y - 1))
        if x < len(mat) - 1:
            neigh.append((x + 1, y - 1))
    if y < len(mat[x]) - 1:
        neigh.append((x, y + 1))
        if x > 0:
            neigh.append((x - 1, y + 1))

    return neigh


print(mat)


def mprint(mat):
    for x in range(len(inp)):
        st = ""
        for y in range(len(inp[0])):
            st += str(mat[x][y])
        print(st)


cnt = 0


def iterate(mat):
    mat2 = deepcopy(mat)
    flash = []
    all_flash = []

    for x in range(len(inp)):
        for y in range(len(inp[0])):
            if mat2[x][y] == 9:
                flash.append((x, y))
                all_flash.append((x, y))
            else:
                mat2[x][y] += 1

    while len(flash) > 0:
        x, y = flash.pop()
        neigh = get_neigh(x, y)

        for xn, yn in neigh:
            if mat2[xn][yn] == 9:
                if (xn, yn) not in all_flash:
                    flash.append((xn, yn))
                    all_flash.append((xn, yn))
            else:
                mat2[xn][yn] += 1

    for x, y in all_flash:
        mat2[x][y] = 0

    if len(all_flash) == 100:
        print("all_flash", len(all_flash))
    return mat2, len(all_flash)


for i in range(1, 300):
    print("\n", i)
    mat, aux = deepcopy(iterate(mat))

    cnt += aux
print(cnt)
