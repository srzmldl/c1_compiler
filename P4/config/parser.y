%{
#include <stdio.h>
#include <string>
#define DEBUG
#include "node.hh"
#include "util.hh"
#include "global.hh"
extern int yylex ();
extern void yyerror (const char *msg);
extern void yywarning (const char *msg);
/*extern int workBrackTwo(int u, int v);
extern int workBrackOne(int u);
extern int workBrackZero(int u);*/
InputNode *root;
char *buffer;
%}

%union
{
    int  num;
    std::string *var;
    Node *node;
    std::string *ident;
}

%token <num> num_tok const_tok int_tok void_tok
%token <num> if_tok else_tok while_tok ident_tok
%token <num> eol_tok err_tok
%token <num> ',' ';' '=' '{' '}' '[' ']' '(' ')'

%left equ_tok nequ_tok
%left more_tok moreEqu_tok less_tok lessEqu_tok
%left '+' '-'
%left '*' '/' '%'
%right ONEOP

%type <num> Exp
%%


CompUnit :  {debug("(%d,%d)Compunit ::= empty\n", @$.first_line, @$.first_column);}
        | CompUnit Decl { debug("(%d,%d)Compunit ::= CompUnit Decl\n", @$.first_line, @$.first_column);}
        | CompUnit FuncDef {debug("(%d,%d)Compunit ::= CompUnit FuncDef\n", @$.first_line, @$.first_column);}
         ;        

Decl : ConstDecl {debug("(%d,%d)Decl ::= ConstDecl\n", @$.first_line, @$.first_column);}
        | VarDecl {debug("(%d,%d)Decl ::= VarDecl\n", @$.first_line, @$.first_column);}
        ;
        
ConstDecl: const_tok int_tok MultiConstDef ';'{debug("(%d,%d)ConstDecl ::= const int  MultiConstDef\n", @$.first_line, @$.first_column);}
           | const_tok MultiConstDef ';' {
               sprintf(buffer, "lack int after const (%d, %d)", @1.last_line, @1.last_column);
               yywarning(buffer);
               debug("(%d,%d)ConstDecl ::= const MultiConstDef\n", @$.first_line, @$.first_column);
             }
           ;         
           
MultiConstDef:  ConstDef {debug("(%d,%d)MultiConstDef :: = ConstDef\n", @$.first_line, @$.first_column);}
        | MultiConstDef ',' ConstDef {debug("(%d,%d)MultiConstDef :: = MultiConstDef, ConstDef\n", @$.first_line, @$.first_column);}
          ;        

ConstDef: ident_tok '=' Exp {debug("(%d,%d)ConstDef ::= ident_tok = Exp\n", @$.first_line, @$.first_column);}
        | ident_tok '[' Exp ']' '=' '{' MultiExp '}' {debug("(%d,%d)ConstDef ::= ident_tok [ Exp ] = { MultiExp }\n", @$.first_line, @$.first_column);}
        |  ident_tok '[' ']' '=' '{' MultiExp '}' {debug("(%d,%d)ConstDef ::= ident_tok [ Exp ] = { MultiExp }\n", @$.first_line, @$.first_column);} 
        ;
            
VarDecl: int_tok MultiVar ';' {debug("(%d,%d)VarDecl::= int MultiVar ;\n", @$.first_line, @$.first_column);}
         ;        
        
MultiVar: Var {debug("(%d,%d)MultiVar :: = Var\n", @$.first_line, @$.first_column);}
        | MultiVar ',' Var {debug("(%d,%d)MultiVar ::= MultiVar, Var\n", @$.first_line, @$.first_column);}
        ;

Var: ident_tok {debug("(%d,%d)Var :: = ident_tok\n", @$.first_line, @$.first_column);}
        | ident_tok '[' Exp ']' {debug("(%d,%d)Var :: =  ident_tok [ Exp ]\n", @$.first_line, @$.first_column);}
        |  ident_tok '=' Exp {debug("(%d,%d)Var :: =  ident_tok = Exp\n", @$.first_line, @$.first_column);}
        | ident_tok '[' Exp ']' '=' '{' MultiExp'}' {debug("(%d,%d)Var :: =  ident_tok [ Exp ] = { MultiExp}\n", @$.first_line, @$.first_column);}
        | ident_tok '[' ']' '=' '{' MultiExp'}' {debug("(%d,%d)Var :: =  ident_tok [ ] = { MultiExp}\n", @$.first_line, @$.first_column);}
         ;
         
MultiExp: Exp {debug("(%d,%d)MultiExp :: = Exp\n", @$.first_line, @$.first_column);}
        | MultiExp ',' Exp {debug("(%d,%d)MultiExp ::= MultiExp, Exp\n", @$.first_line, @$.first_column);}
        ;
            
FuncDef: void_tok ident_tok '(' ')'  Block {debug("(%d,%d)FuncDef ::= void_tok ident_tok ( ) Block\n", @$.first_line, @$.first_column);}
         ;
         
Block: '{' MultiBlock '}' {debug("(%d,%d)Block ::= MultiBlock\n", @$.first_line, @$.first_column);}
       ;
        
MultiBlock: BlockItem {debug("(%d,%d)MultiBlock :: = BlockItem\n", @$.first_line, @$.first_column);}
        |  MultiBlock BlockItem {debug("(%d,%d)MultiBlock ::= MultiBlock BlockItem\n", @$.first_line, @$.first_column);}
        ;
        
