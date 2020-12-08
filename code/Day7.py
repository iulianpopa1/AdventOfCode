import re
from utils import DataFiles

dataFiles = DataFiles(__file__)

input = dataFiles.get_input()  # inputRaw = dataFiles.input
inputEX = dataFiles.get_inputEX()  # inputRawEX = dataFiles.inputEX


def contains_color(bag_color):
    for color, needed in bag_rules.items():
        if bag_color in needed.keys():
            contains_gold.add(color)
            contains_color(color)


def needed_bags(bag_color):
    total = 0

    if len(bag_rules[bag_color]) == 0:
        return 0

    for comp_bag in bag_rules[bag_color]:
        no_bags = bag_rules[bag_color][comp_bag]

        need_bags = needed_bags(comp_bag)

        total += no_bags + no_bags * need_bags
    return total


bag_rules = dict()  # key: color, value: dict(color, quantity)

# Parsing
for line in input:
    color, all_rules = re.findall(r'(.*) bags contain (.*).$', line)[0]

    bag_rules[color] = dict()

    rules = all_rules.split(', ')

    for rule in rules:
        try:
            bag_quantity, bag_color = re.findall(r'^(\d+) (.*) bag.*$', rule)[0]
            bag_rules[color][bag_color] = int(bag_quantity)
        except:
            pass

contains_gold = set()
contains_color('shiny gold')

print('Part 1:', len(contains_gold))
print('Part 2:', needed_bags('shiny gold'))