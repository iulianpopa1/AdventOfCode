from utils import DataFiles
import re

dataFiles = DataFiles(__file__)

input = dataFiles.get_input_chunks(sep="\n\n")
inputEX = dataFiles.get_input_chunks(sep="\n\n", example=True)


class Monkey:
    def __init__(self, input_chunk):
        lines = input_chunk.splitlines()
        self.monkey_nr = int(lines[0][len("Monkey ") : -len(":")])
        self.items = [int(item.strip()) for item in lines[1][len("  Starting items: ") :].split(",")]
        self.action_op, self.action_val = (lines[2][len("  Operation: new = old ") :]).split()
        self.test_div_by = int(lines[3][len("  Test: divisible by ") :])
        self.if_true = int(lines[4][len("    If true: throw to monkey ") :])
        self.if_false = int(lines[5][len("    If false: throw to monkey ") :])

    def print(self):
        print("monkey_nr:", self.monkey_nr)
        print("starting_items", self.items)
        print("operation_for_new_op", self.action_op, "operation_for_new_value", self.action_val)
        print("divisible_by", self.test_div_by)
        print("test_true", self.if_true)
        print("test_false", self.if_false)


def eval_op(old, op, value):
    if op == "+":
        if value == "old":
            return old + old
        else:
            return old + int(value)
    if op == "*":
        if value == "old":
            return old * old
        else:
            return old * int(value)


monkeys = []

for chunk in input:
    monkeys.append(Monkey(chunk))

gcd = 1
for monkey in monkeys:
    gcd *= monkey.test_div_by

counts = [0] * len(monkeys)

for round in range(20):
    for m_index in range(len(monkeys)):
        while len(monkeys[m_index].items) > 0:
            old = monkeys[m_index].items.pop(0)
            new = eval_op(old, monkeys[m_index].action_op, monkeys[m_index].action_val) % gcd  # // 3 # for Part 1

            if new % monkeys[m_index].test_div_by == 0:
                monkeys[monkeys[m_index].if_true].items.append(new)
            else:
                monkeys[monkeys[m_index].if_false].items.append(new)

            counts[m_index] += 1

cnt = sorted(counts, reverse=True)
print(cnt[0] * cnt[1])
