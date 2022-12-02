from utils import DataFiles

dataFiles = DataFiles(__file__)

input = dataFiles.get_input(splitlines=True)  # dataFiles.get_input_chunks(sep="\n\n")
inputEX = dataFiles.get_input(splitlines=True, example=True)

obj_score = {
    "X": 1,  # X(rock) ~ 1pt
    "Y": 2,  # Y(paper) ~ 2pt
    "Z": 3,  # Z(scissors) ~ 3pt
}

battle_score = {
    "LOSE": 0,  # LOSE  ~ 0 pt
    "DRAW": 3,  # DRAW  ~ 3 pt
    "WIN": 6,  # WIN   ~ 6 pt
}

# the outcome for the player2 against player1
battle_eval = {
    "A": {
        "X": "DRAW",
        "Y": "WIN",  # Y vs A
        "Z": "LOSE",  # Z vs A
    },
    "B": {
        "X": "LOSE",
        "Y": "DRAW",
        "Z": "WIN",
    },
    "C": {
        "X": "WIN",
        "Y": "LOSE",
        "Z": "DRAW",
    },
}

battle_eval_p2 = {}
for key in battle_eval.keys():
    battle_eval_p2[key] = dict((v, k) for k, v in battle_eval[key].items())

req_outcome_p2 = {"X": "LOSE", "Y": "DRAW", "Z": "WIN"}

total_p1 = 0
total_p2 = 0

for line in input:
    p1, p2 = line.split()

    total_p1 += obj_score[p2] + battle_score[battle_eval[p1][p2]]

    total_p2 += battle_score[req_outcome_p2[p2]] + obj_score[battle_eval_p2[p1][req_outcome_p2[p2]]]

print("Part 1:", total_p1)
print("Part 2:", total_p2)
