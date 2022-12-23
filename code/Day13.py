from utils import DataFiles
from itertools import zip_longest
from functools import cmp_to_key

dataFiles = DataFiles(__file__)

input = dataFiles.get_input(splitlines=True)  # dataFiles.get_input_chunks(sep="\n\n")
inputEX = dataFiles.get_input(splitlines=True, example=True)

input = [eval(line) for line in input if line != ""]
inputEX = [eval(line) for line in inputEX if line != ""]


def compare(left, right):
    if left is None:
        return -1
    if right is None:
        return 1

    if type(left) == type(right) == int:
        return (left > right) - (left < right)

    elif type(left) == type(right) == list:
        for l2, r2 in zip_longest(left, right):
            if (result := compare(l2, r2)) != 0:
                return result
        return 0
    else:
        l2 = [left] if type(left) == int else left
        r2 = [right] if type(right) == int else right
        return compare(l2, r2)


def part1(input):
    return sum(((i + 1) // 2 + 1) for i in range(0, len(input), 2) if compare(input[i], input[i + 1]) == -1)


def part2(input):
    div1, div2 = [[2]], [[6]]
    sorted_packets = sorted([*input, div1, div2], key=cmp_to_key(compare))
    return (sorted_packets.index(div1) + 1) * (sorted_packets.index(div2) + 1)


print("Part1:", part1(input))
print("Part2:", part2(input))
