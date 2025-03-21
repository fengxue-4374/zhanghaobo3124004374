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
#define LD 100 //数组大小

// 定义数据对象

struct LNode {
	char data[LD];
	struct LNode* next;
};

// 链表的生成

struct LNode* BuildList()
{
	struct LNode* head;   
	struct LNode* p1, * p2;
	int i = 0;
	puts("请向链表中输入数据:");
	head = NULL;
	p1 = p2 = (struct LNode*)malloc(sizeof(LNode));// 建立动态空间
	gets_s(p1->data,LD);//获得字符串
	for (; p1->data[0] != '\0';)
	{
		i++;
		if (i == 1)
			head = p1;      // 第一个链表节点
		else
			p2->next = p1;  // next指向新的动态空间
		p2 = p1;            // p2存储p1的内容
		p1 = (struct LNode*)malloc(sizeof(LNode));
		gets_s(p1->data, LD);
	}
	p2->next = NULL;// 指向链表末尾
	return (head);
}


//链表的销毁

 void DestroyList(LNode *L) {
	
	 struct LNode* p; 
	 // 遍历整个链表输出直到为空
	 while (L !=NULL) {     
		p = L;
		L = L->next;  
		free(p);   //释放空间
	}
}

//链表插入

 void InsertList(LNode *L) {
	 if (L == NULL) {
		 puts("链表为空，无法插入。");
		 return;
	 }

	 int i;
	 puts("请输入要插入的位置:");
	 while (scanf_s("%d", &i) != 1 || i < 1) {
		 puts("输入无效，请输入一个大于0的整数:");
		 while (getchar() != '\n');  // 清除输入缓冲区
	 }

	 struct LNode* p = L;
	 int j = 0;
	 while (p && j < i - 1) {  // 遍历链表直到所要插入的位置
		 p = p->next;
		 j++;
	 }

	 if (p == NULL) {
		 puts("插入位置超出链表范围。");
		 return;
	 }

	 LNode* s = (LNode*)malloc(sizeof(LNode));
	 if (s == NULL) {
		 puts("内存分配失败。");
		 return;
	 }

	 puts("请输入要插入的数据:");
	 while (getchar() != '\n');  // 清除输入缓冲区
	 if (fgets(s->data, LD, stdin) != NULL) {
		 // 去除换行符
		 size_t len = strlen(s->data);
		 if (len > 0 && s->data[len - 1] == '\n') {
			 s->data[len - 1] = '\0';
		 }
	 }
	 else {
		 puts("数据输入失败。");
		 free(s);
		 return;
	 }

	 s->next = p->next;
	 p->next = s;
	 puts("数据插入成功。");
 }

//链表删除
  void DeleteList(LNode *L) {
	 struct LNode* p = L;
	 int i;
	 puts("请输入要删除的位置:");
	 scanf_s("%d", &i);
	 int j = 0;
	 while (p->next && j < i - 1) {   //遍历链表直到所要删除的位置
		 p = p->next;
		 j++;
	 }
	 struct LNode* q = p->next;
	 p->next = q->next;
	 free(q);
 }

//输出链表
  void print1(LNode* L)
  {
	  puts("这个链表如下:");
	  while (L != NULL)//遍历整个链表输出直到为空
	  {
		  printf("%s\n", L->data);//输出p所指向的节点的数据
		  L = L->next;//使p指向下一个节点
	  }
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
	  printf("[A]\tBuildList\n");
	  printf("[B]\tDestroyList\n");
	  printf("[C]\tInsertList\n");
	  printf("[D]\tDeleteList\n");
	  printf("[E]\tPrint\n");
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
				  pt = BuildList();
				  line = 0;
				  break;
			  }
			  else if (c1 == 'b' || c1 == 'B')
			  {
				  system("cls");//系统清屏
				  gotoxy(0, 0);
				  DestroyList(pt);
				  line = 0;
				  break;
			  }
			  else if (c1 == 'C' || c1 == 'c')
			  {
				  system("cls");//系统清屏
				  gotoxy(0, 0);
				  InsertList(pt);
				  line = 0;
				  break;
			  }
			  else if (c1 == 'd' || c1 == 'D')
			  {
				  system("cls");//系统清屏
				  gotoxy(0, 0);
				  DeleteList(pt);
				  line = 0;
				  break;
			  }
			  else if (c1 == 'e' || c1 == 'E')
			  {
				  system("cls");//系统清屏
				  gotoxy(0, 0);
				  print1(pt);
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
	  struct LNode* head = NULL;
	  menu_control(head);
	  return 0;
  }




