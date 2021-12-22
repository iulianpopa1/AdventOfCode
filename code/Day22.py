from utils import DataFiles
from collections import *
from math import *

import numpy as np
import re

dataFiles = DataFiles(__file__)

input = dataFiles.input
inputEX = dataFiles.inputEX

inp = input[:]


def parse_inp():
    parsed_inp = []

    for l in inp:
        spl = l.split()
        onoff = True if spl[0] == "on" else False
        ranges = [int(nr) for nr in re.findall(r"[\+\-]?\d+", spl[1])]
        xr = sorted([ranges[0], ranges[1]])
        yr = sorted([ranges[2], ranges[3]])
        zr = sorted([ranges[4], ranges[5]])
        parsed_inp.append((onoff, (xr, yr, zr)))

    return parsed_inp


def part1():
    on_cubes = set()

    for onoff, (xr, yr, zr) in inp:
        for x in range(max(-50, xr[0]), min(50, xr[1]) + 1):
            for y in range(max(-50, yr[0]), min(50, yr[1]) + 1):
                for z in range(max(-50, zr[0]), min(50, zr[1]) + 1):
                    if onoff:
                        on_cubes.add((x, y, z))
                    else:
                        on_cubes.discard((x, y, z))

    return len(on_cubes)


def intersect_range(r1, r2):
    if r2[0] <= r1[1] and r1[0] <= r2[1]:
        nums = sorted([r1[0], r1[1], r2[0], r2[1]])
        return [nums[1], nums[2]]


def intersect_area(area1, area2):
    x1, y1, z1 = area1
    x2, y2, z2 = area2

    xr = intersect_range(x1, x2)
    yr = intersect_range(y1, y2)
    zr = intersect_range(z1, z2)

    if all((xr, yr, zr)):
        return (xr, yr, zr)


class Cuboid:
    def __init__(self, area):
        self.area = area
        self.ignored = []

    def remove(self, area):
        clean_area = intersect_area(self.area, area)

        if clean_area:
            for vacuum in self.ignored:
                vacuum.remove(clean_area)
            self.ignored.append(Cuboid(clean_area))

    def size(self):
        x, y, z = self.area

        return (x[1] - x[0] + 1) * (y[1] - y[0] + 1) * (z[1] - z[0] + 1) - sum(cuboid.size() for cuboid in self.ignored)


def part2():
    cuboids = []

    for is_on, area in inp:
        for cuboid in cuboids:
            cuboid.remove(area)
        if is_on:
            cuboids.append(Cuboid(area))

    return sum(cuboid.size() for cuboid in cuboids)


inp = parse_inp()
print("Part1:", part1())
print("Part2:", part2())
