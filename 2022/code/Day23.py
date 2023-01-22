from utils import DataFiles
from collections import defaultdict

dataFiles = DataFiles(__file__)

input = dataFiles.get_input(splitlines=True)  # dataFiles.get_input_chunks(sep="\n\n")
inputEX = dataFiles.get_input(splitlines=True, example=True)

dirs = [
    [(-1, 0), (-1, -1), (-1, 1)],  # N: -1,0
    [(1, 0), (1, -1), (1, 1)],  # S: 1,0
    [(0, -1), (-1, -1), (1, -1)],  # W: 0,-1
    [(0, 1), (-1, 1), (1, 1)],  # E: 0,1
]

all_dirs = [(-1, 0), (-1, -1), (-1, 1), (1, 0), (1, -1), (1, 1), (0, -1), (-1, -1), (1, -1), (0, 1), (-1, 1), (1, 1)]

grid = defaultdict(lambda: False)
for x in range(len(input)):
    for y in range(len(input[0])):
        if input[x][y] == "#":
            grid[x, y] = True


def next_state(curr_grid, dir_iterator):
    curr_dirs = dirs[dir_iterator:] + dirs[:dir_iterator]
    new_list_grid = defaultdict(list)
    stationary = set()

    for k, v in list(curr_grid.items()):
        x, y = k
        if v == True:

            if not any(curr_grid[x + dx, y + dy] for dx, dy in all_dirs):
                stationary.add((x, y))
                continue

            is_stationary = True
            for aux_dirs in curr_dirs:
                if not any(curr_grid[x + dx, y + dy] for dx, dy in aux_dirs):
                    new_list_grid[x + aux_dirs[0][0], y + aux_dirs[0][1]].append((x, y))
                    is_stationary = False
                    break

            if is_stationary:
                stationary.add((x, y))

    new_grid = defaultdict(lambda: False)
    for x, y in stationary:
        new_grid[x, y] = True

    any_moved = False
    for (x, y), elves in new_list_grid.items():
        if len(elves) == 1:
            new_grid[x, y] = True
            any_moved = True
        else:
            for x, y in elves:
                new_grid[x, y] = True

    return new_grid, (dir_iterator + 1) % 4, any_moved


dir_iterator = 0
round = 1

while True:
    grid, dir_iterator, any_moved_check = next_state(grid, dir_iterator)

    if round == 10:
        min_x, min_y, max_x, max_y = 999, 999, -999, -999
        for (x, y), v in grid.items():
            if v:
                min_x, min_y, max_x, max_y = (min(min_x, x), min(min_y, y), max(max_x, x), max(max_y, y))

        print("Part1:", sum(1 for x in range(min_x, max_x + 1) for y in range(min_y, max_y + 1) if not grid[x, y]))

    if any_moved_check:
        round += 1
    else:
        print("Part2:", round)
        break
