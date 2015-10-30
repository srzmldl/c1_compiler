%{
#include <stdio.h>
#include <string>
#define DEBUG
#include "node.hh"
#include "util.hh"
#include "global.hh"
extern int yylex ();
extern void yyerror (const char *msg);
InputNode *root;
%}

%union
{
    int  num;
    std::string *var;
    Node *node;
    std::string *ident;
}

%token num_tok const_tok int_tok void_tok
%token if_tok else_tok while_tok ident_tok
%token eol_tok err_tok
%token ',' ';' '=' '{' '}' '[' ']' '(' ')'

%left equ_tok nequ_tok
%left more_tok moreEqu_tok less_tok lessEqu_tok
%left '+' '-'
%left '*' '/' '%'
%right ONEOP


%%


CompUnit :  {debug("Compunit ::= empty\n");}
        | CompUnit Decl { debug("Compunit ::= CompUnit Decl\n");}
        | CompUnit FuncDef {debug("Compunit ::= CompUnit FuncDef\n");}
         ;        

Decl : ConstDecl {debug("Decl ::= ConstDecl\n");}
        | VarDecl {debug("Decl ::= VarDecl\n");}
        ;
        
ConstDecl: const_tok int_tok MultiConstDef ';'{debug("ConstDecl ::= const int  MultiConstDef\n");}
           ;         
           
MultiConstDef:  ConstDef {debug("MultiConstDef :: = ConstDef\n");}
        | MultiConstDef ',' ConstDef {debug("MultiConstDef :: = MultiConstDef, ConstDef\n");}
          ;        

ConstDef: ident_tok '=' Exp {debug("ConstDef ::= ident_tok = Exp\n");}
        | ident_tok '[' Exp ']' '=' '{' MultiExp '}' {debug("ConstDef ::= ident_tok [ Exp ] = { MultiExp }\n");}
        |  ident_tok '[' ']' '=' '{' MultiExp '}' {debug("ConstDef ::= ident_tok [ Exp ] = { MultiExp }\n");} 
        ;
            
VarDecl: int_tok MultiVar ';' {debug("VarDecl::= int MultiVar ;\n");}
         ;        
        
MultiVar: Var {debug("MultiVar :: = Var\n");}
        | MultiVar ',' Var {debug("MultiVar ::= MultiVar, Var\n");}
        ;

Var: ident_tok {debug("Var :: = ident_tok\n");}
        | ident_tok '[' Exp ']' {debug("Var :: =  ident_tok [ Exp ]\n");}
        |  ident_tok '=' Exp {debug("Var :: =  ident_tok = Exp\n");}
        | ident_tok '[' Exp ']' '=' '{' MultiExp'}' {debug("Var :: =  ident_tok [ Exp ] = { MultiExp}\n");}
        | ident_tok '[' ']' '=' '{' MultiExp'}' {debug("Var :: =  ident_tok [ ] = { MultiExp}\n");}
         ;
         
MultiExp: Exp {debug("MultiExp :: = Exp\n");}
        | MultiExp ',' Exp {debug("MultiExp ::= MultiExp, Exp\n");}
        ;
            
FuncDef: void_tok ident_tok '(' ')'  Block {debug("FuncDef ::= void_tok ident_tok ( ) Block\n");}
         ;
         
Block: '{' MultiBlock '}' {debug("Block ::= MultiBlock\n");}
       ;
        
MultiBlock: BlockItem {debug("MultiBlock :: = BlockItem\n");}
        |  MultiBlock BlockItem {debug("MultiBlock ::= MultiBlock BlockItem\n");}
        ;
        
BlockItem: {debug("BlockItem ::= empty\n");}
        | Decl {debug("BlockItem ::= Decl\n");}
        | Stmt {debug("BlockItem ::= Stmt\n");}
        ;
        
Stmt:  LVal '=' Exp ';' {debug("Stmt ::= LVal = Exp ;\n");}
        | ident_tok '(' ')' ';' {debug("Stmt ::= ident_tok();\n");}
        | Block {debug("Stmt ::= Block\n");}
        | while_tok '(' Cond ')' Stmt {debug("Stmp ::= while ( Cond ) Stmt\n");}
        | ';' {debug("Stmt ::= ;\n");}
        | if_tok '(' Cond ')' Stmt {debug("Stmp :: = if (Cond) Stmt\n");}
        | if_tok '(' Cond ')' Stmt else_tok Stmt {debug("Stmp :: = if (Cond) Stmt else Stmt\n");}
        ;

LVal:   ident_tok {debug("LVal ::= ident\n");}
        | ident_tok '[' Exp ']' {debug("LVal ::= ident[Exp]\n");}
        ;
        
Cond:   Exp RelOp Exp {debug("Cond ::= Exp RelOp Exp\n");}
        ;
        
RelOp:  equ_tok {debug("RelOp ::= ==\n");}
        | nequ_tok {debug("RelOp ::= !=\n");}
        | less_tok {debug("RelOp ::= <\n");}
        | more_tok {debug("RelOp ::= >\n");}
        | lessEqu_tok {debug("RelOp ::= <=\n");}
        | moreEqu_tok {debug("RelOp ::= >=\n");}
        ;
        
Exp:    Exp BinOp Exp {debug("Exp ::= Exp BinOp Exp\n");}
        | '(' Exp ')'  {debug("Exp ::= ( Exp )\n");}
        | UnaryOp Exp  %prec ONEOP {debug("Exp ::= UnaryOp Exp\n");}    
        | LVal  {debug("Exp ::= LVal\n");}
        | num_tok  {debug("Exp ::= number\n");}
        ;
        
BinOp:   '+'  {debug("BinOp ::= +\n");}
        | '-' {debug("BinOp ::= -\n");}
        | '*' {debug("BinOp ::= *\n");}
        | '/' {debug("BinOp ::= /\n");}
        | '%' {debug("BinOp ::= %%\n");}
        ;
        
UnaryOp: '+' {debug("UnaryOp ::= +\n");}
         | '-' {debug("UnaryOp ::= -\n");}
         ;
         
%%

void yyerror (const char *msg)
{
    error ("%s", msg);
}
