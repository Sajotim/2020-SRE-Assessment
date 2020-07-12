from sys import stdout, stdin


class VirtualMachine:
    def __init__(self, code):
        self.code = code
        self.stack = list()
        self.addr = 0

    def push(self, value):
        self.stack.append(value)

    def pop(self):
        return self.stack.pop()

    def add(self):
        v2 = self.pop()
        v1 = self.pop()
        self.push(v1 + v2)

    def sub(self):
        v2 = self.pop()
        v1 = self.pop()
        self.push(v1 - v2)

    def mul(self):
        v2 = self.pop()
        v1 = self.pop()
        self.push(v1 * v2)

    def div(self):
        v2 = self.pop()
        v1 = self.pop()
        self.push(v1 / v2)

    def equal(self):
        print(str(self.pop()))

    def exit(self):
        exit()

    def dispatcher(self, instr):
        instruct_group = {
            "+": self.add,
            "-": self.sub,
            "*": self.mul,
            "/": self.div,
            "=": self.equal,
            "exit": self.exit
        }
        if instr in instruct_group:
            instruct_group[instr]()
        else:
            self.push(int(instr))

    def run(self):
        while self.addr < len(self.code):
            code = self.code[self.addr]
            self.dispatcher(code)
            self.addr += 1


def read(prompt):
    stdout.write(prompt)
    stdout.flush()
    return stdin.readline()


def repl(prompt="root@Ubuntu> "):
    while True:
        try:
            input = read(prompt)
            code = input.split()
            VirtualMachine(code).run()
        except (RuntimeError, IndexError):
            stdout.write("表达式不合法\n")
        except KeyboardInterrupt:
            stdout.write("请使用exit退出程序\n")


repl()
