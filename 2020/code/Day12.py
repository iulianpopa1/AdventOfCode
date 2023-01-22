from utils import DataFiles
import re


dataFiles = DataFiles(__file__)

input = dataFiles.get_input()  # inputRaw = dataFiles.input
inputEX = dataFiles.get_inputEX()  # inputRawEX = dataFiles.inputEX

reg = re.compile(r'^([A-Z])(\d+)$')

inp = []

for line in input:
    r = re.findall(reg, line)
    inp.append((r[0][0], int(r[0][1])))

# E - 0
# S - 1
# W - 2
# N - 3

# X : E / W = +1 / -1
# Y : N / S = +1 / -1

dirr = {
    'E':  1 + 0j,
    'S':  0 - 1j,
    'W': -1 + 0j,
    'N':  0 + 1j
}

curr_pos = 0 + 0j
curr_dir = 1 + 0j

for dir, units in inp:
    if dir == 'F':
        curr_pos += curr_dir * units
    elif dir == 'R':
        curr_dir *= pow(-1j, (units // 90))
    elif dir == 'L':
        curr_dir *= pow(1j, (units // 90))
    else:
        curr_pos += dirr[dir] * units

print('Part 1:', abs(curr_pos.real) + abs(curr_pos.imag))

curr_pos = 0 + 0j
wayp = 10 + 1j

for dir, units in inp:
    if dir == 'F':
        curr_pos += wayp * units
    elif dir == 'R':
        wayp *= pow(-1j, (units // 90))
    elif dir == 'L':
        wayp *= pow(1j, (units // 90))
    else:
        wayp += dirr[dir] * units

print('Part 2:', abs(curr_pos.real) + abs(curr_pos.imag))
