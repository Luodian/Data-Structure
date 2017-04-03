//
//  BinomialQueue.hpp
//  BinomialQueue
//
//  Created by 李博 on 03/04/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#ifndef BinomialQueue_h
#define BinomialQueue_h
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

template <typename T>
class BinomialQueue
{
public:
    BinomialQueue()
    {
        theTrees.resize(31);
        for (int i = 0; i < 31; ++i)
        {
            theTrees[i] = nullptr;
        }
        currentSize = 0;
    }
    BinomialQueue(const T &item)
    {
        theTrees.resize(31);
        for (int i = 0; i < 31; ++i)
        {
            theTrees[i] = nullptr;
        }
        currentSize = 0;
    }
    BinomialQueue(const BinomialQueue &rhs)
    {
        this = rhs;
    }
    ~BinomialQueue()
    {
        theTrees.clear();
        currentSize = 0;
        makeEmpty();
    }
    //只要有1个不为空则返回false
    bool isEmpty() const
    {
        for (int i = 0; i < theTrees.size(); ++i)
        {
            if (theTrees[i] != nullptr)
            {
                return false;
            }
        }
        return true;
    }
    //只要有1个为空则返回false;
    bool isFull() const
    {
        for (int i = 0; i < theTrees.size(); ++i)
        {
            if (theTrees[i] == nullptr)
            {
                return false;
            }
        }
        return true;
    }
    const T & findMin() const
    {
        int minIndex = findMinIndex();
        return theTrees[minIndex]->element;
    }
    void insert(const T & x)
    {
        BinomialQueue<T> tempQueue;
        BinomialNode *tempNode = new BinomialNode;

        tempNode->element = x;
        tempNode->nextSibling = tempNode->leftChild = nullptr;
        
        tempQueue.setCurrentSize(1);
        tempQueue.theTrees[0] = tempNode;
        merge(tempQueue);
    }
    void deleteMin()
    {
        if (isEmpty() == 1)
        {
            // throw UnderflowException();
            cout<<"UnderflowException\n";
        }
        int minIndex = findMinIndex();
        
        BinomialNode *oldRoot = theTrees[minIndex];
        BinomialNode *deletedTree = oldRoot->leftchild;
        delete oldRoot;
        
        BinomialQueue<T> deletedQueue;
        deletedQueue.theTrees.resize(minIndex + 1);
        deletedQueue.currentSize = (1 << minIndex) - 1;
        for (int j = minIndex - 1;j >= 0; --j)
        {
            deletedQueue.theTrees[j] = deletedTree;
            deletedTree = deletedTree->nextSibling;
            deletedQueue.theTrees[j]->nextSibling = nullptr;
        }
        
        theTrees[minIndex] = nullptr;
        currentSize -= deletedQueue.currentSize + 1;
        merge(deletedQueue);
    }
    void deleteMin(const T &minItem)
    {
        if (isEmpty() == 1)
        {
            // throw UnderflowException();
            cout<<"UnderflowException\n";
        }
        int minIndex = findMinIndex();
        minItem = theTrees[minIndex]->element;
        
        BinomialNode *oldRoot = theTrees[minIndex];
        BinomialNode *deletedTree = oldRoot->leftchild;
        delete oldRoot;
        
        BinomialQueue<T> deletedQueue;
        deletedQueue.theTrees.resize(minIndex + 1);
        deletedQueue.currentSize = (1 << minIndex) - 1;
        for (int j = minIndex - 1;j >= 0; --j)
        {
            deletedQueue.theTrees[j] = deletedTree;
            deletedTree = deletedTree->nextSibling;
            deletedQueue.theTrees[j]->nextSibling = nullptr;
        }
        
        theTrees[minIndex] = nullptr;
        currentSize -= deletedQueue.currentSize + 1;
        merge(deletedQueue);
    }
    void makeEmpty()
    {
        for (int i = 0; i < 31; ++i)
        {
            if (theTrees[i] != nullptr)
            {
                makeEmpty(theTrees[i]);
            }
        }
    }
    //t1和t2分别是H1和H2中的树，而carry是从上一步得来的树
    //从秩为i的树以及秩为i+1的carry树所形成的树，而其形成过程依赖于8种可能情形的每一种
    //该过程从秩为0开始直到产生二项队列的最后的秩。
    void merge(BinomialQueue<T> & rhs)
    {
        if (this == &rhs)
        {
            return;
        }
        //items of comparable element;
        currentSize += rhs.currentSize;
        if (currentSize > (int)capacity())
        {
            int oldNumTrees = theTrees.size();
            int newNumTrees = max(theTrees.size(), rhs.theTrees.size()) + 1;
            theTrees.resize(newNumTrees);
            for (int i = oldNumTrees; i < newNumTrees; ++i)
            {
                theTrees[i] = nullptr;
            }
        }
        
        BinomialNode *carry = nullptr;
        for (int i = 0, j = 1; j <= currentSize; ++i, j *= 2)
        {
            BinomialNode *t1 = theTrees[i];
            BinomialNode *t2 = i < theTrees.size() ? rhs.theTrees[i] : nullptr;
            int whichCase = t1 == nullptr ? 0 : 1;
            whichCase += t2 == nullptr ? 0 : 2;
            whichCase += carry == nullptr ? 0 : 4;
            if (whichCase == 0)
            {
                //No trees
                continue;
            }
            else if (whichCase == 1)
            {
                continue;
                //only this
            }
            else if (whichCase == 2)
            {
                //only rhs
                theTrees[i] = t2;
                rhs.theTrees[i] = nullptr;
            }
            else if (whichCase == 4)
            {
                //only carry
                theTrees[i] = carry;
                carry = nullptr;
            }
            else if (whichCase == 3)
            {
                //this and rhs
                carry = combineTrees(t1,t2);
                theTrees[i] = nullptr;
                rhs.theTrees[i] = nullptr;
            }
            else if (whichCase == 5)
            {
                //this and carry;
                carry = combineTrees(t1,carry);
                theTrees[i] = nullptr;
            }
            else if (whichCase == 6)
            {
                carry = combineTrees(t2,carry);
                rhs.theTrees[i] = nullptr;
            }
            else
            {
                theTrees[i] = carry;
                carry = combineTrees(t1,t2);
                rhs.theTrees[i] = nullptr;
            }
        }
        
        for (int k = 0; k < rhs.theTrees.size(); ++k)
        {
            rhs.theTrees[k] = nullptr;
        }
        rhs.currentSize = 0;
        
    }
    void setCurrentSize(const T &x)
    {
        currentSize = x;
    }
    const BinomialQueue & operator = (const BinomialQueue & rhs);
private:
    struct BinomialNode
    {
        T element;
        BinomialNode *leftChild;
        BinomialNode *nextSibling;
        
