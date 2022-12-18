from utils import DataFiles

dataFiles = DataFiles(__file__)

input = dataFiles.get_input(splitlines=True)  # dataFiles.get_input_chunks(sep="\n\n")
inputEX = dataFiles.get_input(splitlines=True, example=True)


def adjacent(a, b):
    """
    Returns True if a and b are adjacent points
    """
    if a[0] == b[0] and a[1] == b[1] and abs(a[2] - b[2]) == 1:
        return True
    elif a[0] == b[0] and abs(a[1] - b[1]) == 1 and a[2] == b[2]:
        return True
    elif abs(a[0] - b[0]) == 1 and a[1] == b[1] and a[2] == b[2]:
        return True
    else:
        return False


def get_adj_cubes(curr):
    to_return = []

    nx1 = curr[0] + 1
    ny1 = curr[1] + 1
    nz1 = curr[2] + 1
    nx_1 = curr[0] - 1
    ny_1 = curr[1] - 1
    nz_1 = curr[2] - 1
    if -2 <= nx_1 <= 21 and nx_1 != curr[0]:
        to_return.append((nx_1, curr[1], curr[2]))
    if -2 <= ny_1 <= 21 and ny_1 != curr[1]:
        to_return.append((curr[0], ny_1, curr[2]))
    if -2 <= nz_1 <= 21 and nz_1 != curr[2]:
        to_return.append((curr[0], curr[1], nz_1))
    if -2 <= nx1 <= 21 and nx1 != curr[0]:
        to_return.append((nx1, curr[1], curr[2]))
    if -2 <= ny1 <= 21 and ny1 != curr[1]:
        to_return.append((curr[0], ny1, curr[2]))
    if -2 <= nz1 <= 21 and nz1 != curr[2]:
        to_return.append((curr[0], curr[1], nz1))
    return to_return


cubes = []
cubes_set = set()
for line in input:
    x, y, z = line.split(",")
    cubes.append((int(x), int(y), int(z)))
    cubes_set.add((int(x), int(y), int(z)))

adj_cnt = 0

for i in range(len(cubes)):
    for j in range(len(cubes)):
        if i != j:
            if adjacent(cubes[i], cubes[j]):
                adj_cnt += 1

ans_p1 = len(cubes) * 6 - adj_cnt
print("Part1", ans_p1)

space = {(x, y, z) for x in range(-2, 22) for y in range(-2, 22) for z in range(-2, 22)}
space -= cubes_set

queue = [(-2, -2, -2)]
while queue:
    curr = queue.pop()
    if curr in space:
        space.remove(curr)
        queue += get_adj_cubes(curr)


p2 = ans_p1

for cube in space:
    for adj in get_adj_cubes(cube):
        if adj in cubes_set:
            p2 -= 2
    p2 += 6
    cubes_set.add(cube)

print("Part 2:", p2)
