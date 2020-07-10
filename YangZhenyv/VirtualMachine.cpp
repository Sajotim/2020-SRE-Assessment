#include <iostream>
#include <fstream>
#include <cstring>
#include "VirtualMachine.h"
#include "DataProcess.h"


/*
 * 弹出数据栈顶数据"x"并计入寄存器
 * 弹出数据栈顶数据"y"并与寄存器数据相加/减乘/除/取余
 * 将结果压入数据栈
 * (不知道这样子理解寄存器正不正确 */

VirtualMachine::VirtualMachine() {
    mode = -1; RAM_top = -1;
}

/*protect*/
bool VirtualMachine::EMPTY() const{
    if (RAM_top == -1) {
        return true;
    }
    return false;
}

int VirtualMachine::SIZE() const{
    return RAM_top+1;
}

int VirtualMachine::PUSH(int x){
    if (mode == 2){
        std::cout << "PUSH\t" << x << std::endl;
    }
    if(RAM_top > MAX_DEPTH){
        std::cout << "栈满" << std::endl;
        return false;
    }
    else{
        RAM_top++;
        data_RAM[RAM_top] = x;
        return true;
    }
}

int VirtualMachine::TOP(){
    if (EMPTY()){
        std::cout << "RAM的大小为";
        return 0;
    }
    return data_RAM[RAM_top];
}

int VirtualMachine::POP(){
    if (RAM_top >= 0){
        int top_val = data_RAM[RAM_top];
        data_RAM[RAM_top] = 0;
        RAM_top--;
        if (mode == 2){
            std::cout << "POP\t\t" << top_val << std::endl;
        }
        return top_val;
    } else{
        std::cout << "RAM的大小为";
        return 0;
    }

}

void VirtualMachine::ADD(){
    Register = POP();
    if (mode == 2) {
        std::cout << "ADD\t" << TOP() << "\t" << Register << std::endl;
    }
    PUSH(Register + POP());
}

void VirtualMachine::SUB(){
    Register = POP();
    if (mode == 2){
        std::cout << "SUB\t" << TOP() << "\t" << Register << std::endl;
    }
    PUSH(Register - POP());
}

void VirtualMachine::MUL(){
    Register = POP();
    if (mode == 2){
        std::cout << "MUL\t" << TOP() << "\t" << Register << std::endl;
    }
    PUSH(POP() * Register);
}

bool VirtualMachine::DIV(){
    Register = POP();
    if (Register == 0){
        std::cout << "除数不能为零！" << std::endl;
        POP();
        return false;
    }else{
        if (mode == 2){
            std::cout << "DIV\t" << TOP() << "\t" << Register << std::endl;
        }
        PUSH( Register / POP());
        return true;
    }
}

bool VirtualMachine::MOD(){
    Register = POP();
    if (Register == 0){
        std::cout << "除数不能为零！" << std::endl;
        POP();
        return false;
    }else{
        if (mode == 2){
            std::cout << "MOD\t" << TOP() << "\t" << Register << std::endl;
        }
        PUSH(POP() % Register);
        return true;
    }
}

void VirtualMachine::READ(){
    if (RAM_top == -1){
        std::cout << "data_RAM is empty" << std::endl;
    } else {
        std::cout << "No.\tVal" << std::endl;
        for (int i = RAM_top; i >= 0; i--) {
            std::cout << i << "\t" << data_RAM[i] << std::endl;
        }
    }
}

void VirtualMachine::HELP(){
    std::string data;
    std::ifstream infile;
    infile.open("..\\help.txt");
    while(getline(infile,data))
    {
        std::cout<<data<<std::endl;
    }
    std::cout<<std::endl;
    infile.close();
}


/*public:*/
void VirtualMachine::load_main_interface(){
    std::cout << "选择一个指令参数 " << std::endl;
    std::cout << "0. 帮助" << std::endl;
    std::cout << "1. 列式计算(不可视)" << std::endl;
    std::cout << "2. 列式计算(可视)" << std::endl;
    std::cout << "3. 使用指令" << std::endl;
    std::cout << "4. 重启" << std::endl;
    std::cout << "5. 退出" << std::endl;
    std::cin >> mode;
    while(mode < 0 || mode > 5){
        std::cout << "Wrong input!" << std::endl;
        std::cin >> mode;
    }
}

