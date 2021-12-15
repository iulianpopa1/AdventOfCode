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


mat = repeatGrid(mat, 5)

for x in range(len(mat)):
    for y in range(len(mat[0])):
        G.add_node((x, y), weight=mat[x, y])

for x in range(len(mat)):
    for y in range(len(mat[0])):
        ngh = get_neigh(x, y)
        for ng_x, ng_y in ngh:
            G.add_edge((x, y), (ng_x, ng_y), weight=mat[ng_x][ng_y])
            G.add_edge((ng_x, ng_y), (x, y), weight=mat[x][y])


start = (0, 0)
end = (len(mat) - 1, len(mat[0]) - 1)

sum = -mat[0][0]
for x in nx.dijkstra_path(G, start, end, weight="weight"):
    sum += mat[x[0]][x[1]]
print(sum)
