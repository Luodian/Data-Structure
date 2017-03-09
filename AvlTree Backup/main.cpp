//
//  main.cpp
//  AvlTree
//
//  Created by 李博 on 2016/12/8.
//  Copyright © 2016年 李博. All rights reserved.
//

#include <iostream>
#include <map>
#include <cmath>
#include "AvlTree.cpp"
#include "MirrorTree.cpp"

using namespace std;



void TestLeftRotate()
{
    try
    {
        cout<<"****** Now it's a sample of single left rotation ********\n";
        BinarySearchTree<int> Mirror;
        AvlTree TrueType;
        for (int i = 3;i >= 1; --i)
        {
            TrueType.insert(i);
            Mirror.insert(i);
        }
        cout<<"****** Aftre inserted the tree is ******\n\n";
        Mirror.PrintTree();
        cout<<"****** Aftre rotated the tree is *******\n\n";
        TrueType.PrintTree();
    }
    catch(const char *msg)
    {
        cerr<<msg;
    }
}

void TestRightRotate()
{
    try
    {
        cout<<"****** Now it's a sample of single right rotation ********\n";
        BinarySearchTree<int> Mirror;
        AvlTree TrueType;
        for (int i = 1;i <= 3; ++i)
        {
            TrueType.insert(i);
            Mirror.insert(i);
        }
        cout<<"****** Aftre inserted the tree is ******\n\n";
        Mirror.PrintTree();
        cout<<"****** Aftre rotated the tree is *******\n\n";
        TrueType.PrintTree();
    }
    catch(const char *msg)
    {
        cerr<<msg;
    }
}

void TestLRRotate()
{
    try
    {
        cout<<"****** Now it's a sample of double LR rotation ********\n";
        BinarySearchTree<int> Mirror;
        AvlTree TrueType;
        Mirror.insert(4);
        Mirror.insert(1);
        Mirror.insert(8);
        Mirror.insert(5);
        Mirror.insert(6);
        TrueType.insert(4);
        TrueType.insert(1);
        TrueType.insert(8);
        TrueType.insert(5);
        TrueType.insert(6);
        cout<<"****** Aftre inserted the tree is ******\n\n";
        Mirror.PrintTree();
        cout<<"****** Aftre rotated the tree is *******\n\n";
        TrueType.PrintTree();
    }
    catch(const char *msg)
    {
        cerr<<msg;
    }
}


void TestRLRotate()
{
    try
    {
        cout<<"****** Now it's a sample of double RL rotation ********\n";
        BinarySearchTree<int> Mirror;
        AvlTree TrueType;
        Mirror.insert(6);
        Mirror.insert(2);
        Mirror.insert(9);
        // Mirror.insert(1);
        Mirror.insert(4);
        Mirror.insert(3);
        TrueType.insert(6);
        TrueType.insert(2);
        TrueType.insert(9);
        // TrueType.insert(1);
        TrueType.insert(4);
        TrueType.insert(3);
        cout<<"****** Aftre inserted the tree is ******\n\n";
        Mirror.PrintTree();
        cout<<"****** Aftre rotated the tree is *******\n\n";
        TrueType.PrintTree();
    }
    catch(const char *msg)
    {
        cerr<<msg;
    }
}

void TestOfInsert()
{
    cout<<"****** Now it's a sample of serial insertion ********\n";
    try
    {
        AvlTree TrueType;
        // for (int i = 0; i < 10; ++i)
        // {
        //     TrueType.insert(i);
        //     cout<<"******* After inserted "<<i<<" the tree is *******\n\n";
        //     TrueType.PrintTree();
        // }
        TrueType.insert(5);
        TrueType.insert(1);
        TrueType.insert(8);
        TrueType.insert(7);
        TrueType.insert(9);
        // TrueType.insert(6);
        TrueType.PrintTree();

    }
    catch(const char *msg)
    {
        cerr<<msg;
    }
}

void TestOfRemove()
{
    cout<<"********* Now it's a sample of removal **********\n\n";
    try
    {
        AvlTree TrueType;
        for (int i = 0; i < 10; ++i)
        {
            TrueType.insert(i);
        }
        TrueType.PrintTree();
        cout<<"********* After removed 3 the tree is **********\n\n";
        TrueType.remove(3);
        TrueType.PrintTree();
        cout<<"********* After removed 6 the tree is **********\n\n";
        TrueType.remove(6);
        TrueType.PrintTree();
    }
    catch(const char *msg)
    {
        cerr<<msg;
    }
}

int main(int argc, const char * argv[])
{
    // freopen("out.txt","w",stdout);
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    TestOfInsert();
    TestOfRemove();
    TestLeftRotate();
    TestRightRotate();
    TestLRRotate();
    TestRLRotate();
    return 0;
}
