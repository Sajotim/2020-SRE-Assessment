#include "VM.h"

VM::VM(unsigned char *eop, int stackSize) {
	base = (int)eop;
	ip = eop;
	sp = (int*)calloc(stackSize, 1) + stackSize / 4 - 1;
	ax = 0;
	bx = 0;
	cx = 0;
	dx = 0;
}

VM::~VM() {

}

int VM::start() {
	while (true) {
		switch (*ip++) {
		case 0:
			return ax;
		case 1:
			opPush(ip);
			break;
		case 2:
			opPop(ip);
			break;
		case 3:
			opJmp();
			break;
		case 4:
			opJe();
			break;
		case 5:
			opJne();
			break;
		case 6:
			opJg();
			break;
		case 7:
			opJge();
			break;
		case 8:
			opJl();
			break;
		case 9:
			opJle();
			break;
		case 10:
			opMov(ip);
			break;
		case 11:
			opIn(ip);
			break;
		case 12:
			opOut(ip);
			break;
		case 13:
			opMem();
			break;
		case 14:
			opNop();
			break;
		case 15:
			opCmp(ip);
			break;
		case 16:
			opAdd(ip);
			break;
		case 17:
			opMul(ip);
			break;
		case 18:
			opDiv(ip);
			break;
		case 19:
			opMod(ip);
			break;
		case 20:
			opAnd(ip);
			break;
		case 21:
			opOr(ip);
			break;
		case 22:
			opXor(ip);
			break;
		case 23:
			opNeg(ip);
			break;
		default:
			return -1;
		}
	}
}

void VM::opPush(unsigned char* &ip) {
	switch (*ip++) {
	case 0: // push ax
		*sp-- = ax;
		break;
	case 1: // push bx
		*sp-- = bx;
		break;
	case 2: // push cx
		*sp-- = cx;
		break;
	case 3: // push dx
		*sp-- = dx;
		break;
	case 4: // push sp
		*sp-- = (int)sp;
		break;
	case 5: // push imm
		*sp-- = *(int*)ip;
		ip += 4;
	}
}

void VM::opPop(unsigned char* &ip) {
	switch (*ip++) {
	case 0: // pop ax
		ax = *++sp;
		break;
	case 1: // pop bx
		bx = *++sp;
		break;
	case 2: // pop cx
		cx = *++sp;
		break;
	case 3: // pop dx
		dx = *++sp;
		break;
	case 4: // pop sp
		sp = (int*)*++sp;
	}
}

void VM::opJmp() {
	ip = (unsigned char*)*(int*)ip + base;
}

void VM::opJe() {
	if (!ax)
		opJmp();
	else
		ip += 4;
}

void VM::opJne() {
	if (ax)
		opJmp();
	else
		ip += 4;
}

void VM::opJg() {
	if (ax > 0)
		opJmp();
	else
		ip += 4;
}

void VM::opJge() {
	if (ax >= 0)
		opJmp();
	else
		ip += 4;
}

void VM::opJl() {
	if (ax < 0)
		opJmp();
	else
		ip += 4;
}

void VM::opJle() {
	if (ax <= 0)
		opJmp();
	else
		ip += 4;
}

void VM::opMov(unsigned char* &ip) {
	switch (*ip++) {
	case 0: // mov ax bx
		ax = bx;
		break;
	case 1: // mov ax cx
		ax = cx;
		break;
	case 2: // mov ax dx
		ax = dx;
		break;
	case 3: // mov ax [ax]
		ax = *(int*)(ax + base);
		break;
	case 4: // mov ax [bx]
		ax = *(int*)(bx + base);
		break;
	case 5: // mov ax [cx]
		ax = *(int*)(cx + base);
		break;
	case 6: // mov ax [dx]
		ax = *(int*)(dx + base);
		break;
	case 7: // mov ax imm
		ax = *(int*)ip;
		ip += 4;
		break;
	case 8: // mov bx ax
		bx = ax;
		break;
	case 9: // mov bx cx
		bx = cx;
		break;
	case 10: // mov bx dx
		bx = dx;
		break;
	case 11: // mov bx [ax]
		bx = *(int*)(ax + base);
		break;
	case 12: // mov bx [bx]
		bx = *(int*)(bx + base);
		break;
	case 13: // mov bx [cx]
		bx = *(int*)(cx + base);
		break;
	case 14: // mov bx [dx]
		bx = *(int*)(dx + base);
		break;
	case 15: // mov bx imm
		bx = *(int*)ip;
		ip += 4;
		break;
	case 16: // mov cx ax
		cx = ax;
		break;
	case 17: // mov cx bx
		cx = bx;
		break;
	case 18: // mov cx dx
		cx = dx;
		break;
	case 19: // mov cx [ax]
		cx = *(int*)(ax + base);
		break;
	case 20: // mov cx [bx]
		cx = *(int*)(bx + base);
		break;
	case 21: // mov cx [cx]
		cx = *(int*)(cx + base);
		break;
	case 22: // mov cx [dx]
		cx = *(int*)(dx + base);
		break;
	case 23: // mov cx imm
		cx = *(int*)ip;
		ip += 4;
		break;
	case 24: // mov dx ax
		dx = ax;
		break;
	case 25: // mov dx bx
		dx = bx;
		break;
	case 26: // mov dx cx
		dx = cx;
		break;
	case 27: // mov dx [ax]
		dx = *(int*)(ax + base);
		break;
	case 28: // mov dx [bx]
		dx = *(int*)(bx + base);
		break;
	case 29: // mov dx [cx]
		dx = *(int*)(cx + base);
		break;
	case 30: // mov dx [dx]
		dx = *(int*)(dx + base);
		break;
	case 31: // mov dx imm
		dx = *(int*)ip;
		ip += 4;
		break;
	case 32: // mov [ax] ax
		*(int*)(ax + base) = ax;
		break;
	case 33: // mov [ax] bx
		*(int*)(ax + base) = bx;
		break;
	case 34: // mov [ax] cx
		*(int*)(ax + base) = cx;
		break;
	case 35: // mov [ax] dx
		*(int*)(ax + base) = dx;
		break;
	case 36: // mov [bx] ax
		*(int*)(bx + base) = ax;
		break;
	case 37: // mov [bx] bx
		*(int*)(bx + base) = bx;
		break;
	case 38: // mov [bx] cx
		*(int*)(bx + base) = cx;
		break;
	case 39: // mov [bx] dx
		*(int*)(bx + base) = dx;
		break;
	case 40: // mov [cx] ax
		*(int*)(cx + base) = ax;
		break;
	case 41: // mov [cx] bx
		*(int*)(cx + base) = bx;
		break;
	case 42: // mov [cx] cx
		*(int*)(cx + base) = cx;
		break;
	case 43: // mov [cx] dx
		*(int*)(cx + base) = dx;
		break;
	case 44: // mov [dx] ax
		*(int*)(dx + base) = ax;
		break;
	case 45: // mov [dx] bx
		*(int*)(dx + base) = bx;
		break;
	case 46: // mov [dx] cx
		*(int*)(dx + base) = cx;
		break;
	case 47: // mov [dx] dx
		*(int*)(dx + base) = dx;
	}
}

