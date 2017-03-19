//
//  main.cpp
//  Threading Plus
//
//  Created by 李博 on 17/03/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#include "Threading.hpp"

int main(int argc, const char * argv[])
{
    ThreadingTree<char> my;
    string order = "ABDH##I##E##CF#J##G##";
    // my.CreateThreading(order);
    my.ThreadingPostTree(order);
    
    return 0;
}
