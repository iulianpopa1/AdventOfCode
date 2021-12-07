from utils import DataFiles
from collections import *
from numpy import *
from math import *

dataFiles = DataFiles(__file__)

input = dataFiles.input
inputEX = dataFiles.inputEX

inp = input[:]
inpp = [int(x) for x in inp[0].split(",")]

best = math.inf
for j in range(min(inpp), max(inpp)):
    possible = sum([abs(x - j) for x in inpp])
    best = min(best, possible)

print("Part1:", best)


best = math.inf
for j in range(min(inpp), max(inpp)):
    possible = sum([abs(x - j) * (abs(x - j) + 1) // 2 for x in inpp])
    best = min(best, possible)

print("Part2:", best)
