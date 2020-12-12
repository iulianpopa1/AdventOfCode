from utils import DataFiles

dataFiles = DataFiles(__file__)

input = dataFiles.get_input()  # inputRaw = dataFiles.input
inputEx = dataFiles.get_inputEX()  # inputRawEX = dataFiles.inputEX

i = 0

while(i < len(input)):
    j = i + 1
    while(j < len(input)):
        if int(input[i]) + int(input[j]) == 2020:
            print('Part 1: ', int(input[i]) * int(input[j]))
        j += 1
    i += 1

i = 0
while(i < len(input)):
    j = i + 1
    while(j < len(input)):
        k = j + 1
        while(k < len(input)):
            if int(input[i]) + int(input[j]) + int(input[k]) == 2020:
                print('Part 2: ', int(input[i]) * int(input[j]) * int(input[k]))
            k += 1
        j += 1
    i += 1

p1 = 0
p2 = 0

for i in input:
    a = int(i)
    for j in input:
        b = int(j)
        if(i != j and a + b == 2020):
            p1 = a * b
        for k in input:
            c = int(k)
            if(i != j != k and a + b + c == 2020):
                p2 = a * b * c

print('Part 1:', p1)
print('Part 2:', p2)
