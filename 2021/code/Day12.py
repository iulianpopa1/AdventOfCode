from utils import DataFiles
from collections import *
from math import *
import networkx as nx

import numpy as np
import re

dataFiles = DataFiles(__file__)

input = dataFiles.input
inputEX = dataFiles.inputEX

inp = input[:]

g = nx.Graph()

for line in inp:
    x, y = line.split("-")
    g.add_edge(x, y)


def custom_path(path, double_use=False):
    if path[-1] == "end":
        yield path

    for x in g.neighbors(path[-1]):
        c_double_use = double_use

        if x.islower() and x in path:
            if not c_double_use:
                if x in ("start", "end"):
                    continue
                c_double_use = True
            else:
                continue

        yield from custom_path(path + [x], c_double_use)


p1_paths = list(custom_path(["start"], True))
print("part 1", len(p1_paths))
p2_paths = list(custom_path(["start"], False))
print("part 2", len(p2_paths))
