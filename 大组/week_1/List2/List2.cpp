#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#define upkey 72   //定义各个变量的值
#define downkey 80
#define leftkey 75
#define rightkey 77

//定义双向链表结构体
typedef int ElemType;
typedef struct _DoubleListNode
{
	ElemType data;
	struct _DoubleListNode* prior;	// 前驱指针
	struct _DoubleListNode* next;	// 后驱指针
}DoubleListNode;
typedef DoubleListNode* DoubleLinkList;

//双向链表初始化
DoubleLinkList ListInit()
{
	DoubleLinkList list = (DoubleLinkList)malloc(sizeof(DoubleListNode));
	list->prior = NULL;
	list->next = NULL;
	list->data = -1;
	return list;
}
// 双向链表插入数据的函数
void ListInsert(DoubleLinkList list) {
    if (list == NULL) {
        puts("链表为空。");
        return;
    }

    int position;
    ElemType data;

    // 输入插入位置
    puts("请输入要插入的位置:");
    while (scanf("%d", &position) != 1 || position < 1) {
        puts("输入无效，请输入一个大于0的整数:");
        while (getchar() != '\n'); // 清除输入缓冲区
    }

    // 输入插入数据
    puts("请输入要插入的数据:");
    while (scanf("%d", &data) != 1) {
        puts("输入无效，请输入一个整数:");
        while (getchar() != '\n'); // 清除输入缓冲区
    }

    DoubleListNode* p = list;
    int j = 0;

    // 找到插入位置的前一个节点
    while (p && j < position - 1) {
        p = p->next;
        j++;
    }

    if (p == NULL) {
        puts("插入位置超出链表范围。");
        return;
    }

    // 创建新节点
    DoubleListNode* newNode = (DoubleListNode*)malloc(sizeof(DoubleListNode));
    if (newNode == NULL) {
        puts("内存分配失败。");
        return;
    }
    newNode->data = data;

    // 插入新节点
    newNode->next = p->next;
    if (p->next != NULL) {
        p->next->prior = newNode;
    }
    p->next = newNode;
    newNode->prior = p;

    puts("插入成功。");
}
//双向链表删除
void ListDelete(DoubleLinkList list) {
    if (list == NULL) {
        puts("链表为空。");
        return;
    }

    int position;

    // 输入删除位置
    puts("请输入要删除的位置:");
    while (scanf("%d", &position) != 1 || position < 1) {
        puts("输入无效，请输入一个大于0的整数:");
        while (getchar() != '\n'); // 清除输入缓冲区
    }

    DoubleListNode* p = list->next;
    int j = 1;

    // 找到要删除的节点
    while (p && j < position) {
        p = p->next;
        j++;
    }

    if (p == NULL) {
        puts("删除位置超出链表范围。");
        return;
    }

    // 删除节点
    if (p->prior != NULL) {
        p->prior->next = p->next;
    }
    if (p->next != NULL) {
        p->next->prior = p->prior;
    }

    free(p);
    puts("删除成功。");
}

//双向链表查找
void ListFind(DoubleLinkList list) {
    if (list == NULL) {
        puts("链表为空。");
        return;
    }

    ElemType data;

    // 输入查找数据
    puts("请输入要查找的数据:");
    while (scanf("%d", &data) != 1) {
        puts("输入无效，请输入一个整数:");
        while (getchar() != '\n'); // 清除输入缓冲区
    }

    DoubleListNode* p = list->next;
    int position = 1;

    // 遍历链表查找数据
    while (p != NULL) {
        if (p->data == data) {
            printf("找到数据 %d，位置为 %d。\n", data, position);
            return;
        }
        p = p->next;
        position++;
    }

    puts("未找到数据。");
}

// 双向链表销毁
void ListDestroy(DoubleLinkList list) {
    if (list == NULL) {
        puts("链表为空。");
        return;
    }

    DoubleListNode* p = list;
    DoubleListNode* temp;

    // 逐个释放节点
    while (p != NULL) {
        temp = p;
        p = p->next;
        free(temp);
    }

    puts("链表已销毁。");
}

