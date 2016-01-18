import re
#import example as ex
import components as st
import distance as dist
import visualization as visual
#import analysis as al
import extract as ex
import driver as dr
import config as cf


re_function = r"[a-zA-Z_]+\w*[ ]+[a-zA-Z_]+\w[ ]*\(.*\)"



functions = []
cur_function = []

def splittest():
    i = "[B100 (ENTRY)]"
    new = re.split('\(| |\)|\[|\]',i)
    while '' in new:
        new.remove('')
    if len(new)>1:
        return (int)(new[0][1:]),new[1]
    else:
        return new[0],"GENERAL"

def get_name_and_attr(string):
    temp = re.split('\(| |\)|\[|\]',string)
    while '' in temp:
        temp.remove('')
    if len(temp)>1:
        return temp[0],temp[1]
    else:
        return temp[0],"GENERAL"

def mytest():
    i = 'Preds (2): B2 B3'

    match = re.match(r'(\d+):(.*)', i)

    if match:
        print type(match.group(0))

    match =re.match(r'Preds \((\d+)\):(.*)',i)
    if match:
        i = match.group(2).split()
        print i


def level(string):
    i = 0
    for ch in string:
        if ch == ' ':
            i = i + 1
        else:
            return i
    return i





def parse_statement(statement):
    pass

def new_basic_block(string):
    label,attr = get_name_and_attr(string)
    block = st.BasicBlock(label,attr)
    return block





def StmtType(string):

    stmt=re.match(r'\s*(\[.*\])\s*\((.*)\)\s*',string)
    if stmt:
         mark = stmt.group(2).split(',')[0]
         if mark == "ImplicitCastExpr":
             return "Cast"
         else:
             return "func_call"
    else:
        stmt = re.match(r'\s*\[.*\]\s*(\[.*\])',string)
        if stmt:
            return "array_op"
        else:
            stmt = stmt = re.match(r'(\d+)|([a-zA-Z_]+\w*)',string)
            if stmt:
                return "identifier"
            else:
                stmt = re.match(r'(\".*\")',string)
                if stmt:
                    return "string"
                else:
                    return "Unknow_operation "+string

def print_matrix(matrix):
    for line in matrix:
        for item in line:
            print "%.3f\t"%item,
        print '\n'

def matrix_gen(func1,func2,distance):
    matrix = []
    block_index = []
    block_column = []
    for block1 in func1.getblocks():
        block_index.append(block1.get_label())

    for block2 in func2.getblocks():
        block_column.append(block2.get_label())

    for block1 in func1.getblocks():
        line = []
        for block2 in func2.getblocks():
            line.append(distance(block1.get_list(),block2.get_list()))
        matrix.append(line)

    #print_matrix(matrix)


    #al.build_matrix_df(matrix,block_index,block_column)
    simi_mat = ex.public_sequence(matrix,block_index,block_column,4,0.33,1)

    li = []
    for item in matrix:
        li.append(max(item))

    i = len(matrix)
    j = len(matrix[0])

    visual.draw_matrix(matrix,i,j,max(li),simi_mat)


def matrix_gen_test(func1,func2,distance):
    matrix = []
    block_index = []
    block_column = []
    print func1.getseq()
    engine_x = st.resort_block(func1.getseq(),func1)
    engine_y = st.resort_block(func2.getseq(),func2)
    print engine_x

    for block1 in func1.getblocks():
        block_index.append(block1.get_label())

    for block2 in func2.getblocks():
        block_column.append(block2.get_label())

    for block1 in engine_x:
        line = []
        for block2 in engine_y:
            line.append(distance(block1,block2))
        matrix.append(line)

    #print_matrix(matrix)


    #al.build_matrix_df(matrix,block_index,block_column)
    simi_mat = ex.public_sequence(matrix,func1.getseq(),func2.getseq(),cf.min_seq_length,cf.threshhold,cf.max_gap_length)

    li = []
    for item in matrix:
        li.append(max(item))

    i = len(matrix)
    j = len(matrix[0])

    visual.draw_matrix(matrix,i,j,max(li),simi_mat)


def dump_matrix(func1,func2,distance,members1,members2):
    matrix = []
    block_index = []
    block_column = []
    #print func1.getseq()
    engine_x = st.resort_block(func1.getseq(),func1)
    engine_y = st.resort_block(func2.getseq(),func2)
    #print engine_x

    for block1 in func1.getblocks():
        block_index.append(block1.get_label())

    for block2 in func2.getblocks():
        block_column.append(block2.get_label())

    for block1 in engine_x:
        line = []
        for block2 in engine_y:
            line.append(distance(block1,block2))
        matrix.append(line)

    #print_matrix(matrix)


    #al.build_matrix_df(matrix,block_index,block_column)

    simi_mat = ex.public_sequence(matrix,func1.getseq(),func2.getseq(),4,0.33,1)

    li = []
    for item in matrix:
        li.append(max(item))

    i = len(matrix)
    j = len(matrix[0])

    visual.dump_matrix(matrix,i,j,max(li),simi_mat,members1,members2)


def parser():

    collections = []

    #s = ex.func_foo.split("\n")
    #print s
    files = dr.load_files()
    for dir in files:
        fr = open(dir)
        functions = []
        cur_function=None
        cur_block=None
        cur_seq = []

        for line in fr.readlines():
            if line and not line==' ' and not line=='\n':
                #print line[:-1]
                degree = level(line)
                #print degree
                if degree==3:
                    st.add_statement(line[:-1],cur_block)
                elif degree==1:
                    #print "new block"
                    if cur_block:
                        cur_function.add_block(cur_block)
                    cur_block=new_basic_block(line[:-1])
                elif degree==0:
                    #print "new function"
                    if cur_function:
                        cur_function.add_block(cur_block)
                        cur_function.add_seq(cur_seq)
                        functions.append(cur_function)
                        cur_block=None
                        cur_seq = []
                    cur_function = st.Function(line[:-1])
                elif degree==4:
                    cur_seq.append(line[4:-1])
        cur_function.add_block(cur_block)
        cur_function.add_seq(cur_seq)
        functions.append(cur_function)
        collections.append(functions)

    #print len(functions)
    #functions[0].DumpFunction()
    #for func in functions:
    #    print func.getname()


    #matrix_gen_test(functions[0],functions[0],dist.Euclidean)

    return files,collections






