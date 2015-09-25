%option noyywrap

%{
#include <bits/stdc++.h>
#include "tok.h"
%}

dig [0-9]
numb {dig}+

alpha [A-Za-z_]
name {alpha}({alpha}|{dig})*
%%


{numb}     {
    num_val = atol(yytext);
    return(number);
}
"if"  return ifk;
"else" return elsek;
"const" return constk;
"int" return intk;
"while" return whilek;
"void" return voidk;
"," return comma;
";" return semicolon;
"+"|"-"|"*"|"/"|"%" {
    str_val = yytext;
    return op;
}
"=" return assign;
"<="|">="|"=="|"!="|"<"|">" {
    
    str_val = yytext;
    return comp;
}
"{"|"}" {
    str_val = yytext;
    return brace;
}
"["|"]" {
    str_val = yytext;
    return bracket;
}
"("|")" {
    str_val = yytext;
    return parenth;
}
{name} {
    str_val = yytext;
    return ident;
}

[\n]	   { printf("\n"); }	
[\t ]*     /* throw away whitespace */
.          {
              printf("Illegal character"); 
              return(nul);
           }

"/*"  	{
    int c;

    while((c = yyinput()) != 0)
    {
        if(c == '*')
        {
            if((c = yyinput()) == '/')
            break;
            else
            unput(c);
        }
    }
}

%%

