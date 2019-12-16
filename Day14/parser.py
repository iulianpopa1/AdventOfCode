
fin = open("input.txt", "r")
fout = open("P_input.txt", 'w')

splitted_lines = []
lines = fin.readlines()

for line in lines:
    line = line.strip()
    line = line.replace(',', '')
    line = line.replace('=>', '-1 =>')

    line = line.strip()

    splitted_lines.append(line + ' ') #extend(elem)

print(splitted_lines)

for elem in splitted_lines:
    elem.strip()
    fout.write(elem + '\n')
