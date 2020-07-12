#include <climits>
#include <stack>
#include "DataProcess.h"

// 栈实现四则运算 https://www.cnblogs.com/lcplcpjava/p/6576935.html

int DataProcess::op_level(char x){
    if(x == '*' || x == '/' || x == '%')  return 2;
    if(x == '+' || x == '-')  return 1;
    if(x == '(')  return 0;
    else return -1;
}

std::string DataProcess::inf_to_pre(std::string old_expression){
    // 每个数字，字符之间都用' '隔开
    std::stack <char> S1, S2;		//运算符栈和答案栈
    std::string ret;
    for (int i = (int)old_expression.size()-1 ; i >= 0; i--){
        if (old_expression.at(i) == ' ' || old_expression.at(i) == '\t')
            continue;
        // 运算式开头的负数处理
        if (i == 0 && old_expression.at(i) == '-'){
            S2.pop();
            S2.push('-');    S2.push(' ');
            continue;
        }
        // 是数字，直接入栈
        if(isdigit(old_expression.at(i))){
            S2.push(old_expression.at(i));
            if (i == 0 || (i > 0 && !isdigit(old_expression.at(i-1)))){
                // 到了数字的开头
                S2.push(' ');
            }
        }
        else if ((old_expression.at(i)) == ')')
            S1.push(')');
            // 运算式中间的负数处理 负号前必有'('
        else if (i > 0 && old_expression.at(i-1) == '(' && old_expression.at(i) == '-'){
            S2.pop();
            S2.push('-'); S2.push(' ');
        }
            // 是')', 弹出S1直到遇到'('
        else if ((old_expression.at(i)) == '('){
            while(S1.top() != ')'){
                S2.push(S1.top());  S2.push(' ');
                S1.pop();
            }
            S1.pop();
        }
        else {
            // 若当前比S1栈顶运算符'优先级'低，则将S1栈顶的运算符弹出并压入到S2中
            while (!S1.empty() && op_level(old_expression.at(i)) < op_level(S1.top())){
                S2.push(S1.top()); S2.push(' ');
                S1.pop();
            }
            S1.push(old_expression.at(i));
        }
    }
    // 将S1的运算符依次弹出压入S2
    while (!S1.empty()){
        S2.push(S1.top()); S2.push(' ');
        S1.pop();
    }
    // 将S2的数据弹出赋值给ret变量
    while(!S2.empty()){
        ret += S2.top();
        S2.pop();
    }
    return ret;
}

int DataProcess::str_to_int(const std::string& str){
    int num = 0, flag = 1;
    if (str.at(0) == '-')   flag = -1;
    for(char i : str){
        if(i == ' ' || i == '-') continue;
        num = num*10+i-'0';
    }
    return num*flag;
}
