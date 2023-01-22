fin = open("input.txt", "r")
fout = open("P_input.txt", 'w')

splitted_lines = []
lines = fin.readlines()
for line in lines:
    splitted = line.split(sep=')')
    print(splitted)

    for elem in splitted:
        fout.write(elem + ' ')


