#define ATTRCNT 14
#define nul -1


enum attr{
    // all 14
    //== 8 only one attr
    ifk = 1, elsek, constk, intk, whilek, voidk,
    assign,
    comma, semicolon,
    //=== 5 op==
    op, 
    //pluso, subo, mulo, divo, modo,
    //== 6 com ===
    comp,
    //equc, notEquc, lessc, morec, lessEquc, moreEquc,
    //=== brace=== {}
    brace,
    //lbrace, rbrace,
    //== bracket []
    bracket,
    number,
    ident,
    parenth
};

extern char attrStr[30][10];
extern char *str_val;
extern int num_val;