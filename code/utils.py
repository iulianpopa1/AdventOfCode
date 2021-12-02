import re


class DataFiles:
    _code_path = ""
    _input_path = ""
    _example_path = ""
    input = ""
    inputEX = ""
    raw_input = ""
    raw_inputEX = ""

    def __init__(self, path):
        self._code_path = path
        self._input_path = path.replace("code", "inputs").replace("Day", "").replace(".py", ".txt")
        self._example_path = re.sub(r"(\w+)(.txt$)", r"Example\g<2>", self._input_path)

        self._inputFile = open(self._input_path)
        self._inputEXFile = open(self._example_path)

        self.input = self.get_input()
        self.inputEX = self.get_inputEX()

    def __del__(self):
        self._inputFile.close()
        self._inputEXFile.close()

    def print_paths(self):
        print(self._code_path)
        print(self._input_path)
        print(self._example_path)

    def get_input(self):
        return self._inputFile.read().splitlines()

    def get_inputEX(self):
        return self._inputEXFile.read().splitlines()

    def get_input_raw(self):
        return self._inputFile.read()

    def get_inputEX_raw(self):
        return self._inputEXFile.read()
