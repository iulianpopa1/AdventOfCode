#fin = open("input.txt", "r")
fout = open("P_input.txt", 'w')

#text = fin.read()
# 🡅🡅🡅 Read from file 🡅🡅🡅

with open("input.txt", "r") as fin:
    line1 = fin.readline()
    sp = line1.split(sep=',')
    print(sp)
    for strr in sp:
        fout.write('\n' + strr[0] + ' ' + strr[1:])

    fout.write('X 0')

    line2 = fin.readline()
    sp = line2.split(sep=',')
    print(sp)
    for strr in sp:
        fout.write('\n' + strr[0] + ' ' + strr[1:])
