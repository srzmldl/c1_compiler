<div id="table-of-contents">
<h2>Table of Contents</h2>
<div id="text-table-of-contents">
<ul>
<li><a href="#sec-1">1. Files and directorys</a></li>
<li><a href="#sec-2">2. Tips</a></li>
<li><a href="#sec-3">3. 脚本使用说明</a></li>
<li><a href="#sec-4">4. 程序功能</a>
<ul>
<li><a href="#sec-4-1">4.1. calcSum.c</a></li>
<li><a href="#sec-4-2">4.2. pickMax.c</a></li>
<li><a href="#sec-4-3">4.3. bubleSort.c</a></li>
<li><a href="#sec-4-4">4.4. factorial.c</a></li>
<li><a href="#sec-4-5">4.5. genereatePermutatioon.c</a></li>
</ul>
</li>
</ul>
</div>
</div>

# Files and directorys<a id="sec-1" name="sec-1"></a>

<table border="2" cellspacing="0" cellpadding="6" rules="groups" frame="hsides">


<colgroup>
<col  class="left" />

<col  class="left" />
</colgroup>
<thead>
<tr>
<th scope="col" class="left">Name</th>
<th scope="col" class="left">Description</th>
</tr>
</thead>

<tbody>
<tr>
<td class="left">README.org</td>
<td class="left">this file</td>
</tr>


<tr>
<td class="left">README.md</td>
<td class="left">exported frome README.org</td>
</tr>


<tr>
<td class="left">src/</td>
<td class="left">source(\*.h, \*.c)</td>
</tr>


<tr>
<td class="left">doc/</td>
<td class="left">designing decument of this project</td>
</tr>


<tr>
<td class="left">bin/</td>
<td class="left">shell</td>
</tr>


<tr>
<td class="left">test/</td>
<td class="left">test programs</td>
</tr>
</tbody>
</table>

# Tips<a id="sec-2" name="sec-2"></a>

-   检查时请直接运行bin下的bash.sh,可以自动编译,运行所有程序.并且输出带有提示的检查信息
-   请根据编辑器情况自行选择README.org与README.md,后者由插件转码,体验较差.请尽量看org文档

# 脚本使用说明<a id="sec-3" name="sec-3"></a>

-   脚本在"bin/bash.sh".
-   在终端中输入"bash bash.sh"即可
-   执行之后会编译所有程序,并输出检查信息.检查十分便利
-   执行之后bash会自动删除可执行文件.如果需要留下可执行文件,请删掉rm那一句命令
-   实现方法:简单粗暴,遍历/src文件夹下的所有.c后缀文件.取出名字,再和删掉后缀名后的中间变量一起作为gcc的两个参数.然后再删除可执行文件

# 程序功能<a id="sec-4" name="sec-4"></a>

## calcSum.c<a id="sec-4-1" name="sec-4-1"></a>

-   计算数组中每一个元素和.
-   测试gcc,clang中对const数组的不同要求.
-   写一下简陋的循环

## pickMax.c<a id="sec-4-2" name="sec-4-2"></a>

-   找出按一定规则生成的数组中的最大值
-   测试加减乘除模这些运算
-   测试溢出int时的情况

## bubleSort.c<a id="sec-4-3" name="sec-4-3"></a>

-   对数组元素从小到大排序,最后自行检验是否有序,体现在flag中
-   测试循环嵌套
-   写较长的c1程序

## factorial.c<a id="sec-4-4" name="sec-4-4"></a>

-   输出n的阶乘,程序中为10
-   测试无参函数调用以及递归

## genereatePermutatioon.c<a id="sec-4-5" name="sec-4-5"></a>

-   生成1-n组成的排列,按照字典序输出
-   测试递归
-   测试无参数传递的回溯
-   测试局部变量,全局变量作用域