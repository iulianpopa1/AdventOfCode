from utils import DataFiles

dataFiles = DataFiles(__file__)

input = dataFiles.get_input(splitlines=True)  # dataFiles.get_input_chunks(sep="\n\n")
inputEX = dataFiles.get_input(splitlines=True, example=True)


dirs_letter = {"U": [-1, 0], "D": [1, 0], "L": [0, -1], "R": [0, 1]}

ex_pos = [[0, 0], [0, 0]]
tail_pos = {(0, 0)}

for line in input:
    dir, steps = line.split()

    for step in range(int(steps)):
        dx, dy = dirs_letter[dir]
        ex_pos[0][0] += dx
        ex_pos[0][1] += dy

        td_x = ex_pos[0][0] - ex_pos[1][0]
        td_y = ex_pos[0][1] - ex_pos[1][1]

        if abs(td_x) > 1 or abs(td_y) > 1:
            ex_pos[1][0] += -1 if td_x < 0 else 1 if td_x > 0 else 0
            ex_pos[1][1] += -1 if td_y < 0 else 1 if td_y > 0 else 0

        tail_pos.add((ex_pos[1][0], ex_pos[1][1]))

print("Part 1:", len(tail_pos))

ex_pos = [[0, 0], [0, 0], [0, 0], [0, 0], [0, 0], [0, 0], [0, 0], [0, 0], [0, 0], [0, 0]]
tail_pos = {(0, 0)}

for line in input:
    dir, steps = line.split()
    for step in range(int(steps)):
        dx, dy = dirs_letter[dir]
        ex_pos[0][0] += dx
        ex_pos[0][1] += dy

        for i in range(1, len(ex_pos)):
            td_x = ex_pos[i - 1][0] - ex_pos[i][0]
            td_y = ex_pos[i - 1][1] - ex_pos[i][1]

            if abs(td_x) > 1 or abs(td_y) > 1:
                ex_pos[i][0] += -1 if td_x < 0 else 1 if td_x > 0 else 0
                ex_pos[i][1] += -1 if td_y < 0 else 1 if td_y > 0 else 0

        tail_pos.add((ex_pos[-1][0], ex_pos[-1][1]))

print("Part 2:", len(tail_pos))
