#include "VM.h"

VM::VM(unsigned char *eop, int stackSize) {
	if (stackSize <= 0 || stackSize % 4) {
		error = true;
		return;
	}
	error = false;
	base = (int)eop;
	ip = eop;
	ss = (int*)calloc(stackSize, 1);
	se = ss + stackSize / 4;
	sp = se - 1;
	ax = 0;
	bx = 0;
	cx = 0;
	dx = 0;
}

VM::~VM() {

}

int VM::start() {
	while (!error) {
		switch (*ip++) {
		case 0:
			return ax;
		case 1:
			opPushAx();
			break;
		case 2:
			opPushBx();
			break;
		case 3:
			opPushCx();
			break;
		case 4:
			opPushDx();
			break;
		case 5:
			opPushSp();
			break;
		case 6:
			opPushImm();
			break;
		case 7:
			opPopAx();
			break;
		case 8:
			opPopBx();
			break;
		case 9:
			opPopCx();
			break;
		case 10:
			opPopDx();
			break;
		case 11:
			opPopSp();
			break;
		case 12:
			opJmp();
			break;
		case 13:
			opJe();
			break;
		case 14:
			opJne();
			break;
		case 15:
			opJg();
			break;
		case 16:
			opJge();
			break;
		case 17:
			opJl();
			break;
		case 18:
			opJle();
			break;
		case 19:
			opMovBx2Ax();
			break;
		case 20:
			opMovCx2Ax();
			break;
		case 21:
			opMovDx2Ax();
			break;
		case 22:
			opMovMem2Ax();
			break;
		case 23:
			opMovImm2Ax();
			break;
		case 24:
			opMovAx2Bx();
			break;
		case 25:
			opMovCx2Bx();
			break;
		case 26:
			opMovDx2Bx();
			break;
		case 27:
			opMovMem2Bx();
			break;
		case 28:
			opMovImm2Bx();
			break;
		case 29:
			opMovAx2Cx();
			break;
		case 30:
			opMovBx2Cx();
			break;
		case 31:
			opMovDx2Cx();
			break;
		case 32:
			opMovMem2Cx();
			break;
		case 33:
			opMovImm2Cx();
			break;
		case 34:
			opMovAx2Dx();
			break;
		case 35:
			opMovBx2Dx();
			break;
		case 36:
			opMovCx2Dx();
			break;
		case 37:
			opMovMem2Dx();
			break;
		case 38:
			opMovImm2Dx();
			break;
		case 39:
			opMovAx2Mem();
			break;
		case 40:
			opMovBx2Mem();
			break;
		case 41:
			opMovCx2Mem();
			break;
		case 42:
			opMovDx2Mem();
			break;
		case 43:
			opMovImm2Mem();
			break;
		case 44:
			opInInt();
			break;
		case 45:
			opInString();
			break;
		case 46:
			opOutChar();
			break;
		case 47:
			opOutInt();
			break;
		case 48:
			opOutString();
			break;
		case 49:
			opAlloc();
			break;
		case 50:
			opNop();
			break;
		case 51:
			opAdd();
			break;
		case 52:
			opMul();
			break;
		case 53:
			opDiv();
			break;
		case 54:
			opAnd();
			break;
		case 55:
			opOr();
			break;
		case 56:
			opXor();
			break;
		case 57:
			opNeg();
			break;
		case 58:
			opCmp();
			break;
		default:
			error = true;
		}
	}
	return -1;
}

void VM::opPushAx() {
	if (sp <= ss || sp >= se) {
		error = true;
		return;
	}
	*sp-- = ax;
}

void VM::opPushBx() {
	if (sp <= ss || sp >= se) {
		error = true;
		return;
	}
	*sp-- = bx;
}

void VM::opPushCx() {
	if (sp <= ss || sp >= se) {
		error = true;
		return;
	}
	*sp-- = cx;
}

void VM::opPushDx() {
	if (sp <= ss || sp >= se) {
		error = true;
		return;
	}
	*sp-- = dx;
}

