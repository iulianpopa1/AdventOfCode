from utils import DataFiles
from collections import *
from numpy import *
from math import *
import re

dataFiles = DataFiles(__file__)

input = dataFiles.input
inputEX = dataFiles.inputEX

inp = input[:]

incomplete_inp = []


def check2(my_string):
    brackets = ["()", "{" + "}", "[]", "<>"]
    open_tup = set("({[<")
    found = True
    while found:
        found = False
        for br in brackets:
            fnd = my_string.find(br)
            if fnd != -1:
                found = True
                my_string = my_string.replace(br, "")

    if my_string != "" and set(my_string).issubset(open_tup):
        return my_string

    return ""


def calc_s(my_string):
    ans = 0

    for c in reversed(my_string):
        if c == "(":
            ans = ans * 5 + 1
        elif c == "[":
            ans = ans * 5 + 2
        elif c == "{":
            ans = ans * 5 + 3
        elif c == "<":
            ans = ans * 5 + 4
    print(ans)
    return ans


ans = []

for string in inp:
    kek = check2(string)
    if kek != "":
        print(string, "-", kek)
        ans.append(int(calc_s(kek)))

ans = sorted(ans)
print(ans)

print(ans[len(ans) // 2])
