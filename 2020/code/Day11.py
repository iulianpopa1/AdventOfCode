import copy
from utils import DataFiles

dataFiles = DataFiles(__file__)

input = dataFiles.get_input()  # inputRaw = dataFiles.input
inputEX = dataFiles.get_inputEX()  # inputRawEX = dataFiles.inputEX

map = [list(s) for s in input]
dir = [(1, 0), (-1, 0), (0, 1), (0, -1), (1, 1), (1, -1), (-1, 1), (-1, -1)]

def count_neigh(map, i, j, part):
    neigh = 0
    for dx, dy in dir:
        x = i + dx
        y = j + dy
        if part == 1:
            if 0 <= x < len(map) and 0 <= y < len(map[0]):
                if map[x][y] == '#':
                    neigh += 1
        else:
            while 0 <= x < len(map) and 0 <= y < len(map[0]):
                if map[x][y] == '#':
                    neigh += 1
                    break
                elif map[x][y] == 'L':
                    break
                x += dx
                y += dy
    return neigh



def exec(map, part):
    seats_req_to_empty = 4 if part == 1 else 5

    map_c = copy.deepcopy(map)
    modif = False
    for i in range(len(map_c)):
        for j in range(len(map_c[0])):

            cnt = count_neigh(map_c, i, j, part)
            
            if map_c[i][j] == 'L' and cnt == 0:
                map[i][j] = '#'
                modif = True
            elif map_c[i][j] == '#' and cnt >= seats_req_to_empty:
                map[i][j] = 'L'
                modif = True
    return modif

def run(part):
    mapp = copy.deepcopy(map)
    ans = 0

    while True:
        modif = exec(mapp, part)
        if modif == False:
            break

    for i in range(len(mapp)):
        for j in range(len(mapp[0])):
            if mapp[i][j] == '#':
                ans += 1
    
    return ans

print('Part 1', run(1))
print('Part 2', run(2))
