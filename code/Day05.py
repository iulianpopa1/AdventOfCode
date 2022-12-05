from utils import DataFiles
import re

dataFiles = DataFiles(__file__)

input = dataFiles.get_input_chunks(sep="\n\n")
inputEX = dataFiles.get_input_chunks(sep="\n\n", example=True)


initial_config = input[0]
i_c_l = initial_config.splitlines()

stacks = [[]]

for i in range(1, int(i_c_l[len(i_c_l) - 1].strip().split()[-1]) + 1):
    stacks.append([])
    print("i=", i)
    letter_pos = (i - 1) * 4 + 1

    for j in range(int(len(i_c_l) - 2), -1, -1):
        aux_package = i_c_l[j][letter_pos]
        if aux_package != " ":
            stacks[i].append(aux_package)


print(stacks)

moves = input[1:][0].splitlines()

pattern = re.compile("move (\d+) from (\d+) to (\d+)")

for move in moves:
    mtch = pattern.match(move)
    how_many = int(mtch.group(1))
    frm = int(mtch.group(2))
    to = int(mtch.group(3))

    aux_stack = []
    for _ in range(how_many):
        aux_stack.append(stacks[frm].pop())
    stacks[to].extend(reversed(aux_stack))


solution = ""

for stack in stacks:
    if len(stack) > 0:
        solution += stack.pop()

print("solution", solution)


"""
from utils import DataFiles
import re

dataFiles = DataFiles(__file__)

input = dataFiles.get_input_chunks(sep="\n\n")
inputEX = dataFiles.get_input_chunks(sep="\n\n", example=True)


initial_config = input[0]
i_c_l = initial_config.splitlines()

stacks = [[]]

for i in range(1, int(i_c_l[len(i_c_l) - 1].strip().split()[-1]) + 1):
    stacks.append([])
    print("i=", i)
    letter_pos = (i - 1) * 4 + 1

    for j in range(int(len(i_c_l) - 2), -1, -1):
        aux_package = i_c_l[j][letter_pos]
        if aux_package != " ":
            stacks[i].append(aux_package)


print(stacks)

moves = input[1:][0].splitlines()

pattern = re.compile("move (\d+) from (\d+) to (\d+)")

for move in moves:
    mtch = pattern.match(move)
    how_many = int(mtch.group(1))
    frm = int(mtch.group(2))
    to = int(mtch.group(3))
    for _ in range(how_many):
        stacks[to].append(stacks[frm].pop())


solution = ""

for stack in stacks:
    if len(stack) > 0:
        solution += stack.pop()

print("solution", solution)

"""
