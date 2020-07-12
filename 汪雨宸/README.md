基于寄存器的简单虚拟机
模拟了物理机的运行
fetch——>decode——>execute
——————————————————————————————————————
LOAD_A       |  02  |   read RAM location into register A
LOAD_B       |  01  |
STORE_A    |  04  |  write from register A into RAM location
ADD             |  08  |  add two registers and store the value into the second register
SUB             |  12  |
MULTI          |  14  |
DEVIDE       |  15  | 
HALT            |  00  |
——————————————————————————————————————

易知前三种操作码，后四位的地址为RAM中的一个地址
register定义为了枚举类型，可以直接通过下标访问，A为0，B为1...
后四种操作，地址为两个寄存器，如执行0802，即是用寄存器C中的值减去寄存器A中的值，并将结果存入第二个寄存器也就是C中。

为验证正确性，运行switch-case语句同时输出了结果。
![运行结果.png](https://i.loli.net/2020/07/12/ePfVXLkGYTJdDyU.png)