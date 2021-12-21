from utils import DataFiles
from collections import *
from math import *

import numpy as np
import re

dataFiles = DataFiles(__file__)

input = dataFiles.input
inputEX = dataFiles.inputEX

inp = input[:]

algorithm = [int(ch == "#") for ch in inp[0]]

image = inp[2:]


def exec(pixels, inf):
    i_min = min(p[0] for p in pixels)
    i_max = max(p[0] for p in pixels)
    j_min = min(p[1] for p in pixels)
    j_max = max(p[1] for p in pixels)

    new_pixels = set()

    for i in range(i_min - 1, i_max + 2):
        for j in range(j_min - 1, j_max + 2):
            index = 0
            for ii in range(i - 1, i + 2):
                for jj in range(j - 1, j + 2):
                    index <<= 1
                    if i_min <= ii <= i_max and j_min <= jj <= j_max:
                        index |= int((ii, jj) in pixels)
                    else:
                        index |= inf

            if algorithm[index]:
                new_pixels.add((i, j))

    return new_pixels


pixels = set((i, j) for i in range(len(image)) for j in range(len(image[i])) if image[i][j] == "#")
pixels = sorted(pixels)

for i in range(50):
    if i == 2:
        print("Part1:", len(pixels))

    pixels = exec(pixels, i & algorithm[0])


print("Part2:", len(pixels))
