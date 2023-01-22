from utils import DataFiles
import re

dataFiles = DataFiles(__file__)

input = dataFiles.get_input(splitlines=True)  # dataFiles.get_input_chunks(sep="\n\n")
inputEX = dataFiles.get_input(splitlines=True, example=True)

curr_folder = ""

file_sizes = {}

for line in input:
    if line.startswith("$ ls"):
        continue
    if line[0] == "$":
        aux_line = line
        aux_line = aux_line.removeprefix("$ ")

        if aux_line.startswith("cd"):
            aux_line = aux_line.removeprefix("cd ")

            if aux_line == "..":
                curr_folder = curr_folder.removesuffix("/" + curr_folder.split("/")[-1])
                if len(curr_folder) == 0:
                    curr_folder = "/"
            else:
                if aux_line == "/":
                    curr_folder += "/"
                else:
                    if curr_folder != "/":
                        curr_folder += "/" + aux_line.strip()
                    else:
                        curr_folder += aux_line.strip()

            curr_folder = curr_folder.strip()
        continue

    if line.startswith("dir"):
        continue

    size, name = line.split(" ")

    aux_file = ""
    for i in ["/"] + curr_folder.split("/"):
        if i != "":
            aux_file += i
            if aux_file not in file_sizes:
                file_sizes[aux_file] = int(size)
            else:
                file_sizes[aux_file] += int(size)

total_p1 = 0

for folder, size in file_sizes.items():
    if size <= 100000:
        total_p1 += size

print("Part1:", total_p1)

fs_total = 70000000
fs_req = 30000000
sys_total = file_sizes["/"]
free_space = fs_total - sys_total

sizes = sorted(list(file_sizes.values()))

for size in sizes:
    if free_space + size >= fs_req:
        print("Part2:", size)
        break
