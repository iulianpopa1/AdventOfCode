from utils import DataFiles
import re

dataFiles = DataFiles(__file__)

input = dataFiles.get_input(splitlines=True)  # dataFiles.get_input_chunks(sep="\n\n")
inputEX = dataFiles.get_input(splitlines=True, example=True)


def range_overlap_p1(x1, x2, y1, y2):
    return x1 <= y1 <= y2 <= x2 or y1 <= x1 <= x2 <= y2


def range_overlap_p2(x1, x2, y1, y2):
    return (x2 >= y1 and x1 <= y2) or (y2 >= x1 and y1 <= x2)


total_p1 = 0
total_p2 = 0

for line in input:
    xoy = re.match("(\d+)-(\d+),(\d+)-(\d+)", line)
    x1, x2, y1, y2 = int(xoy.group(1)), int(xoy.group(2)), int(xoy.group(3)), int(xoy.group(4))

    total_p1 += range_overlap_p1(x1, x2, y1, y2)
    total_p2 += range_overlap_p2(x1, x2, y1, y2)


print("Part1:", total_p1)
print("Part2:", total_p2)
