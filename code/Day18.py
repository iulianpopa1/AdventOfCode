from utils import DataFiles
import re

dataFiles = DataFiles(__file__)

input = dataFiles.get_input()  # inputRaw = dataFiles.input
inputEX = dataFiles.get_inputEX()  # inputRawEX = dataFiles.inputEX


def eval_simple_expr(expr):
    ops = expr.split()
    result = ops[0]
    i = 1
    while i < len(ops):
        result = str(eval(result + ops[i] + ops[i + 1]))
        i += 2

    return result


def solve_p1(expr):
    par_reg = re.compile(r'\([^\(\)]+\)')
    while expr.count('('):
        expr = re.sub(par_reg,
                      lambda x: str(eval_simple_expr(x[0][1:-1])), expr)

    return int(eval_simple_expr(expr))


def eval_add_first(expr):
    while expr.count('+'):
        expr = re.sub(r'\d+ \+ \d+',
                      lambda x: str(eval(x[0])), expr)

    return int(eval_simple_expr(expr))


def solve_p2(expr):
    par_reg = re.compile(r'\([^\(\)]+\)')
    while expr.count('('):
        expr = re.sub(par_reg,
                      lambda x: str(eval_add_first(x[0][1:-1])), expr)
    return eval_add_first(expr)


print('Part1:', sum(solve_p1(line) for line in input))
print('Part2:', sum(solve_p2(line) for line in input))
