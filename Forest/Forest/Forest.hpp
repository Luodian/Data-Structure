//
//  Forest.hpp
//  Forest
//
//  Created by 李博 on 20/03/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#ifndef Forest_h
#define Forest_h

#include "Header.hpp"

using namespace std;

template<typename T> class Forest;
template<typename T> class BinaryTree;
template<typename T> class TreeNode;
template<typename T> class BinaryNode;
template<typename T> class Tree;

template<typename T>
class BinaryNode
{
    friend class BinaryTree<T>;
    friend class Forest<T>;
    friend class Tree<T>;
private:
    T element;
    BinaryNode<T> *left;
    BinaryNode<T> *right;
public:
    BinaryNode (const T &theElement = '*',BinaryNode *LT = nullptr,BinaryNode *RT = nullptr)
    :element(theElement),left(LT),right(RT)
    {
        
    }
};

template<typename T>
class TreeNode
{
    friend class Tree<T>;
    friend class BinaryTree<T>;
    friend class Forest<T>;
private:
    T element;
    vector<TreeNode<T> *> childs;
public:
    TreeNode(const T data = T())
    {
        element = data;
        childs.clear();
    }
};

template<typename T>
class Forest
{
    friend class BinaryTree<T>;
    friend class Tree<T>;
private:
    int TreeNum;
    vector<TreeNode<T> *>  TreeRoots;
public:
    TreeNode<T> * operator [] (const int &choice) const
    {
        if (choice < TreeRoots.size())
        {
            return TreeRoots[choice];
        }
        else
        {
            return nullptr;
        }
    }
    Forest()
    {
        TreeRoots.clear();
        TreeNum = 0;
    }
    
};

template<typename T>
class Tree
{
    friend class BinaryTree<T>;
    friend class Forest<T>;
private:
    TreeNode<T> *root;
    void init(const T &theElement = '*')
    {
        root = new TreeNode<T>(theElement);
    }
    void toBinaryTree(TreeNode<T> *&Troot,BinaryNode<T> *&Broot)
    {
        if (Troot == nullptr)
        {
            return;
        }
        if (Broot == nullptr)
        {
            Broot = new BinaryNode<T>;
        }
        Broot->element = Troot->element;
        if(Troot->childs.size() != 0 && Troot->childs[0] != nullptr)
        {
            toBinaryTree(Troot->childs[0],Broot->left);
        }
        BinaryNode<T> *oldestBrother = Broot->left;
        for (int i = 1; i < Troot->childs.size(); ++i)
        {   
            toBinaryTree(Troot->childs[i],oldestBrother->right);
            oldestBrother = oldestBrother->right;
        }
    }
    //将q树拷贝给p树
    TreeNode<T> * Treecpy(TreeNode<T> *q)
    {
        if (q == nullptr)
        {
            return nullptr;
        }
        TreeNode<T> *cur = new TreeNode<T>(q->element);
        cur->childs.resize(q->childs.size());
        for (int i = 0; i < q->childs.size(); ++i)
        {
            cur->childs[i] = Treecpy(q->childs[i]);
        }
        return cur;
    }
public:
    Tree(const T &theElement = '*')
    {
        init(theElement);
    }
    //通过forest来定义Tree()
    Tree(TreeNode<T> *Troot)
    {
        root = new TreeNode<T>;
        root = Treecpy(Troot);
    }
    void toBinaryTree(BinaryTree<T> &t)
    {
        BinaryNode<T> *Broot = t.root;
        toBinaryTree(root,Broot);
    }
};

template<typename T>
class BinaryTree
{
    friend class Tree<T>;
    friend class Forest<T>;
private:
    BinaryNode<T> *root;
    void init()
    {
        Maxsize = 10000;
        CountNodes = 0;
        root = new BinaryNode<T>;
    }

    int Maxsize;
    int CountNodes;
    int TreeHeight;
    char TreeBuffer[10][200];
    int h_x;
    void CreateBinaryTree(const string &order,int &&index,BinaryNode<T> * &t)
    {
        if (order[index] == '#')
        {
            t = nullptr;
            return;
        }
        CountNodes ++;
        t = new BinaryNode<T>(order[index],nullptr,nullptr);
        CreateBinaryTree(order,move(++index),t->left);
        CreateBinaryTree(order,move(++index),t->right);
    }
    void makeEmpty(BinaryNode<T> * &t)
    {
        if (t != nullptr)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr; //最后使root指向空指针。
    }
    int GetHeight(BinaryNode<T> *p)
    {
        if (p == nullptr)
        {
            return 0;
        }
        int lefth = GetHeight(p->left);
        int righth = GetHeight(p->right);
        return max(lefth,righth) + 1;
    }
    void prework(BinaryNode<T> *root,int level)
    {
        if (root == nullptr)
        {
            h_x += (pow(2,TreeHeight - level) - 1);
            return;
        }
        prework(root->left,level + 1);
        TreeBuffer[level][h_x++] = root->element;
        prework(root->right,level + 1);
    }
    void _try(BinaryNode<T> *root)
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
    void toTree(BinaryNode<T> * &Broot,TreeNode<T> * &Troot)
    {
        if (Broot->left == nullptr)
        {
            return;
        }
        TreeNode<T> *pTroot = Troot;
        BinaryNode<T> *pCurRoot = Broot->left;

        //选取最左儿子，长子作为当前的根节点。

        if(pCurRoot != nullptr)
        {
            Troot->childs.push_back(new TreeNode<T>(pCurRoot->element));
        }
        toTree(pCurRoot,pTroot->childs[0]);

        while(pCurRoot->right != nullptr)
        {
            //转换当前节点的所有右儿子为根节点的儿子。
            pCurRoot = pCurRoot->right;
            pTroot->childs.push_back(new TreeNode<T>(pCurRoot->element));
            toTree(pCurRoot,pTroot);
        }
    }
    void toForest(BinaryNode<T> * &Broot,Forest<T> &F)
    {
        if (Broot == nullptr)
        {
            return;
        }
        toForest(Broot->right,F);
        TreeNode<T> *Troot = new TreeNode<T>(Broot->element);
        toTree(Broot,Troot);

        F.TreeRoots.push_back(Troot);
    }
public:
    BinaryTree()
    {
        init();
    }
    BinaryTree(const string &order)
    {
        CreateBinaryTree(order,0,root);
    }
    BinaryTree(const BinaryTree &rhs)
    {
        init();
        *this = rhs;
    }
    ~BinaryTree()
    {
        makeEmpty(root);
    }
    void makeEmpty()
    {
        makeEmpty(root);
    }
    void CreateBinaryTree(const string &order)
    {
        CountNodes = 0;
        CreateBinaryTree(order,0,root);
    }
    void Display()
    {
        h_x = 0;
        TreeHeight = 0;
        _try(root);
    }
    Tree<T>& toTree()
    {
        Tree<T> ret;
        TreeNode<T> *pTroot = ret.root;
        ret = toTree(pTroot,root);
        return ret;
    }
    void toTree(Tree<T> &ret)
    {
        TreeNode<T> *pTroot = ret.root;
        toTree(root,pTroot);
    }
    void toForest(Forest<T> &ret)
    {
        toForest(root,ret);
    }
};



#endif /* Forest_h */
