from utils import DataFiles

dataFiles = DataFiles(__file__)

input = dataFiles.get_input()  # inputRaw = dataFiles.input
inputEX = dataFiles.get_inputEX()  # inputRawEX = dataFiles.inputEX

numbers = [int(line) for line in input]
numbers.sort()

diff_1 = 0
diff_3 = 1

prev = 0

for curr in numbers:
    diff = curr - prev
    if diff == 1:
        diff_1 += 1
    if diff == 3:
        diff_3 += 1
    prev = curr

print('Part 1:', diff_1 * diff_3)

numbers.insert(0, 0)

dp = [1] + [0] * len(numbers)

for i in range(len(numbers)):
    for j in range(i):
        if(numbers[i] - numbers[j] <= 3):
            dp[i] += dp[j]

print('Part 2:', dp[len(numbers) - 1])
