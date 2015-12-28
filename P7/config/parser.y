%{
#include <stdio.h>
#include <string>
#include <string.h>
//#define DEBUG
#include "node.hh"
#include "util.hh"
#include "global.hh"
extern int yylex ();
extern void yyerror (const char *msg);
extern void yywarning (const char *msg);
extern void drawErrWarnPos(int x, int y);
extern std::vector < std::string > wholeFile;
InputNode *root;
extern std::vector <Node*> nodeVec;
extern int errorFlag;
char buffer[1024];
%}

%union
{
    int  num;
    Node *node;
    std::string *name;
}

%token <num> num_tok
%token const_tok int_tok void_tok
%token if_tok else_tok while_tok
%token <node> ident_tok
%token eol_tok err_tok
%token  ',' ';' '=' '{' '}' '[' ']' '(' ')'

%left  equ_tok nequ_tok
%left  more_tok moreEqu_tok less_tok lessEqu_tok
%left '+' '-'
%left '*' '/' '%'
%right ONEOP

%type <node> CompUnit Decl FuncDef ConstDecl VarDecl MultiConstDef ConstDef Exp
%type <node> MultiExp MultiVar Var BlockItem Stmt LVal Cond MultiBlock Block 
%type <name> RelOp


%locations
%%

CompUnit :  {
    debug("(%d,%d)Compunit ::= empty\n", @$.first_line, @$.first_column);
    if (!errorFlag) {
        root = new InputNode();
        nodeVec.push_back(root);
        root->setLoc((Loc*)&(@$));
    }
 }
| CompUnit Decl {
    debug("(%d,%d)Compunit ::= CompUnit Decl\n", @$.first_line, @$.first_column);
    if (!errorFlag) {
        if (root) root->append($2);
    }
 }
| CompUnit FuncDef {
        debug("(%d,%d)Compunit ::= CompUnit FuncDef\n", @$.first_line, @$.first_column);
        if (!errorFlag && root) root->append($2);
 }
;

Decl : ConstDecl {
    debug("(%d,%d)Decl ::= ConstDecl\n", @$.first_line, @$.first_column);
    $$ = $1;
 }
| VarDecl {
    debug("(%d,%d)Decl ::= VarDecl\n", @$.first_line, @$.first_column);
    $$ = $1;
  }
;

//===============warning1===============
ConstDecl: const_tok int_tok MultiConstDef ';'{
    debug("(%d,%d)ConstDecl ::= const int  MultiConstDef\n", @$.first_line, @$.first_column);
    if (!errorFlag) {
        $$ = new ConstDeclNode($3->head);
        nodeVec.push_back($$);
        $$->setLoc((Loc*)&(@$));
    }
    
 }
| const_tok MultiConstDef ';' {
        if (!errorFlag) {
            $$ = new ConstDeclNode($2->head);
            nodeVec.push_back($$);
            $$->setLoc((Loc*)&(@$));
        }
        
        sprintf(buffer, "expect 'int' after const at (%d, %d)", @1.last_line, @1.last_column);
        yywarning(buffer);
        drawErrWarnPos(@1.last_line, @1.last_column);
        debug("(%d,%d)ConstDecl ::= const MultiConstDef\n", @$.first_line, @$.first_column);
 }

;         
//=================warning 1 End=================
MultiConstDef:  ConstDef {
    debug("(%d,%d)MultiConstDef :: = ConstDef\n", @$.first_line, @$.first_column);
    $$ = $1;
 }
| MultiConstDef ',' ConstDef {
    debug("(%d,%d)MultiConstDef :: = MultiConstDef, ConstDef\n", @$.first_line, @$.first_column);
    if (!errorFlag) {
        $$ = $3;
        $1->next = $3;
        $$->head = $1->head;
    }
  }
;

ConstDef: ident_tok '=' Exp {
    debug("(%d,%d)ConstDef ::= ident_tok = Exp\n", @$.first_line, @$.first_column);
    if (!errorFlag) {
        $$ = new ConstDefEleNode((IdentNode*)$1, $3);
        nodeVec.push_back($$);
        $$->setLoc((Loc*)&(@$));
    }
    
    }
