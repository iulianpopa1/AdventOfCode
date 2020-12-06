from functools import reduce
import string
from utils import DataFiles

dataFiles = DataFiles(__file__)

inputRaw = dataFiles.input
inputRawEX = dataFiles.inputEX
input = inputRaw.read().split('\n\n')
inputEX = inputRawEX.read().split('\n\n')

alpha = list(string.ascii_lowercase)

p1 = 0
p2 = 0

for line in input:
    for char in alpha:
        #Part 1
        if char in line:
            p1 += 1
        
        #Part 2
        every = True

        for z in line.split('\n'):
            if char not in z:
                every = False

        if every == True:
            p2 += 1

print('Part 1:', p1)
print('Part 2:', p2)