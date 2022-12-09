from utils import DataFiles

dataFiles = DataFiles(__file__)

input = dataFiles.get_input(splitlines=True)  # dataFiles.get_input_chunks(sep="\n\n")
inputEX = dataFiles.get_input(splitlines=True, example=True)


dirs_letter = {"U": [-1, 0], "D": [1, 0], "L": [0, -1], "R": [0, 1]}


def solve(knots):
    rope = [(0, 0)] * knots
    seen_tail_pos = {(0, 0)}

    for line in input:
        dir, steps = line.split()

        for step in range(int(steps)):
            dx, dy = dirs_letter[dir]
            rope[0] = (rope[0][0] + dx, rope[0][1] + dy)

            for i in range(1, len(rope)):
                td_x = rope[i - 1][0] - rope[i][0]
                td_y = rope[i - 1][1] - rope[i][1]

                if abs(td_x) > 1 or abs(td_y) > 1:
                    rope[i] = (
                        rope[i][0] + (-1 if td_x < 0 else 1 if td_x > 0 else 0),
                        rope[i][1] + (-1 if td_y < 0 else 1 if td_y > 0 else 0),
                    )

            seen_tail_pos.add((rope[-1][0], rope[-1][1]))

    return len(seen_tail_pos)


print("Part 1:", solve(2))
print("Part 2:", solve(10))
