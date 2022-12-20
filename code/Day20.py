from utils import DataFiles
import copy

dataFiles = DataFiles(__file__)

input = dataFiles.get_input(splitlines=True)  # dataFiles.get_input_chunks(sep="\n\n")
inputEX = dataFiles.get_input(splitlines=True, example=True)

numbers = []
for i, nr in enumerate(input):
    numbers.append((int(nr), i))


def run(numbers):
    n = len(numbers)

    for i in range(n):
        for j in range(n):
            if numbers[j][1] == i:
                break

        aux = numbers.pop(j)[0]
        j = (j + aux) % (n - 1)
        numbers.insert(j, (aux, i))

    for z in range(n):
        if numbers[z][0] == 0:
            break

    return numbers[(z + 1000) % n][0] + numbers[(z + 2000) % n][0] + numbers[(z + 3000) % n][0]


nrs = copy.copy(numbers)
print("Part1:", run(nrs))

nrs = copy.copy(numbers)
nrs = [(nr * 811589153, i) for nr, i in nrs]

for i in range(10):
    ans = run(nrs)

print("Part2:", ans)
