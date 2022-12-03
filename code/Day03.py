from utils import DataFiles
import numpy as np

dataFiles = DataFiles(__file__)

input = dataFiles.get_input(splitlines=True)  # dataFiles.get_input_chunks(sep="\n\n")
inputEX = dataFiles.get_input(splitlines=True, example=True)

p1 = 0

for rucksack in input:
    ruk_1, ruk_2 = rucksack[: len(rucksack) // 2], rucksack[len(rucksack) // 2 :]

    common = list(set(ruk_1) & set(ruk_2))

    if common[0].islower():
        p1 += ord(common[0]) - 97 + 1
    else:
        p1 += ord(common[0]) - 65 + 26 + 1

print("Part1:", p1)


p2 = 0

# for pos in range(len(input) // 3):
#     ruk_1, ruk_2, ruk_3 = input[pos * 3], input[pos * 3 + 1], input[pos * 3 + 2]
for chunk_of_3 in np.reshape(input, (len(input) // 3, 3)):
    common = list(set(chunk_of_3[0]) & set(chunk_of_3[1]) & set(chunk_of_3[2]))

    if common[0].islower():
        p2 += ord(common[0]) - 96
    else:
        p2 += ord(common[0]) - 65 + 27

print("Part2:", p2)
