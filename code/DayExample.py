from utils import DataFiles

dataFiles = DataFiles(__file__)

input = dataFiles.get_input()  # inputRaw = dataFiles.input
inputEx = dataFiles.get_inputEX()  # inputRawEX = dataFiles.inputEX
