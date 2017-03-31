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
template<typename T> class generator;

template<typename T>
class BinaryNode
{
    friend class BinaryTree<T>;
    friend class Forest<T>;
    friend class Tree<T>;
    friend class generator<T>;
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
    friend class generator<T>;
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
    friend class generator<T>;
public:
    int TreeNum;
    vector<TreeNode<T> *>  TreeRoots;
    //将森林转化成二叉树，通过调用森林中每个树节点的toBinaryTree()例程完成。
//    void toBinaryTree(vector<BinaryNode<T> *> BinRootArray)
//    {
//        for (int i = 0 ; i < TreeRoots.size(); ++i)
//        {
//            BinaryNode<T> BinRoot = new BinaryNode<T>;
//            toBinaryTree(TreeRoots[i],BinRoot);
//            BinRootArray.push_back(BinRoot);
//        }
//    }
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
    Forest()
    {
        TreeRoots.clear();
        TreeNum = 0;
    }
    void CreateForest(const string &order)
    {
        BinaryTree<T> first(order);
        Forest<T> last;

        first.toForest(last);

        for (int i = 0; i < last.TreeRoots.size(); ++i)
        {
            TreeNode<T> *p = last.TreeRoots[i];
            TreeNode<T> *q = Treecpy(p);
            TreeRoots.push_back(q);
        }
    }
    //将森林转化成二叉树，通过调用森林中每个树节点的toBinaryTree()例程完成。
    void toBinaryTree(vector<BinaryTree<T>> &BinTrees)
    {
        for (int i = 0; i < TreeRoots.size(); ++i)
        {
            BinaryTree<T> instanitionBinaryTree;
            Tree<T> instanitionTree;
            instanitionTree.root = TreeRoots[i];
            instanitionTree.toBinaryTree(instanitionBinaryTree);
            
            BinTrees.push_back(instanitionBinaryTree);
        }
    }
    void Display()
    {
        for (int i = 0; i < TreeRoots.size(); ++i)
        {
            cout<<"The "<<i + 1<<"th tree is :\n";
            Tree<T> A;
            A.root = TreeRoots[i];
            A.Display();
            cout<<"\n";
        }
    }

};

template<typename T>
class Tree
{
    friend class BinaryTree<T>;
    friend class Forest<T>;
    friend class generator<T>;
private:
    TreeNode<T> *root;
    void init(const T &theElement = '*')
    {
        root = new TreeNode<T>(theElement);
    }
    void TreeToBinaryTree(TreeNode<T> *&Troot,BinaryNode<T> *&Broot)
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
            TreeToBinaryTree(Troot->childs[0],Broot->left);
        }
        BinaryNode<T> *oldestBrother = Broot->left;
        for (int i = 1; i < Troot->childs.size(); ++i)
        {   
            TreeToBinaryTree(Troot->childs[i],oldestBrother->right);
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
    void Display(TreeNode<T> *p,int level)
    {
        int size = (int)p->childs.size();
        for (int i = size - 1; i >= size / 2; --i)
        {
            Display(p->childs[i], level + 1);
        }
        for (int j = 0; j < level; j++)
        {
            cout<<"\t";
        }
        cout <<p->element<<endl;
        for (int i = size / 2 - 1; i >= 0; --i)
        {
            Display(p->childs[i], level + 1);
        }
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
        TreeToBinaryTree(root,Broot);
    }
    void Display()
    {
        Display(root,0);
    }
};

