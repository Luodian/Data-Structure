//
//  Leftist.hpp
//  LeftistHeap
//
//  Created by 李博 on 13/03/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#ifndef Leftist_h
#define Leftist_h

#include "Header.hpp"
using namespace std;

template <typename Comparable>
class LeftistHeap
{
    
private:
    struct LeftistNode
    {
        Comparable element;
        LeftistNode *left;
        LeftistNode *right;
        int npl;
        LeftistNode(const Comparable & theElement = Comparable(), LeftistNode *lt = nullptr,LeftistNode *rt = nullptr,int np = 0)
        : element(theElement),left(lt),right(rt),npl(np)
        {};
    };
    LeftistNode *root;

    //对于左式堆的合并，首先比较两个堆的头结点
    //将元素较小的结点与较大的结点的右子树进行合并
    //并且递归的执行merge函数，递归出口为有一者为单结点时结束。
    LeftistNode * merge (LeftistNode * h1, LeftistNode * h2)
    {
        if (h1 == nullptr)
        {
            return h2;
        }
        if (h2 == nullptr)
        {
            return h1;
        }
        if (h1->element < h2->element)
        {
            return merge1(h1,h2);
        }
        else
        {
            return merge1(h2,h1);
        }
    }
    //在递归的出口的最后，此时肯定是满足堆序性质的，但是不一定满足左式堆性质
    //若右子树的零路径长大于左子树，因此我们需要交换其左右子树
    //头结点的零路径长会被更新为两者中的较小值+1，此时显然
    //右子树的零路径长最小，因此我们执行这样的更新。
    LeftistNode * merge1 (LeftistNode * h1, LeftistNode *h2)
    {
        if (h1->left == nullptr) //single node
        {
            h1->left = h2;
        }
        else
        {
            h1->right = merge(h1->right,h2);
            if (h1->left->npl < h1->right->npl)
            {
                swapChildren(h1);
            }
            h1->npl = h1->right->npl + 1;
        }
        return h1;
    }

    //插入是合并的一个特殊的例程
    //相当于当前树与一个单结点进行合并。
    //
    void insert(LeftistNode * &root,const Comparable &x)
    {
        LeftistNode *single = nullptr;
        single = new LeftistNode(x);
        root = merge(root,single);
    }
    void swapChildren(LeftistNode * &t)
    {
        if (t == nullptr)
        {
            return;
        }
        LeftistNode *temp = t->right;
        t->right = t->left;
        t->left = temp;
    }
    void makeEmpty()
    {
        while(!empty())
        {
            pop_front();
        }
    }
    // void reclaimMemory(LeftistNode *t);
    // LeftistNode *clone(LeftistNode *t) const;
public:
    LeftistHeap()
    {
        root = nullptr;
    }
    LeftistHeap(const LeftistHeap &rhs)
    {
        makeEmpty();
        root = nullptr;
        *this = rhs;
    }
    ~LeftistHeap()
    {
        makeEmpty();
    }
    bool empty()
    {
        return root == nullptr;
    }
    // void insert(const Comparable &x)
    // {
    //     root = merge(new LeftistNode(x),root);
    // }
    void pop_front()
    {
        if ((*this).empty())
        {
            flowType t = Underflow;
            throw t;
        }
        LeftistNode *oldRoot = root;
        root = merge(root->left,root->right);
        delete oldRoot;
    }
    // void pop_front(Comparable &minItem)
    // {
    //     minItem = front();
    //     pop_front();
    // }
    void merge(LeftistHeap &rhs)
    {
        if (this == &rhs)
        {
            return;
        }
        root = merge(root,rhs.root);
        rhs.root = nullptr;
    }
    Comparable front()
    {
        return root->element;
    }
    void insert(const Comparable &x)
    {
        insert(root,x);
    }
};

#endif /* Leftist_h */