void HideCursor()
{
	HANDLE fd = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cinfo;
	cinfo.bVisible = 0;
	cinfo.dwSize = 1;
	SetConsoleCursorInfo(fd, &cinfo);//隐藏光标
}
void gotoxy(int x, int y) {
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
	SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置
}

void menu()
{
	printf("=======================\n");
	printf("[A]\tListInit\n");
	printf("[B]\tListInsert\n");
	printf("[C]\tListDelete\n");
	printf("[D]\tListFind\n");
	printf("[E]\tListDestroy\n");
	printf("[F]\tQuit\n");
	printf("=======================\n");
	printf("请输入所要进行的选项");
}
void show(int line)
{
	gotoxy(0, 0);
	menu();
	gotoxy(0, line);//选中部分高亮变色
	if (line == 1)
		printf("\033[1;34;45m[A]\tListInit\n\033[0m");
	if (line == 2)
		printf("\033[1;34;45m[B]\tListInsert\n\033[0m");
	if (line == 3)
		printf("\033[1;34;45m[C]\tListDelete\n\033[0m");
	if (line == 4)
		printf("\033[1;34;45m[D]\tListFind\n\033[0m");
	if (line == 5)
		printf("\033[1;34;45m[E]\tListDestroy\n\033[0m");
	if (line == 6)
		printf("\033[1;34;45m[F]\tQuit\n\033[0m");
}
void menu_control(DoubleLinkList pt)
{
	char c1, c2, ch;
	int line, sec;
	long long j;
	time_t t;
	struct tm* lt;
	while (1)
	{
		system("cls");//系统清屏
		system("color 79");  //设置控制台的颜色
		Beep(2000, 250);//发声
		HideCursor();//隐藏光标
		menu();//显示菜单
		line = 1;
		gotoxy(0, line);//到达第一行首位置
		printf("\033[1;34;45m[A]\tInput\n\033[0m");
		while ((c1 = _getch()) != '/r')//读取按键的值
		{
			if (c1 == -32)
			{
				c2 = _getch();//获得第二个键值
				ch = c2;
				if (ch == upkey && line != 1)
				{
					line--;
					show(line);
					continue;
				}
				else if (ch == downkey && line != 6)
				{
					line++;
					show(line);
					continue;
				}
				else if (ch == downkey && line == 6)
				{
					line = 1;
					show(line);
					continue;
				}
				else if (ch == upkey && line == 1)
				{
					line = 6;
					show(line);
					continue;
				}
			}
			if (c1 == 'a' || c1 == 'A')
			{
				system("cls");//系统清屏
				gotoxy(0, 0);
				pt = ListInit();
				line = 0;
				break;
			}
			else if (c1 == 'b' || c1 == 'B')
			{
				system("cls");//系统清屏
				gotoxy(0, 0);
				ListInsert(pt);
				line = 0;
				break;
			}
			else if (c1 == 'C' || c1 == 'c')
			{
				system("cls");//系统清屏
				gotoxy(0, 0);
				ListDelete(pt);
				line = 0;
				break;
			}
			else if (c1 == 'd' || c1 == 'D')
			{
				system("cls");//系统清屏
				gotoxy(0, 0);
				ListFind(pt);
				line = 0;
				break;
			}
			else if (c1 == 'e' || c1 == 'E')
			{
				system("cls");//系统清屏
				gotoxy(0, 0);
				ListDestroy(pt);
				line = 0;
				break;
			}
			else if (c1 == 'f' || c1 == 'F')
			{
				system("cls");//系统清屏
				gotoxy(0, 0);
				exit(0);
				line = 0;
				break;
			}
		}
		time(&t);//获得时间戳
		lt = localtime(&t);//转为时间结构
		sec = lt->tm_sec;
		do
		{
			time(&t);
			lt = localtime(&t);
			j = lt->tm_sec - sec;
			if (j < 0)
				j = j + 60;
		} while (j < 5);
	}
}
int main()
{
	DoubleLinkList head = NULL;
	menu_control(head);
	return 0;
}




