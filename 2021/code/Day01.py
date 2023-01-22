from utils import DataFiles

dataFiles = DataFiles(__file__)

input = dataFiles.input
inputEX = dataFiles.inputEX

counter1 = 0

for i in range(1, len(input)):
    if int(input[i - 1]) < int(input[i]):
        counter1 += 1

print("Part 1:", counter1)

counter2 = 0

for i in range(3, len(input)):
    # if input[i - 3] < input[i]:
    if int(input[i - 3]) + int(input[i - 2]) + int(input[i - 1]) < int(input[i - 2]) + int(input[i - 1]) + int(
        input[i]
    ):
        counter2 += 1

print("Part 2:", counter2)
