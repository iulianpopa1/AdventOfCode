import re
from utils import DataFiles

dataFiles = DataFiles(__file__)

input = dataFiles.get_input()  # inputRaw = dataFiles.input
inputEX = dataFiles.get_inputEX()  # inputRawEX = dataFiles.inputEX


reg_big_attr = re.compile(r'(.*) bags contain (.*).$')
reg_shiny_gold = re.compile(r'(\d+) shiny gold')
reg_no_col = re.compile(r'^(\d+) (.*) bag.*$')


p1 = 0
bag_dict_ingredients = dict()

for line in inputEX:
    xx = reg_big_attr.findall(line)
    
    bag_main = xx[0][0]
    bag_dict_ingredients[bag_main] = dict()

    xxx = xx[0][1].split(', ')

    for xxxx in xxx:
        yy = reg_no_col.findall(xxxx)
        if(len(yy) != 0):
            bag_comp = yy[0][1]
            bag_comp_q = yy[0][0]
            bag_dict_ingredients[bag_main][bag_comp] = bag_comp_q


def apart_bag(bag_col):
    p2 = 0
    if len(bag_dict_ingredients[bag_col]) == 0:
        return 0
    
    for aux_bag in bag_dict_ingredients[bag_col]:
        ingredients = int(bag_dict_ingredients[bag_col][aux_bag])
        more_ing = apart_bag(aux_bag)
        p2 += ingredients + ingredients * more_ing
    return p2


print(apart_bag('shiny gold'))


# Part 1
# cont_bags = set()
# cont_bags.add('shiny gold')

# found = True
# while found == True:
#     found = False
#     for bag, ingredients in bag_dict_ingredients.items():
#         if bag not in cont_bags:
#             for aux in ingredients.keys():
#                 if aux in cont_bags:
#                     cont_bags.add(bag)
#                     print(ingredients)
#                     found = True
#                     break

# print('Part1 :', len(cont_bags) - 1)

