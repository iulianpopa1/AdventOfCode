import enum
from utils import DataFiles
from collections import *
from math import *

import numpy as np
import re

dataFiles = DataFiles(__file__)

input = dataFiles.input
inputEX = dataFiles.inputEX

inp = inputEX[:]


def split_inp(inp):
    new_inp = []
    index = 0
    aux = [inp[0]]

    for line in inp[1:]:
        if line[:3] == "inp":
            new_inp.append(aux[:])
            aux.clear()
        else:
            aux.append(line)

    new_inp.append(aux[:])
    aux.clear()

    return new_inp


inp = split_inp(inp)


def run_line(line):
    command = line.split()
    op = command[0]
    a = command[1]
    if len(command) > 2:
        b = command[2]

    if op == "inp":
        pass
    elif op == "add":
        pass
    elif op == "mul":
        pass
    elif op == "div":
        pass
    elif op == "mod":
        pass
    elif op == "eql":
        pass


w, x, y, z = 0, 0, 0, 0

# for i in inp:
#     run_line(i)

blocks = [block.split("\n") for block in open("input/24.txt").read().split("inp w\n")[1:]]
model_max = [0] * 14
model_min = [0] * 14
stack = []
for i, block in enumerate(blocks):
    if block[3] == "div z 1":
        stack.append((i, int(block[14].split(" ")[-1])))  # add y <val>
    elif block[3] == "div z 26":
        j, x = stack.pop()
        diff = x + int(block[4].split(" ")[-1])  # add x <-val>
        if diff < 0:
            i, j, diff = j, i, -diff
        model_max[i] = 9
        model_max[j] = 9 - diff
        model_min[i] = 1 + diff
        model_min[j] = 1
print("".join(map(str, model_max)))
print("".join(map(str, model_min)))
