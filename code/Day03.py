from utils import DataFiles
import numpy
from collections import *

dataFiles = DataFiles(__file__)

input = dataFiles.input
inputEX = dataFiles.inputEX

inp = input[:]

# Initialize the count array
cnt = numpy.zeros((len(inp[0]), 2), numpy.int)

# Count 0s and 1s
for i in range(len(inp)):
    for j in range(len(inp[i])):
        if inp[i][j] == "0":
            cnt[j][0] += 1
        else:
            cnt[j][1] += 1

gamma = ""
epsilon = ""

# Create 'gamma' and 'epsilon' rates
for j in range(len(inp[0])):
    if int(cnt[j][0]) < int(cnt[j][1]):
        gamma += "1"
        epsilon += "0"
    else:
        gamma += "0"
        epsilon += "1"


print("Part 1: ", int(gamma, 2) * int(epsilon, 2))

# part2
inp = input[:]
for j in range(len(inp[0])):
    del cnt
    cnt = numpy.zeros((len(inp[0]), 2), numpy.int)

    for i2 in range(len(inp)):
        for j2 in range(len(inp[i2])):
            if inp[i2][j2] == "0":
                cnt[j2][0] += 1
            else:
                cnt[j2][1] += 1

    if int(cnt[j][1]) >= int(cnt[j][0]):
        inp = [x for x in inp if x[j] == "1"]
    else:
        inp = [x for x in inp if x[j] == "0"]

    if len(inp) == 1:
        gamma = inp[0]
        break

inp = input[:]

for j in range(len(inp[0])):
    cnt = numpy.zeros((len(inp[0]), 2), numpy.int)

    for i2 in range(len(inp)):
        for j2 in range(len(inp[i2])):
            if inp[i2][j2] == "0":
                cnt[j2][0] += 1
            else:
                cnt[j2][1] += 1

    if int(cnt[j][0]) <= int(cnt[j][1]):
        inp = [x for x in inp if x[j] == "0"]
    else:
        inp = [x for x in inp if x[j] == "1"]

    if len(inp) == 1:
        epsilon = inp[0]
        break

print("Part 2: ", int(gamma, 2) * int(epsilon, 2))


### TRYHARD
inp = input[:]
gamma = ""
epsilon = ""

# Transpose the matrix
for x in ["".join(s) for s in zip(*inp)]:
    condition_evaluation = x.count("0") < x.count("1")
    gamma += str(int(condition_evaluation))
    epsilon += str(int(not (condition_evaluation)))

print("Part 1: ", int(gamma, 2) * int(epsilon, 2))

# Part 2
inp_oxygen = input[:]
inp_co2 = input[:]

for pos in range(len(inp_oxygen[0])):
    trans_gamma = ["".join(s) for s in zip(*inp_oxygen)]
    more = 1 - int(min(trans_gamma[pos], key=trans_gamma[pos].count))
    inp_oxygen = [x for x in inp_oxygen if x[pos] == str(more)]

    trans_gamma = ["".join(s) for s in zip(*inp_co2)]
    fewer = int(min(trans_gamma[pos], key=trans_gamma[pos].count))
    inp_co2 = [x for x in inp_co2 if x[pos] == str(fewer)]

print("Part 2: ", int(inp_oxygen[0], 2) * int(inp_co2[0], 2))
