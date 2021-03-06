<div id="table-of-contents">
<h2>Table of Contents</h2>
<div id="text-table-of-contents">
<ul>
<li><a href="#sec-1">1. 学习内容</a></li>
<li><a href="#sec-2">2. 理解kaleidoscope的词法分析过程</a>
<ul>
<li><a href="#sec-2-1">2.1. 教程笔记</a>
<ul>
<li><a href="#sec-2-1-1">2.1.1. 语言基础</a></li>
<li><a href="#sec-2-1-2">2.1.2. Lexer</a></li>
</ul>
</li>
<li><a href="#sec-2-2">2.2. 要做的题</a>
<ul>
<li><a href="#sec-2-2-1">2.2.1. 解释gettok()函数参数传递</a></li>
<li><a href="#sec-2-2-2">2.2.2. 拓展词法分析器</a></li>
<li><a href="#sec-2-2-3">2.2.3. 拓展修改后的词法分析去,识别token</a></li>
</ul>
</li>
</ul>
</li>
<li><a href="#sec-3">3. 学习使用Flex</a>
<ul>
<li><a href="#sec-3-1">3.1. flex是什么</a></li>
<li><a href="#sec-3-2">3.2. flex词法文件与生成的词法分析器的接口(两个一起说了)</a>
<ul>
<li><a href="#sec-3-2-1">3.2.1. 声明段</a></li>
<li><a href="#sec-3-2-2">3.2.2. 规则段</a></li>
<li><a href="#sec-3-2-3">3.2.3. 代码段</a></li>
</ul>
</li>
</ul>
</li>
<li><a href="#sec-4">4. Flex生成C1词法分析器</a>
<ul>
<li><a href="#sec-4-1">4.1. 为C1语言单词写词法规则</a></li>
<li><a href="#sec-4-2">4.2. 用Flex生成C1词法分析器</a>
<ul>
<li><a href="#sec-4-2-1">4.2.1. tok.cpp</a></li>
<li><a href="#sec-4-2-2">4.2.2. tok.h</a></li>
<li><a href="#sec-4-2-3">4.2.3. main.cpp</a></li>
<li><a href="#sec-4-2-4">4.2.4. lexer.lex</a></li>
</ul>
</li>
</ul>
</li>
<li><a href="#sec-5">5. 阅读clang词法分析文件</a>
<ul>
<li><a href="#sec-5-1">5.1. Clang - Token.h</a></li>
<li><a href="#sec-5-2">5.2. Clang - Lexer.h, Lexer.cpp</a></li>
<li><a href="#sec-5-3">5.3. Clang - Diagnostic.h, Diagnostic.cpp</a></li>
</ul>
</li>
<li><a href="#sec-6">6. 阅读clang词法分析文件</a>
<ul>
<li><a href="#sec-6-1">6.1. Clang-Token.h</a></li>
<li><a href="#sec-6-2">6.2. clang-Lexer.h, Lexer.cpp</a>
<ul>
<li><a href="#sec-6-2-1">6.2.1. 处理各类token</a></li>
<li><a href="#sec-6-2-2">6.2.2. goto语句</a></li>
<li><a href="#sec-6-2-3">6.2.3. 如何记录位置信息的(一个例子)</a></li>
<li><a href="#sec-6-2-4">6.2.4. 字符串转化token</a></li>
</ul>
</li>
<li><a href="#sec-6-3">6.3. Clang-Diagnostic.h, Diagnostic.cpp</a></li>
</ul>
</li>
</ul>
</div>
</div>

# 学习内容<a id="sec-1" name="sec-1"></a>

-   LLVM,Flex,Bison从头构造C1编译器
-   阅读Clang源码

# 理解kaleidoscope的词法分析过程<a id="sec-2" name="sec-2"></a>

## 教程笔记<a id="sec-2-1" name="sec-2-1"></a>

### 语言基础<a id="sec-2-1-1" name="sec-2-1-1"></a>

-   定义:这是一种能用条件,数学等定义函数的语言.
-   唯一数据类型:64-bit 浮点数.所以无需定义
-   可调用标准库函数,需要先extern声明

