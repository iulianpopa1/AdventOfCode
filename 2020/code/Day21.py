from utils import DataFiles

dataFiles = DataFiles(__file__)

input = dataFiles.get_input()  # inputRaw = dataFiles.input
inputEX = dataFiles.get_inputEX()  # inputRawEX = dataFiles.inputEX

def parse(inp):
    allergenss = {}
    ingredients = set()
    for line in inp:
        ingreds = set(line.split(" (contains ")[0].split())
        allerg = line.split(" (contains ")[1][:-1].split(", ")

        ingredients = set.union(ingredients, ingreds)

        for allergen in allerg:
            if allergen not in allergenss:
                allergenss[allergen] = ingreds
            else:
                allergenss[allergen] = set.intersection(allergenss[allergen], ingreds)

    for v in allergenss.values():
        ingredients = set.difference(ingredients, set(v))

    return allergenss, ingredients


def part1(ingredients, inp):
    ans = 0
    for line in inp:
        ingreds = set(line.split(" (contains ")[0].split())
        for ingred in ingreds:
            if ingred in ingredients:
                ans += 1
    return ans


def part2(allergens):
    keys = sorted(allergens.keys(), key=lambda x: len(allergens[x]))
    saved_alerg_w_ingred = dict()

    i = 0
    while i < len(keys):
        allergen = list(allergens[keys[i]])
        if len(allergen) == 1:
            saved_alerg_w_ingred[keys[i]] = allergen[0]
            for j in range(len(keys)):
                if allergen[0] in allergens[keys[j]]:
                    allergens[keys[j]].remove(allergen[0])
            i = 0
        else:
            i += 1
    
    return ','.join([saved_alerg_w_ingred[x] for x in sorted(saved_alerg_w_ingred)])


allergenss, ingredients = parse(input)
print('Part1:', part1(ingredients, input))
print('Part2:', part2(allergenss))
