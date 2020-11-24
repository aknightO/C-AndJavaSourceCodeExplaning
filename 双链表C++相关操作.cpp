// 双链表和LinkedList关系.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//对于C++而言，双链表采用单链表类似的结构声明，双链表包含一个指向后继节点和前结点的指针，双链表有前一个结点和后一个结点，所以访问更加方便
#include <iostream>
using namespace std;
//建立双链表
typedef struct DNode {
	int data;
	struct DNode *prior;//指向前驱结点
	struct DNode *next;//指向下一个结点
}DLinkNode;

//建立双链表，头插法
void CreatListF(DLinkNode *&L, int a[], int n)
{
	//由含有n个元素的数组a创建带头结点的双链表L
	DLinkNode *s;
	L = (DLinkNode*)malloc(sizeof(DLinkNode));//创建头结点
	L->next = L->prior = NULL;//前后指针域变空
	for (int i = 0; i < n; i++)
	{
		s = (DLinkNode*)malloc(sizeof(DLinkNode));//创建数据结点s
		s->data = a[i];
		//头插法
		s->next = L->next;//将s结点插入到L结点之后
		if (L->next != NULL)//若L存在数据结点，修改L-.>next的前驱结点
			L->next->prior = s;
		L->next = s;
		s->prior = L;
	}
}

//建立双链表，尾插法
void CreatListR(DLinkNode *&L, int a[], int n)
{
	//由含有n个元素的数组创建带头结点的双链表
	DLinkNode *r,*s;
	L = (DLinkNode*)malloc(sizeof(DLinkNode));
	r = L;
	for (int i = 0; i < n; i++)
	{
		s = (DLinkNode*)malloc(sizeof(DLinkNode));
		s->data = a[i];
		r->next = s; s->prior = r;//将s结点插入到r结点之后
		r = s;
	}
	r->next = NULL;//尾部结点的指针域置为空
}

//双链表中的插入操作
//在双链表为i的位置插入一个新结点，结点的值为e
bool ListInsert(DLinkNode *&L, int i, int e)
{
	int j = 0;
	DLinkNode *p = L, *s;//p指向头结点，j置为零
	if (i <= 0) return false;
	if (j < i - 1 && p != NULL)//找到第i-1个结点
	{
		j++;
		p = p->next;
	}
	if (p == NULL)
		return false;//未找到第i-1个结点
	else
	{
		s = (DLinkNode*)malloc(sizeof(DLinkNode));
		s->data = e;
		s->next = p->next;//在p结点之前插入s结点
		if (p->next != NULL)
			p->next->prior = s;
		s->prior = p;
		p->next = s;
		return true;
	}
}
//删除双链表中的第i个结点
bool  DeleteList(DLinkNode *&L, int i, int &e)
{
	int j = 0;
	DLinkNode *p = L, *q;
	if (i <= 0) return false;
	while (j < -i - 1 && p != NULL)//找到第i-1个结点
	{
		j++;
		p = p->next;
	}
	if (p == NULL)
		return false;
	else
	{
		q = p->next;//q指向第i个节点
		if (q == NULL)
			return false; //不存在第i个结点
		e = q->data;
		p->next = q->next;//删除p结点
		if (p->next != NULL)//若p存在后继结点，则修改它的前驱结点
			p->next->prior = p;
		//在内存中释放第i个结点q
		free(q);
		return true;
	}
}

