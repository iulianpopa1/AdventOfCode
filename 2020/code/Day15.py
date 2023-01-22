from utils import DataFiles
import collections


dataFiles = DataFiles(__file__)

input = dataFiles.get_input()  # inputRaw = dataFiles.input
inputEX = dataFiles.get_inputEX()  # inputRawEX = dataFiles.inputEX

data = [int(x) for x in input[0].strip().split(',')]

def solve(data, end):
    spoken = {x: i for i, x in enumerate(data[:-1])}
    prev = data[-1]
    for turn in range(len(data), end):
        if prev in spoken.keys():
            prev_spoken = spoken[prev]
            next = turn - prev_spoken - 1
        else:
            next = 0
        
        spoken[prev] = turn - 1
        prev = next
    return prev

print('Part1:', solve(data, 2020))
print('Part2:', solve(data, 30000000))
