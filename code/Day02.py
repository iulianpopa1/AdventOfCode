from utils import DataFiles

dataFiles = DataFiles(__file__)

input = dataFiles.input
inputEX = dataFiles.inputEX

inp = input

# Part 1
hor = 0
dep = 0

for i in range(len(inp)):
    dir = inp[i].split()[0]
    x = int(inp[i].split()[1])

    if dir == "forward":
        hor += x

    if dir == "down":
        dep += x
    if dir == "up":
        dep -= x

print("Part 1:", dep * hor)

# Part 2
hor = 0
dep = 0
aim = 0

for i in range(len(inp)):
    dir = inp[i].split()[0]
    x = int(inp[i].split()[1])

    if dir == "forward":
        hor += x
        dep += aim * x

    if dir == "down":
        aim += x
    if dir == "up":
        aim -= x

print("Part 2:", dep * hor)
