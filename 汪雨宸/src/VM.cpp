// VM.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <bitset>
#include "VM.h"
using namespace std;

int main(){ 
	VirtualMachine VM;
	VM.Fetch(InputData());
	VM.printf();
	VM.Decode_Execute();
	return 0;
}