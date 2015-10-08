<div id="table-of-contents">
<h2>Table of Contents</h2>
<div id="text-table-of-contents">
<ul>
<li><a href="#sec-1">1. 理解Kaleidoscope的语法分析和AST</a>
<ul>
<li><a href="#sec-1-1">1.1. 解释include/ast.h中ExprAST里的virtual的作用，在继承时的原理</a>
<ul>
<li><a href="#sec-1-1-1">1.1.1. virtual解释</a></li>
<li><a href="#sec-1-1-2">1.1.2. vtable</a></li>
</ul>
</li>
<li><a href="#sec-1-2">1.2. MainLoop,HandleDefinition, HandleTopLevelExpression，AST结构</a>
<ul>
<li><a href="#sec-1-2-1">1.2.1. MainLoop</a></li>
<li><a href="#sec-1-2-2">1.2.2. HandleDefinition</a></li>
<li><a href="#sec-1-2-3">1.2.3. HandleTopLevelExpression</a></li>
</ul>
</li>
<li><a href="#sec-1-3">1.3. Kaleidoscope在Lexer和Parser间传递信息（token、语义值、用什么函数和变量）</a></li>
<li><a href="#sec-1-4">1.4. Kaleidoscope处理算符优先级</a>
<ul>
<li><a href="#sec-1-4-1">1.4.1. 解释ParseBinOpRHS以及优先级处理方式</a></li>
<li><a href="#sec-1-4-2">1.4.2. 分析a*b*c、a*b+c、a+b*c分别如何处理(对象不好表示,意会一下)</a></li>
</ul>
</li>
<li><a href="#sec-1-5">1.5. 解释Error, ErrorP, ErrorF的作用，举例说明它们在语法分析中应用</a></li>
<li><a href="#sec-1-6">1.6. Kaleidoscope不支持声明变量，给变量赋值，那么变量的作用是什么？</a></li>
<li><a href="#sec-1-7">1.7. 为什么不需要{&#x2026;}或begin&#x2026;end？</a></li>
<li><a href="#sec-1-8">1.8. Kaleidoscope是如何避免if/then/else语句的二义性的？</a></li>
<li><a href="#sec-1-9">1.9. Kaleidoscope只有一种数据类型double，那么if/then/else的分支条件是如何实现的？</a></li>
</ul>
</li>
<li><a href="#sec-2">2. 拓展while循环</a>
<ul>
<li><a href="#sec-2-1">2.1. toy.cpp</a></li>
<li><a href="#sec-2-2">2.2. dumpdot.cpp</a></li>
<li><a href="#sec-2-3">2.3. ash.h</a></li>
</ul>
</li>
</ul>
</div>
</div>

# 理解Kaleidoscope的语法分析和AST<a id="sec-1" name="sec-1"></a>

## 解释include/ast.h中ExprAST里的virtual的作用，在继承时的原理<a id="sec-1-1" name="sec-1-1"></a>

### virtual解释<a id="sec-1-1-1" name="sec-1-1-1"></a>

ExprAST中函数前加virtual关键字标识这是虚拟函数. 这样在其派生的类(如NumberExprAST, VariableExprAST等)中通过重写相应函数来实现对基类这些虚拟函数的覆盖. 当基类的指针pt  派生类的对象时,pt调用虚拟函数时调用的时派生类中重写的函数.

这里的ExprAST中有两个纯虚函数,表明ExprAST是一个抽象基类,不能创建抽象基类的独立对象,只能用来被继承.

因为ExprAST类是抽象基类,所以其析构函数也必须有virtual关键字.如果抽象基类不是虚析构函数,当我们用delete来释放基类指针(它其实指向的是派生类的对象实例)占用的内存的时候，只有基类的析构函数被调用，而派生类的析构函数不会被调用，这就可能引起内存泄露。如果基类的析构函数是虚析构，那么在delete基类指针时，继承树上的析构函数会被自低向上依次调用，即最底层派生类的析构函数会被首先调用，然后一层一层向上直到该指针声明的类型。

### vtable<a id="sec-1-1-2" name="sec-1-1-2"></a>

当继承一个含有虚函数的基类时，编译器会对新类创建一个新的VTABLE，并且插入新函数地址，如果没有重写基类的虚函数，则使用基类的虚函数地址。虚函数机制通过VTABLE实现，编译器对每个包含虚函数的类创建一个表（称为VTABLE表），在这个VTABLE表中，编译器存放每个特定类的虚函数地址。这个表不是类的成员之一，而是将这个表的地址存放在类中，即类中有一个成为VPTR的地址，存放着虚函数列表的的地址.这个VPTR通常是被隐藏的。

## MainLoop,HandleDefinition, HandleTopLevelExpression，AST结构<a id="sec-1-2" name="sec-1-2"></a>

### MainLoop<a id="sec-1-2-1" name="sec-1-2-1"></a>

-   不断循环询问ready>
-   根据取得token(存储在CurTok中)分情况讨论
    -   eof符号: 输入完成,退出循环
    -   分号: 取下一个token
    -   def定义: 调用HandleDefinition处理定义
    -   extern声明: 调用HandleExtern处理声明
    -   其他情况: 调用HandleTopLevelExpression处理顶层表达式

### HandleDefinition<a id="sec-1-2-2" name="sec-1-2-2"></a>

这个函数用来处理函数定义,调用parsedefinition看能否正确匹配一个函数定义,匹配成功则输出成功信息.否则为了方便错误恢复直接跳过已读token取下一个token.

对应抽象语法树FunctionAST如下: (结构简单就直接用文本了)
-   括号拼起来表示表示一整个节点,逗号分隔不同儿子(括号中地逗号仅表示分隔关系).
-   proto &#x2013;> def &#x2013;> (FnName, '(', ArgNames, ')'), expression

### HandleTopLevelExpression<a id="sec-1-2-3" name="sec-1-2-3"></a>

这个函数用来处理顶层表达式,先调用ParseTopLevelExpr看能否匹配一个顶层表达式,能匹配输出成功信息.否则直接读取下一个token

对应抽象语法树TopLevelExpAST如下:
-   proto &#x2013;> identifier, '(', number, if, for
-   之后的省略(情况太多,体现topLevelExp地AST结构即可)

## Kaleidoscope在Lexer和Parser间传递信息（token、语义值、用什么函数和变量）<a id="sec-1-3" name="sec-1-3"></a>

-   parser调用ast命名空间中的getNextToken间接调用gettok(),得到token存在Curtok中
-   枚举类型Token中定义了各种类型的token,区别结束符,def,extern,标识符,数字等.
    -   负数标识特殊涵意
    -   非负数为未知字符
-   gettok返回值为token类型,如果不是特殊token就直接返回相应字符
-   通过全局变量NumVal, IdentifierStr等记录数字值以及标识符字符串来传递语义值

## Kaleidoscope处理算符优先级<a id="sec-1-4" name="sec-1-4"></a>

### 解释ParseBinOpRHS以及优先级处理方式<a id="sec-1-4-1" name="sec-1-4-1"></a>

1.  基本原理

    -   用STL的map做hash(BinopPrecedence)),value值越高,代表优先级越高
    -   ExprPrec参数为算式优先级,LHS为算式.可以理解成算式最后一次运算当成整体为算式优先级.如果当前算符优先级比这个低,那么为该递归的中止条件
    -   递归计算运算符左部,右部.计算完成之后将运算符,左部,右部拼起来通过指针LHS将参数传出去

