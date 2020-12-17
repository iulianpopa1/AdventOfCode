import collections
from utils import DataFiles

dataFiles = DataFiles(__file__)

input = dataFiles.get_input()  # inputRaw = dataFiles.input
inputEX = dataFiles.get_inputEX()  # inputRawEX = dataFiles.inputEX


def parse(input, part):
    active = []
    for x, line in enumerate(input):
        for y, c in enumerate(line):
            if c == '#':
                if part == 1:
                    active.append((x, y, 0))
                elif part == 2:
                    active.append((x, y, 0, 0))
    return active

def neighs(coord, part):
    for dx in range(-1, 2):
        for dy in range(-1, 2):
            for dz in range(-1, 2):
                if part == 1:
                    if dx != 0 or dy != 0 or dz != 0:
                        yield coord[0] + dx, coord[1] + dy, coord[2] + dz
                elif part == 2:
                    for dw in range(-1, 2):
                        if dx != 0 or dy != 0 or dz != 0 or dw != 0:
                            yield coord[0] + dx, coord[1] + dy, coord[2] + dz, coord[3] + dw

def run_cycle(active, part):
    cnt_active = collections.defaultdict(int)
    for coord in active:
        for neighbor in neighs(coord, part):
            cnt_active[neighbor] += 1
    
    active_n = []
    for coord in active:
        if 2 <= cnt_active.pop(coord, 0) <= 3:
            active_n.append(coord)

    for coord in cnt_active:
        if cnt_active[coord] == 3:
            active_n.append(coord)

    return active_n

def main(input, part):
    active_coords = parse(input, part)
    for _ in range(6):
        active_coords = run_cycle(active_coords, part)
    
    return len(active_coords)

print('Part1:', main(input, 1))
print('Part2:', main(input, 2))
