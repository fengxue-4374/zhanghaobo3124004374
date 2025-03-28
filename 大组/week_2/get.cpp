#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

// ���峣��������
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define MAXSIZE 100 

typedef char ElemType;
typedef int Status;

// ջ�ڵ�ṹ
typedef struct StackNode {
    ElemType data;          // ������
    struct StackNode* next;  // ָ����һ���ڵ��ָ��
    int stacksize;          // ջ���õ��������
} StackNode, * LinkStack;

// ȫ�ֱ�������
LinkStack OPND;  // ������ջ
LinkStack OPTR;  // ������ջ

// ��ʼ��ջ
Status InitStack(LinkStack& S) {
    S = NULL;
    return OK;
}


 // ��ջ����
Status Push(LinkStack& S, ElemType e) {
    StackNode* p = new StackNode;  // �����½ڵ�
    if (!p) return OVERFLOW;       // �ڴ����ʧ��

    p->data = e;     // ���ýڵ�����
    p->next = S;     // �½ڵ�ָ��ԭջ��
    S = p;           // ����ջ��ָ��
    return OK;
}


 // ��ջ����
 
ElemType Pop(LinkStack& S) {
    if (S == NULL) return '\0';  // ջ��

    ElemType e = S->data;     // ����ջ������
    StackNode* p = S;         // ��ʱ����ջ���ڵ�
    S = S->next;              // �ƶ�ջ��ָ��
    delete p;                 // �ͷ�ԭջ���ڵ�
    return e;
}

 // ��ȡջ��Ԫ��

ElemType GetTop(LinkStack S) {
    return (S != NULL) ? S->data : '\0';
}


// �ж��ַ��Ƿ�Ϊ�����
int IsOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '#');
}


 // �Ƚ���������ȼ�
 
char Precede(char t, char ch) {
    // �������ȼ���
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

    // �������������ӳ��
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

// ִ���������

int Operate(int a, char op, int b) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
        if (b == 0) {
            printf("���󣺳������\n");
            exit(EXIT_FAILURE);
        }
        return a / b;
    default:
        printf("����δ֪����� '%c'\n", op);
        exit(EXIT_FAILURE);
    }
}


 // �������ʽ��ֵ����
 
int EvaluateExpression() {
    InitStack(OPND);  // ��ʼ��������ջ
    InitStack(OPTR);  // ��ʼ��������ջ
    Push(OPTR, '#');  // ѹ����ʼ��

    char ch, theta;
    int num = 0;      // ���ڴ����λ��
    bool readingNum = false;  // ����Ƿ����ڶ�ȡ����

    printf("��������ʽ(��#����): ");
    ch = getchar();
    while (ch != '#' || GetTop(OPTR) != '#') {
        if (ch == ' ') {  // �����ո�
            ch = getchar();
            continue;
        }

        if (!IsOperator(ch)) {
            // ��������(������λ��)
            if (ch >= '0' && ch <= '9') {
                num = num * 10 + (ch - '0');
                readingNum = true;
                ch = getchar();
                continue;
            }
            else {
                printf("���󣺷Ƿ��ַ� '%c'\n", ch);
                exit(EXIT_FAILURE);
            }
        }
        else {
            // ���֮ǰ���ڶ�ȡ���֣����������������������ѹջ
            if (readingNum) {
                Push(OPND, num + '0');  // ת��Ϊ�ַ��洢
                num = 0;
                readingNum = false;
            }

            switch (Precede(GetTop(OPTR), ch)) {
            case '<':  // ջ����������ȼ���
                Push(OPTR, ch);
                ch = getchar();
                break;

            case '>': {  // ջ����������ȼ��ߣ�ִ������
                theta = Pop(OPTR);
                int b = Pop(OPND) - '0';
                int a = Pop(OPND) - '0';
                Push(OPND, Operate(a, theta, b) + '0');
                break;
            }

            case '=':  // ����ƥ�����ʽ����
                Pop(OPTR);  // ���������Ż���ʼ��
                ch = getchar();
                break;

            default:
                printf("������Ч����������\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    // ���ս���ڲ�����ջ��
    return GetTop(OPND) - '0';
}

int main() {
    printf("�������ʽ��ֵ����\n");
    printf("֧�������: + - * / ( )\n");
    printf("ʾ������: 3*(4+5)#\n\n");

    int result = EvaluateExpression();
    printf("\n������Ϊ: %d\n", result); 

    return 0;
}