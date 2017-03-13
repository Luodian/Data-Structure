//
//  Leftist.hpp
//  LeftistHeap
//
//  Created by 李博 on 13/03/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#ifndef Leftist_h
#define Leftist_h

#include <iostream>
#include <cstdio>
#include <iomanip>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <bitset>
#include <numeric>
#include <set>
#include <list>
#include <map>

using namespace std;

enum flowType{Underflow,Overflow};
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
        LeftistNode(const Comparable & theElement, LeftistNode *lt = nullptr,LeftistNode *rt = nullptr,int np = 0)
        : element(theElement),left(lt),right(rt),npl(np)
        {};
    };
    LeftistNode *root;
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
    void insert(LeftistNode * &root,const Comparable &x)
    {
        LeftistNode single = new LeftistNode(x);
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
        while(isEmpty() == 0)
        {
            deleteMin();
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
    bool isEmpty()
    {
        return root == nullptr;
    }
    const Comparable & finMin() const;
    // void insert(const Comparable &x)
    // {
    //     root = merge(new LeftistNode(x),root);
    // }
    void deleteMin()
    {
        if (isEmpty())
        {
            flowType t = Underflow;
            throw t;
        }
        LeftistNode *oldRoot = root;
        root = merge(root->left,root->right);
        delete oldRoot;
    }
    void deleteMin(Comparable &minItem)
    {
        minItem = findMin();
        deleteMin();
    }
    void merge(LeftistHeap &rhs)
    {
        if (this == &rhs)
        {
            return;
        }
        root = merge(root,rhs.root);
        rhs.root = nullptr;
    }
    void findMin(const LeftistNode * &root)
    {
        return root->element;
    }
    void insert(const Comparable &x)
    {
        insert(root,x);
    }
};

#endif /* Leftist_h */