void VirtualMachine::start(){
    std::cout << "Welcome to Rei 0.0" << std::endl;
    while (RAM_top != -1) POP();     // 清空栈
    load_main_interface();
}

void VirtualMachine::run(){
    if (mode != 0)
        std::cout << "输入 \":change\" 来改变运行内容" << std::endl;
    while (true){
        switch (mode){
            case 0:
                HELP();
                load_main_interface();
                break;
            case 1:
            case 2:
                calculate();
                break;
            case 3:
                using_code();
            case 4:
                reboot();
                break;
            case 5:
                exit();
        }
    }
}

void VirtualMachine::reboot(){
    std::cout << "Killing and rebirthing myself..." << std::endl << std::endl;
    start();
}

void VirtualMachine::exit(){
    std::cout << "Killing myself..." << std::endl;
    std::exit(0);
}

void VirtualMachine::calculate(){
    std::cout << ">>> ";
    std::cin >> expression;
    if (expression == ":change"){
        load_main_interface();
    }
    else{
        load_program();
        run_program();
    }
}

void VirtualMachine::load_program() {
    expression = DataProcess::inf_to_pre(expression);
    if (mode == 2) std::cout << "Infix expression to Prefix expression:" << expression << std::endl;
    std::string instr;
    for (int i = 0; i < expression.size(); i++) {
        if (expression.at(i) == ' ')
            continue;
            // 数字判断
        else if (isdigit(expression.at(i)) ||
                 (i < expression.size() - 2 && expression.at(i) == '-' && isdigit(expression.at(i + 1)))) {
            instr += expression.at(i);
            // 到数字末尾
            if ((i < expression.size() - 2 && expression.at(i + 1) == ' ') || i == expression.size() - 1) {
                program_RAM.push(DataProcess::str_to_int(instr));
                program_RAM.push(Push);
                instr = "";
            }
        } else {
            // Empty, Size, Push, Top, Pop, Add, Sub, Mul, Div, Mod, Read, Help
            switch (expression.at(i)) {
                case '+':
                    program_RAM.push(Add);
                    break;
                case '-':
                    program_RAM.push(Sub);
                    break;
                case '*':
                    program_RAM.push(Mul);
                    break;
                case '/':
                    program_RAM.push(Div);
                    break;
                case '%':
                    program_RAM.push(Mod);
                    break;
            }
        }
    }
}

