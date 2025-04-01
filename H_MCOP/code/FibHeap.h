#ifndef ROUTER_FIBHEAP_H
#define ROUTER_FIBHEAP_H

#include "FibHeap_head.h"
#include <cmath>
#include <iomanip>

CFibHeap::CFibHeap(void):m_keyNum(0), m_maxDegree(0), m_min(NULL)
{

}


CFibHeap::~CFibHeap(void)
{
}

//添加节点
void CFibHeap::fibHeapInsert(nodePointer node)
{
    if (m_keyNum == 0)
        m_min = node;

    else
    {
        addNode(m_min, node);
        if (m_min->key > node->key)
            m_min = node;
    }
    m_keyNum++;
}

//添加节点外部接口
void CFibHeap::fibHeapInsert(int name, eletype key)
{
    nodePointer node = new SFibHeapNode(name, key);
    fibHeapInsert(node);
}

//将节点添加到根节点链表中
void CFibHeap::addNode(nodePointer node, nodePointer nodeAdd)
{
    nodePointer leftNode = node->left;

    leftNode->right = nodeAdd;
    nodeAdd->left = leftNode;
    nodeAdd->right = node;
    node->left = nodeAdd;
}

//合并两个斐波那契堆
void CFibHeap::fibHeapUnion(CFibHeap & other)
{
    if (other.m_min == NULL)
        return;

    if (m_maxDegree < other.m_maxDegree)
        m_maxDegree = other.m_maxDegree;

    if (m_min == NULL)
    {
        m_min = other.m_min;
        m_keyNum = other.m_keyNum;
    }

    else
    {
        if (m_min->key > other.m_min->key)
            m_min = other.m_min;
        //连接两个根链表
        addList(other.m_min);
        m_keyNum += other.m_keyNum;
    }

}

//将otherMin的list添加到m_min的根list中
void CFibHeap::addList(nodePointer otherMin)
{
    nodePointer rightNode = m_min->right;

    m_min->right = otherMin->right;
    otherMin->right->left = m_min;

    otherMin->right = rightNode;
    rightNode->left = otherMin;
}

//返回最小key
bool CFibHeap::minmum(eletype * key)
{
    if (m_min == NULL)
        return false;

    *key = m_min->key;
    return true;
}

//指向最小节点
nodePointer CFibHeap::minnode(){
    return m_min;
}

//抽取最小节点
nodePointer CFibHeap::extractMinNode()
{
    nodePointer minNode = m_min;
    if (minNode != NULL)
    {
        while (m_min->child != NULL)
        {
            nodePointer child = m_min->child;
            deleteNodeFromList(child);

            if (child->right == child)
                m_min->child = NULL;

            else
                m_min->child = child->right;

            addNode(m_min, child);
            child->parent = NULL;
        }

        deleteNodeFromList(m_min);

        if (m_min->right == m_min)
            m_min = NULL;

        else
        {
            m_min = m_min->right;
            consolidata();
        }

        m_keyNum--;
    }
    return minNode;
}

//从双链表结构中删除指定节点
void CFibHeap::deleteNodeFromList(nodePointer node)
{
    if(node->parent)
        node->parent->child = node->right;

    nodePointer leftNode = node->left;
    nodePointer rightNode = node->right;

    leftNode->right = rightNode;
    rightNode->left = leftNode;
}

