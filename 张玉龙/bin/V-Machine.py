import math


class Machine:
    def __init__(self, commend):
        self.command = commend
        # 声明数据流动的过程
        self.data_movenent = []
        self.stack = []
        self.adr = 0
        # 声明被调用的指令
        self.order_applied = []
        self.key2 = 0

    # 采用类似的字符简化定义函数，加入，弹出元素和返回栈顶元素等
    def push(self, value):
        self.stack.append(value)
        self.data_movenent.append("数据从寄存器入栈")

    def pop(self):
        self.data_movenent.append("数据出栈")
        return self.stack.pop()

    @property
    def peek(self):
        return self.stack[-1]

    # 返回栈的大小
    def size(self):
        return len(self.stack)

    def order(self, op):
        # 编辑指令集合
        order_list = {
            "+": self.pl,
            "-": self.min,
            "*": self.mul,
            "/": self.div,
            "%": self.re,
            "file": self.file,
            "trunc": self.trunc,
            "fabs": self.fabs,
            "eq": self.eq,
            "swap": self.swap,
            "over": self.over,
            "drop": self.drop,
        }
        # 判断情况，如果是整数或字符则存入栈中，指令则执行
        if op in order_list:
            print("指令，开始执行")
            order_list[op]()
            self.order_applied.append(op)

        elif isinstance(op, str) and op[0] == op[-1] == '"':
            self.push(op[1:-1])
        # 定义持续运行函数
        else:
            try:
                op = int(op)
                if self.key2:
                    op = bin(op)
                self.push(op)
            except ValueError as e:
                print(e)
                exit(0)

    def operate(self):
        self.data_movenent.append("数据与指令已进入寄存器")
        self.key2 = int(input("是否转换为二进制计算数值？ 1 or 0 ："))
        while self.adr < len(self.command):
            op = self.command[self.adr]
            self.adr += 1
            self.order(op)
        try:
            if self.stack[0]:
                print("输出结果")
                # if self.key2:
                #   self.stack[0] = int(self.stack[0],2)
                print(self.stack[0])
            else:
                print("输出结果：")
                print("0")
        except IndexError:
            print("指令完成")
        key0 = int(input("是否显示数据流向和采用指令？ 0 or 1 :"))
        if key0:
            for i in self.data_movenent:
                print("数据转移：%s" % i)
            for i in self.order_applied:
                print("指令%s ：“%s”" % (self.order_applied.index(i) + 1, i))

    # 定义编辑指令函数
    def pl(self):
        # 相加·
        int1 = self.pop()
        int2 = self.pop()
        self.push(int2 + int1)

    def min(self):
        int1 = self.pop()
        int2 = self.pop()
        self.push(int2 - int1)

    def mul(self):
        int1 = self.pop()
        int2 = self.pop()
        self.push(int2 * int1)

    def div(self):
        int1 = self.pop()
        int2 = self.pop()
        self.push(int2 / int1)

    def re(self):
        int1 = self.pop()
        int2 = self.pop()
        self.push(int2 % int1)

    def file(self):
        addr = input("请输入文件地址：")
        model = input("请输入模式：（w,r）")
        file0 = open(addr, model)
        if model == "w":
            content = input("请输入写入内容： ")
            file0.write(content)
            file0.close()
        elif model == "r":
            content = file0.read
            print(content)

    def trunc(self):
        int1 = self.pop()
        self.push(math.trunc(int1))

    def fabs(self):
        int1 = self.pop()
        self.push(math.fabs(int1))
    def eq(self):
        int1 = self.pop()
        int2 = self.pop()
        self.push(int1 == int2)

    def drop(self):
        self.pop()

    def over(self):
        int1 = self.pop()
        int2 = self.pop()
        self.push(int2)
        self.push(int1)
        self.push(int2)

    def swap(self):
        int1 = self.pop()
        int2 = self.pop()
        self.push(int1)
        self.push(int2)

if __name__ == "__main__":
    while True:
        print("计算指令请先输入数值，其它指令先直接输入指令\n")
        commend = input("请输入值或指令（A B order）：").split()
        Machine(commend).operate()
        key = input("是否继续？否请输入 exit：")
        if key == "exit":
            break