from utils import DataFiles

dataFiles = DataFiles(__file__)

input = dataFiles.get_input()  # inputRaw = dataFiles.input
inputEx = dataFiles.get_inputEX()  # inputRawEX = dataFiles.inputEX

def solve(seat):
    fb_min = 0
    fb_max = 127
    lr_min = 0
    lr_max = 7

    for ch in seat:
        if ch == 'F' or ch == 'B':
            half = (fb_max - fb_min + 1) // 2
            if ch == 'F':
                fb_max -= half
            elif ch == 'B':
                fb_min += half 
        else:
            if ch == 'L' or ch == 'R':
                half = (lr_max - lr_min + 1) // 2
                if ch == 'L':
                    lr_max -= half
                elif ch == 'R':
                    lr_min += half

    return fb_min * 8 + lr_max

    

seats = []
for coded_seat in input:
    decoded_seat = solve(coded_seat)
    seats.append(decoded_seat)

max_seat = max(seats)
print('Part 1:', max_seat)

for i in range(min(seats), max_seat):
    if i not in seats:
        print('Part 2:', i)


