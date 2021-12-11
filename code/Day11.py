from numpy.lib.twodim_base import diag
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


def get_neigh_x(x, y, x_min=0, y_min=0, x_max=inf, y_max=inf, diag=False):
    possible_x = [x]
    possible_y = [y]

    possible_x.append(x - 1) if x > x_min else None
    possible_x.append(x + 1) if x < x_max else None
    possible_y.append(y - 1) if y > y_min else None
    possible_y.append(y + 1) if y < y_max else None

    if diag == False:
        return [(a, b) for a in possible_x for b in possible_y if (a, b) != (x, y) and (a != x ^ b != y)]
    else:
        return [(a, b) for a in possible_x for b in possible_y if (a, b) != (x, y)]


def iterate(mat):
    aux_mat = deepcopy(mat)

    flash = []
    all_flash = []

    for x in range(len(inp)):
        for y in range(len(inp[0])):
            aux_mat[x][y] += 1
            if aux_mat[x][y] > 9:
                flash.append((x, y))
                all_flash.append((x, y))

    while len(flash) > 0:
        x, y = flash.pop()
        neigh = get_neigh_x(x, y, x_max=len(inp) - 1, y_max=len(inp[0]) - 1, diag=True)
        for xn, yn in neigh:
            aux_mat[xn][yn] += 1
            if aux_mat[xn][yn] > 9 and (xn, yn) not in all_flash:
                flash.append((xn, yn))
                all_flash.append((xn, yn))

    for x, y in all_flash:
        aux_mat[x][y] = 0

    if len(all_flash) == 100:
        return aux_mat, len(all_flash), True

    return aux_mat, len(all_flash), False


cnt = 0

for i in range(1, 300):
    mat, aux, part2_check = deepcopy(iterate(mat))
    cnt += aux

    if i == 100:
        print("Part1:", cnt)
    if part2_check == True:
        print("Part2:", i)
        exit()
