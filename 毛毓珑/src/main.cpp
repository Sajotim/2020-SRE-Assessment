#include <stdbool.h> 
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
using namespace std;
//指令集
map<string, int> m;
void map_including() {
    m["PSH"] = 0;
    m["ADD"] = 1;
    m["POP"] = 2;
    m["SET"] = 3;
    m["HLT"] = 4;
    m["MUL"] = 5;
    m["DIV"] = 6;
    m["MOD"] = 7;
	m["XOR"] = 8;
	m["OR"] = 9;
	m["AND"] = 10;
}

//寄存器
enum {
    R0=0,
    R1,
    R2,
    R3,
    R4,//前四个系统用
	I0,
	I1,
	I2,
	I3,
	I4,//任意寄存器
    SP,
    PC,
    RCOUNT
};
int reg[RCOUNT];
//全局数据栈
int &sp = reg[SP];
int stack[256];

//将要执行的指令
int program[256];
int &pc = reg[PC];
//获取指令
int fetch() {
    return program[pc];
}
bool running = true;
//关于四则运算的二进制逻辑实现
void add() {
    reg[R0] = stack[sp--];
    reg[R1] = stack[sp--];
    int i = 0;
    reg[R2] = 0; //c 进位
    reg[R3] = 0; //s 结果
    //全加器
    //似乎最后一位不能移动的-1在这里刚好形成了一个补码，所以减法器也不用写了
    do {
        reg[R3] |= (((reg[R0] ^ reg[R1]) & 1) ^ reg[R2]) << i;
        reg[R2] = (((reg[R0] ^ reg[R1]) & 1) & reg[R2]) | ((reg[R0] & reg[R1]) & 1);
        reg[R0] >>= 1; reg[R1] >>= 1;
    } while (i++ < sizeof(int) * 8 - 1);
    stack[++sp] = reg[R3];
}
int div() {
    int i = -1;
    stack[sp] = -stack[sp];
    while (stack[sp - 1] >= 0)
    {
        add();
        sp++, i++;
    }sp--;
    return i;
}
ofstream fout("out.txt");
void eval(int instr) {
    switch (instr) {
    case 0: {//PSH
        sp++;
        stack[sp] = program[++pc];
        break;
    }
    case 1: {//ADD
        add();
        break;
    }
    case 2: {//POP
        fout << stack[sp--] <<'\n';
        break;
    }
    case 3: {//SET
		int a = program[++pc];
        reg[a] = program[++pc];
		break;
    }
    case 4: {//HLT
        running = false;
        printf("done\n");
        break;
    }
    //乘除取模 基于加法器
    case 5: {//MUL
        int a = stack[sp];
        reg[R4] = stack[sp-1];   
        stack[sp - 1] = 0;
        for (int i = 0; i < a; i++)
        {
            stack[sp] = reg[R4];
            add();
            sp++;
        }
        sp--;
        break;
    }
    case 6: {//DIV
        stack[sp] = div();
        break;
    }
    case 7: {//MOD
        div();
        stack[sp] -= stack[sp+1];
        break;
    }
	//逻辑运算
	case 8: {//XOR
		reg[R0] = stack[sp--];
		reg[R1] = stack[sp--];
		stack[++sp] = reg[R0] ^ reg[R1];
		break;
	}
	case 9: {//OR
		reg[R0] = stack[sp--];
		reg[R1] = stack[sp--];
		stack[++sp] = reg[R0] | reg[R1];
		break;
	}
	case 10: {//AND
		reg[R0] = stack[sp--];
		reg[R1] = stack[sp--];
		stack[++sp] = reg[R0] & reg[R1];
		break;
	}
    }
}
int main() {
    sp = -1;
    pc = 0;
    map_including();
    int i = 0;
    ifstream programfile("program.txt");
    
    if (!programfile.is_open())
    {
        cout << "Error opening file"; exit(1);
    }
    while (!programfile.eof())
    {
        string pro;
        programfile >> pro;
        if (pro[0] >= '0' && pro[0] <= '9' || pro[0] == '-')
        {
            stringstream ss;
            ss << pro;
            ss >> program[i++];
        }
        else
            program[i++] = m[pro];
    }
    while (running) {
		cout << pc << ' ';
        eval(fetch()); 
        pc++; // increment the ip every iteration
    }
}

