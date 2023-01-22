from utils import DataFiles

dataFiles = DataFiles(__file__)

input = dataFiles.get_input_chunks(sep="\n\n")
inputEX = dataFiles.get_input_chunks(example=True)

all_calories = []

for chunk in input:
    total_calories = 0

    for line in chunk.splitlines():
        total_calories += int(line)

    all_calories.append(total_calories)

all_calories.sort(reverse=True)

print("Part 1:", all_calories[0])
print("Part 2:", sum(all_calories[:3]))
