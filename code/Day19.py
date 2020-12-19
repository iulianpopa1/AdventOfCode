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
        spl = line.split(': ')
        rules[spl[0]] = spl[1]
    
    return rules, messages

def decode():
    for k, v in rules.items():
        if(v[0] == '"'):
            decoded[k] = v[1]
        else:
            spl = v.split()
            fully_decoded = True

            for s in spl:
                if s not in decoded.keys() and s != '|':
                    fully_decoded = False

            if fully_decoded == True:
                r = ''
                for s in spl:
                    if s in decoded.keys():
                        r += decoded[s]
                    else:
                        r += '|'

                decoded[k] = '(' + r + ')'


rules, messages = parse(input)
decoded = {}

while '0' not in decoded.keys():
    decode()

p1 = 0
for message in messages:
    if re.match('^' + decoded['0'] + '$', message):
        p1 += 1

print('Part1:', p1)

messages_found = set()
rules['8'] = '42 | 42 8'
rules['11'] = '42 31 | 42 11 31'

while True:
    is_loop = True
    decode()

    for message in messages:
        if re.match('^' + decoded['0'] + '$', message):
            messages_found.add(message)
            if message not in messages_found:
                messages_found.add(message)
                is_loop = False
    
    if is_loop == True:
        print('Part2:', len(messages_found))
        break




