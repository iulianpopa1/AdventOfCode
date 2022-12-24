from utils import DataFiles
from math import ceil

dataFiles = DataFiles(__file__)

input = dataFiles.get_input(splitlines=True)  # dataFiles.get_input_chunks(sep="\n\n")
inputEX = dataFiles.get_input(splitlines=True, example=True)

parsed_input = []
for line in input:
    rows = line.split(". ")
    aux_line = rows[0].removeprefix("Blueprint ").removesuffix(" ore").split(": Each ore robot costs ")
    blueprint_nr, ore_robot_cost_ore = int(aux_line[0]), int(aux_line[1])
    clay_robot_cost_ore = int(rows[1].removeprefix("Each clay robot costs ").removesuffix(" ore"))
    aux_line = rows[2].removeprefix("Each obsidian robot costs ").removesuffix(" clay").split(" ore and ")
    obsidian_robot_cost_ore, obsidian_robot_cost_clay = int(aux_line[0]), int(aux_line[1])
    aux_line = rows[3].removeprefix("Each geode robot costs ").removesuffix(" obsidian.").split(" ore and ")
    geode_robot_cost_ore, geode_robot_cost_obsidian = int(aux_line[0]), int(aux_line[1])

    parsed_input.append(
        (
            blueprint_nr,
            ore_robot_cost_ore,  # 1
            clay_robot_cost_ore,  # 2
            obsidian_robot_cost_ore,  # 3
            obsidian_robot_cost_clay,  # 4
            geode_robot_cost_ore,  # 5
            geode_robot_cost_obsidian,  # 6
        )
    )


def step(costs, resources=(0, 0, 0), dr=(1, 0, 0), timeleft=24):

    if timeleft == 1:
        return 0

    need_ore = dr[0] < int(ceil((max(costs[0], costs[1], costs[2], costs[4]) * timeleft - resources[0]) / timeleft))
    need_clay = dr[1] < int(ceil((costs[3] * timeleft - resources[1]) / timeleft))
    need_obsidian = dr[2] < int(ceil((costs[5] * timeleft - resources[2]) / timeleft))

    build_geode = resources[0] >= costs[4] and resources[2] >= costs[5]
    build_obsidian = resources[0] >= costs[2] and resources[1] >= costs[3] and need_obsidian
    build_clay = resources[0] >= costs[1] and need_clay and need_obsidian
    build_ore = resources[0] >= costs[0] and need_ore

    score = 0
    if build_geode:
        aux_res = (resources[0] + dr[0] - costs[4], resources[1] + dr[1], resources[2] + dr[2] - costs[5])
        score = max(score, step(costs, resources=aux_res, dr=dr, timeleft=timeleft - 1) + timeleft - 1)
    elif build_obsidian:
        aux_res = (resources[0] + dr[0] - costs[2], resources[1] + dr[1] - costs[3], resources[2] + dr[2])
        score = max(score, step(costs, resources=aux_res, dr=(dr[0], dr[1], dr[2] + 1), timeleft=timeleft - 1))
    else:
        if build_ore:
            aux_res = (resources[0] + dr[0] - costs[0], resources[1] + dr[1], resources[2] + dr[2])
            score = max(score, step(costs, resources=aux_res, dr=(dr[0] + 1, dr[1], dr[2]), timeleft=timeleft - 1))
        if build_clay:
            aux_res = (resources[0] + dr[0] - costs[1], resources[1] + dr[1], resources[2] + dr[2])
            score = max(score, step(costs, resources=aux_res, dr=(dr[0], dr[1] + 1, dr[2]), timeleft=timeleft - 1))
        if not build_ore:
            aux_res = (resources[0] + dr[0], resources[1] + dr[1], resources[2] + dr[2])
            score = max(score, step(costs, resources=aux_res, dr=dr, timeleft=timeleft - 1))

    return score


ans1 = 0
ans2 = 1
step_cnt = 0

for bp in parsed_input:
    bpid, oro, clo, obo, obc, gor, gob = bp
    costs = (oro, clo, obo, obc, gor, gob)
    ans1 += bpid * step(costs)

    if step_cnt < 3:
        ans2 *= step(costs, timeleft=32)
        step_cnt += 1


print("Part 1:", ans1)
print("Part 2:", ans2)
