%{
#include "pl0.h"
#include <stdio.h>
%}

alpha [A-Za-z_]
dig [0-9]
name {alpha}({alpha}|{dig})*

%%

"if"  return ifk;
"else" return elsek;
"const" return constk;
"int" return intk;
"while" return whilek;
"+" return plus;
"-" return sub;
"*" return mul;
"/" return div;
"%" return mod;
"==" return equ;
"!=" return notEqu;
"<" return less;
">" return more;
"<=" return lessEqu;
">=" return moreEqu;
"=" return assign;
"(" return lbrace;
")" return rbrace;
"[" return lbracket;
"]" return rbracket;
"," return comma;
";" return semicolon;

dig+     {
              num = atol(yytext);
              return(number);
           }

[\n]	   { printf("\n"); }	
[\t ]*     /* throw away whitespace */
.          {
              printf("Illegal character"); 
              return(nul);
           }
name  {
    
}
"/*"  	{
    int c;

    while((c = yyinput()) != 0)
    {
        if(c == '\n')
        ++mylineno;

        else if(c == '*')
        {
            if((c = yyinput()) == '/')
            break;
            else
            unput(c);
        }
    }
}

%%


void getsym()
{
	sym = yylex();
}