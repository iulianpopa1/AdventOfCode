from utils import DataFiles

dataFiles = DataFiles(__file__)

input = dataFiles.get_input(splitlines=True)  # dataFiles.get_input_chunks(sep="\n\n")
inputEX = dataFiles.get_input(splitlines=True, example=True)


def range_overlap_p1(x1, x2, y1, y2):
    return int(x1) <= int(y1) <= int(y2) <= int(x2) or int(y1) <= int(x1) <= int(x2) <= int(y2)


def range_overlap_p2(x1, x2, y1, y2):
    return (int(x2) >= int(y1) and int(x1) <= int(y2)) or (int(y2) >= int(x1) and int(y1) <= int(x2))


ttl_p1 = 0
ttl_p2 = 0
for line in input:
    x, y = line.split(",")
    x1, x2 = x.split("-")
    y1, y2 = y.split("-")
    ttl_p1 += range_overlap_p1(x1, x2, y1, y2)
    ttl_p2 += range_overlap_p2(x1, x2, y1, y2)

print(ttl_p1)
print(ttl_p2)