void VM::opPushSp() {
	if (sp <= ss || sp >= se) {
		error = true;
		return;
	}
	int tmp = (int)sp;
	*sp-- = tmp;
}

void VM::opPushImm() {
	if (sp <= ss || sp >= se) {
		error = true;
		return;
	}
	*sp-- = *(int*)ip;
	ip += 4;
}

void VM::opPopAx() {
	if (sp <= ss || sp >= se) {
		error = true;
		return;
	}
	ax = *++sp;
}

void VM::opPopBx() {
	if (sp <= ss || sp >= se) {
		error = true;
		return;
	}
	bx = *++sp;
}

void VM::opPopCx() {
	if (sp <= ss || sp >= se) {
		error = true;
		return;
	}
	cx = *++sp;
}

void VM::opPopDx() {
	if (sp <= ss || sp >= se) {
		error = true;
		return;
	}
	dx = *++sp;
}

void VM::opPopSp() {
	if (sp <= ss || sp >= se) {
		error = true;
		return;
	}
	sp = (int*)*++sp;
}

void VM::opJmp() {
	ip = base + (unsigned char*)*(int*)ip;
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

void VM::opMovBx2Ax() {
	ax = bx;
}

void VM::opMovCx2Ax() {
	ax = cx;
}

void VM::opMovDx2Ax() {
	ax = dx;
}

void VM::opMovMem2Ax() {
	ax = *(int*)(base + ax);
}

void VM::opMovImm2Ax() {
	ax = *(int*)ip;
	ip += 4;
}

void VM::opMovAx2Bx() {
	bx = ax;
}

void VM::opMovCx2Bx() {
	bx = cx;
}

void VM::opMovDx2Bx() {
	bx = dx;
}

void VM::opMovMem2Bx() {
	bx = *(int*)(base + ax);
}

void VM::opMovImm2Bx() {
	bx = *(int*)ip;
	ip += 4;
}

void VM::opMovAx2Cx() {
	cx = ax;
}

void VM::opMovBx2Cx() {
	cx = bx;
}

void VM::opMovDx2Cx() {
	cx = dx;
}

void VM::opMovMem2Cx() {
	cx = *(int*)(base + ax);
}

void VM::opMovImm2Cx() {
	cx = *(int*)ip;
	ip += 4;
}

void VM::opMovAx2Dx() {
	dx = ax;
}

void VM::opMovBx2Dx() {
	dx = bx;
}

void VM::opMovCx2Dx() {
	dx = cx;
}

void VM::opMovMem2Dx() {
	dx = *(int*)(base + ax);
}

void VM::opMovImm2Dx() {
	dx = *(int*)ip;
	ip += 4;
}

void VM::opMovAx2Mem() {
	*(int*)(base + ax) = ax;
}

void VM::opMovBx2Mem() {
	*(int*)(base + ax) = bx;
}

void VM::opMovCx2Mem() {
	*(int*)(base + ax) = cx;
}

void VM::opMovDx2Mem() {
	*(int*)(base + ax) = dx;
}

void VM::opMovImm2Mem() {
	*(int*)(base + ax) = *(int*)ip;
	ip += 4;
}

void VM::opInInt() {
	cin >> ax;
}

void VM::opInString() {
	cin >> (char*)(ax + base);
}

void VM::opOutChar() {
	cout << (char)ax;
}

void VM::opOutInt() {
	cout << ax;
}

void VM::opOutString() {
	cout << (char*)(ax + base);
}

void VM::opAlloc() {
	ax = (int)calloc(ax, 1) - base;
}

void VM::opNop() {

}

void VM::opAdd() {
	ax += bx;
}

void VM::opMul() {
	ax *= bx;
}

void VM::opDiv() {
	cx = ax % bx;
	ax /= bx;
}

void VM::opAnd() {
	ax &= bx;
}

void VM::opOr() {
	ax |= bx;
}

void VM::opXor() {
	ax ^= bx;
}

void VM::opNeg() {
	ax = ~ax;
}

void VM::opCmp() {
	ax -= bx;
}