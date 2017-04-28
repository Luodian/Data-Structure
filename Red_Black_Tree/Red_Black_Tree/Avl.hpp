//
//  Avl.hpp
//  Red_Black_Tree
//
//  Created by 李博 on 24/04/2016.
//  Copyright © 2017 李博. All rights reserved.
//

#ifndef Avl_h
#define Avl_h

#include "Header.hpp"

using namespace std;

namespace AVL
{
class AvlTree
{
private:
    struct AvlNode
    {
        int element;
        AvlNode *left;
        AvlNode *right;
        int height;
        int count;
        AvlNode(const int & theElement = 0, AvlNode *lt = nullptr,AvlNode *rt = nullptr,int h = 0,int ct = 0):
        element(theElement),left(lt),right(rt),height(h),count(ct){}
    };
    AvlNode *root;
    int h_x;
    char TreeBuffer[20][400];
    int TreeHeight;
    int GetHeight(AvlNode *p)
    {
        return p->height + 1;
    }
    void prework(AvlNode *root,int level)
    {
        if (root == nullptr)
        {
            h_x += (pow(2,TreeHeight - level) - 1);
            return;
        }
        prework(root->left,level + 1);
        TreeBuffer[level][h_x++] = root->element + '0';
        prework(root->right,level + 1);
    }
    void _try(AvlNode *root)
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
            throw "Buffer Out!\n";
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
    void PrintTree(AvlNode *root)
    {
        h_x = 0;
        TreeHeight = 0;
        memset(TreeBuffer,0,sizeof(TreeBuffer));
        _try(root);
        cout<<"\n";
    }
    
    int height(AvlNode *t)
    {
        return t == nullptr ? -1 : t->height;
    }
    //左旋提左儿子为根
    void rotateWithLeftChild(AvlNode * &k2)
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left),height(k2->right)) + 1;
        k1->height = max(height(k1->left),k2->height) + 1;
        k2 = k1;
    }
    //右旋提右儿子为根
    //mirror type
    void rotateWithRightChild(AvlNode * &k1)
    {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left),height(k1->right)) + 1;
        k2->height = max(height(k2->right),k1->height) + 1;
        k1 = k2;
    }
    
    //针对LR型树修正，先右旋拐点，在左旋头结点
    //参数为上方结点
    void doubleWithLeftChild(AvlNode * &k1)
    {
        rotateWithRightChild(k1->left);
        rotateWithLeftChild(k1);
    }
    //针对RL型树修正，先左旋拐点，在右旋头结点。
    void doubleWithRightChild(AvlNode * &k1)
    {
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }
    bool find(const int &x,AvlNode * t)
    {
        if (t == nullptr)
        {
            cout<<"Can't find.\n";
            return 0;
        }
        else
        {
            while(t!=nullptr)
            {
                if (x == t->element)
                {
                    return 1;
                }
                else if (x < t->element)
                {
                    t = t->left;
                }
                else
                {
                    t = t->right;
                }
            }
            return 0;
        }
    }
    void insert(const int &x,AvlNode * &t)
    {
        if (t == nullptr)
        {
            t = new AvlNode(x,nullptr,nullptr);
            t->count ++;
        }
        else if (x < t->element)
        {
            insert(x,t->left);
            if (height(t->left) - height(t->right) == 2)
            {
                if (x < t->left->element)
                {
                    rotateWithLeftChild(t);
                }
                else
                {
                    doubleWithLeftChild(t);
                }
            }
        }
        else if (x > t->element)
        {
            insert(x,t->right);
            if (height(t->right) - height(t->left) == 2)
            {
                if (x > t->right->element)
                {
                    rotateWithRightChild(t);
                }
                else
                {
                    doubleWithRightChild(t);
                }
            }
        }
        else if (x == t->element)
        {
            t->count ++;
        }
        t->height = max(height(t->left),height(t->right)) + 1;
    }
    AvlNode * findmax(AvlNode * root)
    {
        while (root->left != nullptr || root->right != nullptr)
        {
            if(root->right != nullptr)
            {
                root = root->right;
            }
            else if(root->left != nullptr)
            {
                root = root->left;
            }
        }
        return root;
    }
    AvlNode * findmin(AvlNode * root)
    {
        while (root->left != nullptr || root->right != nullptr)
        {
            if (root->left != nullptr)
            {
                root = root->left;
            }
            else if (root->right != nullptr)
            {
                root = root->right;
            }
        }
        return root;
    }
    AvlNode *Father = nullptr;
    void FindParent(AvlNode * &t,AvlNode *root)
    {
        if (t == root)
        {
            Father = nullptr;
            return;
        }
        if (root->left == nullptr && root->right == nullptr)
        {
            return;
        }
        if (root->left == t || root->right == t)
        {
            Father = root;
            return;
        }
        if (root->right != nullptr)
            FindParent(t,root->right);
        if (root->left != nullptr)
            FindParent(t,root->left);
        return;
    }
    void Remove(int x,AvlNode * &t)
    {
        if (t == nullptr)
        {
            throw "No such value\n";
        }
        int val = t->element;
        if (x == t->element)
        {
            AvlNode *temp = nullptr;
            if (t->right == nullptr && t->left == nullptr)
            {
                FindParent(t,root);
                if (Father->right == t)
                {
                    Father->right = nullptr;
                }
                else if (Father->left == t)
                {
                    Father->left = nullptr;
                }
                else
                {
                    throw "Undefined\n";
                }
                delete t;
                return;
            }
            if (t->right != nullptr)
            {
                temp = findmin(t->right);
            }
            else if (t->left != nullptr)
            {
                temp = findmax(t->left);
            }
            val = temp->element;
            x = temp->element;
        }
        if (x < t->element)
        {
            if (val != t->element)
            {
                t->element = val;
            }
            Remove(x,t->left);
            if (height(t->right) - height(t->left) == 2)
            {
                if (height(t->right->right) > height(t->right->left))
                {
                    rotateWithRightChild(t);
                }
                else
                {
                    doubleWithRightChild(t);
                }
            }
        }
        else if (x > t->element)
        {
            if (val != t->element)
            {
                t->element = val;
            }
            Remove(x,t->right);
            if (height(t->left) - height(t->right) == 2)
            {
                if (height(t->left->left) > height(t->left->right))
                {
                    rotateWithLeftChild(t);
                }
                else
                {
                    doubleWithLeftChild(t);
                }
            }
        }
        t->height = max(height(t->left),height(t->right)) + 1;
    }
    void makeEmpty(AvlNode * &t)
    {
        if (t != nullptr)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr; //最后使root指向空指针。
    }
public:
    AvlTree()
    {
        root = nullptr;
        h_x = 0;
        memset(TreeBuffer,0,sizeof(TreeBuffer));
        TreeHeight = 0;
    }
    ~AvlTree()
    {
        makeEmpty(root);
    }
    void clear()
    {
        makeEmpty(root);
    }
    void insert(const int &x)
    {
        insert(x,root);
    }
    int find(const int &x)
    {
        return find(x,root);
    }
    void remove(const int &x)
    {
        Remove(x,root);
    }
    void PrintTree()
    {
        PrintTree(root);
    }
};
}
#endif /* Avl_h */