| ident_tok '[' Exp ']' '=' '{' MultiExp '}' {
        debug("(%d,%d)ConstDef ::= ident_tok [ Exp ] = { MultiExp }\n", @$.first_line, @$.first_column);
        if (!errorFlag) {
            $$ = new ConstDefArrLimNode((IdentNode*)$1, $3, $7->head);
            nodeVec.push_back($$);
            $$->setLoc((Loc*)&(@$));
        }
        
          }
|  ident_tok '[' ']' '=' '{' MultiExp '}' {
        debug("(%d,%d)ConstDef ::= ident_tok [ Exp ] = { MultiExp }\n", @$.first_line, @$.first_column);
         if (!errorFlag) {
             $$ = new ConstDefArrNoLimNode((IdentNode*)$1, $6->head);
             nodeVec.push_back($$);
             $$->setLoc((Loc*)&(@$));   
         }
   }

;

VarDecl: int_tok MultiVar ';' {
        debug("(%d,%d)VarDecl::= int MultiVar ;\n", @$.first_line, @$.first_column);
        if (!errorFlag) {
            $$ = new VarDeclNode($2->head);
            nodeVec.push_back($$);
            $$->setLoc((Loc*)&(@$));
        }
 }

;

MultiVar: Var {
    debug("(%d,%d)MultiVar :: = Var\n", @$.first_line, @$.first_column);
    $$ = $1;
 }
| MultiVar ',' Var {
    debug("(%d,%d)MultiVar ::= MultiVar, Var\n", @$.first_line, @$.first_column);
    if (!errorFlag) {
        $$ = $3;
        $1->next = $3;
        $$->head = $1->head;
    }
  }

;

Var: ident_tok {
    debug("(%d,%d)Var :: = ident_tok\n", @$.first_line, @$.first_column);
    if (!errorFlag) {
        $$ = new VarDefEleNoEquNode((IdentNode *)$1);
        nodeVec.push_back($$);
        $$->setLoc((Loc*)&(@$));
    }
    
 }
| ident_tok '[' Exp ']' {
    debug("(%d,%d)Var :: =  ident_tok [ Exp ]\n", @$.first_line, @$.first_column);
    if (!errorFlag) {
        $$ = new VarDefArrLimNoEquNode((IdentNode *)$1, $3);
        nodeVec.push_back($$);
        $$->setLoc((Loc*)&(@$));
    }
    
  }
|  ident_tok '=' Exp {
    debug("(%d,%d)Var :: =  ident_tok = Exp\n", @$.first_line, @$.first_column);
    if (!errorFlag) {
        $$ = new VarDefEleEquNode((IdentNode*)$1, $3);
        nodeVec.push_back($$);
        $$->setLoc((Loc*)&(@$));
    }
    
   }
| ident_tok '[' Exp ']' '=' '{' MultiExp'}' {
    debug("(%d,%d)Var :: =  ident_tok [ Exp ] = { MultiExp}\n", @$.first_line, @$.first_column);
    if (!errorFlag) {
        $$ = new VarDefArrLimEquNode((IdentNode*) $1,  $3, $7->head);
        nodeVec.push_back($$);
        $$->setLoc((Loc*)&(@$));
    }
  }
| ident_tok '[' ']' '=' '{' MultiExp'}' {
    debug("(%d,%d)Var :: =  ident_tok [ ] = { MultiExp}\n", @$.first_line, @$.first_column);
    if (!errorFlag) {
        $$ = new VarDefArrNoLimEquNode((IdentNode*)$1, $6->head);
        nodeVec.push_back($$);
        $$->setLoc((Loc*)&(@$));
    }
  }

;

MultiExp: Exp {
    debug("(%d,%d)MultiExp :: = Exp\n", @$.first_line, @$.first_column);
    $$ = $1;
 }
| MultiExp ',' Exp {
    debug("(%d,%d)MultiExp ::= MultiExp, Exp\n", @$.first_line, @$.first_column);
    if (!errorFlag) {
        $$ = $3;
        $1->next = $3;
        $$->head = $1->head;
    }
  }
