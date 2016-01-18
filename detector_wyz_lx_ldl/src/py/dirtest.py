import os


if __name__ == '__main__':
    input_path ='../../samples/cfg/input/'
    save_path = "./output/"
    listdir = os.listdir(input_path)
    for target in listdir:
        print target