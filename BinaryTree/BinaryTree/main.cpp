//
//  BinaryTree.cpp
//  BinaryTree
//
//  Created by 李博 on 2016/11/11.
//  Copyright © 2016年 李博. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <cmath>

using namespace std;
template <typename Object>
class BinaryTree
{
private:
    //二叉链表表示
    struct BinaryNode
    {
        Object element;
        BinaryNode *left;
        BinaryNode *right;
        BinaryNode (const Object &theElement = Object(),BinaryNode *LT = nullptr,BinaryNode *RT = nullptr)
        :element(theElement),left(LT),right(RT)
        {
        }
    };
    void init()
    {
        Maxsize = 10000;
        CountNodes = 0;
        root = new BinaryNode;
        TreeInVector.reserve(Maxsize);
        TreeInVector.clear();
        for (int i = 0; i < 5; ++i)
        {
            StoreOrder[i].clear();
        }
    }
    BinaryNode *root;
    //数组表示
    int Maxsize;
    int CountNodes;
    int TreeHeight;
    char TreeBuffer[10][200];
    int h_x;
    vector<Object> TreeInVector;
    //用来保存
    //0-先序
    //1-中序
    //2-后序
    //3-层序
    vector<Object> StoreOrder[5];
    void CreateArrayTree(const string &order,int &&index,int &&StoreIndex)
    {
        if (order[index] == '#')
        {
            TreeInVector[StoreIndex] = '^';
            return;
        }
        TreeInVector[StoreIndex] = order[index];
        CreateArrayTree(order,move(++index),move(StoreIndex * 2));
        CreateArrayTree(order,move(++index),move(StoreIndex * 2 + 1));
    }
    void CreateBTree(const string &order,int &&index,BinaryNode * &t)
    {
        if (order[index] == '#')
        {
            t = nullptr;
            return;
        }
        CountNodes ++;
        t = new BinaryNode(order[index],nullptr,nullptr);
        CreateBTree(order,move(++index),t->left);
        CreateBTree(order,move(++index),t->right);
    }
    void Bread_First_Create(const string &order,BinaryNode * &root)
    {
        BinaryNode *Q[1000];
        int front = 1,rear = 0;
        root = nullptr;
        for (int i = 0; i < order.size(); ++i)
        {
            BinaryNode *p = nullptr;
            if (order[i] != '#')
            {
                p = new BinaryNode;
                p->element = order[i];
                p->left = nullptr;
                p->right = nullptr;
            }
            rear ++;
            Q[rear] = p;
            if (rear == 1)
            {
                root = p;
            }
            else
            {
                if (p != nullptr && Q[front] != nullptr)
                {
                    if (rear % 2 == 0)
                    {
                        Q[front]->left = p;
                    }
                    else
                    {
                        Q[front]->right = p;
                    }
                }
                if (rear % 2 == 1)
                {
                    front ++;
                }
            }
        }
    }
    void Pre_Traversal(const BinaryNode *t)
    {
        if (t == nullptr)
        {
            return;
        }
        cout<<t->element;
        StoreOrder[0].push_back(t->element);
        Pre_Traversal(t->left);
        Pre_Traversal(t->right);
    }
    void Pre_NonRecur(BinaryNode *root)
    {
        BinaryNode *p = root;
        stack<BinaryNode *> s;
        while (!s.empty() || p != nullptr)
        {
            while(p != nullptr)
            {
                cout<<p->element;
                s.push(p);
                p = p->left;
            }
            if (!s.empty())
            {
                p = s.top();
                s.pop();
                p = p->right;
            }
        }
    }
    void In_NonRecur(BinaryNode *root)
    {
        BinaryNode *p = root;
        stack<BinaryNode *> s;
        while (!s.empty() || p != nullptr)
        {
            while (p != nullptr)
            {
                s.push(p);
                p = p->left;
            }
            if (!s.empty())
            {
                p = s.top();
                s.pop();
                cout<<p->element;
                p = p->right;
            }
        }
    }
    void Post_NonRecur(BinaryNode *root)
    {
        BinaryNode  *p = root;
        stack<BinaryNode *> s;
        s.push(p);
        s.push(p);
        while (!s.empty())
        {
            p = s.top();
            s.pop();
            if (!s.empty() && p == s.top())
            {
                if (p->right != nullptr)
                {
                    s.push(p->right);
                    s.push(p->right);
                }
                if (p->left != nullptr)
                {
                    s.push(p->left);
                    s.push(p->left);
                }
            }
            else
            {
                cout<<p->element;
            }
        }
    }
    void In_Traversal(const BinaryNode *t)
    {
        if (t == nullptr)
        {
            return;
        }
        In_Traversal(t->left);
        cout<<t->element;
        StoreOrder[1].push_back(t->element);
        In_Traversal(t->right);
    }
    void Post_Traversal(const BinaryNode *t)
    {
        if (t == nullptr)
        {
            return;
        }
        Post_Traversal(t->left);
        Post_Traversal(t->right);
        cout<<t->element;
        StoreOrder[2].push_back(t->element);
    }
    void Breadth_First(BinaryNode *root)
    {
        queue<BinaryNode *> NodeInQueue;
        NodeInQueue.push(root);
        while (!NodeInQueue.empty())
        {
            BinaryNode *Cur = NodeInQueue.front();
            NodeInQueue.pop();
            cout<<Cur->element;
            StoreOrder[3].push_back(Cur->element);
            if (Cur->left != nullptr)
            {
                NodeInQueue.push(Cur->left);
            }
            if (Cur->right != nullptr)
            {
                NodeInQueue.push(Cur->right);
            }
        }
    }
    void makeEmpty(BinaryNode * &t)
    {
        if (t != nullptr)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr; //最后使root指向空指针。
    }
    int GetHeight(BinaryNode *p)
    {
        if (p == nullptr)
        {
            return 0;
        }
        int lefth = GetHeight(p->left);
        int righth = GetHeight(p->right);
        return max(lefth,righth) + 1;
    }
    void prework(BinaryNode *root,int level)
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
    void _try(BinaryNode *root)
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
    BinaryTree()
    {
        init();
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
    void CreateBTree(const string &order)
    {
        CountNodes = 0;
        CreateBTree(order,0,root);
    }
    void CreateArrayTree(const string &order)
    {
        CreateArrayTree(order,0,1);
    }
    void Pre_Traversal()
    {
        Pre_Traversal(root);
        cout<<"\n";
    }
    void In_Traversal()
    {
        In_Traversal(root);
        cout<<"\n";
    }
    void Post_Traversal()
    {
        Post_Traversal(root);
        cout<<"\n";
    }
    void Pre_NonRecur()
    {
        Pre_NonRecur(root);
        cout<<"\n";
    }
    void In_NonRecur()
    {
        In_NonRecur(root);
        cout<<"\n";
    }
    void Post_NonRecur()
    {
        Post_NonRecur(root);
        cout<<"\n";
    }
    void Breadth_First()
    {
        Breadth_First(root);
        cout<<"\n";
    }
    void ArrayTravel()
    {
        for (int i = 1; TreeInVector[i] != 0; ++i)
        {
           if (TreeInVector[i] != '^')
               cout<<TreeInVector[i];
        }
        cout<<"\n";
    }
    void BFSCreateTree(const string &order)
    {
        Bread_First_Create(order,root);
    }
    void Display()
    {
        h_x = 0;
        TreeHeight = 0;
        _try(root);
    }
};

int main(int argc, const char * argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("out.txt","w",stdout);
    BinaryTree<char> my;
    cout<<"Now we uses two ways to construct tree: \n\n";
    string order = "A#BC#D###";
    my.CreateBTree(order);
    my.Display();
    cout<<"\tFirstly we constructed a tree according full preorder: \n";
    cout<<"\t"<<order<<"\n\n";

    cout<<"\tTraversal with recursion\n";
    cout<<"\t********************************\n";
    cout<<"\tPreorder Traversal: ";
    my.Pre_Traversal();
    cout<<"\tInorder Traversal: ";
    my.In_Traversal();
    cout<<"\tPostorder Traversal: ";
    my.Post_Traversal();
    cout<<"\tLevelorder Traversal: ";
    my.Breadth_First();

    cout<<"\n\tTraversal without recursion\n";
    cout<<"\t********************************\n";
    cout<<"\tPreorder Traversal: ";
    my.Pre_NonRecur();
    cout<<"\tInorder Traversal: ";
    my.In_NonRecur();
    cout<<"\tPostorder Traversal: ";
    my.Post_NonRecur();


    my.makeEmpty();
    //清空整棵树
    string levelorder = "ABCDEFGHI###J##";
    my.BFSCreateTree(levelorder);
    cout<<"\tThen we constructed a tree according full preorder: \n";
    cout<<"\t"<<levelorder<<"\n\n";
    cout<<"\n\tTraversal with recursion\n";
    cout<<"\t********************************\n";
    cout<<"\tPreorder Traversal: ";
    my.Pre_Traversal();
    cout<<"\tInorder Traversal: ";
    my.In_Traversal();
    cout<<"\tPostorder Traversal: ";
    my.Post_Traversal();
    cout<<"\tLevelorder Traversal: ";
    my.Breadth_First();

    cout<<"\n\tTraversal without recursion\n";
    cout<<"\t********************************\n";
    cout<<"\tPreorder Traversal: ";
    my.Pre_NonRecur();
    cout<<"\tInorder Traversal: ";
    my.In_NonRecur();
    cout<<"\tPostorder Traversal: ";
    my.Post_NonRecur();
    return 0;
}



