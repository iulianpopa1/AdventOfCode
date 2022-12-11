from utils import DataFiles
import numpy as np

dataFiles = DataFiles(__file__)

input = dataFiles.get_input(splitlines=True)  # dataFiles.get_input_chunks(sep="\n\n")
inputEX = dataFiles.get_input(splitlines=True, example=True)


def find_common_letters(items):
    to_return = set(items[0])

    for item in items:
        to_return &= set(item)

    return to_return


p1, p2 = 0

for rucksack in input:
    half_splits = [rucksack[: len(rucksack) // 2], rucksack[len(rucksack) // 2 :]]

    common = list(find_common_letters(half_splits))

    if common[0].islower():
        p1 += ord(common[0]) - ord("a") + 1
    else:
        p1 += ord(common[0]) - ord("A") + 26 + 1


# for pos in range(len(input) // 3):
#   common = list(find_common_letters(input[pos * 3 : pos * 3 + 2]))
for chunk_of_3 in np.reshape(input, (len(input) // 3, 3)):
    common = list(find_common_letters(chunk_of_3))

    if common[0].islower():
        p2 += ord(common[0]) - ord("a") + 1
    else:
        p2 += ord(common[0]) - ord("A") + 26 + 1

print("Part1:", p1)
print("Part2:", p2)
