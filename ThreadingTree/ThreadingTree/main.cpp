//
//  main.cpp
//  ThreadingTree
//
//  Created by 李博 on 2016/11/13.
//  Copyright © 2016年 李博. All rights reserved.
//

//
//  BinaryTree.cpp
//  BinaryTree
//
//  Created by 李博 on 2016/11/11.
//  Copyright © 2016年 李博. All rights reserved.
//

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>

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
        ThreadingNode (const Object &theElement = Object())
        {
            Ltag = Link;
            Rtag = Link;
        }
    };
    void init()
    {
        head = nullptr;
        root = nullptr;
        temp = nullptr;
    }
    ThreadingNode *temp;
    ThreadingNode *head;
    ThreadingNode *root;
    int TreeHeight;
    int h_x;
    char TreeBuffer[10][200];
    void CreateThreading(const string &order,int &&index,ThreadingNode * &p)
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
            CreateThreading(order,move(++index),p->left);
            CreateThreading(order,move(++index),p->right);
        }
    }
    ThreadingNode *prev = nullptr;
    void ThreadingInTree(ThreadingNode *p)
    {
        if (p != nullptr)
        {
            ThreadingInTree(p->left);
            p->Ltag = (p->left) ? Link : Thread;
            p->Rtag = (p->right) ? Link : Thread;
            if (prev != nullptr)
            {
                if (prev->Rtag == Thread)
                {
                    prev->right = p;
                }
                if (p->Ltag == Thread)
                {
                    p->left = prev;
                }
            }
            prev = p;
            ThreadingInTree(p->right);
        }
    }
    //用中序线索化二叉树求结点的先序后继
    //如果左子树不为空，返回左儿子即可
    //如果左子树空，右子树非空，返回右儿子
    //如果左右子树都空，则找到右线索中第一个有右儿子的的结点，返回这个右儿子。
    ThreadingNode * UseIn_FindPreTail(ThreadingNode *p)
    {
        ThreadingNode *q = nullptr;
        if (p->Ltag == Link)
        {
            q = p->left;
        }
        else
        {
            q = p;
            while (q->Rtag == Thread)
            {
                q = q->right;
            }
            q = q->right;
        }
        return q;
    }
    //用中序线索化二叉树求结点的中序后继
    //右子树非空则右子树中的最左结点就是中序后继
    //右子树为空则右线索就是中序后继
    ThreadingNode * UseIn_FindInTail(ThreadingNode *p)
    {
        ThreadingNode *q;
        q = p->right;
        if (p->Rtag == Link)
        {
            while (q->Ltag == Link)
            {
                q = q->left;
            }
        }
        return q;
    }
    //找到p的父亲结点;
    ThreadingNode *father = nullptr;
    void FindParent(ThreadingNode *p,ThreadingNode *root)
    {
        ThreadingNode *r = root;
        if ((r->Rtag == Link && r->right == p) ||(r->Ltag == Link && r->left == p))
        {
            father = r;
        }
        if (r != nullptr && r->Ltag == Link)
        {
            FindParent(p,r->left);
        }
        r = root;
        if (r != nullptr && r->Rtag == Link)
        {
            FindParent(p,r->right);
        }
    }
    //用中序线索二叉树求结点的后序后继
    //记录p的父结点father
    //如果father没有右子树(指r->rtag == thread)或者是r->right != p,此时的r为p的后序后继
    //如果father有右子树，则r右子树进行后序遍历的第一个结点就是后序后继
    ThreadingNode * UseIn_FindPostTail(ThreadingNode *p)
    {
        father = nullptr;
        FindParent(p,root);
        //说明是根节点
        if (father == nullptr)
        {
            return nullptr;
        }
        //如果没有右子树的情况
        if (father->Rtag == Thread || father->right == p)
        {
            return father;
        }
        else
        {
            ThreadingNode *r = father->right;
            while(r->Ltag == Link || r->Rtag == Link)
            {
                if (r->Ltag == Link)
                {
                    r = r->left;
                }
                else if (r->Rtag == Link)
                {
                    r = r->right;
                }
            }
            return r;
        }
        return nullptr;
    }
    ThreadingNode* search(ThreadingNode *root,Object obj)
    {
        if (root == nullptr)
        {
            return nullptr;
        }
        if (root->element == obj)
        {
            return root;
        }
        ThreadingNode*  result = nullptr;
        if (root->Ltag == Link && (result = search(root->left,obj)))
        {
            return result;
        }
        else if (root->Rtag == Link && (result = search(root->right,obj)))
        {
            return result;
        }
        return nullptr;
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
    //    void makeEmpty(ThreadingNode * &t)
    //    {
    //        if (t != nullptr)
    //        {
    //            makeEmpty(t->left);
    //            makeEmpty(t->right);
    //            delete t;
    //        }
    //        t = nullptr; //最后使root指向空指针。
    //    }
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
    void CreateThreading(const string &order)
    {
        CreateThreading(order,0,root);
    }
    void ThreadingInTree()
    {
        prev = nullptr;
        head = new ThreadingNode;
        head->element = '*';
        if (root == nullptr)
        {
            head->left = head;
            head->Ltag = Link;
            head->right = head;
            head->Rtag = Link;
        }
        else
        {
            prev = head;
            head->left = root;
            head->Ltag = Link;
            ThreadingInTree(root);
            prev->right = head;
            prev->Rtag = Thread;
            head->right = head;
        }
    }
    Object UseIn_FindPreTail(const Object &a)
    {
        ThreadingNode *t = nullptr;
        t = UseIn_FindPreTail(search(root,a));
        if (t == nullptr)
        {
            return 0;
        }
        return t->element;
    }
    Object UseIn_FindInTail(const Object &a)
    {
        ThreadingNode *t = nullptr;
        t = UseIn_FindInTail(search(root,a));
        if (t == nullptr)
        {
            return 0;
        }
        return t->element;
    }
    Object UseIn_FindPostTail(const Object &a)
    {
        ThreadingNode *t = nullptr;
        t = UseIn_FindPostTail(search(root,a));
        if (t == nullptr)
        {
            return 0;
        }
        return t->element;
    }
    void PreTraversal()
    {
        ThreadingNode *temp = head;
        do
        {
            temp = UseIn_FindPreTail(temp);
            if (temp != head)
            {
                cout<<temp->element;
            }
        }while (temp != head);
        cout<<"\n";
    }
    void InTraversal()
    {
        ThreadingNode *temp = head;
        do
        {
            temp = UseIn_FindInTail(temp);
            if (temp != head)
            {
                cout<<temp->element;
            }
        }while (temp != head);
        cout<<"\n";
    }
    void PostTraversal()
    {
        ThreadingNode *temp = root;
        // while(temp->Ltag == Link)
        // {
        //     temp = temp->left;
        // }
        // while(temp->Rtag == Link)
        // {
        //     temp = temp->right;
        // }
        while (temp->Ltag == Link || temp->Rtag == Link)
        {
            if (temp->Ltag == Link)
            {
                temp = temp->left;
            }
            else if (temp->Rtag == Link)
            {
                temp = temp->right;
            }
        }
        do
        {
            if (temp != nullptr)
            {
                cout<<temp->element;
            }
            temp = UseIn_FindPostTail(temp);
        }while(temp!=nullptr);
        cout<<"\n";
    }
    // void traverse_level(ThreadingNode *root)  
    // {  
    //     if (root == 0) {  
    //         return;  
    //     }  
    //     int n = 0, depth = 0;
    //     std::queue<ThreadingNode*>  qnodes;  
    //     std::vector<int>       num_nodes; // num_nodes[i] :　第ｉ层结点总数   
          
    //     num_nodes.push_back(1);     // 第0层结点个数  
    //     num_nodes.push_back(0);     
          
    //     for (qnodes.push(root); !qnodes.empty(); qnodes.pop()) 
    //     {  
    //         ThreadingNode *temp = qnodes.front();

    //         std::cout << temp->element << "  ";  
              
    //         if (temp->Ltag == Link) 
    //         {  
    //             qnodes.push(temp->left);  
    //             num_nodes[depth+1]++;  
    //         }  
    //         if (temp->Rtag == Link) {  
    //             qnodes.push(temp->right);  
    //             num_nodes[depth+1]++;  
    //         }  
              
    //         // 当前层最后一个节点   
    //         if (++n == num_nodes[depth]) 
    //         {  
    //             n = 0;  
    //             depth++;  
    //             num_nodes.push_back(0);  
    //             std::cout << std::endl;  
    //         }  
    //     }  
    // }
    // void _try()
    // {
    //     traverse_level(root);
    // }
    void Display()
    {
        _draw(root);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("in.txt","r",stdin);
    // freopen("out.txt","w",stdout);
    ThreadingTree<char> my;
    string order = "ABDH##I##E##CF#J##G##";
    my.CreateThreading(order);
    my.ThreadingInTree();
    cout<<"You have created the threading tree.\n";
    my.Display();
    char Pre,In,Post;
    char ret;
    cout<<"\nPlease input node you want to search:";
    cin>>Pre;
    ret = my.UseIn_FindPreTail(Pre);
    if (ret != 0)
        cout<<"In Preorder the node after "<<Pre<<" is :"<<ret;
    else
    {
        cout<<"You have reached to end\n";
    }
    cout<<"\n";
    cout<<"\nPlease input node you want to search:";
    cin>>In;
    ret = my.UseIn_FindInTail(In);
    if (ret != 0)
        cout<<"In Inorder the node after "<<In<<" is :"<<ret;
    else
    {
        cout<<"You have reached to end\n";
    }
    cout<<"\n";
    cout<<"\nPlease input node you want to search:";
    cin>>Post;
    ret = my.UseIn_FindPostTail(Post);
    if (ret != 0)
        cout<<"In Postorder the node after "<<Post<<" is :"<<ret;
    else
    {
        cout<<"You have reached to end\n";
    }
    cout<<"\n";
    cout<<"\nNow I will show you three different ways of traversal according to inthreads\n";
    cout<<"\nFirst the preorder is: ";
    my.PreTraversal();
    cout<<"\nSecond the inorder is: ";
    my.InTraversal();
    cout<<"\nThird the postorder is: ";
    my.PostTraversal();

    // my.UseThreadCaculatePreorder();
}
// pre:ABDHIECFJG
// in:HDIBEAFJCG
// level:ABCDEFGHIJ
// post:HIDEBJFGCA

