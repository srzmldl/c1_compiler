%{
#include <stdio.h>
#include <string>
#include <string.h>
#define DEBUG
#include "node.hh"
#include "util.hh"
#include "global.hh"
extern int yylex ();
extern void yyerror (const char *msg);
extern void yywarning (const char *msg);
extern void draw(int x, int y);
extern std::vector < std::string > wholeFile;
InputNode *root;
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
    root = new InputNode();
     }
    | CompUnit Decl {
        debug("(%d,%d)Compunit ::= CompUnit Decl\n", @$.first_line, @$.first_column);
        root->append($2);
     }
    | CompUnit FuncDef {
        debug("(%d,%d)Compunit ::= CompUnit FuncDef\n", @$.first_line, @$.first_column);
        root->append($2);
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
    
ConstDecl: const_tok int_tok MultiConstDef ';'{
    debug("(%d,%d)ConstDecl ::= const int  MultiConstDef\n", @$.first_line, @$.first_column);
    $$ = new ConstDeclNode($3->head);
     }
    | const_tok MultiConstDef ';' {
        $$ = new ConstDeclNode($2->head);
        sprintf(buffer, "expect 'int' after const at (%d, %d)", @1.last_line, @1.last_column);
        yywarning(buffer);
        draw(@1.last_line, @1.last_column + 1);
        debug("(%d,%d)ConstDecl ::= const MultiConstDef\n", @$.first_line, @$.first_column);
     }
    ;         
    
MultiConstDef:  ConstDef {
    debug("(%d,%d)MultiConstDef :: = ConstDef\n", @$.first_line, @$.first_column);
    $$ = $1;
     }
    | MultiConstDef ',' ConstDef {
        debug("(%d,%d)MultiConstDef :: = MultiConstDef, ConstDef\n", @$.first_line, @$.first_column);
        $$ = $3;
        $1->next = $3;
        $$->head = $1->head;
          }
    ;        
    
ConstDef: ident_tok '=' Exp {
    debug("(%d,%d)ConstDef ::= ident_tok = Exp\n", @$.first_line, @$.first_column);
    $$ = new ConstDefEleNode((IdentNode*)$1, $3);
    }
    | ident_tok '[' Exp ']' '=' '{' MultiExp '}' {
        debug("(%d,%d)ConstDef ::= ident_tok [ Exp ] = { MultiExp }\n", @$.first_line, @$.first_column);
        $$ = new ConstDefArrLimNode((IdentNode*)$1, $3, $7->head);
          }
     |  ident_tok '[' ']' '=' '{' MultiExp '}' {
        debug("(%d,%d)ConstDef ::= ident_tok [ Exp ] = { MultiExp }\n", @$.first_line, @$.first_column);
        $$ = new ConstDefArrNoLimNode((IdentNode*)$1, $6->head);
          }
        ;
        
VarDecl: int_tok MultiVar ';' {
        debug("(%d,%d)VarDecl::= int MultiVar ;\n", @$.first_line, @$.first_column);
        $$ = new VarDeclNode($2->head);
          }
    ;        
        
MultiVar: Var {
        debug("(%d,%d)MultiVar :: = Var\n", @$.first_line, @$.first_column);
        $$ = $1;
          }
        | MultiVar ',' Var {
        debug("(%d,%d)MultiVar ::= MultiVar, Var\n", @$.first_line, @$.first_column);
        $$ = $3;
        $1->next = $3;
        $$->head = $1->head;
          }
        ;
        
Var: ident_tok {
        debug("(%d,%d)Var :: = ident_tok\n", @$.first_line, @$.first_column);
        $$ = new VarDefEleNoEquNode((IdentNode *)$1);
          }
        | ident_tok '[' Exp ']' {
        debug("(%d,%d)Var :: =  ident_tok [ Exp ]\n", @$.first_line, @$.first_column);
        $$ = new VarDefArrLimNoEquNode((IdentNode *)$1, $3);
          }
    |  ident_tok '=' Exp {
        debug("(%d,%d)Var :: =  ident_tok = Exp\n", @$.first_line, @$.first_column);
        $$ = new VarDefEleEquNode((IdentNode*)$1, $3);
          }
     | ident_tok '[' Exp ']' '=' '{' MultiExp'}' {
        debug("(%d,%d)Var :: =  ident_tok [ Exp ] = { MultiExp}\n", @$.first_line, @$.first_column);
        $$ = new VarDefArrLimEquNode((IdentNode*) $1,  $3, $7->head);
          }
     | ident_tok '[' ']' '=' '{' MultiExp'}' {
        debug("(%d,%d)Var :: =  ident_tok [ ] = { MultiExp}\n", @$.first_line, @$.first_column);
        $$ = new VarDefArrNoLimEquNode((IdentNode*)$1, $6->head);
          }
        ;
         
MultiExp: Exp {
        debug("(%d,%d)MultiExp :: = Exp\n", @$.first_line, @$.first_column);
        $$ = $1;
          }
        | MultiExp ',' Exp {
        debug("(%d,%d)MultiExp ::= MultiExp, Exp\n", @$.first_line, @$.first_column);
        $$ = $3;
        $1->next = $3;
        $$->head = $1->head;
          }
        ;
        
FuncDef: void_tok ident_tok '(' ')'  Block {
        debug("(%d,%d)FuncDef ::= void_tok ident_tok ( ) Block\n", @$.first_line, @$.first_column);
        $$ = new FuncDefNode((IdentNode*) $2, (BlockNode*) $5);
          }
     ;
     
Block: '{' MultiBlock '}' {
        debug("(%d,%d)Block ::= MultiBlock\n", @$.first_line, @$.first_column);
        if ($2 == NULL) $$ = new BlockNode($2);
        else $$ = new BlockNode($2->head);
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
        $$ = $2;
        if ($1 != NULL) {
        $1->next = $2;
        $$->head = $1->head;
          } else {
        $$->head = $2;
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
        $$ = new AssignStmtNode($1, $3);
          }
    | ident_tok '(' ')' ';' {
        debug("(%d,%d)Stmt ::= ident_tok();\n", @$.first_line, @$.first_column);
        $$ = new CallStmtNode((IdentNode*) $1);
          }
    | Block {
        debug("(%d,%d)Stmt ::= Block\n", @$.first_line, @$.first_column);
        $$ = $1;
          }
    | while_tok '(' Cond ')' Stmt {
        debug("(%d,%d)Stmp ::= while (Cond) Stmt\n", @$.first_line, @$.first_column);
        $$ = new WhileStmtNode((CondNode*) $3, (StmtNode*) $5);
          }
    | ';' {
        debug("(%d,%d)Stmt ::= ;\n", @$.first_line, @$.first_column);
        $$ = new CommaStmtNode();
          }
    | if_tok '(' Cond ')' Stmt {
        debug("(%d,%d)Stmp :: = if (Cond) Stmt\n", @$.first_line, @$.first_column);
        $$ = new IfStmtNode((CondNode*)$3, (StmtNode*)$5);
          }
    | if_tok '(' Cond ')' Stmt else_tok Stmt {
        debug("(%d,%d)Stmp :: = if (Cond) Stmt else Stmt\n", @$.first_line, @$.first_column);
        $$ = new IfElseStmtNode((CondNode*)$3, (StmtNode*)$5, (StmtNode*)$7);
          }
    ;


Cond:   Exp RelOp Exp {
        $$ = new CondNode($1, $2, $3);
        debug("(%d,%d)Cond ::= Exp RelOp Exp\n", @$.first_line, @$.first_column);
          }
    ;

LVal:   ident_tok {
        $$ = $1;
        debug("(%d,%d)LVal ::= ident\n", @$.first_line, @$.first_column);
          }
     | ident_tok '[' Exp ']' {
        $$ = new RefArrNode((IdentNode*)$1, $3);
        debug("(%d,%d)LVal ::= ident[Exp]\n", @$.first_line, @$.first_column);
          }
    ;
  
        
RelOp:  equ_tok {
        debug("(%d,%d)RelOp ::= ==\n", @$.first_line, @$.first_column);
        $$ = new std::string("==");
          }
    | nequ_tok {
        debug("(%d,%d)RelOp ::= !=\n", @$.first_line, @$.first_column);
        $$ = new std::string("!=");
          }
    | less_tok {
        debug("(%d,%d)RelOp ::= <\n", @$.first_line, @$.first_column);
        $$ = new std::string("<");
          }
    | more_tok {
        debug("(%d,%d)RelOp ::= >\n", @$.first_line, @$.first_column);
        $$ = new std::string(">");
          }
    | lessEqu_tok {
        debug("(%d,%d)RelOp ::= <=\n", @$.first_line, @$.first_column);
        $$ = new std::string("<=");
          }
    | moreEqu_tok {
        debug("(%d,%d)RelOp ::= >=\n", @$.first_line, @$.first_column);
        $$ = new std::string(">=");
          }
    ;
    
Exp:    num_tok  {
        //$$ = 0;
        $$ = new NumNode($1);
        debug("(%d,%d)Exp ::= number\n", @$.first_line, @$.first_column);
 }
    | LVal  {
            //$$ = 0;
        $$ = $1;
        debug("(%d,%d)Exp ::= LVal\n", @$.first_line, @$.first_column);
      }
    | Exp '+' Exp {
            //$$ = workBrackTwo($1, $3);
        $$ = new BinaryExpNode($1, '+', $3);
        debug("(%d,%d)Exp ::= Exp + Exp\n", @$.first_line, @$.first_column);
      }
    | Exp '-' Exp {
            //$$ = workBrackTwo($1, $3);
        $$ = new BinaryExpNode($1, '-', $3);
        debug("(%d,%d)Exp ::= Exp - Exp\n", @$.first_line, @$.first_column);
      }
    
    
    | '-' Exp %prec ONEOP {
            //$$ = workBrackOne($2);
        $$ = new UnaryExpNode('-', $2);
        debug("(%d,%d)Exp ::= - Exp\n", @$.first_line, @$.first_column);
      }
    | '+' Exp %prec ONEOP {
            //$$ = workBrackOne($2);
        $$ = new UnaryExpNode('+', $2);
        debug("(%d,%d)Exp ::= + Exp\n", @$.first_line, @$.first_column);
      }
    
    | Exp '*' Exp {
            //$$ = workBrackTwo($1, $3);
        
        $$ = new BinaryExpNode($1, '*', $3);
        debug("(%d,%d)Exp ::= Exp * Exp\n", @$.first_line, @$.first_column);
      }
    | Exp '/' Exp {
            //$$ = workBrackTwo($1, $3);
        
        $$ = new BinaryExpNode($1, '/', $3);
        debug("(%d,%d)Exp ::= Exp / Exp\n", @$.first_line, @$.first_column);
          }
    | Exp '%' Exp {
            //$$ = workBrackTwo($1, $3);
        $$ = new BinaryExpNode($1, '%', $3);
        debug("(%d,%d)Exp ::= Exp %% Exp\n", @$.first_line, @$.first_column);
      }
    | '(' Exp ')'  {
        //$$ = workBrackZero($2);
        $$ = $2;
        debug("(%d,%d)Exp ::= ( Exp )\n", @$.first_line, @$.first_column);
          }  
    | Exp error Exp {
            //$$ = workBrackTwo($1, $2);
            sprintf(buffer, "expect BinOp after Exp at (%d, %d)", @1.last_line, @1.last_column);
            
            yyerror(buffer);
            draw(@1.last_line, @1.last_column + 1);
            debug("(%d,%d)Exp ::= Exp Exp\n", @$.first_line, @$.first_column);
 }
    
    | '(' Exp error {
            sprintf(buffer, "expect ')' after Exp at (%d, %d)", @2.last_line, @2.last_column);
            yyerror(buffer);
            draw(@2.last_line, @2.last_column + 1);
            debug("(%d,%d)Exp :: = ( Exp\n", @$.first_line, @$.first_column);
      }
    | Exp error ')' {
            sprintf(buffer, "expect '(' before Exp at (%d, %d) ", @1.first_line, @1.first_column);
            yyerror(buffer);
            draw(@1.first_line, @1.first_column - 1);
            debug("(%d,%d)Exp :: = Exp )\n", @$.first_line, @$.first_column);
 }
    | error ')' {
            sprintf(buffer, "expect '(' before ')' at (%d, %d)\n", @1.first_line, @1.first_column);
            yyerror(buffer);
            draw(@1.first_line, @1.first_column - 1);
            debug("(%d, %d)Exp :: = )\n", @$.first_line, @$.first_column);
      }
    | error {
            yyerror("bye! You are really foolish\n"); return 0;
      }
    ;
        
    
%%

/*int workBrackTwo(int u, int v) {
    
}

int workBrackOne(int u) {
    return 1;
}

int workBrackZero(int u) {
    return 1;
} */

void yyerror(const char *msg)
{
    // if (strcmp(msg, "syntax error") != 0)
        error("%s", msg);
}

int checkBlank(char x) {
    return (x == ' ' || x == '\t');
}

void draw(int line, int column) {
    std::string tmp = wholeFile[line - 1];
    if (column <= 0) {
        column++;
        tmp = " " + tmp;
    }
    if (column >= tmp.length()) {
        tmp = tmp + " ";
    }
    int len = tmp.length();
    column--;
    int delta = 0;
    for (int i = 0; i < len; ++i) {
        if (checkBlank(tmp[i]) && i > 0 && checkBlank(tmp[i - 1])) {
            if (i <= column) delta++;
        } else {
            printf("%c", tmp[i]);
        }
    }
    printf("\n");
    column -= delta;
    for (int i = 0; i < column; ++i)
        printf("-");
    printf("^");
    for (int i = column + 1; i < len - delta; ++i)
        printf("-");
    printf("\n");
}

void yywarning(const char *msg) {
    warning("%s", msg);
}