import re
from utils import DataFiles

dataFiles = DataFiles(__file__)

input = dataFiles.get_input()  # inputRaw = dataFiles.input
inputEx = dataFiles.get_inputEX()  # inputRawEX = dataFiles.inputEX

p1 = 0
p2 = 0

reg = re.compile(r'(\d+)-(\d+) ([a-z]): ([a-z]+)')

for pwd in input:
    groups = reg.match(pwd).groups()
    lo = int(groups[0])
    hi = int(groups[1])
    ch = groups[2]
    word = groups[3]
    
    if lo <= word.count(ch) <= hi:
        p1 += 1

    if ((word[lo-1] == ch) != (word[hi-1] == ch)):
        p2 += 1

print('Part 1: ', p1)
print('Part 2: ', p2)
