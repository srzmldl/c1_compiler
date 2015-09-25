#include <bits/stdc++.h>
#include "tok.h"

extern FILE *yyin;  // file pointer used in lexer
extern int yylex(); // lexer function provided by lexer.l

const int oneAttr = 9;
void print_token(int token)
{
    if (token <= 0) return ;
    printf("< %s", attrStr[token]);
    if (token <= oneAttr) printf(" >");
    else if (token == number) printf(", %d >", num_val);
    else if (token >= 1) printf(", %s >", str_val);
}
int main(int args, char *argv[])
{
    char *inFileName;
	//printf("please input source program file name: ");
    //scanf("%s", inFileName);
    FILE *infile;
    if ((infile = fopen(argv[1], "r")) == NULL) {
        printf("File %s can't be opened.\n", inFileName);
        exit(1);
    }
    yyin = infile;
    while (int token =  yylex())
        print_token(token);
    return 0;
}