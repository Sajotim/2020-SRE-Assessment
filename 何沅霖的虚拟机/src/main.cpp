#include "VM_main.h"

void show(){
    std::cout<<"__     ____  __ ____   _____  __\n"
               "\\ \\   / /  \\/  | __ ) / _ \\ \\/ /\n"
               " \\ \\ / /| |\\/| |  _ \\| | | \\  / \n"
               "  \\ V / | |  | | |_) | |_| /  \\ \n"
               "   \\_/  |_|  |_|____/ \\___/_/\\_\\\n"
               "       1.运行        2调试   \n";

}

void run(int f_debug = false){
    VM_BOX start,*BOX;
    BOX = &start;
    BOX ->initialization(f_debug);
    BOX ->load_to_memory();
    BOX ->boot();
}

void choice(int cp){
    if (cp == RUN){
        std::cout << "正在运行：多则运算程序(支持四则，按位异或，按位与，按位或运算)" << std::endl;;
        run();
    }
    else if (cp == DEBUG){
        std::cout << "正在运行：多则运算程序" << std::endl << "运行完毕后会输出指令调用顺序和数据流向" << std::endl;;
        run(true);
    }
    else {
        std::cout << "输入错误" <<std::endl;
    }
}

int main() {
    show();
    int cp;
    std::cout << "请选择功能:";
    std::cin >> cp;
    choice(cp);
    system("pause");
    return 0;
}
