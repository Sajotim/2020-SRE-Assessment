#include <iostream>
#include <string.h>
#include "vm.h"
using namespace std;

bool VM::Empty() const{
	if (STA_top == -1) {
		return true;
	}
	return false;
}
int VM::Size() const{
	return STA_top + 1;
}
int VM::Push(int x){
		cout << "Push " << x << endl;
	if (STA_top > MAX_DEPTH){
		cout << "栈STA满" << endl;
		return false;
	}
	else{
		STA_top++;
		data_STA[STA_top] = x;
		return true;
	}
}
int VM::Top(){
	if (Empty()){
		cout << "栈STA的大小为";
		return 0;
	}
	return data_STA[STA_top];
}
int VM::Pop(){
	if (STA_top >= 0){
		int top_val = data_STA[STA_top];
		data_STA[STA_top] = 0;
		STA_top--;
		if (mode == 2){
			cout << "POP\t\t" << top_val << endl;
		}
		return top_val;
	}
	else{
		cout << "栈STA的大小为";
		return 0;
	}

}
void VM::Plus(){
	Register = Pop();
		cout << "Plus\t" << Top() << "\t" << Register << endl;
	Push(Register + Pop());
}
void VM::Min(){
	Register = Pop();
		cout << "Min\t" << Top() << "\t" << Register << endl;
	Push(Register - Pop());
}
void VM::Mul(){
	Register = Pop();
		cout << "Mul\t" << Top() << "\t" << Register << endl;
	Push(Pop() * Register);
}
bool VM::Div(){
	Register = Pop();
	if (Register == 0){
		cout << "除数不能为零!" << endl;
		Pop();
		return false;
	}
	else{
			cout << "Div\t" << Top() << "\t" << Register << endl;
		Push(Register / Pop());
		return true;
	}
}
bool VM::Mod(){
	Register = Pop();
	if (Register == 0){
		cout << "除数不能为零！" << endl;
		Pop();
		return false;
	}
	else{
			cout << "Mod\t" << Top() << "\t" << Register << endl;
		Push(Pop() % Register);
		return true;
	}
}
// 读取
void VM::Read()   {
	if (STA_top == -1){
		cout << "STA数据为空" << endl;
	}
	else {
		cout << "No.\tVal" << endl;
		for (int i = STA_top; i >= 0; i--) {
			cout << i << "\t" << data_STA[i] << endl;
		}
	}
}

// 执行程序
void VM::Execute()   {
	cout << "简单虚拟机启动" << endl;
	while (STA_top != -1) Pop();     // 清空栈
	cout << "请选择需要的功能 " << endl
		<< "0. 计算加" << endl
		<< "1. 计算减" << endl
		<< "2. 计算乘" << endl
		<< "3. 计算除" << endl
		<< "4. 计算余数" << endl
		<< "5. 重启" << endl
		<< "6. 退出" << endl;
	cin >> mode;
	while (mode < 0 || mode > 6){
		cout << "暂未完成！" << endl;
		cin >> mode;
		while (true){
			switch (mode){
			case 0:
				Plus();
				break;
			case 1:
				Min();
				break;
			case 2:
				Mul();
				break;
			case 3:
				Div();
				break;
			case 4:
				Mod();
				break;
			case 5:
				Reboot();
				break;
			case 6:
				Exit();
				break;
			}
		}
	}
}
void VM::Reboot(){
	cout << "重启中..." << endl;
	Execute();
}
void VM::Exit(){
	cout << "退出中..." << endl;
	exit(0);
}
void VM::Reset(){
	data.clear();
	instruct.clear();
	while (!stk.empty())
	{
		stk.pop();
	}
	data.resize(101);

	cout << endl << "虚拟机复位" << endl;
}