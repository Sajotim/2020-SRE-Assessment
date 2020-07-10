#include "VM.h"

#include <fstream>

int main(int argc, char **argv) {
	if (argc == 2) {
		fstream file(argv[1], ios::in | ios::binary);
		if (!file) {
			cout << "打开文件失败" << endl;
			return -1;
		}
		file.seekg(0, file.end);
		int size = file.tellg();
		file.seekg(0, file.beg);
		unsigned char *binary = (unsigned char*)calloc(size, 1);
		file.read((char*)binary, size);
		file.close();
		VM vm(binary, 4096);
		int returnCode = vm.start();
		cout << endl << "程序已退出，返回码：" << returnCode << endl;
		return returnCode;
	}
	else
		cout << "使用方法：VM.exe 文件名.op" << endl;
}