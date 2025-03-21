#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#define upkey 72   //�������������ֵ
#define downkey 80
#define leftkey 75
#define rightkey 77

//����˫������ṹ��
typedef int ElemType;
typedef struct _DoubleListNode
{
	ElemType data;
	struct _DoubleListNode* prior;	// ǰ��ָ��
	struct _DoubleListNode* next;	// ����ָ��
}DoubleListNode;
typedef DoubleListNode* DoubleLinkList;

//˫�������ʼ��
DoubleLinkList ListInit()
{
	DoubleLinkList list = (DoubleLinkList)malloc(sizeof(DoubleListNode));
	list->prior = NULL;
	list->next = NULL;
	list->data = -1;
	return list;
}
// ˫������������ݵĺ���
void ListInsert(DoubleLinkList list) {
    if (list == NULL) {
        puts("����Ϊ�ա�");
        return;
    }

    int position;
    ElemType data;

    // �������λ��
    puts("������Ҫ�����λ��:");
    while (scanf("%d", &position) != 1 || position < 1) {
        puts("������Ч��������һ������0������:");
        while (getchar() != '\n'); // ������뻺����
    }

    // �����������
    puts("������Ҫ���������:");
    while (scanf("%d", &data) != 1) {
        puts("������Ч��������һ������:");
        while (getchar() != '\n'); // ������뻺����
    }

    DoubleListNode* p = list;
    int j = 0;

    // �ҵ�����λ�õ�ǰһ���ڵ�
    while (p && j < position - 1) {
        p = p->next;
        j++;
    }

    if (p == NULL) {
        puts("����λ�ó�������Χ��");
        return;
    }

    // �����½ڵ�
    DoubleListNode* newNode = (DoubleListNode*)malloc(sizeof(DoubleListNode));
    if (newNode == NULL) {
        puts("�ڴ����ʧ�ܡ�");
        return;
    }
    newNode->data = data;

    // �����½ڵ�
    newNode->next = p->next;
    if (p->next != NULL) {
        p->next->prior = newNode;
    }
    p->next = newNode;
    newNode->prior = p;

    puts("����ɹ���");
}
//˫������ɾ��
void ListDelete(DoubleLinkList list) {
    if (list == NULL) {
        puts("����Ϊ�ա�");
        return;
    }

    int position;

    // ����ɾ��λ��
    puts("������Ҫɾ����λ��:");
    while (scanf("%d", &position) != 1 || position < 1) {
        puts("������Ч��������һ������0������:");
        while (getchar() != '\n'); // ������뻺����
    }

    DoubleListNode* p = list->next;
    int j = 1;

    // �ҵ�Ҫɾ���Ľڵ�
    while (p && j < position) {
        p = p->next;
        j++;
    }

    if (p == NULL) {
        puts("ɾ��λ�ó�������Χ��");
        return;
    }

    // ɾ���ڵ�
    if (p->prior != NULL) {
        p->prior->next = p->next;
    }
    if (p->next != NULL) {
        p->next->prior = p->prior;
    }

    free(p);
    puts("ɾ���ɹ���");
}

//˫���������
void ListFind(DoubleLinkList list) {
    if (list == NULL) {
        puts("����Ϊ�ա�");
        return;
    }

    ElemType data;

    // �����������
    puts("������Ҫ���ҵ�����:");
    while (scanf("%d", &data) != 1) {
        puts("������Ч��������һ������:");
        while (getchar() != '\n'); // ������뻺����
    }

    DoubleListNode* p = list->next;
    int position = 1;

    // ���������������
    while (p != NULL) {
        if (p->data == data) {
            printf("�ҵ����� %d��λ��Ϊ %d��\n", data, position);
            return;
        }
        p = p->next;
        position++;
    }

    puts("δ�ҵ����ݡ�");
}

// ˫����������
void ListDestroy(DoubleLinkList list) {
    if (list == NULL) {
        puts("����Ϊ�ա�");
        return;
    }

    DoubleListNode* p = list;
    DoubleListNode* temp;

    // ����ͷŽڵ�
    while (p != NULL) {
        temp = p;
        p = p->next;
        free(temp);
    }

    puts("���������١�");
}

void HideCursor()
{
	HANDLE fd = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cinfo;
	cinfo.bVisible = 0;
	cinfo.dwSize = 1;
	SetConsoleCursorInfo(fd, &cinfo);//���ع��
}
void gotoxy(int x, int y) {
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// ��ȡ��׼����豸���
	SetConsoleCursorPosition(hOut, pos);//���������ֱ���ָ���ĸ����壬����λ��
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
	printf("��������Ҫ���е�ѡ��");
}
void show(int line)
{
	gotoxy(0, 0);
	menu();
	gotoxy(0, line);//ѡ�в��ָ�����ɫ
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
		system("cls");//ϵͳ����
		system("color 79");  //���ÿ���̨����ɫ
		Beep(2000, 250);//����
		HideCursor();//���ع��
		menu();//��ʾ�˵�
		line = 1;
		gotoxy(0, line);//�����һ����λ��
		printf("\033[1;34;45m[A]\tInput\n\033[0m");
		while ((c1 = _getch()) != '/r')//��ȡ������ֵ
		{
			if (c1 == -32)
			{
				c2 = _getch();//��õڶ�����ֵ
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
				system("cls");//ϵͳ����
				gotoxy(0, 0);
				pt = ListInit();
				line = 0;
				break;
			}
			else if (c1 == 'b' || c1 == 'B')
			{
				system("cls");//ϵͳ����
				gotoxy(0, 0);
				ListInsert(pt);
				line = 0;
				break;
			}
			else if (c1 == 'C' || c1 == 'c')
			{
				system("cls");//ϵͳ����
				gotoxy(0, 0);
				ListDelete(pt);
				line = 0;
				break;
			}
			else if (c1 == 'd' || c1 == 'D')
			{
				system("cls");//ϵͳ����
				gotoxy(0, 0);
				ListFind(pt);
				line = 0;
				break;
			}
			else if (c1 == 'e' || c1 == 'E')
			{
				system("cls");//ϵͳ����
				gotoxy(0, 0);
				ListDestroy(pt);
				line = 0;
				break;
			}
			else if (c1 == 'f' || c1 == 'F')
			{
				system("cls");//ϵͳ����
				gotoxy(0, 0);
				exit(0);
				line = 0;
				break;
			}
		}
		time(&t);//���ʱ���
		lt = localtime(&t);//תΪʱ��ṹ
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




