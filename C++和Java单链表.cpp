// C++和Java单链表.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;
//C++中的设计
typedef struct LNode {
	int data;
	struct LNode *next;
}LinkNode;
/*
//java中的设计
public class Linked <T>{

	private class Node{
		private T t;
		private Node next;
		public Node(T t,Node next){
			this.t = t;
			this.next = next;
		}
		public Node(T t){
			this(t,null);
		}
	}
	private Node head;    		//头结点
	private int size;			//链表元素个数
	//构造函数
	public Linked(){
		this.head = null;
		this.size = 0;
	}
}
*/

//关于单链表的插入和删除
//插入：s->next = p->next;p->next = s;
//删除1：p->next = p->next->next;(这个是修改指针的写法)
//删除2：q=p->next; p->next = q->next;free(q)
//free(q)的意思是释放这个内存空间

//建立单链表，头插法
void CreatListF(LinkNode *L, int  a[], int n)
{
	LinkNode* s;
	L = (LinkNode*)malloc(sizeof(LinkNode));//分配空间,建立头结点
	L->next = NULL;
	for (int i = 0; i < n; i++) {
		s = (LinkNode*)malloc(sizeof(LinkNode));
		s->data = a[i];
		s->next = L->next;
		L->next = s;
	}
}
//尾插法
void CreatListR(LinkNode*&L, int a[], int n)
{
	LinkNode *s,*r;//尾插法我们一般创建r在尾部
	//建立头结点
	L = (LinkNode*)malloc(sizeof(LinkNode));
	r = L;//r始终指向尾结点
	for (int i = 0; i < n; i++)
	{
		s = (LinkNode*)malloc(sizeof(LinkNode));
		s->data = a[i];//s->data指定的是现在所申明的s结点
		//尾插法
		r->next = s;
		r = s;
	}
	r->next = NULL;//r始终指向尾部结点
}

/*
//java中的代码实现和理解
先找到该目标索引的前一个结点，记录为pre，把要插入的结点node的下一个结点node.next指向pre的下一个结点pre.next；再把pre.next指向node结点。
如果先进行pre.next指向要插入的结点，再进行node.next指向pre.next的话，无疑是要插入的结点自己指向了自己，无法连接上整个链表，在链表的操作中，
有时候顺序的执行会带来不一样的结果。


//链表头部添加元素
	public void addFirst(T t){
		Node node = new Node(t);	//节点对象
		node.next = this.head;
		this.head = node;
		//this.head = new Node(e,head);等价上述代码
		this.size++;//size++的意思是链表的长度加一
	}
	//向链表尾部插入元素
	public void addLast(T t){
		this.add(t, this.size);//这个相当于尾插法，java把这些都封装了，看起来不明显
	}
	//向链表中间插入元素
	public void add(T t,int index){
		if (index <0 || index >size){
			throw new IllegalArgumentException("index is error");
		}
		if (index == 0){
			this.addFirst(t);
			return;
		}
		Node preNode = this.head;
		//找到要插入节点的前一个节点
		for(int i = 0; i < index-1; i++){
			preNode = preNode.next;
		}
		Node node = new Node(t);
		//要插入的节点的下一个节点指向preNode节点的下一个节点
		node.next = preNode.next;
		//preNode的下一个节点指向要插入节点node
		preNode.next = node;
		this.size++;
	}
*/

//初始化线性表
void InitList(LinkNode *L) {
	L = (LinkNode*)malloc(sizeof(LinkNode));
	L->next = NULL;
}

//销毁线性表，相当于手动释放内存
//其过程是pre，p同时指向相邻的两个结点（初始的时候pre指向头结点，p指向首结点），当p不为空的时候循环，释放pre，然后pre，和p同时向后移动
//循环之后pre指向尾结点
void DestoryList(LinkNode*&L)
{
	LinkNode *pre=L, *p=L->next;
	while (!p->next) {
		free(pre);
		pre = p;
		p = pre->next;//这里使用p->next和pre->next是一样的，都是同步往后移动
	}
	free(pre);//最后将尾结点释放
}

//判空
bool isEmpty(LinkNode *L)
{
	return L->next == NULL;
}

