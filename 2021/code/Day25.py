from utils import DataFiles
from collections import *
from math import *
import copy

import numpy as np
import re

dataFiles = DataFiles(__file__)

input = dataFiles.input
inputEX = dataFiles.inputEX

inp = input[:]


mat = []
for line in inp:
    mat.append(line)

rows = len(mat)
cols = len(mat[0])

step = 0
while True:
    step += 1
    moved = False

    mat_aux_h = [[mat[r][c] for c in range(cols)] for r in range(rows)]

    for r in range(rows):
        for c in range(cols):
            if mat[r][c] == ">":
                if mat[r][(c + 1) % cols] == ".":
                    moved = True
                    mat_aux_h[r][(c + 1) % cols] = ">"
                    mat_aux_h[r][c] = "."

    mat_aux_v = [[mat_aux_h[r][c] for c in range(cols)] for r in range(rows)]

    for r in range(rows):
        for c in range(cols):
            if mat_aux_h[r][c] == "v" and mat_aux_h[(r + 1) % rows][c] == ".":
                moved = True
                mat_aux_v[(r + 1) % rows][c] = "v"
                mat_aux_v[r][c] = "."

    if not moved:
        print(step)
        exit()

    mat = mat_aux_v
