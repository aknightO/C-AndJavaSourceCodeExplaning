import java.util.Collection;
import java.util.Iterator;

//为了避免和类库中的LinkedList冲突，这里我们创建自己的MyLinkedList
//首先提到java中的LinkedList是使用双链表来实现的
//public class LinkedList<E> extends AbstractSequentialList<E> implements List<E>, Deque<E>, Cloneable, Serializable
/*
* 考虑到设计方面，我们需要提供三个类：
* 1.MyLinkedList类本身，他包含到两端的链，表的大小以及一些方面
* 2.Node类，它可能是一个私有的嵌套类。一个结点包含数据，和到后一个结点和前驱结点的的链，还有一些适当的构造方法！
* 3.LinkedListIterator类，该类抽象了位置的概念，是一个私有类，并实现接口iterator。它提供方法next，hasNext，和remove方法
**/
public class MyLinkList implements Iterator<Collection>{
    private int theSize;
    private int modCount=0;//modCount代表自从构造依赖对链表所作的改变次数
    private Node beginMarker;
    private Node endMarker;

    //构造结点
    private static class Node{
        public Node(Integer d, Node p, Node n)
        {
            data = d;
            prev = p;
            next = n;
        }
         Integer data;
         Node prev;
         Node next;
    }

    //清除链表
    public void clear()
    {
        doclear();
    }

    private void doclear()
    {

         beginMarker = new Node(null,null,null);
         endMarker =new Node(null,beginMarker,null);
        beginMarker.next = endMarker;
        theSize = 0;
        modCount++;//modCount代表自从构造依赖对链表所作的改变次数
    }

    public int size()
    {
        return theSize;
    }

    //判空
    public boolean isEmpty()
    {
        return size()==0;
    }

    //添加方法
    public boolean add(Integer x,Integer integer)
    {
        add(size(),x);
        return true;
    }
    //在某个下标添加元素
    public void add(int idx,Integer x)
    {
        addBefore(getNode(idx,0,size()),x);
    }
    //addBefore方法，类似于尾插法
    //addBefore意思是在前面加
    /*
    * 在C++中的插入操作：
    * s->next = p->next;
    * 在p结点存在后续结点的时候
    * p ->next->prior = s;
    * s->prior = p;(这个具有指向性问题，s指向p,谁在前代表谁是主体，并且指向它)
    * p->next =s;
    *
    * */
    private void addBefore(Node p,Integer x)
    {
        //新建结点，然后添加相当于C++中的DLinkNode *s = (DLinkNode*)malloc(sizeof(DLinkNode));其中的值后续在给
        Node newNode = new Node(x,p.prev,p.next);
        newNode.prev.next =newNode;
        p.prev = newNode;
        theSize++;
        modCount++;
    }
    //方法连环
    public Integer get(int idx)//返回的是data值
    {
        return getNode(idx).data;
    }
    private Node getNode(int idx)
    {
        return getNode(idx,0,size()-1);
    }
    private Node getNode(int idx,int lower,int upper)
    {
        //使用的是二分思想
        Node p;
        if(idx < lower||idx > upper)
            throw new IndexOutOfBoundsException();//抛出越界异常
        if(idx < size()/2)//当结点下标小于一般长度的时候从前往后寻找
        {
            p = beginMarker.next;//指向后记结点，getNode我们的目的是获取该结点
            for(int i=0;i<idx;i++)
                p=p.next;//向后面循环，找到想要的结点
        }else{
            //当结点下标大于一般结点的时候，从后往前找
            p=endMarker;
            for(int i=size();i>idx;i--) {
                p = p.prev;//从后往前找
            }
        }
        return p;
    }

    //把某个结点内的数值更换为新的数值
    public Integer set(int idx,Integer newVal){
        Node p = getNode(idx);
        Integer oldVal = p.data;
        p.data = newVal;
        return oldVal;
    }

    public Integer remove(int idx)
    {
        return remove(getNode(idx));
        //java双链表中，把所有的越界异常都给了getNode
        //java双链表中所有具有操作性的动作，都会涉及到getNode方法
    }
    /*
    * 在C++中双链表的删除：(p为第i-1个结点，q为第i个结点，我们需要删除q结点)
    * p->next = q->next;
    * 如果p存在存在后继结点
    * q->next->prior = p->next;
    * free(q)
    * */
    private Integer remove(Node p){
        p.next.prev = p.prev;
        p.prev.next=p.next;
        theSize--;
        modCount++;
        return p.data;//返回删除的元素
    }

    //这里继承迭代器
    public java.util.Iterator iterator()
    {
        return new LinkedListIterator();
    }
    private class LinkedListIterator implements java.util.Iterator{
        private Node current=beginMarker.next;//current表示包含由调用next所返回的结点。注意，当current被定位于endMarker时，对next调用是非法的。
        //但是在C++中不非法
        //为了检测在迭代期间集合被修改的情况，迭代器被构造时的链表的modCount存储在数据域expectedModCount
        private int expectedModCount = modCount;
        //如果next方法已经执行，而没有其后的remove方法，则布尔数据域oktoremove为true。
        //因此oktoremove初始值设置为false，在next方法域中设置为true，在remove方法中设置为false
        private boolean oktoremove = false;

        @Override
        public boolean hasNext() {
            //我们希望结果是true的时候，一般我们写不等于进行判断
            return current!=endMarker;
        }

        @Override
        public Object next() {
            if(modCount!=expectedModCount)
                //对list 、map 等迭代的时进行修改就会抛出java.util.ConcurrentModificationException异常
                throw new java.util.ConcurrentModificationException();
            if(!hasNext())
                throw new java.util.NoSuchElementException();
            Integer nextItem = current.data;
            current=current.next;//指针往后走
            //如果next方法已经执行，而没有其后的remove方法，则布尔数据域oktoremove为true。
            //因此oktoremove初始值设置为false，在next方法域中设置为true，在remove方法中设置为false
            oktoremove = true;
            return nextItem;
        }

        @Override
        public void remove() {
            if(modCount!=expectedModCount)
                throw new java.util.ConcurrentModificationException();
            if(!oktoremove)
                throw new IllegalStateException();//非法状态异常
            MyLinkList.this.remove(current.prev);//删除current.prev
            expectedModCount++;
            oktoremove=false;//删除完成后重新置为false
        }
    }


}
