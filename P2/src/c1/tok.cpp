#define ONECNT 23
#define nul -1
#include <bits/stdc++.h>
using namespace std;

enum oneAttr{
    ifk = 0, elsek, constk, intk, whilek,
    plus, sub, mul, div, mod,
    equ, notEqu, less, more, lessEqu, moreEqu,
    assign,
    lbrace, rbrace,
    lbracket, rbracket,
    comma,
    semicolon,
    number,
    ident
};

char oneAttrStr[KEYCNT][10] = {"if", "else", "const", "int", "while", "plus", "sub", "mul", "div", "mod", "equ", "notEqu", "less", "more", "lessEqu", "moreEqu", "assign", "lbrace", "rbrace", "lbracket", "rbracket", "comma", "semicolon", "number", "ident"};

int main()
{
    printf("%s\n%s\n", keyword[0], keyword[1]);
    cout << intk << ' ' << whilek << endl;
    return 0;
}