### Lexer<a id="sec-2-1-2" name="sec-2-1-2"></a>

-   返回值
    -   tok<sub>eof</sub> 文末中止符
    -   tok<sub>def</sub>, tok<sub>extern命令</sub>
    -   tok<sub>identifier</sub> 标识符
    -   tok<sub>number</sub> 数字
    -   [0-255]未知字符
-   lexer实现就是一个gettok函数,如下几个部份
    -   过滤空白符号
    -   识别标识符和关键字
    -   识别数字:注意多个小数点全读完
    -   注释部份
    -   其他未知字符

## 要做的题<a id="sec-2-2" name="sec-2-2"></a>

### 解释gettok()函数参数传递<a id="sec-2-2-1" name="sec-2-2-1"></a>

返回值为int,表示token类别或者未知字符.语义值通过全局变量传递.有如下几种返回值
-   匹配到"def"或者"extern",则返回tok<sub>def或</sub>,tok<sub>extern</sub>
-   除了上面的情况匹配到别的字符串,返回tok<sub>identifier表明是标识符</sub>, 并通过全局变量IdentifierStr传递token语义值.
-   匹配到数字(不考虑多个小数点不合法),用字符串类型NumStr暂存,将其转化成数字后利用全局变量NumVal传递语义值,并且函数返回值为tok<sub>number表示是数字token</sub>
-   如果是注释则递归调用找到下一个token作为返回值
-   其余情况即匹配到表示未知字符,实际上就是ASCII值,返回值就是该字符

### 拓展词法分析器<a id="sec-2-2-2" name="sec-2-2-2"></a>

1.  多行注释

    -   判断多行注释的时候先试探找"/\*",失败了用ungetc将\*退回缓冲区
    -   用了一个类似有限状态机来匹配注释.
        -   sta存状态:0表示"/\*";1为"/\*balabala\*";2表示"/\*
        -   注意到EOF的break
    -   一些常见情况考虑
        -   abc/\*lalala\*/+b 不应该破坏语法树,应该和abc+b效果一样
        -   Num/\*\*/Val这种情况下Num和Val不应改合并起来.所以相对于加间隔符号,错误情况交语法树部份处理,应该和Num Val效果一样
        -   嵌套情况处理好,只需要严格按照状态机来即可
        -   "/\*"匹配不到右边不因这个报错(模仿c语言)

2.  0开头的8进制整数和0x开头的16进制整数

    -   手动判别进制,存入base
    -   十进制要求去合法的最长前缀,strtod正好满足要求
    -   8进制,16进制要求整数,strtol正好满足所有要求,传base作为参数即可.
    -   注意是需要0或者0x,0X前缀,这个判断需要稍微处理,比如".x"不能单纯判第二个是x
    -   注意0.3这种不能算为八进制
    -   借用flag来取出首两个字母,进而决定进制.
    -   因为数据类型不同,所以用NumVal和intNumVal分别存之,用baseToken标记

### 拓展修改后的词法分析去,识别token<a id="sec-2-2-3" name="sec-2-2-3"></a>

-   为了方便以后的修改(因为以后基本不会输出),所以统一放在getNextToken函数里输出.
-   8进制和16进制转化成了十进制输出

# 学习使用Flex<a id="sec-3" name="sec-3"></a>

## flex是什么<a id="sec-3-1" name="sec-3-1"></a>

Flex是生成scanner，scanner识别lexical pattern。输入一个flex文件，将生成一个c源文件：lex.yy.c(缺省)，其中定义了一个函数yylex()，该函数就是扫描器。它根据Flex文件中定义的模式(pattern)对输入的文本串进行分析，然后执行对应的动作(Action)

## flex词法文件与生成的词法分析器的接口(两个一起说了)<a id="sec-3-2" name="sec-3-2"></a>

分成三段:声明,翻译规则,辅助函数.段与段间用'%%'隔开.

### 声明段<a id="sec-3-2-1" name="sec-3-2-1"></a>

-   这一段包含简单名字定义和开始条件的声明。
-   段中的定义不能有缩进。
-   缩进的文本用"%{"和"%}","%{"和"%}"也必须在单独的行，并且不能缩进。
-   例子: Digit   [0-9]