//整合堆，减少根的数目，将有相同度数的根节点合并
void CFibHeap::consolidata()
{
    //计算最大度数上界
    int maxDegree = (int)(log((float)m_keyNum) / log(2.0)) + 2;
    nodePointer * cons = new nodePointer[maxDegree];

    for (int i = 0; i < maxDegree; i++)
        cons[i] = NULL;

    while (m_min != NULL)
    {
        nodePointer tree = extractMinTree();
        int degree = tree->degree;
        while (cons[degree] != NULL)
        {
            nodePointer treeWithSameDegree = cons[degree];

            //保证tree的key小于treeWithSameDegree的key
            if (treeWithSameDegree->key < tree->key)
                swap(treeWithSameDegree, tree);

            //使treeWithSameDegree成为tree的child,key大的为child
            link2Tree(tree, treeWithSameDegree);

            //link2Tree后tree度数成了degree+1，所以需要继续循环,度数为degree的cons为NULL
            cons[degree] = NULL;
            degree++;
        }
        cons[degree] = tree;
    }

    m_min = NULL;
    //将数组中组合成fibHeap
    for (int i = 0; i < maxDegree; i++)
    {
        if (cons[i] != NULL)
        {
            if (m_min == NULL)
                m_min = cons[i];
            else
            {
                nodePointer node = cons[i];
                addNode(m_min, node);

                if (node->key < m_min->key)
                    m_min = node;
            }
        }
    }

    delete []cons;
}

//抽取最小节点的树
nodePointer CFibHeap::extractMinTree()
{
    if (m_min == NULL)
        return NULL;

    nodePointer p = m_min;
    if (p->right == p)
        m_min = NULL;

    else
    {
        deleteNodeFromList(m_min);
        m_min = p->right;
    }

    p->left = p->right = p;//要抽取的树
    return p;
}

//连接两个节点
void CFibHeap::link2Tree(nodePointer parent, nodePointer child)
{
    deleteNodeFromList(child);
    if (parent->child == NULL)
        parent->child = child;

    else
        addNode(parent->child, child);

    child->mark = false;
    child->parent = parent;
    parent->degree++;
}

//减小指定节点的key值
void CFibHeap::decreaseKey(nodePointer x, eletype k)
{
    if (m_min == NULL || x == NULL)
        return;

    if (x->key < k)
        return;

    x->key = k;
    nodePointer parent = x->parent;

    if (parent != NULL && x->key < parent->key)
    {
        cut(parent, x);
        cascadingCut(parent);
    }

    if (x->key < m_min->key)
        m_min = x;
}

//切断指定父节点和子节点
void CFibHeap::cut(nodePointer parent, nodePointer child)
{
    if (child == child->right) {
        parent->child = NULL;
    }

    else
        deleteNodeFromList(child);

    parent->degree--;
    child->parent = NULL;
    child->mark = false;
    child->left = child->right = child;

    addNode(m_min, child);
}

//级联切断操作
void CFibHeap::cascadingCut(nodePointer parent)
{
    nodePointer grandParent = parent->parent;

    if (grandParent != NULL)
    {
        if (parent->mark == false)
            parent->mark = true;
        else
        {
            cut(grandParent, parent);
            cascadingCut(grandParent);
        }
    }
}

//删除指定节点
void CFibHeap::removeNode(nodePointer x)
{
    int key = m_min->key;

    decreaseKey(x, key - 1);
    extractMinNode();
}

void CFibHeap::printTree(nodePointer currentNode, nodePointer prevNode, int direction)
{
    if (currentNode == NULL)
        return;

    nodePointer node = currentNode;

    do
    {
        if (direction == 1)
            cout<<setw(4)<<node->name<<"("<<node->degree<<")"<<"is"<<setw(2)<<prevNode->name<<
                "'s child"<<endl;

        else
            cout<<setw(4)<<node->name<<"("<<node->degree<<")"<<"is"<<setw(2)<<prevNode->name<<
                "'s next"<<endl;

        if (node->child != NULL)
            printTree(node->child, node, 1);

        prevNode = node;
        node = node->right;
        direction = 2;
    } while (node != currentNode);
}

void CFibHeap::print()
{
    if (m_min == NULL)
        return;

    nodePointer currentNode = m_min;
    int i = 0;

    cout<<"print FibHeap:"<<endl;
    do
    {
        cout<<setw(2)<<i<<". "<<setw(4)<<currentNode->name<<"("<<currentNode->degree<<")"
            <<"is root"<<endl;

        printTree(currentNode->child, currentNode, 1);
        i++;
        currentNode = currentNode->right;
    } while (currentNode != m_min);

    cout<<endl;
}


#endif //ROUTER_FIBHEAP_H
