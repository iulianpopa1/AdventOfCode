from numpy.lib.shape_base import tile
from utils import DataFiles
import numpy as np
from collections import defaultdict

dataFiles = DataFiles(__file__)

input = dataFiles.get_input()  # inputRaw = dataFiles.input
inputEX = dataFiles.get_inputEX()  # inputRawEX = dataFiles.inputEX


def parse(inp):
    tiles = {}
    i = 0
    while i < len(inp):
        tile_id = 0
        tile = []
        for j in range(11):
            if i % 12 == 0:
                tile_id = int(inp[i].split('Tile ')[1][:-1])
            else:
                tile.append(inp[i])
            i += 1
        tiles[tile_id] = tile
        i += 1

    return tiles


def printa(arr):
    print('\n')
    for x in arr:
        print(x)


def rotate_cw(tile): return list(map("".join, zip(*reversed(tile))))
def flip_vert(tile): return tile[::-1]
def flip_hor(tile): return [line[::-1] for line in tile]


glb_b = {}
glb_tid_b = {}


def add_border(tile_id, border):
    if border in glb_b.keys():
        glb_b[border].append(tile_id)
    else:
        glb_b[border] = [tile_id]


def add_borders_for_tid(tile_id, u, d, l, r):
    glb_tid_b[tile_id] = [u, r, d, l]


def get_borders(tiles, tile_id):
    tile = tiles[tile_id]
    u = tile[0]  # UP BORDER
    d = tile[-1]  # DOWN BORDER
    l = flip_hor(rotate_cw(tile))[0]  # LEFT BORDER
    r = flip_hor(rotate_cw(tile))[-1]  # RIGHT BORDER

    add_border(tile_id, u)
    add_border(tile_id, r)
    add_border(tile_id, d)
    add_border(tile_id, l)
    add_border(tile_id, u[::-1])
    add_border(tile_id, r[::-1])
    add_border(tile_id, d[::-1])
    add_border(tile_id, l[::-1])
    add_borders_for_tid(tile_id, u, d, l, r)


tiles = parse(input)


for tile in tiles.keys():
    get_borders(tiles, tile)

corners = set()

for t_id in glb_tid_b:
    t_b = glb_tid_b[t_id]
    for i in range(4):
        if( len(glb_b[t_b[i]]) == 2 
        and len(glb_b[t_b[(i + 1) % 4]]) == 2 
        and len(glb_b[t_b[(i + 2) % 4]]) == 1 
        and len(glb_b[t_b[(i + 3) % 4]]) == 1):
            print("yes", t_id)
            corners.add(t_id)

print(corners)
ans = 1
for i in corners:
    ans *= i
print(ans)
    

# for t_id in glb_tid_b:
#     t_b = glb_tid_b[t_id]
#     print('\n')
#     print(t_id)
#     for i in range(4):
#         print(t_b[i], len(glb_b[t_b[i]]))
#         #print(len(glb_b[b]))


# printa(tiles[1427])
# rotate(tiles)
