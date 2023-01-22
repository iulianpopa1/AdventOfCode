fin = open("input.txt", "r")
fout = open("P_input.txt", 'w')

splitted_lines = []
lines = fin.readlines()
for line in lines:
    splitted = line.split(sep=',')
    print(splitted)

    for elem in splitted:
        splitted_lines.append(elem) #extend(elem)

print(splitted_lines)

for elem in splitted_lines:
    fout.write(elem + '\n')