#pragma once

#include <iostream>

using namespace std;

class VM {
public:
	VM(unsigned char*, int);
	~VM();
	int start();
private:
	bool error;
	int base;
	unsigned char *ip;
	int *ss;
	int *se;
	int *sp;
	int ax;
	int bx;
	int cx;
	int dx;
	void opPushAx();
	void opPushBx();
	void opPushCx();
	void opPushDx();
	void opPushSp();
	void opPushImm();
	void opPopAx();
	void opPopBx();
	void opPopCx();
	void opPopDx();
	void opPopSp();
	void opJmp();
	void opJe();
	void opJne();
	void opJg();
	void opJge();
	void opJl();
	void opJle();
	void opMovBx2Ax();
	void opMovCx2Ax();
	void opMovDx2Ax();
	void opMovMem2Ax();
	void opMovImm2Ax();
	void opMovAx2Bx();
	void opMovCx2Bx();
	void opMovDx2Bx();
	void opMovMem2Bx();
	void opMovImm2Bx();
	void opMovAx2Cx();
	void opMovBx2Cx();
	void opMovDx2Cx();
	void opMovMem2Cx();
	void opMovImm2Cx();
	void opMovAx2Dx();
	void opMovBx2Dx();
	void opMovCx2Dx();
	void opMovMem2Dx();
	void opMovImm2Dx();
	void opMovAx2Mem();
	void opMovBx2Mem();
	void opMovCx2Mem();
	void opMovDx2Mem();
	void opMovImm2Mem();
	void opInInt();
	void opInString();
	void opOutChar();
	void opOutInt();
	void opOutString();
	void opAlloc();
	void opNop();
	void opAdd();
	void opMul();
	void opDiv();
	void opAnd();
	void opOr();
	void opXor();
	void opNeg();
	void opCmp();
};