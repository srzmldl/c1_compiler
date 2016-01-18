import re


def is_Cast_or_Call(string,statistic):
    stmt=re.match(r'\s*(\[.*\])\s*\((.*)\)\s*',string)
    if stmt:
        mark = stmt.group(2).split(',')[0]
        if mark == "ImplicitCastExpr":
            # kind of type cast, we don't care about the type of a variable yet

            return "Cast"
        else:
            # a function call
            statistic.add_func_call()
            return "func_call"
    else:
        return None

def is_inc(string,statistic):
    stmt=re.match(r'\[.*\]\s*\+\+',string)
    if stmt:
        statistic.add_inc()
        return "inc"
    else:
        return None

def is_assign(string,statistic):
    stmt = re.match(r'\[.*\]\s*=\s*\[.*\]',string)
    if stmt:
        statistic.add_assign()
        return "assign"
    else:
        return None

def is_relop(string,statistic):
    stmt = re.match(r'\[.*\]\s*(<|>|<=|>=|!=|==)\s*\[.*\]',string)
    if stmt:
        statistic.add_relop()
        return "relop"
    else:
        return None

def is_binop(string,statistic):
    stmt = re.match(r"\[.*\]\s*(\+|-|\*|\/)\s*\[.*\]",string)
    if stmt:
        statistic.add_binop()
        return "binop:"
    else:
        return None



def is_array_op(string,statistic):
    stmt = re.match(r'\s*\[.*\]\s*(\[.*\])',string)
    #[B3.2][B3.4]: get the element from a array
    if stmt:
            statistic.add_array_op()
            return "array_op"
    else:
        return None

def is_id(string,statistic):
    stmt = stmt = re.match(r'(\d+)|([a-zA-Z_]+\w*)',string)
    # identifier can be a number or name of function or variable
    if stmt:
        statistic.add_id()
        return "identifier"
    else:
        return None

def is_string(string,statistic):
    stmt = re.match(r'(\".*\")',string)
    #"str content" : a string to be output or used in printf\scanf
    if stmt:
        statistic.add_string()
        return "string"
    else:
        return None

def is_pointre(string,statistic):
    stmt = re.match(r'\s*&\[(.*)\]',string)
    # &[B2.3] : get the address of the third stmt in BasicBlock 2
    if stmt:
        statistic.add_pointer()
        return "pointer"
    else:
        return None

def is_branch(string,statistic):
    stmt = re.match(r'\s*for\s+(.*)',string)
    # for (...;...;...) stmt
    if stmt:
        statistic.add_branch()
        return "for"
    else:
        stmt = re.match(r'\s*if\s+(.*)',string)
        # if (...) stmt
        if stmt:
            statistic.add_branch()
            return "if"
        else:
            stmt = re.match(r'\s*break;',string)
            # break stmt
            if stmt:
                statistic.add_branch()
                return "break"
            else:
                stmt = re.match(r'\s*while\s+(.*)',string)
                if stmt:
                    statistic.add_branch()
                    return "while"
                else:
                    return None


def is_decl(string,statistic):
    stmt = re.match(r'\s*return\s*\[.*\]\s*',string)
    # return + other: stmt return something
    if stmt:
        statistic.add_return()
        return "return"
    else:
        stmt = re.match(r'(\d+)|([a-zA-Z_]+\w*)\s+(.+)',string)
        # id + other :call stmt with this form is a decl like static int a or double b[10] and so on
        if stmt:
            statistic.add_decl()
            return "decl"
        else:
            return None

def stmt_detect(string, block):
    if not (    is_branch(string,block) or
                is_array_op(string, block) or
                is_Cast_or_Call(string, block) or
                is_decl(string, block) or
                is_id(string, block) or
                is_pointre(string, block) or
                is_string(string, block) or
                is_binop(string, block) or
                is_inc(string, block) or
                is_assign(string, block) or
                is_relop(string, block)
            ):
        return "Unknow stmt "+string
    return None

def print_detect(string,statistic):
    t = stmt_detect(string,statistic)
    if t:
        print t
