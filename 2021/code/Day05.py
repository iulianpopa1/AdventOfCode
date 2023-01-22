from utils import DataFiles
import collections
import numpy as np

dataFiles = DataFiles(__file__)

input = dataFiles.input
inputEX = dataFiles.inputEX

inp = input[:]

vents = [[[int(y) for y in x.split(",")] for x in ln.split(" -> ")] for ln in inp]

map = collections.defaultdict(int)

for (x1, y1), (x2, y2) in vents:
    if (x1 == x2) or (y1 == y2):
        dx = x1 != x2
        dy = y1 != y2
        r = abs(x2 - x1) + abs(y2 - y1) + 1
        for k in range(r):
            map[min(x1, x2) + k * dx, min(y1, y2) + k * dy] += 1

print("Part 1:", sum(1 for x in map.values() if x > 1))

for (x1, y1), (x2, y2) in vents:
    if (x1 != x2) and (y1 != y2):
        dx = np.sign(x2 - x1)
        dy = np.sign(y2 - y1)
        r = abs(x2 - x1) + 1
        for k in range(r):
            map[x1 + dx * k, y1 + dy * k] += 1

print("Part 2:", sum(1 for x in map.values() if x > 1))
