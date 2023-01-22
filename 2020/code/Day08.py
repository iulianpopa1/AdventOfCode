from utils import DataFiles
import re
dataFiles = DataFiles(__file__)

input = dataFiles.get_input()  # inputRaw = dataFiles.input
inputEX = dataFiles.get_inputEX()  # inputRawEX = dataFiles.inputEX


def run(commands):
    accumulator = 0
    pos = 0
    visited = set()

    while(pos < len(commands)):
        if pos in visited:
            return True, accumulator
        visited.add(pos)
        command = commands[pos]

        if command[0] == 'nop':
            pos += 1
        elif command[0] == 'acc':
            accumulator += command[1]
            pos += 1
        elif command[0] == 'jmp':
            pos += command[1]

    return False, accumulator


commands = []

for line in input:
    reg = re.compile(r'^(\w{3}) ([\+|\-]\d+)$')
    command = re.findall(reg, line)[0]  # command = line.split()
    commands.append([command[0], int(command[1])])

_, acc = run(commands)
print('Part 1:', acc)

for i in range(len(commands)):
    command, _ = commands[i]
    if command == 'jmp' or command == 'nop':
        commands[i][0] = 'nop' if command == 'jmp' else 'jmp'
        fin, acc = run(commands)
        if fin == False:
            print('Part 2:', acc)
            break
        commands[i][0] = command
