from os import remove
from utils import DataFiles
from collections import *
from math import *

import numpy as np
import re
import textwrap

dataFiles = DataFiles(__file__)

input = dataFiles.input
inputEX = dataFiles.inputEX

inp = input[:]


def get_vsum(packet):
    version = int(packet[:3], 2)
    packet = packet[3:]
    typeId = int(packet[:3], 2)
    packet = packet[3:]

    if typeId == 4:
        value = ""
        while len(packet) >= 5:
            value += packet[:5]
            if packet[0] == "0":
                packet = packet[5:]
                break
            packet = packet[5:]
        return version, packet

    subpackets_vsum = 0

    i = packet[0]
    if i == "1":
        subpackets = int(packet[1:12], 2)
        packet = packet[12:]

        for _ in range(subpackets):
            curr_subpacket_vsum, packet = get_vsum(packet)
            subpackets_vsum += curr_subpacket_vsum

        return subpackets_vsum + version, packet

    subpackets_length = int(packet[1:16], 2)
    packet = packet[16:]
    stop_at_len = len(packet) - subpackets_length

    while len(packet) > stop_at_len:
        curr_subpacket_vsum, packet = get_vsum(packet)
        subpackets_vsum += curr_subpacket_vsum

    return subpackets_vsum + version, packet


def multiply(vec):
    product = 1
    for x in vec:
        product *= int(x)
    return product


operations = (sum, multiply, min, max, 4, lambda x: x[0] > x[1], lambda x: x[0] < x[1], lambda x: x[0] == x[1])


def get_vsum_2(packet):
    version = int(packet[:3], 2)
    packet = packet[3:]
    typeId = int(packet[:3], 2)
    packet = packet[3:]

    if typeId == 4:
        value = ""
        while len(packet) >= 5:
            value += packet[1:5]
            if packet[0] == "0":
                packet = packet[5:]
                break
            packet = packet[5:]
        return int(value, 2), packet

    subpackets_l = []

    i = packet[0]
    if i == "1":
        subpackets = int(packet[1:12], 2)
        packet = packet[12:]

        for _ in range(subpackets):
            curr_subpacket_vsum, packet = get_vsum_2(packet)
            subpackets_l.append(curr_subpacket_vsum)

        return operations[typeId](subpackets_l), packet

    subpackets_length = int(packet[1:16], 2)
    packet = packet[16:]
    stop_at_len = len(packet) - subpackets_length

    while len(packet) > stop_at_len:
        curr_subpacket_vsum, packet = get_vsum_2(packet)
        subpackets_l.append(curr_subpacket_vsum)

    return operations[typeId](subpackets_l), packet


hx = inp[0]
bn = bin(int(hx, 16))[2:].zfill(len(hx * 4))

print(get_vsum(bn)[0])
print(get_vsum_2(bn)[0])
