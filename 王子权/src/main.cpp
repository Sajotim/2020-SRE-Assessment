#include <iostream>
#include <fstream>
#include "VM.hpp"

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout << "[Usage]: main.exe [filename.vm]" << endl;
        return 0;
    }
    FILE *fp = fopen(argv[1], "rb");
    if (!fp)
    {
        cout << "Please check your file!" << endl;
        return -1;
    }
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    VM vm;
    int *program = (int *)malloc(size);
    fread(program, 1, size, fp);
    fclose(fp);
    vm.initVM();
    int ret = vm.loadProgram(program);
    cout << "[Load status]: " << ret << endl;
    ret = vm.run();
    cout << "[Run status]: " << ret << endl;
    return 0;
}