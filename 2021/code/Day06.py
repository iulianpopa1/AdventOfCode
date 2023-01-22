from utils import DataFiles
from collections import *

dataFiles = DataFiles(__file__)

input = dataFiles.input
inputEX = dataFiles.inputEX

inp = input[:]
inpp = [int(x) for x in inp[0].split(",")]


def simulate(values, days):
    fishes = defaultdict(int)
    for x in values:
        fishes[x] += 1

    for _ in range(days):
        aux = defaultdict(int)
        for k, v in fishes.items():
            if k == 0:
                aux[6] += v
                aux[8] += v
            else:
                aux[k - 1] += v

        fishes = aux

    return sum(fishes.values())


print("Part 1:", simulate(inpp, 80))
print("Part 2:", simulate(inpp, 256))
