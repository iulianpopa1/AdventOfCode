from utils import DataFiles

dataFiles = DataFiles(__file__)

input = dataFiles.get_input(splitlines=True)  # dataFiles.get_input_chunks(sep="\n\n")
inputEX = dataFiles.get_input(splitlines=True, example=True)


data = input[0]

for i in range(len(data) - 4):
    test = data[i : i + 4]
    if len(set(test)) == len(test):
        print("Part1: %d" % (i + 4))
        break

for i in range(len(data) - 14):
    test = data[i : i + 14]
    if len(set(test)) == len(test):
        print("Part2: %d" % (i + 14))
        break
