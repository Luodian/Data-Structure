//
//  Kmp.hpp
//  Kmp
//
//  Created by 李博 on 10/03/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#ifndef Kmp_hpp
#define Kmp_hpp

#include "Header.hpp"

void makePatchTable(const std::string &pattern,std::vector<int> &PatchTable)
{
    int m = (int)pattern.size();
    PatchTable.resize(m);
    PatchTable[0] = 0;
    int k = 0;
    // i is index of suffix;
    // k is index of prefix;
    for (int i = 1; i < m; ++i)
    {
        while(k > 0 && pattern[i] != pattern[k])
        {
            k = pattern[k-1];
        }
        if (pattern[i] == pattern[k])
        {
            k ++;
        }
        PatchTable[i] = k;
    }
}

int kmp(const std::string &Template,const std::string &Pattern)
{
    std::vector<int> PatchTable;
    int n = (int)Template.size();
    int m = (int)Pattern.size();
    makePatchTable(Pattern, PatchTable);
    bool finded = 0;
    int q = 0;
    //i is index of Template
    //j is index of Pattern
    for (int i = 0; i < n; ++i)
    {
        while(q > 0 && Pattern[q] != Template[i])
        {
            q = PatchTable[q-1];
        }
        if (Pattern[q] == Template[i])
        {
            q ++;
        }
        if (q == m)
        {
            return (i - m + 1);
            finded = 1;
        }
    }
    return -1;
}

#endif /* Kmp_hpp */
