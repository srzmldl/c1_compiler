%option noyywrap
%{
#include <string>
#include "node.hh"
#include "tok.hh"

int yycolumn = 1;

#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; \
yylloc.first_column = yycolumn; yylloc.last_column = yycolumn+yyleng-1; \
yycolumn += yyleng;

%}

%option yylineno

dig [0-9]
numb {dig}+

alpha [A-Za-z_]
name {alpha}({alpha}|{dig})*


%%

{numb}     {
    yylval.num = atol(yytext);
    return(num_tok);
            }
"const" return const_tok;
"int" return int_tok;
"void" return void_tok;
"if"  return if_tok;
"else" return else_tok;
"while" return while_tok;
{name} {
    //yylval.ident = new std::string(yytext);
    yylval.node = new IdentNode(new std::string(yytext));
    return ident_tok;
}
"," return ',';
";" return ';';
"+" return '+';
"-" return '-';
"*" return '*';
"/" return '/';
"%" return '%';
"=" return  '=';
"<=" return lessEqu_tok;
">=" return moreEqu_tok;
"==" return equ_tok;
"!=" return nequ_tok;
"<" return less_tok;
">" return more_tok;
"{" return '{';
"}" return '}';
"[" return '[';
"]" return ']';
"(" return '(';
")"  return ')';

"\n" {++yycolumn = 1;}
[\t ]*     {yyleng += 3;}/* throw away whitespace */
. return err_tok;

"/*"  	{
    int c;
    while((c = yyinput()) != 0)
    {
        if (c == '\n') {
           ++yycolumn = 1;
        } else {
          yyleng++;
          if(c == '\t') yyleng += 3;
          if(c == '*') {
              if((c = yyinput()) == '/') {
                   yyleng++;
                   break;
              } else unput(c);
          }
        }
    }
}

%%