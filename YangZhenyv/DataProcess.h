#ifndef YANGZHENYV_DATAPROCESS_H
#define YANGZHENYV_DATAPROCESS_H


#include <string>

/*该类用于存放一些数据处理的函数，包含将表达式从中缀转换为前缀，将数字从str转换成int*/

class DataProcess {
protected:
    // 获取运算符优先级函数
    static int op_level(char x);

public:
    // 中缀式表达转换为前缀式表达函数
    static std::string inf_to_pre(std::string old_expression);
    // 数字从str转换为int函数
    static int str_to_int(const std::string& str);
};




#endif //YANGZHENYV_DATAPROCESS_H
