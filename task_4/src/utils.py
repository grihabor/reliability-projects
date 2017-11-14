import os

DIR_SRC = os.path.split(os.path.abspath(__file__))[0]
DIR_PROJECT = os.path.abspath(os.path.join(DIR_SRC, os.pardir))
DIR_DATA = os.path.join(DIR_PROJECT, 'data')

os.makedirs(DIR_DATA, exist_ok=True)

FILE_INPUT_XML = os.path.join(DIR_DATA, 'input.xml')
