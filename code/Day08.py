from utils import DataFiles

import numpy as np

dataFiles = DataFiles(__file__)


input = dataFiles.get_input(splitlines=True)  # dataFiles.get_input_chunks(sep="\n\n")
inputEX = dataFiles.get_input(splitlines=True, example=True)

dirs = [[-1, 0], [1, 0], [0, -1], [0, 1]]

grid = []
for line in inputEX:
    grid.append(list(map(int, line.strip())))


def is_visible(x, y, max_x, max_y):
    for dx, dy in dirs:
        new_x, new_y = x + dx, y + dy

        while 0 <= new_x < max_x and 0 <= new_y < max_y and grid[new_x][new_y] < grid[x][y]:
            new_x += dx
            new_y += dy

        if not (0 <= new_x < max_x and 0 <= new_y < max_y):
            return True

    return False


def calc_score(x, y):
    sscore = 1
    for dx, dy in dirs:
        curr = 0
        new_x, new_y = x + dx, y + dy

        while 0 <= new_x < max_x and 0 <= new_y < max_y:
            curr += 1
            if grid[new_x][new_y] >= grid[x][y]:
                break

            new_x += dx
            new_y += dy

        sscore *= curr

    return sscore


max_x = len(grid)
max_y = len(grid[0])

total_p1 = 0
total_p2 = 0

for x in range(max_x):
    for y in range(max_y):
        if is_visible(x, y, max_x, max_y):
            total_p1 += 1

        total_p2 = max(total_p2, calc_score(x, y))

print("Part1:", total_p1)
print("Part2:", total_p2)
