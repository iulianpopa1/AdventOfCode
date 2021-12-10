from utils import DataFiles
from collections import *
from numpy import *
from math import *

dataFiles = DataFiles(__file__)

input = dataFiles.input
inputEX = dataFiles.inputEX

inp = input[:]


def check(expression):
    open_tup = tuple("({[<")
    close_tup = tuple(")}]>")
    map = dict(zip(open_tup, close_tup))
    queue = []

    for i in expression:
        if i in open_tup:
            queue.append(map[i])
        elif i in close_tup:
            if not queue or i != queue.pop():
                return i


ans = 0

for string in inp:
    kek = check(string)
    print(string, "-", check(string))
    if kek == ")":
        ans += 3
    elif kek == "]":
        ans += 57
    elif kek == "}":
        ans += 1197
    elif kek == ">":
        ans += 25137

print(ans)
