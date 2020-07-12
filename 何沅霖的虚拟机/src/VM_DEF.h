#include <iostream>
#include <string>
/*类定义 */
enum {
    HEL = 0,
    PUT,
    MOV,
    ADD,
    SUB,
    DIV,
    MUL,
    XOR,
    OR,
    AND,
    NOT,
    JEP,
    JNEP,
    JGP,
    JGEP,
    JLP,
    JLEP,
    JMP,
    OUT,
    inst_c
}; //指令集

enum {
    D_OUT ,
    D_IN ,
}; //数据来源标识

enum {
    axi = 0,
    bxi,
    cxi,
    dxi,
    exi,
    fxi,
    gxi,
    hxi,
    reg_c
}; //寄存器(写程序用)

enum {
    _char,
    _digit
}; //输入输出格式标志

enum {
    RUN = 1,
    DEBUG,
    _reg,
    _inst,
    _out,
}; //调试与运行标志

double reg[reg_c]; //模拟寄存器

int memory[INT8_MAX]; //模拟内存

class VM_BOX {
private:
    int m_address;                      //模拟内存地址
    int flag;                           //运行标志
    int r_address;                      //寄存器地址
    int debug;                          //调试标志
    std::string inst_order, reg_order;  //指令顺序,数据流向
public:
    void d_info(int op,int index = -1);
    void initialization(int f_debug);
    void load_to_memory();
    void boot();
    void instruct(int op);
};