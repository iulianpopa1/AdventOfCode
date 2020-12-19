from utils import DataFiles
import re

dataFiles = DataFiles(__file__)

input = dataFiles.get_input()  # inputRaw = dataFiles.input
inputEX = dataFiles.get_inputEX()  # inputRawEX = dataFiles.inputEX


def parse(input):
    rules_input = input[:input.index('')]
    messages = input[input.index(''):]

    rules = {}

    for line in rules_input:
        rules[line.split(': ')[0]] = line.split(': ')[1]

    return rules, messages


def decode():
    for k, v in rules.items():
        if(v[0] == '"'):
            decoded[k] = v[1]
        else:
            fully_decoded = True

            for s in v.split():
                if s not in decoded.keys() and s != '|':
                    fully_decoded = False

            if fully_decoded == True:
                r = ''
                for s in v.split():
                    if s in decoded.keys():
                        r += decoded[s]
                    else:
                        r += '|'

                decoded[k] = '(' + r + ')'


def part1():
    while '0' not in decoded.keys():
        decode()

    count = 0
    for message in messages:
        if re.match('^' + decoded['0'] + '$', message):
            count += 1
    return count


def part2():
    messages_found = set()
    rules['8'] = '42 | 42 8'
    rules['11'] = '42 31 | 42 11 31'

    while True:
        decode()
        prev_size = len(messages_found)

        for message in messages:
            if re.match('^' + decoded['0'] + '$', message):
                messages_found.add(message)

        if len(messages_found) == prev_size: #There's a loop
            return len(messages_found)


rules, messages = parse(input)
decoded = {}

print('Part1:', part1())
print('Part2:', part2())
