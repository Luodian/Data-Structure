//
//  main.cpp
//  Threading Plus
//
//  Created by 李博 on 17/03/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#include "Threading.hpp"

using namespace std;

int main(int argc, const char * argv[])
{
    ThreadingTree<char> pre,post;
    // cout<<"**************************************\n";
    // 
    cout<<"Create Tree from preorder: "; 
    string order = "ABDH##I##E##CF#J##G##";

    pre.ThreadingPreTree(order);

    cout<<order<<"\n\n";

    cout<<"The tree is : \n\n";

    pre.Display();


    cout<<"Treading tree to preorder traversal: ";
    pre.ThreadingPreTree(order);
    pre.PreOrder();
    cout<<"\n";

    cout<<"Treading tree to post order traversal: ";
    post.ThreadingPostTree(order);
    post.PostOrder();
    cout<<"\n";

    generator<int> Gen;

    cout<<"Now we generate some big tree: \n\n\n";
    // Gen.genTree(1000,999);

    Gen.readEdge("/Users/luodian/Desktop/good edge.txt");
    cout<<"Treading tree to preorder traversal: \n";
    Gen.genPre();
    cout<<"\n\n\n";
    cout<<"Treading tree to post order traversal: \n";
    Gen.genPost();
    cout<<"\n\n\n";
    return 0;
}
