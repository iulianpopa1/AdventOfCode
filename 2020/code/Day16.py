from utils import DataFiles
import re


dataFiles = DataFiles(__file__)

input = dataFiles.get_input()  # inputRaw = dataFiles.input
inputEX = dataFiles.get_inputEX()  # inputRawEX = dataFiles.inputEX


rule_re = re.compile(r'^(.*): (\d+)-(\d+) or (\d+)-(\d+)$')


def parse(inputt):
    i = 0
    rules = {}
    while inputt[i] != '':
        reg = re.findall(rule_re, inputt[i])
        f = reg[0]
        rules[f[0]] = [range(int(f[1]), int(f[2]) + 1),
                       range(int(f[3]), int(f[4]) + 1)]
        i += 1

    your_ticket = []
    while inputt[i] != 'nearby tickets:':
        if(inputt[i - 1] == 'your ticket:'):
            your_ticket = [int(x) for x in inputt[i].strip().split(',')]
        i += 1

    i += 1

    nearby = []
    for j in range(i, len(inputt)):
        numbers = [int(x) for x in inputt[j].strip().split(',')]
        nearby.append(numbers)

    return rules, your_ticket, nearby


def check_nr(n, rules):
    return any(n in ran for rule in rules.values() for ran in rule)


def main():
    rules, your_ticket, nearby = parse(input)
    valid_nearby = []

    sum_p1 = 0
    for ticket in nearby:
        valid_ticket = True
        for nr in ticket:
            if check_nr(nr, rules) == False:
                sum_p1 += nr
                valid_ticket = False
        if valid_ticket == True:
            valid_nearby.append(ticket)

    print('Part1:', sum_p1)

    possible_fields = dict()
    for name, rule in rules.items():
        for j in range(len(valid_nearby[0])):
            if all(any(v[j] in ran for ran in rule) for v in valid_nearby):
                if name in possible_fields:
                    possible_fields[name].add(j)
                else:
                    possible_fields[name] = {j}

    used = set()
    prod_p2 = 1

    for p in sorted(possible_fields, key=lambda l: len(possible_fields[l])):
        if p.split()[0] == 'departure':
            for x in possible_fields[p] - used:
                prod_p2 *= your_ticket[x]
        for aux in possible_fields[p]:
            used.add(aux)

    print('Part2:', prod_p2)


main()