2.  步骤

    -   在需要解析表达式时调用这个函数.
    -   先调用GetTokPrecedence确保是一个运算符,如果不是返回-1,否则返回map中这个key对应的value
    -   上一步已经将字符key转化成value,所以现在比较优先级直接比value即可
    -   下面的TokPrec < ExprPrec为递归中止条件,上小节已经解释
    -   没有中止,则标识现在的运算符生效.BinOp存当前运算符,吃掉下一个标识符token
    -   此时RHS右部子式由ParsePrimary产生.为空的话处理完毕,return 0
    -   否则NextPrec得到下一个运算符优先级
    -   比较当前算符和NextPrec优先级,如果更低,则递归调用,得右部(NextPrec应该先算)),同时当前算符优先级变位TokPrec+1,加1得原因式处理同算符左结合
    -   最后大功告成,将运算符,左部,右部拼起来变成BinaryExprAST即可.

### 分析a\*b\*c、a\*b+c、a+b\*c分别如何处理(对象不好表示,意会一下)<a id="sec-1-4-2" name="sec-1-4-2"></a>

1.  a\*b\*c

    1.  TokPrec = 40, ExprPrec = 0, NextPrec = 40. 同一优先级.继续循环,第一个乘法
    2.  TokPrec = 40, ExprPrec = 0, NextPrec = 无. 中止,第二个乘法
    
    所以先算第一个,后算第二个乘法.

