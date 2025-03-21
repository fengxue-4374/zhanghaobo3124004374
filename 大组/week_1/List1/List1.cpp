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
#define LD 100 //�����С

// �������ݶ���

struct LNode {
	char data[LD];
	struct LNode* next;
};

// ���������

struct LNode* BuildList()
{
	struct LNode* head;   
	struct LNode* p1, * p2;
	int i = 0;
	puts("������������������:");
	head = NULL;
	p1 = p2 = (struct LNode*)malloc(sizeof(LNode));// ������̬�ռ�
	gets_s(p1->data,LD);//����ַ���
	for (; p1->data[0] != '\0';)
	{
		i++;
		if (i == 1)
			head = p1;      // ��һ������ڵ�
		else
			p2->next = p1;  // nextָ���µĶ�̬�ռ�
		p2 = p1;            // p2�洢p1������
		p1 = (struct LNode*)malloc(sizeof(LNode));
		gets_s(p1->data, LD);
	}
	p2->next = NULL;// ָ������ĩβ
	return (head);
}


//���������

 void DestroyList(LNode *L) {
	
	 struct LNode* p; 
	 // ���������������ֱ��Ϊ��
	 while (L !=NULL) {     
		p = L;
		L = L->next;  
		free(p);   //�ͷſռ�
	}
}

//�������

 void InsertList(LNode *L) {
	 if (L == NULL) {
		 puts("����Ϊ�գ��޷����롣");
		 return;
	 }

	 int i;
	 puts("������Ҫ�����λ��:");
	 while (scanf_s("%d", &i) != 1 || i < 1) {
		 puts("������Ч��������һ������0������:");
		 while (getchar() != '\n');  // ������뻺����
	 }

	 struct LNode* p = L;
	 int j = 0;
	 while (p && j < i - 1) {  // ��������ֱ����Ҫ�����λ��
		 p = p->next;
		 j++;
	 }

	 if (p == NULL) {
		 puts("����λ�ó�������Χ��");
		 return;
	 }

	 LNode* s = (LNode*)malloc(sizeof(LNode));
	 if (s == NULL) {
		 puts("�ڴ����ʧ�ܡ�");
		 return;
	 }

	 puts("������Ҫ���������:");
	 while (getchar() != '\n');  // ������뻺����
	 if (fgets(s->data, LD, stdin) != NULL) {
		 // ȥ�����з�
		 size_t len = strlen(s->data);
		 if (len > 0 && s->data[len - 1] == '\n') {
			 s->data[len - 1] = '\0';
		 }
	 }
	 else {
		 puts("��������ʧ�ܡ�");
		 free(s);
		 return;
	 }

	 s->next = p->next;
	 p->next = s;
	 puts("���ݲ���ɹ���");
 }

//����ɾ��
  void DeleteList(LNode *L) {
	 struct LNode* p = L;
	 int i;
	 puts("������Ҫɾ����λ��:");
	 scanf_s("%d", &i);
	 int j = 0;
	 while (p->next && j < i - 1) {   //��������ֱ����Ҫɾ����λ��
		 p = p->next;
		 j++;
	 }
	 struct LNode* q = p->next;
	 p->next = q->next;
	 free(q);
 }

//�������
  void print1(LNode* L)
  {
	  puts("�����������:");
	  while (L != NULL)//���������������ֱ��Ϊ��
	  {
		  printf("%s\n", L->data);//���p��ָ��Ľڵ������
		  L = L->next;//ʹpָ����һ���ڵ�
	  }
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
	  printf("[A]\tBuildList\n");
	  printf("[B]\tDestroyList\n");
	  printf("[C]\tInsertList\n");
	  printf("[D]\tDeleteList\n");
	  printf("[E]\tPrint\n");
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
		  printf("\033[1;34;45m[A]\tBuildList\n\033[0m");
	  if (line == 2)
		  printf("\033[1;34;45m[B]\tDestroyList\n\033[0m");
	  if (line == 3)
		  printf("\033[1;34;45m[C]\tInsertList\n\033[0m");
	  if (line == 4)
		  printf("\033[1;34;45m[D]\tDeleteList\n\033[0m");
	  if (line == 5)
		  printf("\033[1;34;45m[E]\tPrint\n\033[0m");
	  if (line == 6)
		  printf("\033[1;34;45m[F]\tQuit\n\033[0m");
  }
  void menu_control(struct LNode* pt)
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
				  pt = BuildList();
				  line = 0;
				  break;
			  }
			  else if (c1 == 'b' || c1 == 'B')
			  {
				  system("cls");//ϵͳ����
				  gotoxy(0, 0);
				  DestroyList(pt);
				  line = 0;
				  break;
			  }
			  else if (c1 == 'C' || c1 == 'c')
			  {
				  system("cls");//ϵͳ����
				  gotoxy(0, 0);
				  InsertList(pt);
				  line = 0;
				  break;
			  }
			  else if (c1 == 'd' || c1 == 'D')
			  {
				  system("cls");//ϵͳ����
				  gotoxy(0, 0);
				  DeleteList(pt);
				  line = 0;
				  break;
			  }
			  else if (c1 == 'e' || c1 == 'E')
			  {
				  system("cls");//ϵͳ����
				  gotoxy(0, 0);
				  print1(pt);
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
	  struct LNode* head = NULL;
	  menu_control(head);
	  return 0;
  }




