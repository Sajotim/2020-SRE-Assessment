#ifndef YANGZHENYV_VIRTUALMACHINE_H
#define YANGZHENYV_VIRTUALMACHINE_H


#include <string>
#include <stack>

/* data_RAM为存放数据的内存栈。使用数组模拟的原因是为了READ()函数服务。该函数功能为读取栈中的所有数据。
 * program_RAM为存放代码指令的内存栈。因为如果使用模式2：可视的列式计算便可看到所有指令的运行过程。
 * Register为一个寄存器(大概)。进行运算时先从数据栈顶弹出数据暂时保存在Register中，再弹出下一个栈顶数据与其进行运算，将结果压入数据栈中。*/

class VirtualMachine {
private:
    static const int MAX_DEPTH = 1024;          // 栈的最大深度即最大内存
    int mode, RAM_top,Register{}, data_RAM[MAX_DEPTH]{0};
    std::string expression;
    std::stack <int> program_RAM;
    enum instruction{
        Empty, Size, Push, Top, Pop, Add, Sub, Mul, Div, Mod, Read,
    };

protected:
    bool EMPTY() const;
    int SIZE() const;
    int PUSH(int x);
    int TOP();
    int POP();
    void ADD();
    void SUB();
    void MUL();
    bool DIV();
    bool MOD();
    void READ();
    static void HELP();

public:
    VirtualMachine();
    void load_main_interface();
    void start();
    [[noreturn]] void run();
    void reboot();
    static void exit();
    void calculate();
    void load_program();
    [[noreturn]] void using_code();
    void run_program();
};



#endif //YANGZHENYV_VIRTUALMACHINE_H
