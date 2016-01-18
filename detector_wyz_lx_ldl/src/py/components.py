import re
import lex as l

class BlockStatistic:
    def __init__(self):
        self.reset()

    def add_func_call(self):
        self.func_call += 1

    def add_decl(self):
        self.decl += 1

    def add_pointer(self):
        self.pointer += 1

    def add_assign(self):
        self.assign += 1

    def add_string(self):
        self.string += 1

    def add_relop(self):
        self.relop += 1

    def add_binop(self):
        self.binop +=1

    def add_assign(self):
        self.assign += 1

    def add_inc(self):
        self.inc += 1

    def add_id(self):
        self.id += 1

    def add_array_op(self):
        self.array_op += 1

    def add_return(self):
        self.re += 1


    def reset(self):


        self.func_call = 0
        self.decl = 0
        self.pointer = 0
        self.assign = 0
        self.string = 0
        self.relop = 0
        self.binop = 0
        self.inc = 0
        self.id = 0
        self.array_op = 0
        self.re = 0

    def dump(self):
        print "func_call "+str(self.func_call)
        print "decl "+str(self.decl)
        print "pointer "+str(self.pointer)
        print "assign "+str(self.assign)
        print "string "+str(self.string)
        print "reloop "+str(self.relop)
        print "binop "+str(self.binop)
        print "inc "+str(self.inc)
        print "id " +str(self.id)
        print "array_op "+str(self.array_op)

    def matrix(self):
        list = []
        list.append(self.func_call)
        list.append(self.decl)
        list.append(self.pointer)
        list.append(self.assign)
        list.append(self.string)
        list.append(self.relop)
        list.append(self.binop)
        list.append(self.inc)
        list.append(self.id)
        list.append(self.array_op)
        print list

class BasicBlock:
    def __init__(self,label,attr):
        self.label = label
        self.attr = attr
        self.statements = []
        self.Preds = []
        self.Succs = []
        self.T = False
        self.statements.append("")
        self.count = {}
        self.reset_count()

    def add_statement(self,statement):
        self.statements.append(statement)

    def add_Preds(self,Preds):
        self.Preds = Preds

    def add_Succs(self,Succs):
        self.Succs = Succs

    def set_T(self):
        self.T = True

    def DumpBlock(self):
        print "basic block: "+self.label

        for stmt in self.statements[1:]:
            print stmt
        print self.Preds
        print self.Succs
        for k in self.count:
            print k+" "+str(self.count[k])
        print '\n'

    def get_statements(self):
        return self.statements

    def get_label(self):
        return self.label

    def add_func_call(self):
        self.count["func_call"] += 1

    def add_decl(self):
        self.count["decl"] += 1

    def add_pointer(self):
        self.count["pointer"] += 1

    def add_assign(self):
        self.count["assign"] += 1

    def add_string(self):
        self.count["string"] += 1

    def add_relop(self):
        self.count["relop"] += 1

    def add_binop(self):
        self.count["binop"] +=1

    def add_assign(self):
        self.count["assign"] += 1

    def add_inc(self):
        self.count["inc"] += 1

    def add_id(self):
        self.count["id"] += 1

    def add_array_op(self):
        self.count["array_op"] += 1

    def add_return(self):
        self.count["re"] += 1

    def add_branch(self):
        self.count['branch'] +=1

    def get_list(self):
        return self.count.values()

    def reset_count(self):
        self.count['func_call'] = 0
        self.count['decl'] = 0
        self.count['pointer'] = 0
        self.count['assign'] = 0
        self.count['string'] = 0
        self.count['relop'] = 0
        self.count['binop'] = 0
        self.count['inc'] =0
        self.count['id'] = 0
        self.count['array_op'] =0
        self.count['re'] = 0
        self.count['branch'] =0

    def dump_matrix(self):
        print self.count.values()



class Function:
    def __init__(self,name):
        self.name = name
        self.blocks = []
        self.seq = []

    def add_block(self,block):
        self.blocks.append(block)

    def add_seq(self,seq):
        self.seq = seq

    def DumpFunction(self):
        print "function:"+self.name
        print self.seq
        for block in self.blocks:
            block.DumpBlock()

    def getname(self):
        return self.name

    def getblocks(self):
        return self.blocks

    def getseq(self):
        return self.seq

    def retrive_vector(self,label):
        for block in self.blocks:
            if block.get_label() == label:
                return block.get_list()



def get_name_and_attr(string):
    temp = re.split('\(| |\)|\[|\]',string)
    while '' in temp:
        temp.remove('')
    if len(temp)>1:
        return temp[0],temp[1]
    else:
        return temp[0],"GENERAL"

def level(string):
    i = 0
    for ch in string:
        if ch == ' ':
            i = i + 1
        else:
            return i
    return i

def add_statement(string,block):

    stmt = re.match(r'\s*(\d+):\s*(.*)',string)
    if stmt:
        block.add_statement(stmt.group(2))
        t = l.stmt_detect(stmt.group(2),block)
        #if t:
        #    print t
    else:
        stmt = re.match(r'\s*Preds \((\d+)\):(.*)',string)
        if stmt:
            block.add_Preds(stmt.group(2).split())
        else:
            stmt = re.match(r'\s*Succs \((\d+)\):(.*)',string)
            if stmt:
                block.add_Succs(stmt.group(2).split())
            else:
                stmt = re.match(r'\s*T:(.*)',string)
                if stmt:
                    block.add_statement(stmt.group(1))
                    t = l.stmt_detect(stmt.group(1),block)
                    #if t:
                    #    print t
                    block.set_T()
                else:
                    print "Unknow pattern: "+string


def resort_block(seq,func):
    sorted_block = []
    for label in seq:
        sorted_block.append(func.retrive_vector('B'+label))
    return sorted_block

