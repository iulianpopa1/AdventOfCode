from utils import DataFiles
from collections import *
from math import *

import numpy as np
import re

dataFiles = DataFiles(__file__)

input = dataFiles.input
inputEX = dataFiles.inputEX

inp = input[:]


def mprint(mat):
    print()
    for y in range(len(mat)):
        print("".join(mat[y]))


points = []

sv_l = 0

for line in range(len(inp)):
    if inp[line] == "":
        sv_l = line
        break
    y, x = inp[line].split(",")
    points.append((int(y), int(x)))

folds = []

for line in range(sv_l + 1, len(inp)):
    l = inp[line].split("=")
    folds.append((l[0][-1], int(l[1])))

y_max = max(y for y, _ in points)
x_max = max(x for _, x in points)


rows = x_max + 1
cols = y_max + 1
mat = np.empty((rows, cols), dtype=str)
mat.fill(".")

for x, y in points:
    mat[y][x] = "#"


def fold(mat, line, line_v):
    if line == "y":
        for x in range(len(mat[0])):
            mat[line_v][x] = "-"

        for y in range(line_v):
            for x in range(len(mat[0])):
                if mat[2 * line_v - y][x] == "#":
                    mat[y][x] = "#"

        mat = mat[
            : -line_v - 1 :,
        ]
    else:
        for y in range(len(mat)):
            mat[y][line_v] = "|"

        for x in range(line_v):
            for y in range(len(mat)):
                if mat[y][2 * line_v - x] == "#":
                    mat[y][x] = "#"

        mat = mat[:, : -line_v - 1]

    return mat


mat_p1 = fold(mat, folds[0][0], folds[0][1])
ans = 0
for y in range(len(mat_p1)):
    for x in range(len(mat_p1[0])):
        if mat_p1[y][x] == "#":
            ans += 1

for l in range(len(folds)):
    mat = fold(mat, folds[l][0], folds[l][1])
    mprint(mat)

print("Part1:", ans)
exit()
