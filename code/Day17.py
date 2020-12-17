import collections
from utils import DataFiles

dataFiles = DataFiles(__file__)

input = dataFiles.get_input()  # inputRaw = dataFiles.input
inputEX = dataFiles.get_inputEX()  # inputRawEX = dataFiles.inputEX

def parse(input):
    active = []
    for x, line in enumerate(input):
        for y, c in enumerate(line):
            if c == '#':
                active.append((x, y, 0))
    return active


def parse_p2(input):
    active = []
    for x, line in enumerate(input):
        for y, c in enumerate(line):
            if c == '#':
                active.append((x, y, 0, 0))
    return active

def neighs(coord):
    for dx in range(-1, 2):
        for dy in range(-1, 2):
            for dz in range(-1, 2):
                if dx != 0 or dy != 0 or dz != 0:
                    yield coord[0] + dx, coord[1] + dy, coord[2] + dz

def neighs_p2(coord):
    for dx in range(-1, 2):
        for dy in range(-1, 2):
            for dz in range(-1, 2):
                for dw in range(-1, 2):
                    if dx != 0 or dy != 0 or dz != 0 or dw != 0:
                        yield coord[0] + dx, coord[1] + dy, coord[2] + dz, coord[3] + dw


def run_cycle(active):
    cnt_active = collections.defaultdict(int)
    for coord in active:
        for neighbor in neighs(coord):
            cnt_active[neighbor] += 1
    
    active_n = []
    for coord in active:
        if 2 <= cnt_active.pop(coord, 0) <= 3:
            active_n.append(coord)

    for coord, cnt in cnt_active.items():
        if cnt == 3:
            active_n.append(coord)

    return active_n
    

def run_cycle_p2(active):
    cnt_active = collections.defaultdict(int)
    for coord in active:
        for neighbor in neighs_p2(coord):
            cnt_active[neighbor] += 1

    active_n = []
    for coord in active:
        if 2 <= cnt_active.pop(coord, 0) <= 3:
            active_n.append(coord)

    for coord, cnt in cnt_active.items():
        if cnt == 3:
            active_n.append(coord)

    return active_n

def part1(input):
    active_coords = parse(input)
    for _ in range(6):
        active_coords = run_cycle(active_coords)
    
    return len(active_coords)

def part2(input):
    active_coords = parse_p2(input)
    for _ in range(6):
        active_coords = run_cycle_p2(active_coords)
    
    return len(active_coords)


print('Part1:', part1(input))
print('Part2:', part2(input))