### 规则段<a id="sec-3-2-2" name="sec-3-2-2"></a>

-   主要就是正则表达式,每个匹配后根动作.
-   匹配规则值得注意
    -   多个匹配选最长的
    -   长度一样选最先列出来的.
    -   匹配确定之后,全局字符指针yytext指向这个token,长度由yyleng读取
    -   之后这个pattern对应的action执行
    -   接着匹配
    -   没有定义规则,输入文本原样不动拷贝到标准输出
-   action的规则
    -   pattern后空action,匹配直接舍弃
    -   "{"和"}"; "%{"和"%}"包围的复合语句
    -   只有"|"表示执行下一个规则
    -   return语句返回值个yylex()
    -   yylex()被调用时处理上一次没有处理的token
    -   特殊命令一览
        -   ECHO: 拷贝yytext到扫描器的输出
        -   BEGIN: 跟在开始条件后,将扫描放在对应的开始条件中
        -   REJECT: 指示扫描器继续匹配第二好的规则
        -   yymore(): 下次匹配到一个规则时,对应token加yytext
        -   yyless()
        -   unput(c)
        -   input
        -   YY<sub>FLUSH</sub><sub>BUFFER</sub>
        -   yyterminate

### 代码段<a id="sec-3-2-3" name="sec-3-2-3"></a>

该段内容直接拷到lex.yy.c,包含yylex(),用来存放token和table的附加程序等

# Flex生成C1词法分析器<a id="sec-4" name="sec-4"></a>

## 为C1语言单词写词法规则<a id="sec-4-1" name="sec-4-1"></a>

对于C1要考虑的有如下情况.因为规则很简单,所以简要写出正规式即可.
-   关键字: if, else, const, int, while, void
-   操作符: +, -, \*, /, %
-   比较运算符: <, >, `=, !`, <=, >=
-   逗号, 分号
-   数字: 只有整数,所以很好处理
-   标识符: 注意考虑下划线
-   小括号,大括号,中括号
-   赋值号

## 用Flex生成C1词法分析器<a id="sec-4-2" name="sec-4-2"></a>

### tok.cpp<a id="sec-4-2-1" name="sec-4-2-1"></a>

定义一些全局变量,用来传递数字值和标识符.同时定义号字符数组attrStr,简化输出过程.

### tok.h<a id="sec-4-2-2" name="sec-4-2-2"></a>

定义了枚举类型,提高代码可读性.以及定义好nul等.并且进行变量声明

### main.cpp<a id="sec-4-2-3" name="sec-4-2-3"></a>

这是主过程.显判断文件是否能打开.之后每次取一个token,再根据token的取值输出.(分有属性或者没有属性两种情况).思想十分简单.

### lexer.lex<a id="sec-4-2-4" name="sec-4-2-4"></a>

定义简单的正规式,然后把前面列举的词法都考虑进去就行了.通过修改全局变量传递语义值.返回值是token类型.

# 阅读clang词法分析文件<a id="sec-5" name="sec-5"></a>

## Clang - Token.h<a id="sec-5-1" name="sec-5-1"></a>

## Clang - Lexer.h, Lexer.cpp<a id="sec-5-2" name="sec-5-2"></a>

## Clang - Diagnostic.h, Diagnostic.cpp<a id="sec-5-3" name="sec-5-3"></a>

# 阅读clang词法分析文件<a id="sec-6" name="sec-6"></a>

## Clang-Token.h<a id="sec-6-1" name="sec-6-1"></a>

-   Loc: token的位置
-   UnitData: 当是正常的token的时候,是token文本长度.注解token的时候指向末尾
-   \*PtrData: 四个不同指针的集合,因token类型而异
    -   identifiers, keywords, etc: 内容指针
    -   Literals: 文本缓冲区首指针
    -   Annotations: 指向sema-specific data
    -   Eof: 指向Decl
    -   Other: null
-   Kind: token类型
-   Flags: 二进制位标记,01表示是否再当前集合中
-   大致理解method的功能: 这个代码可读性很好啊.把每个单词翻译一下就大致懂了.这么多就不一一说了.随机抽几个
    -   isLiteral() 判断是否位Literal
    -   getIdentifierInfo() 或者identifier的信息,返回指针
    -   clearFlag() 标记清零

