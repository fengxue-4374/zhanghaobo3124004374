#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

// 定义常量和类型
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define MAXSIZE 100 

typedef char ElemType;
typedef int Status;

// 栈节点结构
typedef struct StackNode {
    ElemType data;          // 数据域
    struct StackNode* next;  // 指向下一个节点的指针
    int stacksize;          // 栈可用的最大容量
} StackNode, * LinkStack;

// 全局变量声明
LinkStack OPND;  // 操作数栈
LinkStack OPTR;  // 操作符栈

// 初始化栈
Status InitStack(LinkStack& S) {
    S = NULL;
    return OK;
}


 // 入栈操作
Status Push(LinkStack& S, ElemType e) {
    StackNode* p = new StackNode;  // 创建新节点
    if (!p) return OVERFLOW;       // 内存分配失败

    p->data = e;     // 设置节点数据
    p->next = S;     // 新节点指向原栈顶
    S = p;           // 更新栈顶指针
    return OK;
}


 // 出栈操作
 
ElemType Pop(LinkStack& S) {
    if (S == NULL) return '\0';  // 栈空

    ElemType e = S->data;     // 保存栈顶数据
    StackNode* p = S;         // 临时保存栈顶节点
    S = S->next;              // 移动栈顶指针
    delete p;                 // 释放原栈顶节点
    return e;
}

 // 获取栈顶元素

ElemType GetTop(LinkStack S) {
    return (S != NULL) ? S->data : '\0';
}


// 判断字符是否为运算符
int IsOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '#');
}


 // 比较运算符优先级
 
char Precede(char t, char ch) {
    // 定义优先级表
    const char precedence[7][7] = {
        // +    -    *    /    (    )    #
        {'>', '>', '<', '<', '<', '>', '>'},  // +
        {'>', '>', '<', '<', '<', '>', '>'},  // -
        {'>', '>', '>', '>', '<', '>', '>'},  // *
        {'>', '>', '>', '>', '<', '>', '>'},  // /
        {'<', '<', '<', '<', '<', '=', ' '},   // (
        {'>', '>', '>', '>', ' ', '>', '>'},  // )
        {'<', '<', '<', '<', '<', ' ', '='}   // #
    };

    // 运算符到索引的映射
    int op1, op2;
    switch (t) {
    case '+': op1 = 0; break;
    case '-': op1 = 1; break;
    case '*': op1 = 2; break;
    case '/': op1 = 3; break;
    case '(': op1 = 4; break;
    case ')': op1 = 5; break;
    case '#': op1 = 6; break;
    default: return ' ';
    }
    switch (ch) {
    case '+': op2 = 0; break;
    case '-': op2 = 1; break;
    case '*': op2 = 2; break;
    case '/': op2 = 3; break;
    case '(': op2 = 4; break;
    case ')': op2 = 5; break;
    case '#': op2 = 6; break;
    default: return ' ';
    }

    return precedence[op1][op2];
}

// 执行运算操作

int Operate(int a, char op, int b) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
        if (b == 0) {
            printf("错误：除零错误！\n");
            exit(EXIT_FAILURE);
        }
        return a / b;
    default:
        printf("错误：未知运算符 '%c'\n", op);
        exit(EXIT_FAILURE);
    }
}


 // 算术表达式求值函数
 
int EvaluateExpression() {
    InitStack(OPND);  // 初始化操作数栈
    InitStack(OPTR);  // 初始化操作符栈
    Push(OPTR, '#');  // 压入起始符

    char ch, theta;
    int num = 0;      // 用于处理多位数
    bool readingNum = false;  // 标记是否正在读取数字

    printf("请输入表达式(以#结束): ");
    ch = getchar();
    while (ch != '#' || GetTop(OPTR) != '#') {
        if (ch == ' ') {  // 跳过空格
            ch = getchar();
            continue;
        }

        if (!IsOperator(ch)) {
            // 处理数字(包括多位数)
            if (ch >= '0' && ch <= '9') {
                num = num * 10 + (ch - '0');
                readingNum = true;
                ch = getchar();
                continue;
            }
            else {
                printf("错误：非法字符 '%c'\n", ch);
                exit(EXIT_FAILURE);
            }
        }
        else {
            // 如果之前正在读取数字，现在遇到运算符，将数字压栈
            if (readingNum) {
                Push(OPND, num + '0');  // 转换为字符存储
                num = 0;
                readingNum = false;
            }

            switch (Precede(GetTop(OPTR), ch)) {
            case '<':  // 栈顶运算符优先级低
                Push(OPTR, ch);
                ch = getchar();
                break;

            case '>': {  // 栈顶运算符优先级高，执行运算
                theta = Pop(OPTR);
                int b = Pop(OPND) - '0';
                int a = Pop(OPND) - '0';
                Push(OPND, Operate(a, theta, b) + '0');
                break;
            }

            case '=':  // 括号匹配或表达式结束
                Pop(OPTR);  // 弹出左括号或起始符
                ch = getchar();
                break;

            default:
                printf("错误：无效的运算符组合\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    // 最终结果在操作数栈顶
    return GetTop(OPND) - '0';
}

int main() {
    printf("算术表达式求值程序\n");
    printf("支持运算符: + - * / ( )\n");
    printf("示例输入: 3*(4+5)#\n\n");

    int result = EvaluateExpression();
    printf("\n计算结果为: %d\n", result); 

    return 0;
}