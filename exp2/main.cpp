#include <iostream>
#include <cctype> // for isdigit
#include "C:\Users\81202\Desktop\DS2024-main\exp2\Stack.h" // 请根据实际路径调整
#define N_OPTR 9

typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator;

const char pri[N_OPTR][N_OPTR] = {
    '>', '>', '<', '<', '<', '<', '<', '>', '>',
    '>', '>', '<', '<', '<', '<', '<', '>', '>',
    '>', '>', '>', '>', '<', '<', '<', '>', '>',
    '>', '>', '>', '>', '<', '<', '<', '>', '>',
    '>', '>', '>', '>', '>', '<', '<', '>', '>',
    '>', '>', '>', '>', '>', '>', ' ', '>', '>',
    '<', '<', '<', '<', '<', '<', '<', '=', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    '<', '<', '<', '<', '<', '<', '<', ' ', '=',
};




Operator charToOperator(char op) {
    switch (op) {
        case '+': return ADD;
        case '-': return SUB;
        case '*': return MUL;
        case '/': return DIV;
        case '^':return POW;
        case '!':return FAC;
        case '(':return L_P;
        case ')':return R_P;
        case '\0':return EOE;
        default: throw std::invalid_argument("未知操作符");
    }
}

// 读取数字并压入操作数栈
void readNumber(char*& S, Stack<float>& opnd) {
    float number = 0.0;
    float decimalFactor = 1.0; // 用于处理小数部分
    bool isDecimal = false; // 标记是否为小数

    while (isdigit(*S) || (*S == '.' && !isDecimal)) {
        if (*S == '.') {
            isDecimal = true; // 遇到小数点，标记为小数
        } else {
            if (isDecimal) {
                // 处理小数部分
                number = number * 10 + (*S - '0');
                decimalFactor *= 10; // 增加小数位数
            } else {
                // 处理整数部分
                number = number * 10 + (*S - '0');
            }
        }
        S++;
    }

    if (isDecimal) {
        number /= decimalFactor; // 调整为小数值
    }
    
    opnd.push(number); // 压入操作数栈
}

// 计算函数
float calcu(float opnd1, char op, float opnd2) {
    switch (op) {
        case '+': return opnd1 + opnd2;
        case '-': return opnd1 - opnd2;
        case '*': return opnd1 * opnd2;
        case '/': return opnd1 / opnd2;
        // Add cases for POW, FAC, etc.
        default: return 0; // Error
    }
}

// 判断操作符的优先级
char orderBetween(char top, char current) {
    if (top == '\0') {
        return '<'; // 如果栈为空，任何操作符都应推入栈中
    }
    return pri[top][current];
}

float evaluate(char* S) {
    Stack<float> opnd;
    Stack<char> optr;
    optr.push('\0');
    cout<<optr.empty();
    while (!optr.empty()) { // 处理输入字符串和栈中的操作符
        if (isdigit(*S) ) {
            readNumber(S, opnd);
        } else  // 跳过空格
            switch (orderBetween(charToOperator(optr.top()),charToOperator( *S))) {
                case '<':
                    optr.push(*S);
                    S++;
                    break;
                case '=':
                    optr.pop();
                    S++;
                    break;
                case '>': {
                    char op = optr.pop();
                    if (op == '!') {
                        float pOpnd = opnd.pop();
                        opnd.push(calcu(pOpnd, op, 0));
                    } else {
                        float pOpnd2 = opnd.pop(), pOpnd1 = opnd.pop();
                        opnd.push(calcu(pOpnd1, op, pOpnd2));
                    }
                    break;
                }
                default:
                    std::cout << "式子错误" << std::endl;
                    exit(-1);
            // 移动到下一个字符
        }
    }
    return opnd.pop(); // 返回最终结果
};
int largestRectangleArea(Vector<int>& heights) {
    Stack<int> A; // 记录柱子的下标
    int MaxArea = 0;
    int n = heights.size(); // 获取数组长度

    for (int i = 0; i <= n; i++) {
        // 如果当前柱子比栈顶柱子矮，或者已经处理到最后一个柱子
        while (!A.empty() && (i == n || heights[i] < heights[A.top()])) {
            // 弹出栈顶柱子，计算以该柱子为高的矩形面积
            int height = heights[A.top()];
            A.pop();

            // 计算宽度：如果栈为空，说明这个柱子是最左侧柱子，否则是栈顶柱子右边的柱子
            int width = A.empty() ? i : i - A.top() - 1;

            // 更新最大面积
            MaxArea = max(MaxArea, height * width);
        }
        // 将当前柱子的下标压入栈
        A.push(i);
    }

    return MaxArea;
}
using namespace std;

int main() {
    char s[111] = "3.14*3-1/2"; // 输入表达式
    char* m=s;
    cout << "输入表达式: " << s << endl;
    float result = evaluate(m);
    cout << "计算结果: " << result << endl; // 输出计算结果
    

    
    Vector<int> heights ;
    heights.insert(2);
    heights.insert(4);
    heights.insert(6);
    heights.insert(4);
    heights.insert(3);
    heights.insert(1);
    cout<<largestRectangleArea(heights)<<endl;

    for(int i = 0  ; i < 10 ; i++){
        int l = rand()%106;
        Vector<int> h;
        for(int j = 0 ; j<l;j++){
            h.insert(rand()%106);
        }
        cout<<largestRectangleArea(h)<<endl;
    }

}
