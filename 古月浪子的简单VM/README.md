## 古月浪子的简单VM v2.0

#### 实现的功能：

实现了一台简单的虚拟机及其字节码编译器。

#### 介绍：

程序分为2部分，编译器与虚拟机。

编译器通过解析我自定义的伪汇编代码，将其转换为字节码（xxx.op文件），虚拟机读入字节码文件并完成模拟运行操作。

伪汇编代码的关键字和标识符均不区分大小写，用双引号括起来的字符串区分大小写，字符串支持\n换行。

目前暂不支持为伪汇编代码添加注释。

虚拟机模拟运行环境为32位。

#### 寄存器：

| 特殊寄存器 | 功能                                                         |
| ---------- | ------------------------------------------------------------ |
| base       | 程序基址，所有取地址运算均以base加上相对偏移量来定位真实内存地址，不可读写 |
| ip         | 程序当前指令的指针                                           |
| sp         | 栈顶指针                                                     |

| 通用寄存器 | 功能                                                         |
| ---------- | ------------------------------------------------------------ |
| ax         | 用于传递返回值、判断跳转条件、输入输出、申请内存、存放计算结果、暂存数据 |
| bx         | 暂存数据                                                     |
| cx         | 暂存数据                                                     |
| dx         | 暂存数据                                                     |

#### 指令集/语法：

| 指令            | 功能                                                         |
| :-------------- | ------------------------------------------------------------ |
| label:          | 标记一个名为label的标签                                      |
| push reg        | 将reg中的值入栈 [reg = 通用寄存器,sp]                        |
| push imm        | 将立即数入栈                                                 |
| pop reg         | 出栈并将被出栈的值赋给reg [reg = 通用寄存器,sp]              |
| jmp label       | 无条件跳转到名为label的标签处                                |
| je label        | 若ax等于0则跳转到名为label的标签处                           |
| jne label       | 若ax不等于0则跳转到名为label的标签处                         |
| jg label        | 若ax大于0则跳转到名为label的标签处                           |
| jge label       | 若ax大于等于0则跳转到名为label的标签处                       |
| jl label        | 若ax小于0则跳转到名为label的标签处                           |
| jle label       | 若ax小于等于0则跳转到名为label的标签处                       |
| mov reg1 reg2   | 将reg2的值赋给reg1 [reg1,reg2 = 通用寄存器、reg1 != reg2]    |
| mov reg1 [reg2] | 将reg2指向的地址的值赋给reg1 [reg1,reg2 = 通用寄存器]        |
| mov [reg1] reg2 | 将reg2赋给reg1指向的地址 [reg1,reg2 = 通用寄存器]            |
| mov reg imm     | 将立即数赋给reg [reg = 通用寄存器]                           |
| mov reg "..."   | 将字符串的首地址赋给reg [reg = 通用寄存器]                   |
| in char         | 读入一个字符到ax                                             |
| in int          | 读入一个整数到ax                                             |
| in string       | 读入一个字符串到ax指向的地址                                 |
| out char        | 将ax以字符形式输出                                           |
| out int         | 将ax以整数形式输出                                           |
| out string      | 将ax指向的地址以字符串形式输出                               |
| mem             | 申请以ax的值为大小的内存并将内存地址的相对偏移量赋给ax       |
| nop             | 不进行任何操作                                               |
| cmp reg1 reg2   | 将reg1-reg2的结果赋给ax [reg1,reg2 = 通用寄存器]             |
| add reg1 reg2   | 将reg1+reg2的结果赋给ax [reg1,reg2 = 通用寄存器]             |
| mul reg1 reg2   | 将reg1*reg2的结果赋给ax [reg1,reg2 = 通用寄存器]             |
| div reg1 reg2   | 将reg1/reg2的结果赋给ax（向下取整） [reg1,reg2 = 通用寄存器] |
| mod reg1 reg2   | 将reg1%reg2的结果赋给ax [reg1,reg2 = 通用寄存器]             |
| and reg1 reg2   | 将reg1&reg2的结果赋给ax [reg1,reg2 = 通用寄存器]             |
| or reg1 reg2    | 将reg1\|reg2的结果赋给ax [reg1,reg2 = 通用寄存器]            |
| xor reg1 reg2   | 将reg1^reg2的结果赋给ax [reg1,reg2 = 通用寄存器]             |
| neg reg         | 将~reg的结果赋给ax [reg = 通用寄存器]                        |

#### 测试示例使用方法：

进入bin目录

java -jar VMCompiler.jar calculator.txt

VM.exe calculator.txt.op

输入“1 + 2”

输入“y”

输入“4 * 7”

输入“n”