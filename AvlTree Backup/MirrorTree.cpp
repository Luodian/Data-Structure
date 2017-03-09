#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;


template <typename Comparable>
class BinarySearchTree
{
private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;
        BinaryNode(const Comparable &theElement,BinaryNode *LT ,BinaryNode *RT)
        :element(theElement),left(LT),right(RT){}
    };
    BinaryNode *root;
    int h_x;
    char TreeBuffer[20][400];
    int TreeHeight;
    void insert(const Comparable &x,BinaryNode * &t) const
    {
        if(t == nullptr)
        {
            t = new BinaryNode(x,nullptr,nullptr);
        }
        else if (x < t->element)
        {
            insert(x,t->left);
        }
        else if (x > t->element)
        {
            insert(x,t->right);
        }
    }
    void remove(const Comparable &x,BinaryNode * &t) const //指向指针的引用
    {
        if (t == nullptr)
        {
            return;
        }
        if (x < t->element)
        {
            remove(x,t->left);
        }
        else if (x > t->element)
        {
            remove(x,t->right);
        }
        else if (t->left != nullptr && t->right != nullptr)
        {
            t->element = findMin(t->right)->element;
            //查找和删除右子树中最小的结点。
            remove(t->element,t->right);
        }
        else
        {
            BinaryNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }
    }
    //返回最大结点的指针
    BinaryNode *findMin(BinaryNode *t) const
    {
        if (t == nullptr)
        {
            return nullptr;
        }
        if (t->left == nullptr)
        {
            return t;
        }
        return findMin(t->left);
    }
    //非递归实现
    BinaryNode *findMax(BinaryNode *t) const
    {
        if (t != nullptr)
        {
            while (t->right != nullptr)
            {
                t = t->right;
            }
        }
        return t;
    }
    bool contains(const Comparable &x,BinaryNode *t) const
    {
        if (t == nullptr)
        {
            return false;
        }
        else if (x < t->element)
        {
            return contains(x,t->left);
        }
        else if (t->element < x)
        {
            return contains(x,t->right);
        }
        else
        {
            return true;
        }
    }
    //这里也是一个尾递归的使用，因为算法表达式的简明性是以速度的降低为代价的。
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
        int lefth = 0,righth = 0;
        if (p->left != nullptr)
            lefth = GetHeight(p->left);
        if (p->right != nullptr)
            righth = GetHeight(p->right);
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
        TreeBuffer[level][h_x++] = root->element + '0';
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
    void PrintTree(BinaryNode *root)
    {
        h_x = 0;
        TreeHeight = 0;
        memset(TreeBuffer,0,sizeof(TreeBuffer));
        _try(root);
        cout<<"\n";
    }
public:
    BinarySearchTree()
    {
        root = nullptr;
    }
    BinarySearchTree(const BinarySearchTree &rhs)
    {
        root = clone(rhs);
    }
    ~BinarySearchTree()
    {
        makeEmpty();
    }
    const Comparable & findMin() const;
    const Comparable & findMax() const;
    //return if x is found in tree
    bool contains(const Comparable &x) const
    {
        return contains(x,root);
    }
    bool isEmpty() const;
    void PrintTree() const;
    void makeEmpty()
    {
        makeEmpty(root);
    }
    void insert(const Comparable &x)
    {
        insert(x,root);
    }
    void remove(const Comparable &x)
    {
        remove(x,root);
    }
    //deep copy
    const BinarySearchTree & operator = (const BinarySearchTree &rhs)
    {
        if(this != &rhs)
        {
            makeEmpty();
            root = clone(rhs.root);
        }
        return *this;
    }
    BinaryNode *clone(BinaryNode *t) const
    {
        if (t == nullptr)
        {
            return nullptr;
        }
        return new BinaryNode(t->element,clone(t->left),clone(t->right));
    }
    void PrintTree()
    {
        PrintTree(root);
    }
};
