#include <iostream>
#include <string.h>
#include "vm.h"
using namespace std;

// ¶ÁÈ¡
void VM::Read()   {
	str[0] = new String(" ÆæÆæ¹Ö¹ÖÐéÄâ»ú ");
	str[1] = new String;
	str[2] = new String(" ");
	str[3] = new String("Right!\n");
	str[4] = new String("Wrong!\n");
}

// Ö´ÐÐ³ÌÐò
void VM::Execute()   {
	int ip;
	VM_Stack stack;
	int ipc;
	int a, b, c;

	ip = 0;
	while (ip < ninstr)   {
		ipc = 1;
		switch (instr[ip].opcode)   {
		case 1:
			break;
		case 2:
			stack.Push(NewTempCopy(instr[ip].operand));
			break;
		case 3:
			str[instr[ip].operand]->Assignment(*str[stack.GetTop()]);
			break;
		case 4:
			DelTempCopy(stack.Pop());
			break;
		case 5:
			add();
			break;
		case 6:
			i = stack.Pop();
			if (i == ST_FALSE)   ipc = instr[ip].operand;
			break;
		case 7:
			ipc = instr[ip].operand;
			break;
		case 8:
			a = stack.Pop();
			if (a == ST_FALSE)   ipc = instr[ip].operand;
			break;
		case 9:
			i = stack.Pop(); j = stack.Pop();
			if (strcmp(str[i]->Value(), str[j]->Value()) == 0)   k = ST_TRUE; else k = ST_FALSE;
			DelTempCopy(i); DelTempCopy(j);
			stack.Push(k);
			break;
		case 10:
			i = stack.Pop(); j = stack.Pop();
			if (i == j)   k = ST_TRUE; else k = ST_FALSE;
			stack.Push(k);
			break;
		case 11:
			i = stack.Pop(); j = stack.Pop();
			k = NewTempCopy(j); str[k]->Concatenate(*str[i]);
			DelTempCopy(i); DelTempCopy(j);
			stack.Push(k);
			break;
		case 12:
			i = stack.Pop();
			if (i == ST_FALSE)   i = NewTempCopy("false"); else i = NewTempCopy("true");
			stack.Push(i);
			break;
		}
		ip += ipc;
	}
}
