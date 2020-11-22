// SqlList（java，C++实现）.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;
//现在我们开始使用C++来模拟java中的方法
//C++可以直接操作内存，这也是我更加喜欢使用C++来学习数据结构的原因
//java中的ArrayList实现是数组，在C++中称之为顺序表

#define MaxSize 50

typedef struct {
	int data[MaxSize];
	int length;
}SqlList;

//创建顺序表
//构建顺序表头插法和尾插法这么一说的，这两种方法用于链表
//L是输出型参数，所以带&
void CreatSqlList(SqlList *&L,int a[],int n)
{
	int i, k = 0;
	L = (SqlList*)malloc(sizeof(SqlList));
	while (i<n)
	{
		L->data[k] = a[i];
		i++, k++;
	}
	L->length = k;
}
//初始化线性表
void initSqlList(SqlList *&L)
{
	L = (SqlList*)malloc(sizeof(SqlList));//分配存放线性表的空间
	L->length = 0;
}

//销毁线性表
//这个我先使用java源码比较
void Destory(SqlList*&L) {
	free(L);//释放L所指向的顺序表空间
}
/*
//ArrayList的clear方法
public void clear() {
	++this.modCount;
	for (int var1 = 0; var1 < this.size; ++var1) {
		this.elementData[var1] = null;
	}
	this.size = 0;
}
*/

//判断线性表是否为空表
bool isEmpty(SqlList *L)
{
	return L->length == 0;
}
/*
//java中的isEmpty()
public boolean isEmpty() {
		return this.size == 0;
	}
*/

//求线性表长度
int ListLength(SqlList*L) {
	return L->length;
}
/*
//java中长度计算
public int size() {
		return this.size;
	}
*/

//输出线性表
void DisList(SqlList*L) {
	for (int i = 0; i < L->length; i++)
		printf("%d", L->data[i]);
	printf("\n");
}
/*
//java中我们可以使用迭代器来实现，因为实现了List接口，而List接口继承了Collection接口，而Collection接口继承了Iterator接口
//也可以根据size来实现

 public void forEach(Consumer<? super E> var1) {
		Objects.requireNonNull(var1);
		int var2 = this.modCount;
		Object[] var3 = (Object[])this.elementData;
		int var4 = this.size;

		for(int var5 = 0; this.modCount == var2 && var5 < var4; ++var5) {
			var1.accept(var3[var5]);
		}

		if (this.modCount != var2) {
			throw new ConcurrentModificationException();
		}
	}

*/

//get()求线性表某个数据元素的值
bool getElement(SqlList *L,int i,int &e) {
	if (i<1 || i>L->length)
		return false;
	e = L->data[i-1];
	return true;
}
/*
//java中的get()方法
private void rangeCheck(int var1) {
		if (var1 >= this.size) {
			throw new IndexOutOfBoundsException(this.outOfBoundsMsg(var1));
		}
	}//这个函数是对于长度的判断
	public E get(int var1) {
		this.rangeCheck(var1);
		return this.elementData(var1);
	}//这个调用RangeCheck()方法，然后直接返回元素值，elementData()
*/

//按元素值查找
//平均执行次数（n+1）/2
int LocalElement(SqlList*L, int e)
{
	int i = 0;
	while (i < L->length&&L->data[i] != e)//循环条件是小于长度，并且在第一次没找到的情况下,判断条件放在了循环内，妙啊！（while循环内可以放条件，更简洁）
		i++;
	if (L->length <= i)
		return 0;
	else
		return i;
}

/*
//java中用值获取下标
public int indexOf(Object var1) {
		int var2;
		if (var1 == null) {
			for(var2 = 0; var2 < this.size; ++var2) {
				if (this.elementData[var2] == null) {
					return var2;
				}
			}
		} else {
			for(var2 = 0; var2 < this.size; ++var2) {
				if (var1.equals(this.elementData[var2])) {
					return var2;
				}
			}
		}
		return -1;
	}
*/

//插入数据元素
bool ListInsert(SqlList *&L,int i, int e) {
	int j;
	if (i > L->length+1 || i < 1) return false;//注意：这里是插入操作，Length加一
	i--;//逻辑序号转化物理序号
	//从后往前数
	for (int j = L->length; j > i; j--)
		L->data[j] = L->data[j - 1];
	L->data[i] = e;
	L->length++;//插入成功，length加一，判断的时候也加一
	return true;
}
/*
//java中的add
 public void add(int var1, E var2) {
		this.rangeCheckForAdd(var1);//rangecheck（）函数计算var长度
		this.ensureCapacityInternal(this.size + 1);//ensureCapacityInternal（）函数用于扩容，扩大的长度是var1的长度
		System.arraycopy(this.elementData, var1, this.elementData, var1 + 1, this.size - var1);
		this.elementData[var1] = var2;
		++this.size;
	}


	//扩容的函数
	private void ensureCapacityInternal(int var1) {
		this.ensureExplicitCapacity(calculateCapacity(this.elementData, var1));
	}

	private void ensureExplicitCapacity(int var1) {
		++this.modCount;
		if (var1 - this.elementData.length > 0) {
			this.grow(var1);
		}

	}

	private void grow(int var1) {
		int var2 = this.elementData.length;
		int var3 = var2 + (var2 >> 1);
		if (var3 - var1 < 0) {
			var3 = var1;
		}

		if (var3 - 2147483639 > 0) {
			var3 = hugeCapacity(var1);
		}
		//这里数组的扩容形式是复制到一个新的数组中
		this.elementData = Arrays.copyOf(this.elementData, var3);
	}
*/

//删除第i个元素，使用e返回
bool ListDelete(SqlList *&L, int i, int &e) {
	int j;
	if (i<1 || i>L->length - 1) return false;
	i--;//逻辑序号转化为物理序号
	e = L->data[i];
	for (int j = i; j < L->length - 1; j++)//把后面的元素往前放一个
		L->data[j] = L->data[j + 1];
	L->length--;
	return true;
}
/*
//java中ArrayList的删除操作
public boolean remove(Object var1) {
		int var2;
		if (var1 == null) {
			for(var2 = 0; var2 < this.size; ++var2) {
				if (this.elementData[var2] == null) {
					this.fastRemove(var2);
					return true;
				}
			}
		} else {
			for(var2 = 0; var2 < this.size; ++var2) {
				if (var1.equals(this.elementData[var2])) {
					this.fastRemove(var2);
					return true;
				}
			}
		}

		return false;
	}
private void fastRemove(int var1) {
		++this.modCount;
		int var2 = this.size - var1 - 1;
		if (var2 > 0) {
			System.arraycopy(this.elementData, var1 + 1, this.elementData, var1, var2);
		}

		this.elementData[--this.size] = null;
	}
*/

