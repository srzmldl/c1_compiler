import execute as exe
import distance as dist
import config as cf

files,collections = exe.parser()

def get_target_func():
    print "Choose file from the input:"
    for i in range(len(files)):
        print "%d:  "%i,
        file = files[i].split('/')
        print file[-1]

    file = raw_input("File number:\n")

    functions = collections[int(file)]
    print "choose function from first file:"
    for i in range(len(functions)):
        print "%d:  "%i,
        print functions[i].getname()

    function_id = raw_input("Choose function:\n")

    name = files[int(file)].split('/')[-1].split('.')[0]+'-'+functions[int(function_id)].getname()
    return name,functions[int(function_id)]



if __name__ == '__main__':
    name1,func1 = get_target_func()
    name2,func2 = get_target_func()
    #func1,func2 = get_target_func(),get_target_func()
    #exe.matrix_gen_test(func1,func2,dist.Euclidean)
    exe.dump_matrix(func1,func2,cf.distance,name1,name2)