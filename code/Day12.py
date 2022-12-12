from utils import DataFiles
import networkx

dataFiles = DataFiles(__file__)

input = dataFiles.get_input(splitlines=True)  # dataFiles.get_input_chunks(sep="\n\n")
inputEX = dataFiles.get_input(splitlines=True, example=True)

dirs_letter = {"U": [-1, 0], "D": [1, 0], "L": [0, -1], "R": [0, 1]}
dirs = [[-1, 0], [1, 0], [0, -1], [0, 1]]

xs, ys = 0, 0
xe, ye = 0, 0

max_x = len(input)
max_y = len(input[0])

for aux_x in range(max_x):
    y_S = input[aux_x].find("S")
    y_E = input[aux_x].find("E")

    if y_S != -1:
        xs, ys = aux_x, y_S
        input[aux_x] = input[aux_x].replace("S", "a")

    if y_E != -1:
        xe, ye = aux_x, y_E
        input[aux_x] = input[aux_x].replace("E", "z")

print(xs, ys, xe, ye)


def char_to_ascii(x):
    return ord(x)


G = networkx.DiGraph()

for x in range(max_x):
    for y in range(max_y):
        for dx, dy in dirs:
            new_x = x + dx
            new_y = y + dy
            if 0 <= new_x < max_x and 0 <= new_y < max_y:

                xy_elev = char_to_ascii(input[x][y])
                new_xy_elev = char_to_ascii(input[new_x][new_y])

                if new_xy_elev <= xy_elev + 1:

                    G.add_edge((x, y), (new_x, new_y))


p1 = networkx.shortest_path(G, (xs, ys), (xe, ye))
print(len(p1) - 1)

p2 = 99999999999999999999

for x in range(max_x):
    for y in range(max_y):
        if input[x][y] == "a":
            if networkx.has_path(G, (x, y), (xe, ye)):
                p2_aux = networkx.shortest_path(G, (x, y), (xe, ye))
                p2 = min(p2, len(p2_aux) - 1)

print(p2)
