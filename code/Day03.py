from utils import DataFiles
import numpy

dataFiles = DataFiles(__file__)

input = dataFiles.input
inputEX = dataFiles.inputEX

inp = input

v1 = numpy.empty((100, 2))
v1.fill(0)


for i in range(len(inp)):
    for j in range(len(inp[i])):
        if inp[i][j] == "0":
            v1[j][0] += 1
        else:
            v1[j][1] += 1


ans_gamm = ""
ans_eps = ""

for j in range(len(inp[0])):
    if int(v1[j][0]) > int(v1[j][1]):
        ans_gamm += "0"
        ans_eps += "1"
    else:
        ans_gamm += "1"
        ans_eps += "0"


print(int(ans_gamm, 2) * int(ans_eps, 2))

# part2


n1 = ""
n2 = ""

inp2 = inp.copy()
for j in range(len(inp[0])):
    v2 = numpy.empty((100, 2))
    v2.fill(0)

    for i2 in range(len(inp2)):
        for j2 in range(len(inp2[i2])):
            if inp2[i2][j2] == "0":
                v2[j2][0] += 1
            else:
                v2[j2][1] += 1

    if int(v2[j][1]) >= int(v2[j][0]):
        inp2 = [x for x in inp2 if x[j] == "1"]
    else:
        inp2 = [x for x in inp2 if x[j] == "0"]

    print(inp2)

    if len(inp2) == 1:
        n1 = inp2[0]
        print("n1 : ", n1, int(n1, 2))

del inp2
inp2 = inp.copy()

for j in range(len(inp[0])):
    v2 = numpy.empty((100, 2))
    v2.fill(0)

    for i2 in range(len(inp2)):
        for j2 in range(len(inp2[i2])):
            if inp2[i2][j2] == "0":
                v2[j2][0] += 1
            else:
                v2[j2][1] += 1

    if int(v2[j][0]) <= int(v2[j][1]):
        inp2 = [x for x in inp2 if x[j] == "0"]
    else:
        inp2 = [x for x in inp2 if x[j] == "1"]

    print(inp2)

    if len(inp2) == 1:
        n2 = inp2[0]
        print("n2 : ", n1, int(n2, 2))

print(int(n1, 2) * int(n2, 2))
