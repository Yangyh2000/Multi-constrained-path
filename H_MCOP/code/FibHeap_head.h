#ifndef ROUTER_FIBHEAP_HEAD_H
#define ROUTER_FIBHEAP_HEAD_H

#pragma once
#include "heads.h"
#include <iostream>
using namespace std;
typedef struct _tagFibHeapNode
{
    int name;
    eletype key;
    _tagFibHeapNode * left;
    _tagFibHeapNode * right;
    _tagFibHeapNode * parent;
    _tagFibHeapNode * child;
    int degree;//孩子数
    bool mark;
    _tagFibHeapNode(int num, eletype value)
    {name = num, key = value, left = this, right = this, parent = NULL, child = NULL, degree = 0; mark = false;};
}SFibHeapNode, *nodePointer;

class CFibHeap
{
public:
    CFibHeap(void);
    ~CFibHeap(void);

    void fibHeapInsert(int name, eletype key);//插入节点到根链表，外部接口
    void fibHeapUnion(CFibHeap & other);//合并斐波那契堆
    bool minmum(eletype * key);//返回最小节点值
    nodePointer extractMinNode();//抽取最小节点
    nodePointer extractMinTree();//抽取一棵树
    nodePointer minnode();
    int nodenum(){ return m_keyNum;};
    void decreaseKey(nodePointer x, eletype k);//将节点x的key减为k
    void removeNode(nodePointer x);//删除指定节点
    void print();//打印堆

private:
    int m_keyNum;
    int m_maxDegree;
    nodePointer m_min;
    void fibHeapInsert(nodePointer node);//插入节点到根链表
    void addNode(nodePointer node, nodePointer nodeAdd);//添加nodeAdd到node之前
    void addList(nodePointer min);//连接两个双向循环链表
    void deleteNodeFromList(nodePointer node);//在双向链表中删除一个节点
    void consolidata();//整合堆，减少根的数目，将有相同度数的根节点合并
    void link2Tree(nodePointer parent, nodePointer child);//使得child为parent的child
    void cut(nodePointer parent, nodePointer child);//将child与parent断开，并将child放入根链表
    void cascadingCut(nodePointer parent);//级联切断
    void printTree(nodePointer currentNode, nodePointer prevNode, int direction);
};


#endif //ROUTER_FIBHEAP_HEAD_H
