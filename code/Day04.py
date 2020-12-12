import re
from utils import DataFiles

dataFiles = DataFiles(__file__)

inputRaw = dataFiles.input
inputRawEX = dataFiles.inputEX

input = inputRaw.read().split("\n\n")

def verify(passport):
    field_regex = re.compile(r'(byr|iyr|eyr|hgt|hcl|ecl|pid):(.*?)(?:\s|\Z)')
    field_list = re.findall(field_regex, passport)
    field = dict(field_list)

    if len(field) != 7:
        return False, False

    rules = [
        1920 <= int(field['byr']) <= 2002,
        2010 <= int(field['iyr']) <= 2020,
        2020 <= int(field['eyr']) <= 2030,
        field['hgt'][-2:] == 'cm' and 150 <= int(field['hgt'][:-2]) <= 193 or
        field['hgt'][-2:] == 'in' and 59 <= int(field['hgt'][:-2]) <= 76,
        re.match(r'^#[0-9a-f]{6}$', field['hcl']),
        re.match(r'amb|blu|brn|gry|grn|hzl|oth', field['ecl']),
        re.match(r'^[0-9]{9}$', field['pid'])
    ]

    return True, all(rules)
    

p1 = 0
p2 = 0

for line in input:
    p1_ver, p2_ver = verify(line)
    if p1_ver:
        p1 += 1
    if p2_ver:
        p2 += 1

print('Part1:', p1)
print('Part2:', p2)
