#pragma once
using namespace std;
int program[16];
/*
int decToBin(int dec) { 
	int result = 0, temp = dec, j = 1;	
	while (temp) { 
		result = result + j * (temp % 2);		
		temp = temp / 2;		
		j = j * 10; 
	}	
	return result; 
}
*/
//INSTRUCTION TABLE
const int LOAD_A  =  0b0010;  //  2
const int LOAD_B  =  0b0001;  //  1
const int STORE_A =  0b0100;  //  4
const int ADD     =  0b1000;  //  8
const int SUB     =  0b1100;  // 12
const int MULTI   =  0b1110;  // 14
const int DEVIDE  =  0b1111;  // 15

//指令寄存器的前四位为操作码，后四位为RAM/register地址
struct instruction_register {
	int opcode;
	int address;
};

//几个寄存器
typedef enum {
	A,B,C,D,E,
	NUM_OF_RGT
}RGT;
/*  
 *  修改寄存器的值
 *  int RGT[NUM_OF_RGT];
 *  RGT[A] = 2;
 */

class VirtualMachine {
private:
	int RAM[16];                      //内存
	instruction_register IR;          //指令寄存器
	int instruction_address_register; //指令地址寄存器
	int ALU;
public:
	void Fetch(int *a);               //读取指令
	void Decode_Execute();            //指令译码&&执行指令
	void printf();                    //打印指令
};
void VirtualMachine::Fetch(int *a) {
	cout << "\n开始载入指令" << endl;
	
	for (int i = 0; i < 16 ; i++) {
		
		RAM[i] = a[i]; 
	}

	cout << "载入完成\n" << endl;
}
void VirtualMachine::printf() {
	cout << "打印将处理的指令" << endl;
	for (int i = 0; i < 16 && RAM[i] != 0; i++) {
		if (i < 10) cout << "0" << i << "\t";
		else cout << i << "\t";
		cout << RAM[i] / 1000 << RAM[i] / 100 % 10 << RAM[i] % 100 / 10 << RAM[i] % 100 % 10 << endl;
	}
	cout << "打印完成\n" << endl;
}

void VirtualMachine::Decode_Execute() {
	cout << "开始运行" << endl;
	int RGT[NUM_OF_RGT];
	for (int i = 0; i < 16 && RAM[i] != 0; i++) {
		IR.opcode = RAM[i]/100;
		IR.address = RAM[i] % 100;
		int register_former = IR.address / 10;
		int register_latter = IR.address % 10;
//		cout << IR.opcode << "\t" << IR.address<<"\t";
		switch (IR.opcode)
		{
		case(LOAD_A):
			RGT[A] = RAM[IR.address];
			cout << RGT[A] <<endl;
			break;
		case(LOAD_B):
			RGT[B] = RAM[IR.address];
			cout << RGT[B] << endl;
			break;
		case(STORE_A):
			RAM[IR.address] = RGT[A];
			cout << RAM[IR.address] <<endl;
			break;
		case(ADD):    	
			RGT[register_latter] += RGT[register_former];
			cout << RGT[A] << endl;
			break;
		case(SUB):
			RGT[register_latter] -= RGT[register_former];
			cout << RGT[B] << endl;
			break;
		case(MULTI):
			RGT[register_latter] *= RGT[register_former];
			cout << RGT[B] << endl;
			break;
		case(DEVIDE):
			RGT[register_latter] /= RGT[register_former];
			cout << RGT[B] << endl;
			break;
		default:
			break;
		}
	}
	cout << "运行结束" << endl;
}
int* InputData() {
	cout << "指令，输入exit以结束" << endl;
	for (int i = 0; i < 16; i++) {
		cin >> program[i];
		if (!cin.good())   //判断是否输入类型为int，不是则退出循环
			break;
	}
	return program;
}