;

FuncDef: void_tok ident_tok '(' ')'  Block {
    debug("(%d,%d)FuncDef ::= void_tok ident_tok ( ) Block\n", @$.first_line, @$.first_column);
    if (!errorFlag) {
        $$ = new FuncDefNode((IdentNode*) $2, (BlockNode*) $5);
        nodeVec.push_back($$);
        $$->setLoc((Loc*)&(@$));
    }
 }
;

Block: '{' MultiBlock '}' {
    debug("(%d,%d)Block ::= MultiBlock\n", @$.first_line, @$.first_column);
    if (!errorFlag) {
        if ($2 == NULL) $$ = new BlockNode($2);
        else $$ = new BlockNode($2->head);
        nodeVec.push_back($$);
        $$->setLoc((Loc*)&(@$));
    }  
 }

;

MultiBlock: {
    debug("(%d,%d)MultiBlock ::= empty\n", @$.first_line, @$.first_column);
    $$ = NULL;
}
| BlockItem {
    debug("(%d,%d)MultiBlock :: = BlockItem\n", @$.first_line, @$.first_column);
    $$ = $1;
  }
|  MultiBlock BlockItem {
    debug("(%d,%d)MultiBlock ::= MultiBlock BlockItem\n", @$.first_line, @$.first_column);
    if (!errorFlag) {
        $$ = $2;
        if ($1 != NULL) {
            $1->next = $2;
            $$->head = $1->head;
        } else {
            $$->head = $2;
        }
    }
 }
;

BlockItem: Decl {
    debug("(%d,%d)BlockItem ::= Decl\n", @$.first_line, @$.first_column);
    $$ = $1;
 }
| Stmt {
    debug("(%d,%d)BlockItem ::= Stmt\n", @$.first_line, @$.first_column);
    $$ = $1;
  }

;

Stmt:  LVal '=' Exp ';' {
    debug("(%d,%d)Stmt ::= LVal = Exp ;\n", @$.first_line, @$.first_column);
    if (!errorFlag) {
        $$ = new AssignStmtNode($1, $3);    
        nodeVec.push_back($$);
        $$->setLoc((Loc*)&(@$));
    }
 }
| ident_tok '(' ')' ';' {
    debug("(%d,%d)Stmt ::= ident_tok();\n", @$.first_line, @$.first_column);
    if (!errorFlag) {
        $$ = new CallStmtNode((IdentNode*) $1);
        nodeVec.push_back($$);
        $$->setLoc((Loc*)&(@$));
    }
  }
| Block {
    debug("(%d,%d)Stmt ::= Block\n", @$.first_line, @$.first_column);
    $$ = $1;
    /*if (!errorFlag) {
        $$ = $1;
        nodeVec.push_back($$);
        $$->setLoc((Loc*)&(@$));
        } */
  }
| while_tok '(' Cond ')' Stmt {
    debug("(%d,%d)Stmp ::= while (Cond) Stmt\n", @$.first_line, @$.first_column);
    if (!errorFlag) {
        $$ = new WhileStmtNode((CondNode*) $3, (StmtNode*) $5);
        nodeVec.push_back($$);
        $$->setLoc((Loc*)&(@$));
    }
  }
| ';' {
    debug("(%d,%d)Stmt ::= ;\n", @$.first_line, @$.first_column);
    if (!errorFlag) {
        $$ = new CommaStmtNode();
        nodeVec.push_back($$);
        $$->setLoc((Loc*)&(@$));
    }
  }
| if_tok '(' Cond ')' Stmt {
    debug("(%d,%d)Stmp :: = if (Cond) Stmt\n", @$.first_line, @$.first_column);
    if (!errorFlag) {
        $$ = new IfStmtNode((CondNode*)$3, (StmtNode*)$5);
        nodeVec.push_back($$);
        $$->setLoc((Loc*)&(@$));
    }
  }
