##### 方向： 李玉堂学长的“简单”虚拟机

##### 测试环境：MinGW ，win10

##### 语言：C++

##### 实现功能：

​	1.Level 1 实现一个简易的虚拟机（基于栈）。

​	2.Level 2 提升。

​	3.Level 3 附加功能中的其他计算功能（位运算）。

##### 介绍：

​	1.虚拟机功能：进行小学三年级的四则运算

​	2.虚拟机指令：

| 指令 | 功能描述                 |
| :--- | ------------------------ |
| HEL  | 程序结束标志             |
| PUSH | 压栈                     |
| POP  | 弹出栈顶元素             |
| MOV  | 后移至前                 |
| ADD  | 栈顶两元素相加并push回去 |
| SUB  | 栈顶减去第二个并压回去   |
| DIV  | 略                       |
| MUL  | 略                       |
| XOR  | 略                       |
| OR   | 略                       |
| AND  | 略                       |
| TOP  | 输出栈顶元素             |
| JMP  | 跳转到指定数据段         |
| OUT  | 输出寄存器值             |

#### 测试程序：
```
main:
    push 3
    push 4
    add
    push 2
    sub
    jmp end

no_exec:
    push 7
    mul

end:
    push 3
    mul
    top
    hlt
```

#### 编译：

```bash
compile.py test.txt
```

#### 运行：

```bash
main.exe test.vm
```

#### 结果：

```bash
[Info]: Welcome to use my laji VM!

[VM]: Initing VM...
[VM]: Inited.

[VM]: Loading program...
[Start]: 0x61ded8
[End]: 0x61df1d
[Len]: 17
[VM]: Loaded.
[Debug]:
        0       3       0       4
        2       0       2       3
        13      13      0       7
        4       0       3       4
        9
[Load status]: 0
[VM]: Running program...
15
[VM]: Finished.

[Run status]: 0
```



##### 已知缺陷：不能指定类型输出，不能把寄存器压栈等。