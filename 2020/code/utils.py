import re

class DataFiles():
    code_path = ''
    input_path = ''
    example_path = ''
    
    def __init__(self, path):
        self.code_path = path
        self.input_path = path.replace('code', 'inputs').replace('Day', '').replace('.py', '.txt')
        self.example_path = re.sub(r'(\w+)(.txt$)', r'Example\g<2>', self.input_path)
        self.input = open(self.input_path)
        self.inputEX = open(self.example_path)

    def print_paths(self):
        print(self.code_path)
        print(self.input_path)
        print(self.example_path)

    def get_input(self):
        return self.input.read().splitlines()

    def get_inputEX(self):
        return self.inputEX.read().splitlines()