template<typename T>
class BinaryTree
{
    friend class Tree<T>;
    friend class Forest<T>;
    friend class generator<T>;
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
    BinaryNode<T> * Treecpy(BinaryNode<T> *root)
    {
        if (root == nullptr)
        {
            return nullptr;
        }
        BinaryNode<T> *cur = new BinaryNode<T>(root->element);
        Treecpy(cur->left);
        Treecpy(cur->right);
        return cur;
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
    BinaryTree(BinaryNode<T> *AnotherRoot)
    {
        root = new BinaryNode<T>;
        root = Treecpy(AnotherRoot);
    }
    ~BinaryTree()
    {
//        makeEmpty(root);
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
        cout<<"The binary tree's graph is : \n\n";
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

constexpr static int maxn = 100005;

template<typename T>
class generator
{
    friend class Tree<T>;
    friend class TreeNode<T>;
    friend class BinaryTree<T>;
    friend class BinaryNode<T>;
    friend class Forest<T>;
private:
    Tree<T> genT;
    BinaryTree<T> genBinT;
    vector<int> G[maxn];
    vector<bool> vis;
    int pre[maxn];
    TreeNode<T> *root;
    void genTree(TreeNode<T> *Troot)
    {
        genT.root = Troot;
        genT.toBinaryTree(genBinT);
    }
public:
    generator()
    {
        root = new TreeNode<T>;
    }
    // void genPre()
    // {
    //     genBinT.PreTraver();
    // }
    // void genPost()
    // {
    //     genPost.PostTraver();
    // }
    void init(int n)
    {
        root = nullptr;
        vis.clear();
        vis.resize(maxn);
        for (int i = 0; i < maxn; ++i)
        {
            G[i].clear();
        }
        for (int i = 0; i < n; ++i)
        {
            pre[i] = i;
        }
    }

    int find(const int &x)
    {
        return pre[x] == x ? x : pre[x] = find(pre[x]);
    }

    //dfs的过程建树
    void dfs(int cur,TreeNode<T> *&curRoot)
    {
        vis[cur] = 1;
        for (int i = 0; i < G[cur].size(); ++i)
        {
            int next = G[cur][i];
            if (vis[next] == 0)
            {
                vis[next] = 1;
                if (curRoot == nullptr)
                {
                    curRoot = new TreeNode<T>;
                }
                curRoot->element = cur;
                TreeNode<T> *p = new TreeNode<T>;
                p->element = next;
                curRoot->childs.push_back(p);
                dfs(next,p);
            }
        }
    }
    
    //m为传入边数的参数
    //n为传入点的参数
    //注意 m <= (n*n)/2;
    void genUfs(int n,int m)
    {
        fstream in;
        in.open("/Users/luodian/Desktop/out.txt",ios::in);
        
        // unsigned int seed = (unsigned int)chrono::system_clock::now().time_since_epoch().count();
        // default_random_engine generator(seed);
        // uniform_int_distribution<int> distribution(1,n);
        // auto dice = bind(distribution,generator);
        set<pair<int,int>> EdgeSet;
        
        EdgeSet.clear();
        // pair<int,int> foo;
        // foo = make_pair(1,2);
        // EdgeSet.insert(foo);
        // while(EdgeSet.size() != m)
        // {
        //     int u = dice();
        //     int v = dice();
            
        //     pair<int,int> foo;
        //     foo = make_pair(u,v);
        //     //没有自环，没有重边
        //     if (u != v && EdgeSet.find(foo) == EdgeSet.end())
        //     {
        //         EdgeSet.insert(foo);
        //     }
        // }
        
        init(maxn);
        // //UFS去环，保证是一颗无根树
        // for (auto itr : EdgeSet)
        // {
        //     int u = itr.first;
        //     int v = itr.second;
        //     int fu = find(u);
        //     int fv = find(v);
        //     if (fv != fu)
        //     {
        //         pre[fu] = fv;
        //         pair<int,int> foo;
        //         foo = make_pair(u,v);
        //         EdgeSet.erase(foo);
        //     }
        // }
        //建立无根树
        int u,v;
        for (int i = 0; i < 8; ++i)
        {
            in>>u>>v;
            cout<<u<<" "<<v<<"\n";
            G[u].push_back(v);
            G[v].push_back(u);
        }
        dfs(1,root);
        in.close();
    }
    void genTree()
    {
        genUfs(5,10);
        genTree(root);
    }
    vector<T> accumulation;
    void getString(BinaryNode<T> *root)
    {
        if (root != nullptr)
        {
            accumulation.push_back(root->element);
            getString(root->left);
            getString(root->right);
        }
        else
        {
            accumulation.push_back("#");
        }
    }
};



#endif /* Forest_h */
