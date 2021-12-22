from utils import DataFiles
from collections import *
from math import *
import itertools

import numpy as np
import re

dataFiles = DataFiles(__file__)

input = dataFiles.input
inputEX = dataFiles.inputEX

inp = inputEX[:]


def mod10(x):
    return ((x - 1) % 10) + 1


p1 = 4
p2 = 2
cnt = 0
pos = [p1, p2]
score = [0, 0]

for i in range(1000):
    pos[i % 2] = mod10(pos[i % 2] + (cnt * 3 + 3) % 100 + 3)
    score[i % 2] += pos[i % 2]
    cnt += 3
    if score[i % 2] >= 1000:
        break

print(min(score) * cnt)


def update_tuple(old, turn, new):
    return ([new, old[0]][turn], [old[1], new][turn])


moves = {
    3: 1,
    4: 3,
    5: 6,
    6: 7,
    7: 6,
    8: 3,
    9: 1,
}

all_scores = [0, 0]
universes = {((0, 0), (p1, p2), 0): 1}

while universes:
    for (score, pos, turn), old_count in sorted(universes.items()):
        _ = universes.pop((score, pos, turn))

        for move, count in moves.items():
            new_pos = mod10(pos[turn] + move)
            new_score = score[turn] + new_pos
            new_count = old_count * count

            if new_score >= 21:
                all_scores[turn] += new_count
            else:
                next_pos = update_tuple(pos, turn, new_pos)
                next_score = update_tuple(score, turn, new_score)
                next_key = (next_score, next_pos, (turn + 1) % 2)

                universes[next_key] = universes.get(next_key, 0) + new_count

print(max(all_scores))