        BinomialNode(const T &theElement = T(), BinomialNode *lt = nullptr, BinomialNode *rt = nullptr)
        {
            element = theElement;
            leftChild = lt;
            nextSibling = rt;
        }
    };
    
    enum{DEFAULT_TREES = 1};
    
    int currentSize;
    
    vector<BinomialNode *> theTrees;
    
    int findMinIndex() const
    {
        int i;
        int minIndex;
        for (i = 0;theTrees[i] == nullptr;++i);
        for (minIndex = i;i < theTrees.size(); ++i)
        {
            if (theTrees[i] != nullptr && theTrees[i]->element < theTrees[minIndex]->element)
            {
                minIndex = i;
            }
        }
        return minIndex;
    }
    long long capacity() const
    {
        return (1 << 31) - 1;
    }
    //attach t2 to t1 only if t2 has the same size of t1
    //keep t1 is the minimal root element
    //return t1 as the combined tree
    BinomialNode * combineTrees(BinomialNode *t1, BinomialNode *t2)
    {
        if (t2->element < t1->element)
        {
            return combineTrees(t2,t1);
        }
        t2->nextSibling = t1->leftChild;
        t1->leftChild = t2;
        return t1;
    }
    void makeEmpty(BinomialNode * &t)
    {
        if (t->leftChild != nullptr)
        {
            makeEmpty(t->leftChild);
        }
        if (t->nextSibling != nullptr)
        {
            makeEmpty(t->nextSibling);
        }
        delete t;
    }
    BinomialNode * clone(BinomialNode *t) const;
};
#endif /* BinomialQueue_h */
