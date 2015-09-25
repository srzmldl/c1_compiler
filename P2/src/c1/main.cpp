#include <bits/stdc++.h>
#include <tok.h>

int main(int args, char *argv[])
{
	printf("please input source program file name: ");
    scanf("%s", inFileName);
    if ((infile = fopen(inFileName, "r")) == NULL) {
        printf("File %s can't be opened.\n", inFileName);
        exit(1);
    }
    getSymbol();
    for (;symbol;) {
        if (symbol < KEYCNT)
            printf("<%s>", oneAttrStr[symbol]);
        else if (sym == number)
            printf("<number, %d>", num);
        else printf("<ident, %s>", identStr);
        getSymbol();
    }
}