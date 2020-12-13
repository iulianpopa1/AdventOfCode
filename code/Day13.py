from utils import DataFiles

dataFiles = DataFiles(__file__)

input = dataFiles.get_input()  # inputRaw = dataFiles.input
inputEX = dataFiles.get_inputEX()  # inputRawEX = dataFiles.inputEX


def part1():
    ts = int(input[0])
    ts_c = ts
    buses = [int(x) for x in input[1].split(',') if x != "x"]

    while all(ts_c % n != 0 for n in buses):
        ts_c += 1

    for bus in buses:
        if ts_c % bus == 0:
            return bus * (ts_c - ts)


def part2():
    ts = int(input[0])
    ts_c = ts
    buses = ['x' if x == 'x' else int(x) for x in input[1].split(',')]

    while True:
        v_bus = [bus for i, bus in enumerate(buses) if bus != 'x' and (ts_c + i) % bus == 0]
        add = 1
        for aux in v_bus:
            add *= aux
        ts_c += add

        if all([(ts_c + i) % x == 0 for i, x in enumerate(buses) if x != 'x']):
            return ts_c

print('Part1:', part1())
print('Part2:', part2())
