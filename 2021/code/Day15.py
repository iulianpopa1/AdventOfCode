from utils import DataFiles
from collections import *
from math import *

import networkx as nx
import numpy as np
import re
import matplotlib.pyplot as plt


dataFiles = DataFiles(__file__)

input = dataFiles.input
inputEX = dataFiles.inputEX

inp = input[:]


def get_neigh_x(x, y, x_min=0, y_min=0, x_max=inf, y_max=inf, diag=False):
    possible_x = [x]
    possible_y = [y]

    possible_x.append(x - 1) if x > x_min else None
    possible_y.append(y - 1) if y > y_min else None
    possible_x.append(x + 1) if x < x_max else None
    possible_y.append(y + 1) if y < y_max else None

    if diag == False:
        return [(a, b) for a in possible_x for b in possible_y if (a, b) != (x, y) and (a != x ^ b != y)]
    else:
        return [(a, b) for a in possible_x for b in possible_y if (a, b) != (x, y)]


def get_neigh(x, y):
    neigh = []

    if x > 0:
        neigh.append((x - 1, y))
    if x < len(mat) - 1:
        neigh.append((x + 1, y))
    if y > 0:
        neigh.append((x, y - 1))
    if y < len(mat[x]) - 1:
        neigh.append((x, y + 1))

    return neigh


def repeatGrid(grid, x):
    rows = len(grid)
    cols = len(grid[0])
    ret = np.zeros((rows * x, cols * x), dtype=int)
    for i in range(rows * x):
        for j in range(cols * x):
            ret[i][j] = grid[i % rows][j % cols] + i // rows + j // cols
            while ret[i][j] > 9:
                ret[i][j] -= 9

    return ret


rows = len(inp)
cols = len(inp[0])
mat = np.zeros((rows, cols), dtype=int)
G = nx.DiGraph()

for x in range(len(inp)):
    for y in range(len(inp[0])):
        mat[x][y] = int(inp[x][y])


# mat = repeatGrid(mat, 5)

for x in range(len(mat)):
    for y in range(len(mat[0])):
        G.add_node((x, y), weight=mat[x, y])

for x in range(len(mat)):
    for y in range(len(mat[0])):
        ngh = get_neigh(x, y)
        print(sorted(ngh))
        ngh2 = get_neigh_x(x, y, x_max=len(mat) - 1, y_max=len(mat[0]) - 1)
        print(sorted(ngh2))
        print()
        for ng_x, ng_y in ngh:
            G.add_edge((x, y), (ng_x, ng_y), weight=mat[ng_x][ng_y])
            G.add_edge((ng_x, ng_y), (x, y), weight=mat[x][y])


start = (0, 0)
end = (len(mat) - 1, len(mat[0]) - 1)

sum = -mat[0][0]
for x in nx.dijkstra_path(G, start, end, weight="weight"):
    sum += mat[x[0]][x[1]]
print(sum)
