//
//  BM.hpp
//  Kmp
//
//  Created by 李博 on 11/03/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#ifndef BM_h
#define BM_h

#include "Header.hpp"

constexpr static int sigma_size = 256;

//预先计算坏字符规则数组
void PreBc(std::vector<int> &BadChar,const std::string &Pattern)
{
    int m = (int)Pattern.size();
    BadChar.resize(sigma_size);
    for (int i = 0; i < sigma_size; ++i)
    {
        BadChar[i] = m;
    }
    for (int i = 0; i < m - 1; ++i)
    {
        BadChar[Pattern[i]] = m - 1 - i;
    }
}

//类似于Kmp的思路，计算后缀匹配表
void Presuffix(const std::string &Pattern, std::vector<int> &suffix)
{
    size_t m = Pattern.size();
    suffix.resize(m);
    int q;
    suffix[m-1] = m;
    for (int i = m - 2; i >= 0; --i)
    {
        q = i;
        while(q >= 0 && Pattern[q] == Pattern[m - 1 - (i - q)])
        {
            q --;
        }
        suffix[i] = i - q;
    }
}

//预先计算好后缀规则数组
void PreGs(const std::string &Pattern,std::vector<int> &Goodsuffix)
{
    std::vector<int> suffixTable;
    Presuffix(Pattern,suffixTable);
    size_t m = Pattern.size();
    Goodsuffix.resize(m);
    for (int i = 0; i < m; ++i)
    {
        Goodsuffix[i] = m;
    }
    int j = 0;
    for (int i = m - 1; i >= 0; --i)
    {
        if (suffixTable[i] == i + 1)
        {
            for (; j < m - 1 - i; ++j)
            {
                if (Goodsuffix[j] == m)
                {
                    Goodsuffix[j] = m - 1 - i;
                }
            }
        }
    }
    for (int i = 0; i < m - 1; ++i)
    {
        Goodsuffix[m - 1 - suffixTable[i]] = m - 1 - i;
    }
}

int BMsearch(const std::string &Template,const std::string &Pattern)
{
    std::vector<int> Goodsuffix;
    std::vector<int> BadChar;
    int n = (int)Template.size();
    int m = (int)Pattern.size();
    PreBc(BadChar,Pattern);
    PreGs(Pattern,Goodsuffix);
    int j = 0;
    int i;
    bool finded = 0;
    while(j <= n - m)
    {
        for (i = m - 1; i >= 0 && Pattern[i] == Template[i + j]; -- i);
        if (i < 0)
        {
            finded = 1;
            return j;
        }
        else
        {
            j += (fmax(Goodsuffix[i], BadChar[Template[i + j] - (m - 1 - i)]));
        }
    }
    return -1;
}


#endif /* BM_h */
