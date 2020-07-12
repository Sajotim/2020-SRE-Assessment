#pragma once

#include <iostream>

using namespace std;

class VM {
public:
	VM(unsigned char*, int);
	~VM();
	int start();
private:
	int base;
	unsigned char *ip;
	int *sp;
	int ax;
	int bx;
	int cx;
	int dx;
	void opPush(unsigned char*&);
	void opPop(unsigned char*&);
	void opJmp();
	void opJe();
	void opJne();
	void opJg();
	void opJge();
	void opJl();
	void opJle();
	void opMov(unsigned char*&);
	void opIn(unsigned char*&);
	void opOut(unsigned char*&);
	void opMem();
	void opNop();
	void tpOperate(unsigned char, int(int, int));
	static int tpCmp(int, int);
	static int tpAdd(int, int);
	static int tpMul(int, int);
	static int tpDiv(int, int);
	static int tpMod(int, int);
	static int tpAnd(int, int);
	static int tpOr(int, int);
	static int tpXor(int, int);
	void opCmp(unsigned char*&);
	void opAdd(unsigned char*&);
	void opMul(unsigned char*&);
	void opDiv(unsigned char*&);
	void opMod(unsigned char*&);
	void opAnd(unsigned char*&);
	void opOr(unsigned char*&);
	void opXor(unsigned char*&);
	void opNeg(unsigned char*&);
};