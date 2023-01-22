from utils import DataFiles

dataFiles = DataFiles(__file__)

inputRaw = dataFiles.input
inputRawEX = dataFiles.inputEX


def calc_score(q1, q2):
    ans = 0

    if(len(q1) > 0):
        for i in range(1, len(q1) + 1):
            ans += i * q1[-i]
    else:
        for i in range(1, len(q2) + 1):
            ans += i * q2[-i]

    return ans


def part1(q1, q2):
    while(len(q1) > 0 and len(q2) > 0):
        c1 = q1[0]
        c2 = q2[0]

        if c1 > c2:
            q1 = q1[1:] + [c1, c2]
            q2 = q2[1:]
        else:
            q1 = q1[1:]
            q2 = q2[1:] + [c2, c1]

    return q1, q2


def part2(q1, q2):
    used = set()
    while(len(q1) > 0 and len(q2) > 0):
        roundLog = (tuple(q1), tuple(q2))
        if roundLog in used:
            return q1, q2, 1
        else:
            used.add(roundLog)

        c1 = q1[0]
        c2 = q2[0]
        winner = 0

        if len(q1) > c1 and len(q2) > c2:
            _, _, winner = part2(q1[1:c1 + 1], q2[1:c2 + 1])
        
        if winner == 1 or (c1 > c2 and winner == 0):
            q1 = q1[1:] + [c1, c2]
            q2 = q2[1:]
        else:
            q1 = q1[1:]
            q2 = q2[1:] + [c2, c1]

    if len(q1) > 0:
        return q1, q2, 1
    else:
        return q1, q2, 2


def main(inp):
    players = inp.read().split('\n\n')

    q1 = [int(x) for x in players[0].splitlines()[1:]]
    q2 = [int(x) for x in players[1].splitlines()[1:]]   

    q1_c, q2_c = part1(list.copy(q1), list.copy(q2))
    print('Part1:', calc_score(q1_c, q2_c))

    q1_cc, q2_cc, _ = part2(list.copy(q1), list.copy(q2))
    print('Part2:', calc_score(q1_cc, q2_cc))


main(inputRaw)
