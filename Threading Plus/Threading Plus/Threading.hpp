//
//  Threading.hpp
//  Threading Plus
//
//  Created by 李博 on 17/03/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#ifndef Threading_h
#define Threading_h

#include "header.hpp"

using namespace std;
template <typename Object>
class ThreadingTree
{
private:
   	enum NodeTag {Link,Thread};
    struct ThreadingNode
    {
        Object element;
        ThreadingNode *left;
        NodeTag Ltag;
        NodeTag Rtag;
        ThreadingNode *right;
        ThreadingNode *parent;
        ThreadingNode (const Object &theElement = Object())
        {
            Ltag = Link;
            Rtag = Link;
        }
    };
    void init()
    {
        head = nullptr;
        temp = nullptr;
        root = new ThreadingNode;
        root->parent = nullptr;
        root->left = nullptr;
        root->right = nullptr;
    }
    
    ThreadingNode *temp;
    ThreadingNode *head;
    ThreadingNode *root;
    
    int TreeHeight;
    int h_x;
    char TreeBuffer[10][200];

    void CreateThreading(const string &order,int &&index,ThreadingNode * &p,ThreadingNode * &father)
    {
        if (order[index] == '#')
        {
            p = nullptr;
        }
        else
        {
            p = new ThreadingNode;
            p->element = order[index];
            p->Ltag = Link;
            p->Rtag = Link;
            p->parent = father;
            CreateThreading(order,move(++index),p->left,p);
            CreateThreading(order,move(++index),p->right,p);
        }
    }
    ThreadingNode *prev = nullptr;

    void ThreadingPreTree(ThreadingNode *p)
    {
        if (p != nullptr)
        {
            if (p->left == nullptr)
            {
                p->left = prev;
                p->Ltag = Thread;
            }
            if (prev->right == nullptr)
            {
                prev->right = p;
                prev->Rtag = Thread;
            }
            prev = p;
            if (p->Ltag == Link)
            {
                ThreadingPreTree(p->left);
            }
            if (p->Rtag == Link)
            {
                ThreadingPreTree(p->right);
            }
        }
    }

    void PreOrder(ThreadingNode *head)
    {
        ThreadingNode *p = head->left;
        while(p != head)
        {
            if (p != nullptr)
            {
                cout<<" "<<p->element;
            }
            if (p->Ltag == Link)
            {
                p = p->left;
            }
            else
            {
                p = p->right;
            }
        }
        cout<<"\n";
    }

    void ThreadingPostTree(ThreadingNode *p)
    {
        if (p != nullptr)
        {
            ThreadingPostTree(p->left);
            ThreadingPostTree(p->right);
            if (p->left == nullptr)
            {
                p->left = prev;
                p->Ltag = Thread;
            }
            if (prev && prev->right == nullptr)
            {
                prev->right = p;
                prev->Rtag = Thread;
            }
            prev = p;
        }
    }
    
    void PostOrder(ThreadingNode * root)
    {
        if (root != nullptr)
        {
            ThreadingNode *p = root;
            prev = nullptr;
            while(p != nullptr)
            {
                while(p->left != prev && p->Ltag == Link)
                {
                    p = p->left;
                }
                while (p != nullptr && p->Rtag == Thread)
                {
                    cout<<p->element<<" ";
                    prev = p;
                    p = p->right;
                }
                //此时有可能为只有左子树 故此种情况
                if (p == root)
                {
                    cout<<p->element<<" ";
                    return;
                }
                
                while (p != nullptr && p->right == prev)
                {
                    cout<<p->element<<" ";
                    prev = p;
                    p = p->parent;
                }
                
                if (p != nullptr && p->Rtag == Link)
                {
                    prev = p;
                    p = p->right;
                }
            }
        }
        cout<<"\n";
    }
    void makeEmpty(ThreadingNode * &t)
    {
        if (t->Ltag == Link)
        {
            makeEmpty(t->left);
        }
        if (t->Rtag == Link)
        {
            makeEmpty(t->right);
        }
        delete t;
    }
    int GetHeight(ThreadingNode *p)
    {
        if (p == nullptr)
        {
            return 0;
        }
        int lefth = 0,righth = 0;
        if (p->Ltag == Link)
            lefth = GetHeight(p->left);
        if (p->Rtag == Link)
            righth = GetHeight(p->right);
        return max(lefth,righth) + 1;
    }
    void prework(ThreadingNode *root,int level)
    {
        if (root == nullptr)
        {
            h_x += (pow(2,TreeHeight - level) - 1);
            return;
        }
        if (root->Ltag == Link)
            prework(root->left,level + 1);
        TreeBuffer[level][h_x++] = root->element;
        if (root->Rtag == Link)
            prework(root->right,level + 1);
    }
    void _draw(ThreadingNode *root)
    {
        if (root == nullptr)
        {
            return;
        }
        for (int i = 0; i < 10; ++i)
        {
            for (int j = 0; j < 128; ++j)
            {
                TreeBuffer[i][j] = 127;
            }
        }
        TreeHeight =  GetHeight(root);
        if (TreeHeight > 10)
        {
            cout<<"Buffer out! Can't output\n";
            return;
        }
        prework(root,0);
        for (int i = 0; i < TreeHeight; ++i)
        {
            cout<<"\t\t";
            for (int j = 0; j < 128; ++j)
            {
                if (TreeBuffer[i][j] == 127)
                {
                    cout<<" ";
                }
                else
                {
                    cout<<TreeBuffer[i][j];
                }
            }
            cout<<"\n\n";
        }
    }
public:
    ThreadingTree()
    {
        init();
    }
    ThreadingTree(const ThreadingTree &rhs)
    {
        init();
        *this = rhs;
    }
    ~ThreadingTree()
    {
        makeEmpty(root);
    }
    //线索化二叉树部分
    void ThreadingPreTree(const string &order)
    {
        CreateThreading(order,0,root,root->parent);
        prev = nullptr;
        head = new ThreadingNode;
        head->element = '*';
        if (root == nullptr)
        {
           head->left = head;
           head->Ltag = Thread;
           head->right = head;
           head->Rtag = Link;
        }
        else
        {
           prev = head;
           head->left = root;
           head->Ltag = Link;
           ThreadingPreTree(root);
           prev->right = head;
           prev->Rtag = Thread;
           head->right = head;
        }
        // prev = nullptr;
    }
    void ThreadingPostTree(const string &order)
    {
        CreateThreading(order,0,root,root->parent);
        ThreadingPostTree(root);
    }
    void PreOrder()
    {
        PreOrder(head);
    }
    void PostOrder()
    {
        PostOrder(root);
    }
    void Display()
    {
        _draw(root);
    }
};
#endif /* Threading_h */
