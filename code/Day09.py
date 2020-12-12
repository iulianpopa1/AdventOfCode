import itertools
import numpy as np
from utils import DataFiles

dataFiles = DataFiles(__file__)
input = dataFiles.get_input()


def part1_iterative(numbers):
    for i in range(preamble, len(numbers)):
        sums = set()

        for nr_j in numbers[i - preamble: i]:
            for nr_k in numbers[i - preamble: i]:
                sums.add(nr_j + nr_k)

        if numbers[i] not in sums:
            return numbers[i]


def part1_numpy(numbers):
    for i in range(preamble, len(numbers)):
        partial_sum = np.array(numbers[i - preamble: i], dtype=np.int64)
        sums = partial_sum.reshape(1, -1) + partial_sum.reshape(-1, 1)

        for aux in range(0, preamble):
            sums[aux][aux] = -1

        if numbers[i] not in sums:
            return numbers[i]


def part2_itertools(numbers, missing_number): # 2x faster than the Numpy method due **partial_sum** creation
    for i in range(len(numbers)):
        partial_sum = list(itertools.accumulate(numbers[i:]))[2:] # Faster
        try:
            if missing_number in partial_sum:
                found_ps_index = partial_sum.index(missing_number)
                sum_arr = numbers[i: i + 1 + found_ps_index + 2]
                return min(sum_arr) + max(sum_arr)
        except:
            pass


def part2_numpy(numbers, missing_number):
    for i in range(len(numbers)):
        partial_sum = np.array(numbers[i:]).cumsum()[2:] # Slower
        try:
            if missing_number in partial_sum:
                found_ps_index = np.where(partial_sum == missing_number)[0][0]
                sum_arr = numbers[i: i + 1 + found_ps_index + 2]
                return min(sum_arr) + max(sum_arr)
        except:
            pass


numbers = [int(line) for line in input]
preamble = 25
missing_number = 0

print('Part 1:', part1_iterative(numbers))
print('Part 1:', part1_numpy(numbers))

missing_number = part1_numpy(numbers)

print('Part 2:', part2_itertools(numbers, missing_number))
print('Part 2:', part2_numpy(numbers, missing_number))