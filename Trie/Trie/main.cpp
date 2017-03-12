//
//  main.cpp
//  Trie
//
//  Created by 李博 on 11/03/2017.
//  Copyright © 2017 李博. All rights reserved.
//
#include "Trie.hpp"

int main(int argc, const char * argv[])
{
    Trie<26> A;
    A.insert("abcd");
    A.insert("abef");
    std::cout<<A.search("abcde")<<std::endl;
    return 0;
}
