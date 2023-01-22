from utils import DataFiles
from collections import *
from math import *

import numpy as np
import re

dataFiles = DataFiles(__file__)

input = dataFiles.input
inputEX = dataFiles.inputEX

inp = input[:]

template = inp[0]

rules = defaultdict(str)
for line in range(2, len(inp)):
    left, right = inp[line].split(" -> ")
    rules[left] = right

pairs_cnt = defaultdict(int)
for i in range(len(template) - 1):
    pairs_cnt[template[i : i + 2]] += 1


conversions = defaultdict(str)
for left, right in rules.items():
    conversions[left] = [left[0] + right, right + left[1]]

s1 = template[:2]
s2 = template[-2:]

for step in range(40):
    pairs_cnt_aux = defaultdict(int)
    for left, right in pairs_cnt.items():
        for new_pair in conversions[left]:
            pairs_cnt_aux[new_pair] += right

    s1 = s1[0] + rules[s1]
    s2 = rules[s2] + s2[1]

    pairs_cnt = pairs_cnt_aux

count = defaultdict(int)

for left, right in pairs_cnt.items():
    count[left[0]] += right
    count[left[1]] += right

count[s1[0]] += 1
count[s2[1]] += 1

for k, v in count.items():
    count[k] = v // 2

min_v = min(count.values())
max_v = max(count.values())
print("Part2:", max_v - min_v)
