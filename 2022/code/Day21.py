from utils import DataFiles

dataFiles = DataFiles(__file__)

input = dataFiles.get_input(splitlines=True)  # dataFiles.get_input_chunks(sep="\n\n")
inputEX = dataFiles.get_input(splitlines=True, example=True)

parsed_input = {}
for line in input:
    ln = line.split(" ")
    if len(ln) == 2:
        parsed_input[ln[0][:-1]] = int(ln[1])
    else:
        parsed_input[ln[0][:-1]] = (ln[1], ln[2], ln[3])


def evaluate(exprr):
    if type(parsed_input[exprr]) is int:
        return parsed_input[exprr]
    else:
        a, op, b = parsed_input[exprr]
        if op == "+":
            return evaluate(a) + evaluate(b)
        if op == "-":
            return evaluate(a) - evaluate(b)
        if op == "*":
            return evaluate(a) * evaluate(b)
        if op == "/":
            return evaluate(a) // evaluate(b)


def evaluate_p2(exprr):
    if exprr == "root":
        a, _, b = parsed_input[exprr]
        return evaluate(a) == 3032671800355, evaluate(a), evaluate(b)


print("Part1:", evaluate("root"))

x = 0
steps = 10000000000000
while not x:
    x, y, z = evaluate_p2("root")
    if y < z:
        parsed_input["humn"] -= steps
        steps = steps // 10
    if steps == 0:
        break
    parsed_input["humn"] += steps

print("Part2:", parsed_input["humn"] - 2)
