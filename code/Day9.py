import numpy as np
from utils import DataFiles

dataFiles = DataFiles(__file__)

input = dataFiles.get_input()  # inputRaw = dataFiles.input
inputEX = dataFiles.get_inputEX()  # inputRawEX = dataFiles.inputEX
inputRaw = dataFiles.input
inputRawEX = dataFiles.inputEX

numbers = inputEX

numbers = [int(line) for line in input]
preamble = 25
p1 = 0
p2 = 0

for i, nr_i in enumerate(numbers[preamble:]):
    sums = set()

    for j, nr_j in enumerate(numbers[i: i + preamble]):
        for k, nr_k in enumerate(numbers[j + 1: i + preamble]):
            sums.add(nr_j + nr_k)

    if nr_i not in sums:
        p1 = nr_i

print('Part 1:', p1)

for i in range(len(numbers)):
    for j in range(i + 2, len(numbers)):
        aux = numbers[i: j]

        if sum(aux) == p1:
            p2 = min(aux) + max(aux)

print('Part 2:', p2)

# TODO: use numpy.array