//求线性表的长度
int ListLength(LinkNode *L)
{
	int n = 0;
	LinkNode *p = L;
	while (!p->next)
	{
		n++;
		p = p->next;
	}
	return n;
}

//输出线性表（链表也是线性表）
void DispList(LinkNode *L)
{
	LinkNode *p = L->next;
	while (!p) {
		printf("%d", p->data);
		p = p->next;//这个是为了向后移动
	}
	printf("\n");
}

//求线性表某个数据元素值，GetElement(LinkNode*L, int i,int &e)，查找这类问题一般为bool类型
bool GetElement(LinkNode *L, int i, int &e)
{
	int j = 0;
	LinkNode *p = L;
	if (i <= 0) return false;
	while (j < i && !p)//找到第i个结点p
	{
		//循环找到这个结点
		j++;
		p = p->next;
	}
	if (p == NULL) {
		//找到最后，没有找到e
		return false;
	}
	else
	{
		e = p->data;
		return true;
	}
 }

//按元素值查找，返回逻辑序号
int LocalElem(LinkNode *L, int e)
{
	int i = 0;
	LinkNode *p = L->next;
	while (!p&&p->data != e)//找到需要找的物理下标
	{
		p = p->next;
		i++;
	}
	if (!p)
		return 0;
	else
		return i + 1;//返回逻辑下标

}

//插入数据元素ListInset(&L,i,e),如果i=5，j<4
bool ListInsert(LinkNode *&L, int i, int e)
{
	int j = 0;
	LinkNode *p = L,*s;
	if (i < 0) return false;
	while (j < i - 1 && !p)//查找第i-1个结点
	{
		j++;
		p = p->next;
	}
	if (!p)
		return false;
	else
	{
		//这个使用头插法
		s = (LinkNode*)malloc(sizeof(LinkNode));
		s->data = e;
		s->next = p->next;
		p->next = s;
		return true;
	}
}

//删除元素ListDelete(&L,i,&e)
//这里删除元素，现在我们先在单链表中找到第i-1个结点，由p指向它。如果存在这样的结点，
//且存在后续结点（由q指向它），删除q所指向的结点，返回为true，否则返回false
bool ListDelete(LinkNode*&L, int i, int &e)
{
	int j = 0;
	LinkNode *p = L, *q;
	//头结点也是一个结点，它不能为空
	while (j < i - 1 && !p)//找到第i-1个结点
	{
		j++;
		p = p->next;
	}
	if (p == NULL)
		return false;
	else
	{
		q = p->next;//q指向第i个结点
		if (q == NULL)
			return false;
		e = q->data;
		p->next = q->next;
		free(q);
		return true;
	}
}
/*
//在java中ListDelete
	//删除链表元素
	public void remove(T t){
		if(head == null){
			System.out.println("无元素可删除");
			return;
		}
		//要删除的元素与头结点的元素相同
		while(head != null && head.t.equals(t)){
			head = head.next;
			this.size--;
		}
		
		Node cur = this.head;
		while (cur != null && cur.next != null) {
		if (cur.next.t.equals(t)) {
		this.size--;
		cur.next = cur.next.next;
		}
		else cur = cur.next;
		}
	}

	
	//链表中是否包含某个元素
	public boolean contains(T t){
		Node cur = this.head;
		while(cur != null){
			if(cur.t.equals(t)){
				return true;
			}
			else cur = cur.next;
		}
		return false;
	}

	//删除链表第一个元素
	public T removeFirst(){
		if(this.head == null){
			System.out.println("无元素可删除");
			return null;
		}
		Node delNode = this.head;
		this.head = this.head.next;
		delNode.next =null;
		this.size--;
		return delNode.t;
	}


	//删除链表的最后一个元素
	public T removeLast(){
		if(this.head == null){
			System.out.println("无元素可删除");
			return null;
		}
		//只有一个元素
		if(this.getSize() == 1){
			return this.removeFirst();
		}
		Node cur = this.head;	//记录当前结点
		Node pre = this.head;	//记录要删除结点的前一个结点
		while(cur.next != null){
			pre = cur;
			cur = cur.next;
		}
		pre.next = cur.next;
		this.size--;
		return cur.t;
	}

*/