[[noreturn]] void VirtualMachine::using_code(){
    while (true) {
        std::string code;
        std::cout << ">>> ";
        getline(std::cin, code);
        // code 拆分
        std::string program[3] = {""};
        const char *d = " \t";
        char *p;
        int i = 0;
        p = strtok((char *) code.data(), d);
        while (p) {
            program[i] = p;
            i++;
            p = strtok(nullptr, d);
        }

        if (program[0] == "END" || program[0] == "end") {
            load_program();
            break;
        }
        else if (program[0] == "EMPTY" || program[0] == "empty") {
            program_RAM.push(Empty);
        }
        else if (program[0] == "SIZE" || program[0] == "size") {
            program_RAM.push(Size);
        }
        else if (program[0] == "PUSH" || program[0] == "push") {
            if (program[1].empty()) {
                std::cout << "Wrong input." << std::endl;
            } else {
                program_RAM.push(DataProcess::str_to_int(program[1]));
                program_RAM.push(Push);
            }
        }
        else if (program[0] == "TOP" || program[0] == "top") {
            program_RAM.push(Top);
        }
        else if (program[0] == "POP" || program[0] == "pop") {
            program_RAM.push(Pop);
        }
        else if (program[0] == "ADD" || program[0] == "add") {
            if (program[1].empty() && program[2].empty()) {
                if (SIZE() < 2) std::cout << "Wrong input. Less than 2 elements in RAM_stack." << std::endl;
                else program_RAM.push(Add);
            } else if (!program[1].empty() && !program[2].empty()) {
                program_RAM.push(DataProcess::str_to_int(program[1]));
                program_RAM.push(Push);
                program_RAM.push(DataProcess::str_to_int(program[2]));
                program_RAM.push(Push);
                program_RAM.push(Add);
            }
        }
        else if (program[0] == "SUB" || program[0] == "sub") {
            if (program[1].empty() && program[2].empty()) {
                if (SIZE() < 2) std::cout << "Wrong input. Less than 2 elements in RAM_stack." << std::endl;
                else SUB();
            } else if (!program[1].empty() && !program[2].empty()) {
                program_RAM.push(DataProcess::str_to_int(program[1]));
                program_RAM.push(Push);
                program_RAM.push(DataProcess::str_to_int(program[2]));
                program_RAM.push(Push);
                program_RAM.push(Sub);
            }
        }
        else if (program[0] == "MUL" || program[0] == "mul") {
            if (program[1].empty() && program[2].empty()) {
                if (SIZE() < 2) std::cout << "Wrong input. Less than 2 elements in RAM_stack." << std::endl;
                else MUL();
            } else if (!program[1].empty() && !program[2].empty()) {
                program_RAM.push(DataProcess::str_to_int(program[1]));
                program_RAM.push(Push);
                program_RAM.push(DataProcess::str_to_int(program[2]));
                program_RAM.push(Push);
                program_RAM.push(Mul);
            }
        }
        else if (program[0] == "DIV" || program[0] == "div") {
            if (program[1].empty() && program[2].empty()) {
                if (SIZE() < 2) std::cout << "Wrong input. Less than 2 elements in RAM_stack." << std::endl;
                else DIV();
            } else if (!program[1].empty() && !program[2].empty()) {
                program_RAM.push(DataProcess::str_to_int(program[1]));
                program_RAM.push(Push);
                program_RAM.push(DataProcess::str_to_int(program[2]));
                program_RAM.push(Push);
                program_RAM.push(Div);
            }
        }
        else if (program[0] == "MOD" || program[0] == "mod") {
            if (program[1].empty() && program[2].empty()) {
                if (SIZE() < 2) std::cout << "Wrong input. Less than 2 elements in RAM_stack." << std::endl;
                else MOD();
            } else if (!program[1].empty() && !program[2].empty()) {
                program_RAM.push(DataProcess::str_to_int(program[1]));
                program_RAM.push(Push);
                program_RAM.push(DataProcess::str_to_int(program[2]));
                program_RAM.push(Push);
                program_RAM.push(Mod);
            }
        }
        else if (program[0] == "READ" || program[0] == "read") {
            program_RAM.push(Read);
        }
        else if (program[0] == "HELP" || program[0] == "help") {
            HELP();
        }
        else {
            std::cout << R"(Wrong input. Enter "HELP" or "help" for help.)" << std::endl;
        }
        run_program();
    }

}

void VirtualMachine::run_program(){
    while(!program_RAM.empty()){
        switch(program_RAM.top()){
            // Empty, Size, Push, Top, Pop, Add, Sub, Mul, Div, Mod, Read, Help, Back_to_main
            case Empty:
                if (EMPTY()) {
                    std::cout << "data_RAM is empty" << std::endl;
                } else {
                    std::cout << "data_RAM is not empty" << std::endl;
                }
                break;
            case Size:
                std::cout << SIZE() << std::endl;
                break;
            case Push:
                program_RAM.pop();
                PUSH(program_RAM.top());
                break;
            case Top:
                std::cout << TOP() << std::endl;
                break;
                // - + 2 3 * / + + -3 5 0 5 3
            case Pop:
                std::cout << POP() << std::endl;
                break;
            case Add:
                ADD();
                break;
            case Sub:
                SUB();
                break;
            case Mul:
                MUL();
                break;
            case Div:
                DIV();
                break;
            case Mod:
                MOD();
                break;
            case Read:
                READ();
                break;
        }
        program_RAM.pop();
    }
}