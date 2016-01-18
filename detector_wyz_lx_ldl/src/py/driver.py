import os

def load_files():
    input_path ='../../samples/cfg/input/'
    listdir = os.listdir(input_path)
    files = []

    for item in listdir:
        if item[-4:]=='.txt':
            files.append(input_path+item)

    #print files

    return files


if __name__ == "__main__":
    load_files()