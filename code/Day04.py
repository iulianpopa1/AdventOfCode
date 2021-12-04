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

    def printBingo(self):
        print("\n")
        for i in range(5):
            print(self.playBoard[i])


print(len(inp[1]))

myBingos = []
for x in range(1, len(inp)):
    if len(inp[x]) == 0:
        board = Board(
            [
                [int(x) for x in inp[x + 1].split()],
                [int(x) for x in inp[x + 2].split()],
                [int(x) for x in inp[x + 3].split()],
                [int(x) for x in inp[x + 4].split()],
                [int(x) for x in inp[x + 5].split()],
            ]
        )
        myBingos.append(board)
    x += 5


# for x in inp[0].split(',')
found_bingo = False
summ = 0
for x in [int(y) for y in inp[0].split(",")]:
    for xx in myBingos:
        xx.updateBoard(x)
        if xx.checkBingo():
            summ = 0
            found_bingo = True
            print("bingo : ", x)
            for i in range(5):
                for j in range(5):
                    if xx.playBoard[i][j] != "X":
                        summ += xx.playBoard[i][j]
            print(summ, x)
            print(summ * x)
            print("\n")
            myBingos.remove(xx)