| if_tok '(' Cond ')' Stmt else_tok Stmt {
    debug("(%d,%d)Stmp :: = if (Cond) Stmt else Stmt\n", @$.first_line, @$.first_column);
    if (!errorFlag) {
        $$ = new IfElseStmtNode((CondNode*)$3, (StmtNode*)$5, (StmtNode*)$7);
        nodeVec.push_back($$);
        $$->setLoc((Loc*)&(@$));
    }
  }

;


Cond:   Exp RelOp Exp {
    if (!errorFlag) {
        $$ = new CondNode($1, $2, $3);
        nodeVec.push_back($$);
        $$->setLoc((Loc*)&(@$));
    }
    debug("(%d,%d)Cond ::= Exp RelOp Exp\n", @$.first_line, @$.first_column);
 }

;

LVal:   ident_tok {
    $$ = $1;
    /*if (!errorFlag) {
        $$ = $1;
        nodeVec.push_back($$);
        $$->setLoc((Loc*)&(@$));
        }*/
    debug("(%d,%d)LVal ::= ident\n", @$.first_line, @$.first_column);
 }
| ident_tok '[' Exp ']' {
    if (!errorFlag) {
        $$ = new RefArrNode((IdentNode*)$1, $3);
        nodeVec.push_back($$);
        $$->setLoc((Loc*)&(@$));
    }
    debug("(%d,%d)LVal ::= ident[Exp]\n", @$.first_line, @$.first_column);
  }

;

RelOp:  equ_tok {
    debug("(%d,%d)RelOp ::= ==\n", @$.first_line, @$.first_column);
    if (!errorFlag) 
    $$ = new std::string("==");
 }
| nequ_tok {
    debug("(%d,%d)RelOp ::= !=\n", @$.first_line, @$.first_column);
    if (!errorFlag)
    $$ = new std::string("!=");
  }
| less_tok {
    debug("(%d,%d)RelOp ::= <\n", @$.first_line, @$.first_column);
    if (!errorFlag) $$ = new std::string("<");
  }
| more_tok {
    debug("(%d,%d)RelOp ::= >\n", @$.first_line, @$.first_column);
    if (!errorFlag) $$ = new std::string(">");
  }
| lessEqu_tok {
    debug("(%d,%d)RelOp ::= <=\n", @$.first_line, @$.first_column);
    if (!errorFlag) $$ = new std::string("<=");
  }
| moreEqu_tok {
    debug("(%d,%d)RelOp ::= >=\n", @$.first_line, @$.first_column);
    if (!errorFlag) $$ = new std::string(">=");
  }

;

Exp: num_tok  {
    //$$ = 0;
    
    if (!errorFlag){ 
        $$ = new NumNode($1);
        nodeVec.push_back($$);
        $$->setLoc((Loc*)&(@$));
    }
    debug("(%d,%d)Exp ::= number\n", @$.first_line, @$.first_column);
 }
| LVal  {
    //$$ = 0;
    $$ = $1;
    debug("(%d,%d)Exp ::= LVal\n", @$.first_line, @$.first_column);
  }
| Exp '+' Exp {
            //$$ = workBrackTwo($1, $3);
    if (!errorFlag){ 
        $$ = new BinaryExpNode($1, '+', $3);
        nodeVec.push_back($$);
        $$->setLoc((Loc*)&(@$));
    }
    debug("(%d,%d)Exp ::= Exp + Exp\n", @$.first_line, @$.first_column);
  }
| Exp '-' Exp {
        //$$ = workBrackTwo($1, $3);
    if (!errorFlag){ 
        $$ = new BinaryExpNode($1, '-', $3);
        nodeVec.push_back($$);
        $$->setLoc((Loc*)&(@$));
    }
    debug("(%d,%d)Exp ::= Exp - Exp\n", @$.first_line, @$.first_column);
  }
| '-' Exp %prec ONEOP {
            //$$ = workBrackOne($2);
    if (!errorFlag){ 
        $$ = new UnaryExpNode('-', $2);
        nodeVec.push_back($$);
        $$->setLoc((Loc*)&(@$));
    }
    debug("(%d,%d)Exp ::= - Exp\n", @$.first_line, @$.first_column);
  }
