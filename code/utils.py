import re

class DataFiles():
    __code_path = ''
    __input_path = ''
    __example_path = ''
    
    def __init__(self, path):
        self.__code_path = path
        self.__input_path = path.replace('code', 'inputs').replace('Day', '').replace('.py', '.txt')
        self.__example_path = re.sub(r'(\w+)(.txt$)', r'Example\g<2>', self.__input_path)
        self.input = open(self.__input_path)
        self.inputEX = open(self.__example_path)

    def print_paths(self):
        print(self.__code_path)
        print(self.__input_path)
        print(self.__example_path)

    def get_input(self):
        return self.input.read().splitlines()

    def get_inputEX(self):
        return self.inputEX.read().splitlines()
