#fin = open("input.txt", "r")
fout = open("P_input.txt", 'w')
with open("input.txt", "r") as fin:
    line = fin.readline()
    splitted = line.split(sep=',')
    print(splitted)
    for elem in splitted:
        fout.write(elem + '\n')