## clang-Lexer.h, Lexer.cpp<a id="sec-6-2" name="sec-6-2"></a>

### 处理各类token<a id="sec-6-2-1" name="sec-6-2-1"></a>

1.  数字(LexNumericConstant)

    -   先处理数字前缀
    -   再处理'e/E'+符号的指数情况.海妖判断是不是Microsoft模式的特殊情况
    -   然后处理FP类型数字'P/p'+符号的情况
    -   处理数字分隔符
    -   处理UCN或者UTF-8
    -   最后再更新token的位置和缓冲区指针

2.  标识符(LexIdentifier)

    -   进入函数时已经匹配一个非数字的合法字符
    -   先把无$,\\,?的简单特殊情况处理完
    -   处理有上述特殊字符的情形:
        -   有$, 根据是否支持这个符号决定是否结束
        -   有\\\\, 转义字符
        -   否则时正常的字母

3.  处理"="和'=="

    找到一个'='的时候再找下一个,如果下一个仍然是'=',则还得处理三个等号的情况,交给HandleEndOfConflictMarker去处理.没有冲突就得到了equalequal的token了.下一个是别的字符那么得到equal的token.

4.  跳过注释

    同时读到'/'和'\*'后,开始找啊找,找到了"\*/"后注释结束.以及define里用了一点黑科技快速跳.

### goto语句<a id="sec-6-2-2" name="sec-6-2-2"></a>

-   这么多case,不用goto代码结构会很复杂,嵌套if之类的会特别深
-   更好的描述正规式,goto式不错的选择.可能case中很多处的某些情况的下一步跳到的是与之并行的case中.这种情况一多就只好用goto咯.
-   用这么多goto是因词法分析特性决定的.我们说要避免goto是为了防止逻辑混乱.但此处的goto让逻辑更明确.可以想像成在一个状态,输入一条边(一个if之类的),跳转到下一个状态.

### 如何记录位置信息的(一个例子)<a id="sec-6-2-3" name="sec-6-2-3"></a>

比如LexAngledStringLiteral()中,我们有当前指针位置,有得到的token信息,长度等.然后调用FromTokenWithChars(TokStart指向BufferPtr,用这个函数得到BufferPtr).最后用setLiteralData传入TokStart更改token中的PtrData为TokStart.都是这样的.

### 字符串转化token<a id="sec-6-2-4" name="sec-6-2-4"></a>

对于字符串,\*prtdata记的是token在text buffer中的起始位置.比如需要的到字符串数据时有getLiteralData()函数,返回了text buffer的起始位置指针. 每次确认字符串token时setLiteralData存储PtrData.所以需要用时通过prtData去text buffer取.

## Clang-Diagnostic.h, Diagnostic.cpp<a id="sec-6-3" name="sec-6-3"></a>

测试程序见src/diagnostic.
该程序报错如下:
-   main返回值非int,有警告: 
    -   warning: return type of 'main' is not 'int' [-Wmain-return-type]
    -   void main()
-   又来一个  
    -   note: change return type to 'int'
    -   void main()
-   浮点常数非法,非法后缀,在检测数字常量的过程中查出: 
    -   error: invalid suffix '.3' on floating constant
    -   int a = 1.2.3;
-   未定义变量
    -   error: use of undeclared identifier 'y'
    -   int x = y;
    -   error: use of undeclared identifier 'abc'
    
    abc =;
    ^
    
    -   abc =;
    -   error: use of undeclared identifier 'b'
    -   b = f(8) + f(10);
-   变量检查之后还有表达式检查
    -   error: expected expression
    -   abc =;
-   非法赋值,兵部是表达式不合法
    -   error: expression is not assignable
    -   a = f(5)++f(6);
-   函数返回值匹配
    -   error: void function 'main' should not return a value [-Wreturn-type]
    -   return 0;
-   除0检验,最后的警告,并不报错
    -   warning: division by zero is undefined [-Wdivision-by-zero]
    -   x = a / 0;