fin = open("input.txt", "r")
text = fin.read()
# 🡅🡅🡅 Read from file 🡅🡅🡅


#print()
x = text.split(sep=',')
print(x)


# 🡇🡇🡇 Write in file 🡇🡇🡇
fout = open("P_input.txt", 'w')
for i in x:
    fout.write(i)
    fout.write('\n')
#fout.write(x)