BlockItem: {debug("(%d,%d)BlockItem ::= empty\n", @$.first_line, @$.first_column);}
        | Decl { debug("(%d,%d)BlockItem ::= Decl\n", @$.first_line, @$.first_column);}
        | Stmt {debug("(%d,%d)BlockItem ::= Stmt\n", @$.first_line, @$.first_column);}
        ;
        
Stmt:  LVal '=' Exp ';' {debug("(%d,%d)Stmt ::= LVal = Exp ;\n", @$.first_line, @$.first_column);}
        | ident_tok '(' ')' ';' {debug("(%d,%d)Stmt ::= ident_tok();\n", @$.first_line, @$.first_column);}
        | Block {debug("(%d,%d)Stmt ::= Block\n", @$.first_line, @$.first_column);}
        | while_tok '(' Cond ')' Stmt {debug("(%d,%d)Stmp ::= while (Cond) Stmt\n", @$.first_line, @$.first_column);}
        | ';' {debug("(%d,%d)Stmt ::= ;\n", @$.first_line, @$.first_column);}
        | if_tok '(' Cond ')' Stmt {debug("(%d,%d)Stmp :: = if (Cond) Stmt\n", @$.first_line, @$.first_column);}
        | if_tok '(' Cond ')' Stmt else_tok Stmt {debug("(%d,%d)Stmp :: = if (Cond) Stmt else Stmt\n", @$.first_line, @$.first_column);}
        ;


Cond:   Exp RelOp Exp {debug("(%d,%d)Cond ::= Exp RelOp Exp\n", @$.first_line, @$.first_column);}
        ;

LVal:   ident_tok {debug("(%d,%d)LVal ::= ident\n", @$.first_line, @$.first_column);}
        | ident_tok '[' Exp ']' {debug("(%d,%d)LVal ::= ident[Exp]\n", @$.first_line, @$.first_column);}
        ;
  
        
RelOp:  equ_tok {debug("(%d,%d)RelOp ::= ==\n", @$.first_line, @$.first_column);}
        | nequ_tok {debug("(%d,%d)RelOp ::= !=\n", @$.first_line, @$.first_column);}
        | less_tok {debug("(%d,%d)RelOp ::= <\n", @$.first_line, @$.first_column);}
        | more_tok {debug("(%d,%d)RelOp ::= >\n", @$.first_line, @$.first_column);}
        | lessEqu_tok {debug("(%d,%d)RelOp ::= <=\n", @$.first_line, @$.first_column);}
        | moreEqu_tok {debug("(%d,%d)RelOp ::= >=\n", @$.first_line, @$.first_column);}
        ;
        
Exp:    num_tok  {
                //$$ = 0;
                debug("(%d,%d)Exp ::= number\n", @$.first_line, @$.first_column);
                }
        | LVal  {
                //$$ = 0;
                debug("(%d,%d)Exp ::= LVal\n", @$.first_line, @$.first_column);
                }
        | Exp '+' Exp {
              //$$ = workBrackTwo($1, $3);
              debug("(%d,%d)Exp ::= Exp + Exp\n", @$.first_line, @$.first_column);
              }
        | Exp '-' Exp {
              //$$ = workBrackTwo($1, $3);
              debug("(%d,%d)Exp ::= Exp - Exp\n", @$.first_line, @$.first_column);
              }
        | Exp '*' Exp {
              //$$ = workBrackTwo($1, $3);
              debug("(%d,%d)Exp ::= Exp * Exp\n", @$.first_line, @$.first_column);
              }
        | Exp '/' Exp {
              //$$ = workBrackTwo($1, $3);
              debug("(%d,%d)Exp ::= Exp / Exp\n", @$.first_line, @$.first_column);
              }
        | Exp '%' Exp {
              //$$ = workBrackTwo($1, $3);
              debug("(%d,%d)Exp ::= Exp %% Exp\n", @$.first_line, @$.first_column);
              }
        | '-' Exp %prec ONEOP {
              //$$ = workBrackOne($2);
              debug("(%d,%d)Exp ::= - Exp\n", @$.first_line, @$.first_column);
              }
        | '+' Exp %prec ONEOP {
              //$$ = workBrackOne($2);
              debug("(%d,%d)Exp ::= + Exp\n", @$.first_line, @$.first_column);
              }   
        | '(' Exp ')'  {
              //$$ = workBrackZero($2);
              debug("(%d,%d)Exp ::= ( Exp )\n", @$.first_line, @$.first_column);
              }  
        | Exp Exp {
          //$$ = workBrackTwo($1, $2);
            sprintf(buffer, "lack BinOp after Exp (%d, %d)", @1.last_line, @1.last_column);
            yyerror(buffer);
            debug("(%d,%d)Exp ::= Exp Exp\n", @$.first_line, @$.first_column);
          }
        | '(' Exp {
            sprintf(buffer, "lack ')' after Exp (%d, %d)", @2.last_line, @2.last_column);
            yyerror(buffer);
            debug("Exp :: = ( Exp");
        }
        | Exp error ')' {
            sprintf(buffer, "lack '(' befor Exp (%d, %d)", @1.first_line, @1.first_column);
            yyerror(buffer);
            debug("Exp :: = Exp )");
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
    error("%s", msg);
}

void yywarning(const char *msg) {
    warning("%s", msg);
}