void VM::opIn(unsigned char* &ip) {
	switch (*ip++) {
	case 0: // in char
		char tmp;
		cin >> tmp;
		ax = tmp;
		break;
	case 1: // in int
		cin >> ax;
		break;
	case 2: // in string
		cin >> (char*)(ax + base);
	}
}

void VM::opOut(unsigned char* &ip) {
	switch (*ip++) {
	case 0: // out char
		cout << (char)ax;
		break;
	case 1: // out int
		cout << ax;
		break;
	case 2: // out string
		cout << (char*)(ax + base);
	}
}

void VM::opMem() {
	ax = (int)calloc(ax, 1) - base;
}

void VM::opNop() {

}

void VM::tpOperate(unsigned char op, int tp(int, int)) {
	switch (op) {
	case 0: // op ax ax
		ax = tp(ax, ax);
		break;
	case 1: // op ax bx
		ax = tp(ax, bx);
		break;
	case 2: // op ax cx
		ax = tp(ax, cx);
		break;
	case 3: // op ax dx
		ax = tp(ax, dx);
		break;
	case 4: // op bx ax
		ax = tp(bx, ax);
		break;
	case 5: // op bx bx
		ax = tp(bx, bx);
		break;
	case 6: // op bx cx
		ax = tp(bx, cx);
		break;
	case 7: // op bx dx
		ax = tp(bx, dx);
		break;
	case 8: // op cx ax
		ax = tp(cx, ax);
		break;
	case 9: // op cx bx
		ax = tp(cx, bx);
		break;
	case 10: // op cx cx
		ax = tp(cx, cx);
		break;
	case 11: // op cx dx
		ax = tp(cx, dx);
		break;
	case 12: // op dx ax
		ax = tp(dx, ax);
		break;
	case 13: // op dx bx
		ax = tp(dx, bx);
		break;
	case 14: // op dx cx
		ax = tp(dx, cx);
		break;
	case 15: // op dx dx
		ax = tp(dx, dx);
	}
}

int VM::tpCmp(int reg1, int reg2) {
	return reg1 - reg2;
}

int VM::tpAdd(int reg1, int reg2) {
	return reg1 + reg2;
}

int VM::tpMul(int reg1, int reg2) {
	return reg1 * reg2;
}

int VM::tpDiv(int reg1, int reg2) {
	return reg1 / reg2;
}

int VM::tpMod(int reg1, int reg2) {
	return reg1 % reg2;
}

int VM::tpAnd(int reg1, int reg2) {
	return reg1 & reg2;
}

int VM::tpOr(int reg1, int reg2) {
	return reg1 | reg2;
}

int VM::tpXor(int reg1, int reg2) {
	return reg1 ^ reg2;
}

void VM::opCmp(unsigned char* &ip) {
	tpOperate(*ip++, tpCmp);
}

void VM::opAdd(unsigned char* &ip) {
	tpOperate(*ip++, tpAdd);
}

void VM::opMul(unsigned char* &ip) {
	tpOperate(*ip++, tpMul);
}

void VM::opDiv(unsigned char* &ip) {
	tpOperate(*ip++, tpDiv);
}

void VM::opMod(unsigned char* &ip) {
	tpOperate(*ip++, tpMod);
}

void VM::opAnd(unsigned char* &ip) {
	tpOperate(*ip++, tpAnd);
}

void VM::opOr(unsigned char* &ip) {
	tpOperate(*ip++, tpOr);
}

void VM::opXor(unsigned char* &ip) {
	tpOperate(*ip++, tpXor);
}

void VM::opNeg(unsigned char* &ip) {
	switch (*ip++) {
	case 0: // neg ax
		ax = ~ax;
		break;
	case 1: // neg bx
		ax = ~bx;
		break;
	case 2: // neg cx
		ax = ~cx;
		break;
	case 3: // neg dx
		ax = ~dx;
	}
}