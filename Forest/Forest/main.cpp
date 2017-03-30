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


int main(int argc, const char * argv[])
{
	string order = "ABDH##I##E##CF#J##G##";
    generator<int> gen;
    gen.genUfs(5, 10);
    
    
	BinaryTree<char> first(order);
	Forest<char> last;
	first.toForest(last);
    vector<BinaryTree<char>> Btrees;
    last.toBinaryTree(Btrees);
    
    cout << "Hello, World!\n";
    return 0;
}
