from utils import DataFiles
from collections import *
from math import *

import numpy as np
import re

dataFiles = DataFiles(__file__)

input = dataFiles.input
inputEX = dataFiles.inputEX

inp = input[:]

open_br = "({[<"
close_br = ")}]>"

ch_score_p1 = {"": 0, ")": 3, "]": 57, "}": 1197, ">": 25137}
ch_score_p2 = {"": 0, "(": 1, "[": 2, "{": 3, "<": 4}

map_br = dict(zip(open_br, close_br))

line_scores = []


def calc_score_part2(my_string):
    ans = 0
    for c in reversed(my_string):
        ans = ans * 5 + ch_score_p2[c]

    return ans


def get_first_incorrect(line):
    stack = []

    # Part 1
    for ch in line:
        if ch in open_br:
            stack.append(ch)
        elif ch in close_br:
            if stack == [] or ch != map_br[stack.pop()]:
                return ch

    # Part 2
    if all(ch in open_br for ch in stack):
        line_scores.append(calc_score_part2(stack))

    return ""


print("Part1:", sum(ch_score_p1[get_first_incorrect(line)] for line in inp))
line_scores.sort()
print("Part2:", line_scores[len(line_scores) // 2])


### Another approach for PART 2
incomplete_lines = {}


def is_incomplete(line):
    brackets = ["".join(br) for br in zip(open_br, close_br)]

    while any(br in line for br in brackets):
        for br in brackets:
            line = line.replace(br, "")

    if line != "" and set(line).issubset(open_br):
        return line

    return ""


for string in inp:
    aux = is_incomplete(string)
    if aux != "":
        incomplete_lines[string] = aux


ans = [calc_score_part2(v) for _, v in incomplete_lines.items()]
ans.sort()

print("Part2:", ans[len(ans) // 2])
