from typing import DefaultDict
from utils import DataFiles
from collections import *

dataFiles = DataFiles(__file__)

input = dataFiles.input
inputEX = dataFiles.inputEX

inp = input[:]

print(inp)

inpp = [int(x) for x in inp[0].split(",")]

for day in range(80):
    to_add = 0
    for i in range(len(inpp)):
        if inpp[i] == 0:
            inpp[i] = 6
            to_add += 1
        else:
            inpp[i] -= 1

    for _ in range(to_add):
        inpp.append(8)


print(len(inpp))


fish = defaultdict(int)
for x in inpp:
    fish[x] += 1

for day in range(256):
    aux = defaultdict(int)
    for k, v in fish.items():
        if k == 0:
            aux[6] += v
            aux[8] += v
        else:
            aux[k - 1] += v

    fish = aux
    # print(counts.values())

print(sum(fish.values()))