2.  a\*b+c

    1.  TokPrec = 40, ExprPrec = 0, NextPrec = 20, 优先级高于NextPrec,继续循环,乘法
    2.  TokPrec = 20, ExprPrec = 0, NextPrec = 无, 中止,加法
    
    所以先算乘法,后算加法

3.  a+b\*c

    1.  TokPrec = 20, ExprPrec = 0, NextPrec = 40, 优先级低于NextPrec,递归调用ParseBinOpRHS(21, RHS)
    2.  TokPrec = 40, ExprPrec = 21, 中止此层递归,回溯. 算乘法
    3.  回溯回第一层,算加法
    
    所以先算乘法,再算加法

## 解释Error, ErrorP, ErrorF的作用，举例说明它们在语法分析中应用<a id="sec-1-5" name="sec-1-5"></a>

用来最后输出错误信息,可以理解为最低层得过程. 所有错误输出都通过传入Str参数调用此函数.而后面得两个error虽然实现得功能完全一致,但是为了方便调用函数return,所以ErrorP为返回值PrototypeAST时调用,ErrorF是返回值FunctionAST时调用.

在语法分析中,它们用来输出错误信息,方便修正语法错误. 而ErrorP和ErrorF仅仅得存在仅仅时为了满足调用它得函数得返回值类型要求.

## Kaleidoscope不支持声明变量，给变量赋值，那么变量的作用是什么？<a id="sec-1-6" name="sec-1-6"></a>

函数传参(人家长得好像函数式语言,基本思想就该这样)

## 为什么不需要{&#x2026;}或begin&#x2026;end？<a id="sec-1-7" name="sec-1-7"></a>

因为没有复合语句块,自然不许要begin和end.可以测试if(x<0) then之后输入两个表达式会报错,说期望有else.

## Kaleidoscope是如何避免if/then/else语句的二义性的？<a id="sec-1-8" name="sec-1-8"></a>

我们来看ParseIfExpr()函数即可.
-   先抹掉if
-   读条件句,无条件句return 0
-   读then,无then return0
-   读then的执行语句,无return0
-   读else,无else时return 0
-   读else的执行语句,无时return0

可以见得严格规定了if <\*Cond> then <\*then> else <\*else> 的格式,少了任何一部分都算错误.不会出现我们c语言中的无else这种情况. 在这个严格规定下,加上没有复合语句,当然就没有二义性咯

## Kaleidoscope只有一种数据类型double，那么if/then/else的分支条件是如何实现的？<a id="sec-1-9" name="sec-1-9"></a>

-   BinaryExpr::Codegen中将条件式转化成Builder类型
-   IfExprAST::Codegen中把浮点数经过与0.0的比较转化成了布尔型,这个过程通过Builder.CreateFCmpONE实现
-   变成了bool型就可以愉快地判断啦.

# 拓展while循环<a id="sec-2" name="sec-2"></a>

while和if与for最为相似,所以只需要在所有函数中找到if和for,在中间照着写一个while即可(实际上就是化简版for).添加了如下内容 (本实验只要求输出dot图,所以WhileExprAST::Codegen直接return0)

## toy.cpp<a id="sec-2-1" name="sec-2-1"></a>

-   enum Token 中添加tok<sub>while</sub> = -11
-   gettok 中添加while地case
-   ParsePrimary中添加tok<sub>while地case调用ParseWhileExpr</sub>
-   仿照ParseForExpr写ParseWhileExpr
-   仿照\*ForExprAST::Codegen()写\*WhileExprAST::Codegen()

## dumpdot.cpp<a id="sec-2-2" name="sec-2-2"></a>

-   仿照 ForExprAST::dumpdot写WhileExprAST

## ash.h<a id="sec-2-3" name="sec-2-3"></a>

-   仿照ForExprAST定义WhileExprAST类