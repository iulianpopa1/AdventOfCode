from functools import partial
import itertools
import numpy as np
from utils import DataFiles

dataFiles = DataFiles(__file__)

input = dataFiles.get_input()


def part2_itertools(missing_number): # 2x faster than the Numpy method due **partial_sum** creation
    for i in range(len(numbers)):
        partial_sum = list(itertools.accumulate(numbers[i:]))[2:] # Faster
        try:
            if missing_number in partial_sum:
                found_ps_index = partial_sum.index(missing_number)
                sum_arr = numbers[i: i + 1 + found_ps_index + 2]
                print('Part 2:', min(sum_arr) + max(sum_arr))
        except:
            pass


def part2_numpy(missing_number):
    for i in range(len(numbers)):
        partial_sum = np.array(numbers[i:]).cumsum()[2:] # Slower
        try:
            if missing_number in partial_sum:
                found_ps_index = np.where(partial_sum == missing_number)[0][0]
                sum_arr = numbers[i: i + 1 + found_ps_index + 2]
                print('Part 2:', min(sum_arr) + max(sum_arr))
        except:
            pass


numbers = [int(line) for line in input]
preamble = 25
missing_number = 0

for i in range(preamble, len(numbers)):
    sums = set()

    for nr_j in numbers[i - preamble: i]:
        for nr_k in numbers[i - preamble: i]:
            sums.add(nr_j + nr_k)

    if numbers[i] not in sums:
        missing_number = numbers[i]

print('Part 1:', missing_number)
part2_itertools(missing_number)
part2_numpy(missing_number)