| '+' Exp %prec ONEOP {
            //$$ = workBrackOne($2);
    if (!errorFlag){ 
        $$ = new UnaryExpNode('+', $2);
        nodeVec.push_back($$);
        $$->setLoc((Loc*)&(@$));
    }
    debug("(%d,%d)Exp ::= + Exp\n", @$.first_line, @$.first_column);
  }
| Exp '*' Exp {
            //$$ = workBrackTwo($1, $3);
    if (!errorFlag){ 
        $$ = new BinaryExpNode($1, '*', $3);
        nodeVec.push_back($$);
        $$->setLoc((Loc*)&(@$));
    }
    debug("(%d,%d)Exp ::= Exp * Exp\n", @$.first_line, @$.first_column);
  }
| Exp '/' Exp {
            //$$ = workBrackTwo($1, $3);
    if (!errorFlag){ 
        $$ = new BinaryExpNode($1, '/', $3);
        nodeVec.push_back($$);
        $$->setLoc((Loc*)&(@$));
    }
    debug("(%d,%d)Exp ::= Exp / Exp\n", @$.first_line, @$.first_column);
  }
| Exp '%' Exp {
            //$$ = workBrackTwo($1, $3);
    if (!errorFlag){ 
        $$ = new BinaryExpNode($1, '%', $3);
        nodeVec.push_back($$);
        $$->setLoc((Loc*)&(@$));
    }
    debug("(%d,%d)Exp ::= Exp %% Exp\n", @$.first_line, @$.first_column);
  }
| '(' Exp ')'  {
        //$$ = workBrackZero($2);
    $$ = $2;
    debug("(%d,%d)Exp ::= ( Exp )\n", @$.first_line, @$.first_column);
  }
//================ error kind 1 ====================
| Exp error Exp {
    //$$ = workBrackTwo($1, $2);
    sprintf(buffer, "expect BinOp after Exp at (%d, %d)", @1.last_line, @1.last_column);
    yyerror(buffer);
    drawErrWarnPos(@1.last_line, @1.last_column);
    debug("(%d,%d)Exp ::= Exp Exp\n", @$.first_line, @$.first_column);
 }
//===================error kind 1 end=========================


//============error kind 2 begin=============
| '(' Exp error {
    sprintf(buffer, "expect ')' after Exp at (%d, %d)", @2.last_line, @2.last_column);
    yyerror(buffer);
    drawErrWarnPos(@2.last_line, @2.last_column);
    debug("(%d,%d)Exp :: = ( Exp\n", @$.first_line, @$.first_column);
  }
| Exp error ')' {
    sprintf(buffer, "expect '(' before Exp at (%d, %d) ", @1.first_line, @1.first_column);
    yyerror(buffer);
    drawErrWarnPos(@1.first_line, @1.first_column);
    debug("(%d,%d)Exp :: = Exp )\n", @$.first_line, @$.first_column);
 }
| error ')' {
    sprintf(buffer, "expect '(' before ')' at (%d, %d)\n", @1.first_line, @1.first_column);
    yyerror(buffer);
    drawErrWarnPos(@1.first_line, @1.first_column);
    debug("(%d, %d)Exp :: = )\n", @$.first_line, @$.first_column);
  }
//=================error kind2 end============================
| error {
    yyerror("bye! You are really foolish\n");
    return -1;
  }
;


%%

void yyerror(const char *msg)
{
    // if (strcmp(msg, "syntax error") != 0)
    error("%s", msg);
    handleError();
}

int checkBlank(char x) {
    return (x == ' ' || x == '\t');
}

void drawErrWarnPos(int line, int column) {
    std::string tmp = wholeFile[line - 1];
    int len = tmp.length();
    for (int i = 0; i < len; ++i)
        if (tmp[i] == '\t')
            len += 3;
    printf("%s\n", tmp.c_str());
    for (int i = 0; i < column - 1; ++i)
        printf("-");
    printf("^");
    for (int i = column; i < len; ++i)
        printf("-");
    printf("\n");
}

void yywarning(const char *msg) {
    warning("%s", msg);
}