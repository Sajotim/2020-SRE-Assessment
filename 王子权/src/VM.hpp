#include <stack>
#include <iostream>
#include <cstring>

const int PR_SIZE = 2048;
typedef enum
{
    PUSH,
    POP,
    ADD, //栈顶两数相加
    SUB, //相减
    MUL, //相乘
    DIV, //相除
    OR,  //或
    XOR, //异或
    AND, //与
    TOP, //输出栈顶的值
    OUT, //输出寄存器的值
    SET, //设置寄存器的值
    MOV, //移动寄存器的值
    JMP, //跳转
    HLT
} OP;

typedef enum
{
    AX,
    BX,
    NUM_OF_REG
} REG;

class VM
{
private:
    int ax, bx, ip, tmp;
    int program[PR_SIZE];
    std::stack<int> st;
    int fetch()
    {
        return program[ip++];
    };

public:
    VM(/* args */);
    void initVM();
    bool loadProgram(int *code);
    bool run();
    ~VM();
};

VM::VM(/* args */)
{
    std::cout << "[Info]: Welcome to use my laji VM!\n"
              << std::endl;
}

void VM::initVM()
{
    std::cout << "[VM]: Initing VM..." << std::endl;
    ax = 0;
    bx = 0;
    ip = 0;
    memset(program, 0, sizeof(program));
    std::stack<int>().swap(st);
    std::cout << "[VM]: Inited.\n"
              << std::endl;
}

bool VM::loadProgram(int *code)
{
    std::cout << "[VM]: Loading program..." << std::endl;
    int *end, len, iip = 0;
    end = (int *)memccpy(program, code, HLT, PR_SIZE);
    std::cout << "[Start]: " << program << "\n[End]: " << end;
    len = (end - program);
    std::cout << "\n[Len]: " << len << std::endl;
    std::cout << "[VM]: Loaded.\n[Debug]:";
    for (iip = 0; program[iip] != HLT; iip++)
    {
        if (iip % 4 == 0)
            putchar('\n');
        std::cout << '\t' << program[iip];
    }
    std::cout << std::endl;
    return (len >= PR_SIZE) ? 1 : 0;
}

bool VM::run()
{
    bool running = true;
    std::cout << "[VM]: Running program..." << std::endl;
    while (running)
    {
        int op = fetch();
        switch (op)
        {
        case HLT:
            running = false;
            break;
        case PUSH:
            st.push(fetch());
            break;
        case POP:
            st.pop();
            break;
        case JMP:
            ip = fetch();
            break;
        case TOP:
            std::cout << st.top();
            break;
        case SET:
            switch (fetch())
            {
            case AX:
                ax = fetch();
                break;
            case BX:
                bx = fetch();
                break;
            default:
                std::cout << "\n[VM]: Set error at ip = "
                          << ip - 1 << std::endl;
                return 1;
            }
            break;
        //四则运算
        case ADD:
            tmp = st.top();
            st.pop();
            tmp += st.top();
            st.pop();
            st.push(tmp);
            break;
        case SUB:
            tmp = st.top();
            st.pop();
            tmp = st.top() - tmp;
            st.pop();
            st.push(tmp);
            break;
        case MUL:
            tmp = st.top();
            st.pop();
            tmp *= st.top();
            st.pop();
            st.push(tmp);
            break;
        case DIV:
            tmp = st.top();
            st.pop();
            tmp = st.top() / tmp;
            st.pop();
            st.push(tmp);
            break;
        case OR:
            tmp = st.top();
            st.pop();
            tmp |= st.top();
            st.pop();
            st.push(tmp);
            break;
        case XOR:
            tmp = st.top();
            st.pop();
            tmp ^= st.top();
            st.pop();
            st.push(tmp);
            break;
        case AND:
            tmp = st.top();
            st.pop();
            tmp &= st.top();
            st.pop();
            st.push(tmp);
            break;

        default:
            std::cout << "\n[VM]: Program error at ip = "
                      << ip - 1 << std::endl;
            return 1;
        }
    }
    std::cout << "\n[VM]: Finished.\n"
              << std::endl;
    return 0;
}

VM::~VM()
{
}
