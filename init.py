import shutil
import pathlib
from datetime import date

code_folder_path = pathlib.Path(__file__).parent.joinpath("code").resolve()
input_folder_path = pathlib.Path(__file__).parent.joinpath("input").resolve()


if not code_folder_path.is_dir():
    raise AssertionError('"code" folder doesn\'t exist')

if not input_folder_path.is_dir():
    raise AssertionError('"input" folder doesn\'t exist')

current_day = date.today().day

dayExample_path = code_folder_path.joinpath("DayExample.py")
current_code_path = code_folder_path.joinpath("Day{:02}.py".format(current_day))
current_input_path = input_folder_path.joinpath("{:02}.txt".format(current_day))

if dayExample_path.is_file():
    if not current_code_path.is_file():
        shutil.copyfile(dayExample_path, current_code_path)
        print("Code file was created!")
    else:
        print("Code file already exists!")

    if not current_input_path.is_file():
        open(current_input_path, "a+").close()
        print("Input file was created!")
    else:
        print("Input file already exists!")
else:
    print('"DayExample.py" doesn\'t exist')
    raise AssertionError('"DayExample.py" doesn\'t exist')
