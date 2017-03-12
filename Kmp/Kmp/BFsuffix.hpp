//
//  BruteForce.hpp
//  Kmp
//
//  Created by 李博 on 10/03/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#ifndef BruteForce_hpp
#define BruteForce_hpp

#include "Header.hpp"

int Brutesuffix(const std::string &Pattern, const std::string &Template)
{
    int n = (int)Template.size();
    int m = (int)Pattern.size();
    int j = 0;
    int i;
    while(j <= n - m)
    {
        for (i = m - 1; i >= 0 && Pattern[i] == Template[i+j]; --i);
        if (i < 0)
        {
            return j;
        }
        else
        {
            j++;
        }
    }
    return -1;
}

int BrutePrefix(const std::string &Pattern,const std::string &Template)
{
    size_t n = Template.size();
    size_t m = Pattern.size();
    int j = 0;
    for (int i = 0; i <= n - m; ++i)
    {
        for (j = 0; j < m; j ++)
        {
            if (Template[i+j] != Pattern[j])
            {
                break;
            }
        }
        if (j == m)
        {
            return i;
        }
    }
    return -1;
}

#endif /* BruteForce_hpp */
