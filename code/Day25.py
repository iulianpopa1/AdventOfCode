from utils import DataFiles

dataFiles = DataFiles(__file__)

input = dataFiles.get_input()  # inputRaw = dataFiles.input
inputEX = dataFiles.get_inputEX()  # inputRawEX = dataFiles.inputEX

def run(inp):
    val_a = 1
    loop_a = 1
    while loop_a >= 0:
        val_a = (val_a * 7) % 20201227
        if int(inp[0]) == val_a:
            break
        loop_a += 1

    
    val_b = 1
    for _ in range(loop_a):
        val_b = (val_b * int(inp[1])) % 20201227
    
    print(val_b)

run(input)
