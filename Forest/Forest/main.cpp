//
//  main.cpp
//  Forest
//
//  Created by 李博 on 20/03/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#include "Forest.hpp"
// #include "BinaryTree.hpp"

using namespace std;

// void BinaryTree2Tree(BinaryNode *BinaryRoot,TreeNode * &TreeRoot)
// {

// }
// void Tree2Forest();
// void Forest2Tree();
// void Tree2BinaryTree();

// void Transform()

// void ConverToTree(BinaryNode *BinaryRoot,TreeNode *&TreeRoot)
// {
//     //如果没有左儿子则返回
//     if (root->left == nullptr)
//     {
//         return;
//     }
//     TreeNode *Forest_p = TreeRoot;
//     BinaryNode *BTree_p = BinaryRoot->left;

//     //选取最左儿子，长子作为当前的根节点。
//     Forest_p->childs.push_back(new TreeNode(BTree_p->element));

//     ConverToTree(BinaryRoot->left,TreeRoot->childs[0]);
// }

void B2F_small()
{
    string order = "ABDH##I##E##CF#J##G##";
    // generator<int> gen;
    // gen.genTree();
    
    BinaryTree<char> first(order);
    first.Display();

    Forest<char> last;
    first.toForest(last);
    vector<BinaryTree<char>> Btrees;

    
    last.toBinaryTree(Btrees);
    last.Display();
}

void F2B_small()
{
    string order = "ABDH##I##E##CF#J##G##";
    Forest<char> tempForest;
    tempForest.CreateForest(order);
    tempForest.Display();
    
    vector<BinaryTree<char>> Btrees;
    tempForest.toBinaryTree(Btrees);
    for (int i = 0; i < Btrees.size(); ++i)
    {
        Btrees[i].Display();
    }
//    tempForest.Display();
}

int main(int argc, const char * argv[])
{
    cout<<"********************************************************************\n";
    cout<<"*                                                                  *\n";
    cout<<"*     Here is a small program to transfer binary tree and forest   *\n";
    cout<<"*                                                                  *\n";
    cout<<"********************************************************************\n";

    cout<<"\n\n\n         Here is a transformation from binary tree to forest\n";
    cout<<"********************************************************************\n\n\n";
    B2F_small();
    
    cout<<"\n\n           Here is a transformation from forest to binary tree\n";
    cout<<"********************************************************************\n\n\n";
    F2B_small();
    return 0;
}
