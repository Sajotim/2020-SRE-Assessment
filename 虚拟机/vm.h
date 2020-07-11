#include "myrstring.h"
using namespace std;
enum {
	HEL = 0,
	PUT,
	MOV,
	JUM,
	PLU,
	MIN,
	MUL,
	DIV,
	XOR,
	OR,
	AND,
	OUT,
	inst_c
};

enum {
	_char,
	_digit
};

enum {
	RUN = 1,
	DEBUG,
	_reg,
	_inst,
	_out,
};
// 寄存器
class Instruction {
public:
	static const int const_hel = 1;  // 结束
	static const int const_put = 2;  // 数据存储
	static const int const_mov = 3;  // 数据交换
	static const int const_jum = 4;  // 跳转
	static const int const_plu = 5;  // 加
	static const int const_min = 6;  // 减
	static const int const_mul = 7;  // 乘
	static const int const_div = 8;  // 除
	static const int const_xor = 9;  // 按位异或
	static const int const_or = 10; // 按位或
	static const int const_and = 11; // 按位与
	static const int const_out = 12; // 输出
private:
	int m_address;
	int r_address;
	int debug;
	string inst_order, reg_order;
};

class VM  {
public:
	VM();
	~VM();
	void Read();
	void Execute();
	void Reset();
private:
	int NewTempCopy();
	int NewTempCopy(int j);
	int NewTempCopy(char *s);
	void DelTempCopy(int i);
};