from utils import DataFiles
import sys


dataFiles = DataFiles(__file__)

input = dataFiles.get_input(splitlines=True)  # dataFiles.get_input_chunks(sep="\n\n")
inputEX = dataFiles.get_input(splitlines=True, example=True)

parsed_input = []
for line in input:
    aux_line = line.removeprefix("Sensor at x=").split(",", 1)
    sx, aux_line = int(aux_line[0]), aux_line[1].removeprefix(" y=").split(":", 1)
    sy, aux_line = int(aux_line[0]), aux_line[1].removeprefix(" closest beacon is at x=").split(",", 1)
    bx, aux_line = int(aux_line[0]), aux_line[1].removeprefix(" y=")
    by = int(aux_line)
    parsed_input.append((sx, sy, bx, by))

Y = 2000000
beacons = set()
no_beacons = set()

for sx, sy, bx, by in parsed_input:
    beacons.add((bx, by))

    mht = abs(sx - bx) + abs(sy - by)
    dst_y = abs(sy - Y)

    step = 0
    while dst_y + step <= mht:
        no_beacons.add((sx + step, Y))
        no_beacons.add((sx - step, Y))
        step += 1

print("Part1:", len(no_beacons - beacons))


for y in range(0, 4000001):
    ranges = []
    for sx, sy, bx, by in parsed_input:
        mht = abs(sx - bx) + abs(sy - by)
        dst_y = abs(sy - y)
        mult = mht - dst_y

        if mult > 0:
            ranges.append((sx - mult, sx + mult))
        else:
            continue

    ranges.sort()

    low_x, high_x = ranges[0]
    for aux_low_x, aux_high_x in ranges:
        if aux_low_x <= high_x:
            high_x = max(high_x, aux_high_x)
        else:
            print("Part2:", (high_x + 1) * 4000000 + y)
            exit()
