from utils import DataFiles
from collections import *
from numpy import *
from math import *

dataFiles = DataFiles(__file__)

input = dataFiles.input
inputEX = dataFiles.inputEX

inp = input[:]

cnt = defaultdict(int)

for x in inp:
    s = x.split("|")[1].split()
    for y in s:
        cnt[len(set(y))] += 1

print("Part1:", cnt[2] + cnt[3] + cnt[4] + cnt[7])

ans = 0
for x in inp:
    s1 = [set(x) for x in x.split("|")[0].split()]
    s2 = [set(x) for x in x.split("|")[1].split()]

    d = defaultdict()

    d[1] = next(nr for nr in s1 if len(nr) == 2)
    d[4] = next(nr for nr in s1 if len(nr) == 4)
    d[7] = next(nr for nr in s1 if len(nr) == 3)
    d[8] = next(nr for nr in s1 if len(nr) == 7)
    d[9] = next(nr for nr in s1 if len(nr) == 6 and len((nr) - set.union(d[4], d[7])) == 1)
    d[0] = next(nr for nr in s1 if len(nr) == 6 and nr != d[9] and set(d[7]).issubset(nr))
    d[2] = next(nr for nr in s1 if len(nr) == 5 and len(d[8] - d[9]) == 1 and str((d[8] - d[9]).pop()) in nr)
    d[3] = next(nr for nr in s1 if len(nr) == 5 and set(d[7]).issubset(nr))
    d[5] = next(nr for nr in s1 if len(nr) == 5 and nr != d[2] and nr != d[3])
    d[6] = next(nr for nr in s1 if len(nr) == 6 and nr != d[9] and nr != d[0])

    digits = [v for _, v in sorted(d.items())]

    number = 0
    for nr in s2:
        number = number * 10 + digits.index(nr)

    ans += number

print("Part2:", ans)
