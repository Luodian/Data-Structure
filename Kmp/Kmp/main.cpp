//
//  main.cpp
//  Kmp
//
//  Created by 李博 on 05/03/2017.
//  Copyright © 2017 李博. All rights reserved.
//
#include <iostream>
#include "Kmp.cpp"


int main()
{
    std::vector<int> PatchTable;
    std::string Template = "ABABBXAXX";
    std::string Pattern = "AXX";
    kmp(Template,Pattern,PatchTable);
}

