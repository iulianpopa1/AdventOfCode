from utils import DataFiles

dataFiles = DataFiles(__file__)

input = dataFiles.get_input(splitlines=True)  # dataFiles.get_input_chunks(sep="\n\n")
inputEX = dataFiles.get_input(splitlines=True, example=True)


instr_queue = []
for line in input:
    instr_queue.append(0)

    aux = line.split()
    if aux[0] == "addx":
        instr_queue.append(int(aux[1]))


x = 1
signals_strength_sum = 0

for cycle in range(len(instr_queue)):
    if cycle % 40 == 19:
        signals_strength_sum += (cycle + 1) * x

    x += instr_queue[cycle]

print(signals_strength_sum)


x = 1
for cycle in range(len(instr_queue)):
    if cycle % 40 in [x - 1, x, x + 1]:
        print("#", end="")
    else:
        print(" ", end="")

    if cycle % 40 == 39:
        print()

    x += instr_queue[cycle]
