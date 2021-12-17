from utils import DataFiles
from collections import *
from math import *

import numpy as np
import re

dataFiles = DataFiles(__file__)

input = dataFiles.input
inputEX = dataFiles.inputEX

inp = inputEX[:]

x_min = 143
x_max = 177
y_min = -106
y_max = -71

ans_y_max = 0
y_found = 0


for x_v in range(-300, 300):
    for y_v in range(-300, 300):
        x, y = 0, 0
        x_v_aux, y_v_aux = x_v, y_v
        local_y_max = 0
        while x <= x_max and y >= y_min:
            x += x_v_aux
            y += y_v_aux

            if x_v_aux > 0:
                x_v_aux -= 1
            elif x_v_aux < 0:
                x_v_aux += 1

            y_v_aux -= 1
            local_y_max = max(local_y_max, y)

            if x_min <= x <= x_max and y_min <= y <= y_max:
                ans_y_max = max(ans_y_max, local_y_max)
                y_found += 1
                break

print("Part 1:", ans_y_max)
print("Part 2:", y_found)
