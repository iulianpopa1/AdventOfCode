import os
import re


class DataFiles:
    _code_path = ""
    _input_path = ""
    _example_path = ""

    def __init__(self, path):
        self._code_path = path
        self._input_path = path.replace("code", "input").replace("Day", "").replace(".py", ".txt")
        self._example_path = re.sub(r"(\w+)(.txt$)", r"Example\g<2>", self._input_path)

        self._inputFile = self.open_file(self._input_path)
        self._inputEXFile = self.open_file(self._example_path)

    def open_file(self, path):
        if not os.path.exists(path):
            print("File", path, "is missing. It will be created")
        file = open(path, "a+")
        file.seek(0)
        return file

    def get_input(self, splitlines=False, example=False):
        if example:
            file = self._inputEXFile
        else:
            file = self._inputFile

        if splitlines:
            return file.read().splitlines()
        else:
            return file.read()

    def get_input_chunks(self, sep="\n\n", example=False):
        if example:
            file = self._inputEXFile
        else:
            file = self._inputFile

        return file.read().split("\n\n")

    def __del__(self):
        self._inputFile.close()
        self._inputEXFile.close()
