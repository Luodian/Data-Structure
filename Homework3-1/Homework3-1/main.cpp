//
//  main.cpp
//  Homework3-1
//
//  Created by 李博 on 2016/11/21.
//  Copyright © 2016年 李博. All rights reserved.
//

#include <iostream>
#include <stack>
#include <vector>
#include <cstring>
#include <cmath>
#include "Print.cpp"
using namespace std;

//已知一棵树的先序和中序序列，可以唯一的确定一棵二叉树
//不断的比对先序和中序，找出根节点
//再递归找右子树，左子树，
//用栈逆向记录的答案就是后序，根节点总是最后记录
//而且按照先左后右的顺序输出，因为右子树先入栈，所以输出时靠后。

BinaryNode * Pre_In_Post(char *Pre,char *In,int len)
{
	if (len == 0 || Pre == nullptr || In == nullptr)
	{
		return nullptr;
	}
	char rootElement = Pre[0];
	BinaryNode *Node = new BinaryNode;
	Node->element = rootElement;
	Node->right = Node->left = nullptr;
	int i;
	for (i = 0; i < len && In[i] != rootElement; ++i);
	int lenL = i;
	int lenR = len - i - 1;
	if (lenL > 0)
	{
		Node->left = Pre_In_Post(Pre+1,In,lenL);
	}
	if (lenR > 0)
	{
		Node->right = Pre_In_Post(Pre+lenL+1,In+lenL+1,lenR);
	}
	return Node;
}

BinaryNode * In_Post_Pre(char *In,char *Post,int len)
{
   	if (len <= 0 || In == nullptr || Post == nullptr)
   	{
   		return nullptr;
   	}
   	int RootIndex = len - 1;
   	while (Post[len-1] != In[RootIndex])
   	{
   		--RootIndex;
   	}
   	BinaryNode *root = new BinaryNode;
   	root->element = Post[len-1];
   	root->left = In_Post_Pre(In,Post,RootIndex);
   	root->right = In_Post_Pre(In+RootIndex+1,Post + RootIndex,len - RootIndex - 1);
   	return root;
}


int main(int argc, const char * argv[]) 
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

//Test one : test construct tree according pre and in order;
	char pre[] = "DBACFEG";
	char in[] = "ABCDEFG";
    size_t len = strlen(pre);
	BinaryNode * root =  Pre_In_Post(pre,in,(int)len);
	cout<<"We have constructed a tree according to pre and in order\n";
	cout<<"Preorder is: "<<pre<<"\n";
	cout<<"Inorder is: "<<in<<"\n\n"; 
	Call_try(root);

//Test two : test construct tree according in and post order;
	char In2[] = "ADFEGHMZ";
	char Post2[] = "AFEDHZMG";
	size_t Len2 = strlen(In2);
	BinaryNode * Root2 = In_Post_Pre(In2,Post2,(int)Len2);
	cout<<"We have constructed a tree according to in and post order\n";
	cout<<"Inorder is: "<<In2<<"\n";
	cout<<"Postorder is: "<<Post2<<"\n\n"; 
	Call_try(Root2);
    return 0;
}

