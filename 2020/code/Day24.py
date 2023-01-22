from utils import DataFiles
import re
from collections import defaultdict


dataFiles = DataFiles(__file__)

input = dataFiles.get_input()  # inputRaw = dataFiles.input
inputEX = dataFiles.get_inputEX()  # inputRawEX = dataFiles.inputEX


directions = {
    'e':   2 + 0j,
    'w':  -2 + 0j,
    'se':  1 - 2j,
    'sw': -1 - 2j,
    'nw': -1 + 2j,
    'ne':  1 + 2j
}


def part1(inp):
    gl_wb = defaultdict(bool)
    reg = re.compile(r'(e|se|sw|w|nw|ne)')

    for tile in inp:
        pos = 0 + 0j
        dirs = reg.findall(tile)

        for dir in dirs:
            pos += directions[dir]

        gl_wb[pos] = not gl_wb[pos]

    return sum(gl_wb.values()), gl_wb


def part2(map_pos_WB):
    for _ in range(100):
        new_map = defaultdict(bool)
        adj_wb = {x + y for x in map_pos_WB for y in directions.values()}

        for x in adj_wb:
            neigh_cnt = sum(map_pos_WB[x + y]
                       for y in directions.values())

            if(neigh_cnt == 2 or (map_pos_WB[x] == True and neigh_cnt == 1)):
                new_map[x] = True
            else:
                new_map[x] = False

        map_pos_WB = new_map

    print(sum(map_pos_WB.values()))


ans_p1, map_pos_WB = part1(input)
print('Part1:', ans_p1)
print('Part2:', part2(map_pos_WB))
