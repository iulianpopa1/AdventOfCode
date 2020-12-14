from utils import DataFiles
import re

dataFiles = DataFiles(__file__)

input = dataFiles.get_input()  # inputRaw = dataFiles.input
inputEX = dataFiles.get_inputEX()  # inputRawEX = dataFiles.inputEX

re_mask = re.compile(r'^mask = (\w+)$')
re_mem = re.compile(r'^mem\[(\d+)\] = (\d+)$')

ans_p1 = dict()
ans_p2 = dict()

def modifyBit(n,  p,  b):
    mask = 1 << p
    return (n & ~mask) | ((b << p) & mask)

def modify_val(val, msk):
    for pos, bit in enumerate(reversed(msk)):
        if bit == 'X':
            pass
        else:
            val = modifyBit(val, pos, int(bit))
    return val


def modify_id(id, msk):
    floating_bits = []

    for pos, bit in enumerate(reversed(msk)):
        if bit == '0':
            pass
        elif bit == '1':
            id = modifyBit(id, pos, 1)
        else:
            floating_bits.append(pos)
    
    wr_to_mem = set()
    wr_to_mem.add(id)

    for fl_b in floating_bits:
        add_to_wr = []
        
        for idx in wr_to_mem:
            add_to_wr.append(modifyBit(idx, fl_b, 0))
            add_to_wr.append(modifyBit(idx, fl_b, 1))

        for nr in add_to_wr:
            wr_to_mem.add(nr)

    return wr_to_mem


def part1(inputt):
    for i in range(len(inputt)):
        msk = re.findall(re_mask, inputt[i])
        if(len(msk) > 0):
            i += 1

            while i < len(inputt):
                mem = re.findall(re_mem, inputt[i])
                if len(mem) > 0:                    
                    ans_p1[int(mem[0][0])] = modify_val(int(mem[0][1]), msk[0])
                    i += 1
                else:
                    break
    sum = 0
    for _, val in ans_p1.items():
        sum += val

    return sum


def part2(inputt):
    for i in range(len(inputt)):
        msk = re.findall(re_mask, inputt[i])
        if(len(msk) > 0):
            i += 1

            while i < len(inputt):
                mem = re.findall(re_mem, inputt[i])
                if len(mem) > 0:
                    write_to_mem = modify_id(int(mem[0][0]), msk[0])

                    for mm in write_to_mem:
                        ans_p2[mm] = int(mem[0][1])

                    i += 1
                else:
                    break
    sum = 0
    for _, val in ans_p2.items():
        sum += val
    
    return sum
    

print('Part1:', part1(input))
print('Part2:', part2(input))
