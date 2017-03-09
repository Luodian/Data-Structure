#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


struct BinaryNode
{   
    char element;
    BinaryNode *left;
    BinaryNode *right;
    BinaryNode(char e = char(),BinaryNode *LT = nullptr,BinaryNode *RT = nullptr):element(e),left(LT),right(RT){}
};

int h_x;
char TreeBuffer[10][200];
int TreeHeight;
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

void Call_try(BinaryNode *root)
{
	h_x = 0;
	TreeHeight = 0;
	memset(TreeBuffer,0,sizeof(TreeBuffer));
	_try(root);
}