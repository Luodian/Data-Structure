//
//  main.cpp
//  Patricia
//
//  Created by 李博 on 24/05/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#include <iostream>
#include "Header.hpp"
#include "patricia.hpp"

int main(int argc, const char * argv[])
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    Radix::patricia_tree<std::string, int> test;
    test.insert("aa",1);
    test.insert("ff",2);
    test.insert("aaaa",3);
    // test.insert("aaaa",5);
    test.insert("aaa",4);
    test.insert("abc",6);
    test.insert("abd",7);
    test.insert("dafda",19);
    // test.insert("81",21);
    // test.remove("81",232);
    test.insert("afada",232);
    test.remove("afada",232);
    test.find("afada");
    // // test.remove("abc",31);
    // test.find("81");
    // test.f();
    return 0;
}
