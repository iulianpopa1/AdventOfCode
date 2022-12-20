from utils import DataFiles

dataFiles = DataFiles(__file__)

input = dataFiles.get_input(splitlines=True)  # dataFiles.get_input_chunks(sep="\n\n")
inputEX = dataFiles.get_input(splitlines=True, example=True)

input_str = input[0].strip()


rocks_list = [
    [(2, 0), (3, 0), (4, 0), (5, 0)],
    [(3, 0), (2, 1), (3, 1), (4, 1), (3, 2)],
    [(2, 0), (3, 0), (4, 0), (4, 1), (4, 2)],
    [(2, 0), (2, 1), (2, 2), (2, 3)],
    [(2, 0), (2, 1), (3, 0), (3, 1)],
]


def run_sim(input_str, tower, start_rock, jet, total_rocks):
    for rock_index in range(start_rock, total_rocks):
        rock = rocks_list[rock_index % len(rocks_list)]
        y_offset = max(t[1] for t in tower) + 4
        rock = [(x, y + y_offset) for x, y in rock]

        while True:
            dx = -1 if input_str[jet % len(input_str)] == "<" else 1
            jet += 1

            new_rock = [(x + dx, y) for x, y in rock]

            for x, y in new_rock:
                if x < 0 or x >= 7 or (x, y) in tower:
                    new_rock = rock
                    break

            rock = new_rock
            new_rock = [(x, y - 1) for x, y in rock]

            tower_updated = False
            for x, y in new_rock:
                if (x, y) in tower:
                    tower.update(rock)
                    tower_updated = True
                    break

            if tower_updated:
                break

            rock = new_rock

    return tower


tower = {(x, 0) for x in range(7)}
tower = run_sim(input_str, tower, 0, 0, 2022)

print("Part1:", max(t[1] for t in tower))


import collections


def part2(input_str):
    tower = {(x, 0) for x in range(7)}
    tower_heights = collections.defaultdict(list)
    jet = 0
    steps = 1000000000000

    for rock_idx in range(steps):
        start_key = (rock_idx % len(rocks_list), jet % len(input_str))

        rock = rocks_list[rock_idx % len(rocks_list)]
        y_off = max(t[1] for t in tower) + 4
        rock = [(x, y + y_off) for x, y in rock]

        move_x, move_y = 0, 0

        while True:
            dx = -1 if input_str[jet % len(input_str)] == "<" else 1
            jet += 1

            new_rock = [(x + dx, y) for x, y in rock]

            rock_updated = False
            for x, y in new_rock:
                if x < 0 or x >= 7 or (x, y) in tower:
                    new_rock = rock
                    rock_updated = True

            if rock_updated == False:
                move_x += dx

            rock = new_rock
            new_rock = [(x, y - 1) for x, y in rock]

            if any(c in tower for c in new_rock):
                tower.update(rock)
                move_s_xy = tower_heights[(start_key, move_x, move_y)]
                curr_height = max(t[1] for t in tower)
                stats = (
                    curr_height,
                    rock_idx,
                    tuple(max(t[1] - curr_height for t in tower if t[0] == tx) for tx in range(7)),
                )
                if len(move_s_xy) > 1:
                    curr_diff = curr_height - move_s_xy[-1][0]
                    cycle_length = rock_idx - move_s_xy[-1][1]
                    if (
                        move_s_xy[-1][0] - move_s_xy[-2][0] == curr_diff
                        and move_s_xy[-1][1] - move_s_xy[-2][1] == cycle_length
                    ):
                        remaining_steps = steps - rock_idx - 1
                        cycles = remaining_steps // cycle_length
                        skip_steps = cycles * cycle_length
                        return (
                            max(t[1] for t in run_sim(input_str, tower, rock_idx + 1 + skip_steps, jet, steps))
                            + curr_diff * cycles
                        )
                move_s_xy.append(stats)
                break

            move_y -= 1
            rock = new_rock


print("Part2:", part2(input_str))
