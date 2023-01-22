from os import replace
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


def parse_inp(inp):
    new = list(inp[1])
    for i in range(len(new)):
        if inp[2][i].isalpha():
            new[i] = inp[2][i] + inp[3][i]
    new = new[1:-1]
    return new


def inp_to_target(inp):
    new = inp
    for i in range(len(inp)):
        if inp[i].isalpha():
            new[i] = len(inp[i]) * target_pos[i]
    return new


costs = {"A": 1, "B": 10, "C": 100, "D": 1000}
target = {"A": 2, "B": 4, "C": 6, "D": 8}
target_pos = {2: "A", 4: "B", 6: "C", 8: "D"}
targetSpaces = set(target.values())


target_map = copy.deepcopy(inp)
for letter, positions in target.items():
    target_map[positions[0][0]][positions[0][1]] = "A"
    target_map[positions[1][0]][positions[1][1]] = "B"

print(target_map)
exit()


def find_letters_pos(mat):
    psb = []
    for x in range(len(mat)):
        for y in range(len(mat[0])):
            if mat[x][y].isalpha():
                psb.append((x, y))
    return psb


def find_possible_moves(mat, pos):
    dx = [-1, +1, 0, 0]
    dy = [0, 0, -1, +1]
    psb = []

    for i in range(4):
        x_aux = pos[0] + dx[i]
        y_aux = pos[1] + dy[i]

        if 0 <= x_aux < len(mat) and 0 <= y_aux < len(mat[0]):
            if mat[x_aux][y_aux] == ".":
                psb.append((x_aux, y_aux))

    return psb


def hsh(mat):
    s = ""
    for line in mat:
        s += "".join([x for x in line])

    return hash(s)


target_hsh = hsh(target_map)
hashed = {hsh(inp): {"A": 0, "B": 0, "C": 0, "D": 0}}


def run(mat, cost):
    for ltr_pos in find_letters_pos(mat):
        mvs = find_possible_moves(mat, ltr_pos)
        if len(mvs) > 0:
            for fnd_mv in mvs:
                aux_mat = copy.deepcopy(mat)
                aux_cost = copy.deepcopy(cost)
                aux_mat[fnd_mv[0]][fnd_mv[1]] = mat[ltr_pos[0]][ltr_pos[1]]
                aux_mat[ltr_pos[0]][ltr_pos[1]] = "."
                aux_cost[mat[ltr_pos[0]][ltr_pos[1]]] += 1
                # print(cost)
                # mprint(mat)
                # mprint(aux_mat)
                aux_hsh = hsh(aux_mat)
                if aux_hsh == target_hsh:
                    print("FOUND", aux_cost)

                # print(aux_hsh, aux_cost)
                if (
                    aux_hsh in hashed.keys()
                    or aux_cost["A"] > 25
                    or aux_cost["B"] > 14
                    or aux_cost["C"] > 9
                    or aux_cost["D"] > 17
                ):
                    continue
                else:
                    hashed[aux_hsh] = aux_cost
                    # mprint(aux_mat)
                    run(aux_mat, aux_cost)


mat = copy.deepcopy(inp)
run(mat, {"A": 0, "B": 0, "C": 0, "D": 0})


print(hashed.items())
