from utils import DataFiles

dataFiles = DataFiles(__file__)

input = dataFiles.input
inputEX = dataFiles.inputEX

inp = input[:]


class Board:
    def __init__(self, vals):
        self.position = {}
        self.playBoard = [
            [0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0],
        ]
        self.bingo = {"row": [0, 0, 0, 0, 0], "col": [0, 0, 0, 0, 0], "diagonal": [0, 0]}
        self.createBoard(vals)

    def createBoard(self, vals):
        for i in range(5):
            for j in range(5):
                choice = vals[i][j]
                self.playBoard[i][j] = choice
                self.position[choice] = (i, j)

    def updateBoard(self, val):
        if val in self.position:
            x, y = self.position[val]
            self.playBoard[x][y] = "X"
            self.updateBingo(x, y)

    def updateBingo(self, x, y):
        self.bingo["row"][x] += 1
        self.bingo["col"][y] += 1
        if x == y == 2:
            self.bingo["diagonal"][0] += 1
            self.bingo["diagonal"][1] += 1
        elif x == y:
            self.bingo["diagonal"][0] += 1
        elif x + y == 4:
            self.bingo["diagonal"][1] += 1

    def checkBingo(self):
        return 5 in self.bingo["row"] or 5 in self.bingo["col"]  # or 5 in self.bingo["diagonal"]

    def printBoard(self):
        print("\n")
        for i in range(5):
            print(self.playBoard[i])

    def sumOfUnmarkedNumbers(self):
        nr_sum = 0
        for i in range(5):
            for j in range(5):
                if board.playBoard[i][j] != "X":
                    nr_sum += board.playBoard[i][j]
        return nr_sum


bingoBoards = []

for x in range(len(inp)):
    if len(inp[x]) == 0:
        bingoBoards.append(Board([[int(nr) for nr in inp[x + i].split()] for i in range(1, 6)]))
        x += 5

lastBingo = -1

for number in [int(nr) for nr in inp[0].split(",")]:
    for board in bingoBoards:
        board.updateBoard(number)
        if board.checkBingo():
            unmarkedSum = board.sumOfUnmarkedNumbers()
            # print("{0} BINGO! => Ans: {1} ({2} * {3})".format(number, nr_sum * number, number, nr_sum))
            bingoBoards.remove(board)

            if lastBingo == -1:
                print("Part1:", number * unmarkedSum)
            lastBingo = number * unmarkedSum


print("Part2:", lastBingo)
