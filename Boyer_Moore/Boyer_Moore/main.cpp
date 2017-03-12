//
//  main.cpp
//  Boyer_Moore
//
//  Created by 李博 on 11/03/2017.
//  Copyright © 2017 李博. All rights reserved.
//
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

constexpr static int sigma_size = 256;

void PreBc(std::vector<int> &BadChar,const std::string &Pattern)
{
    int m = Pattern.size();
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

void Presuffix(const std::string &Pattern, std::vector<int> &suffix)
{
    int m = Pattern.size();
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

void PreGs(const std::string &Pattern,std::vector<int> &Goodsuffix)
{
    std::vector<int> suffixTable;
    Presuffix(Pattern,suffixTable);
    int m = Pattern.size();
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

int BMsearch(const std::string &Pattern,const std::string &Template)
{
    std::vector<int> suffixTable;
    std::vector<int> Goodsuffix;
    std::vector<int> BadChar;
    int n = Template.size();
    int m = Pattern.size();
    PreBc(BadChar,Pattern);
    PreGs(Pattern,Goodsuffix);
    int j = 0;
    int i;
    while(j <= n - m)
    {
        for (i = m - 1; i >= 0 && Pattern[i] == Template[i + j]; -- i);
        if (i < 0)
        {
            return j;
        }
        else
        {
            j += (fmax(Goodsuffix[i], BadChar[Template[i + j] - (m - 1 - i)]));
        }
    }
    return 0;
}


int main(int argc, const char * argv[])
{
    std::string A = "Here is a simple example";
    std::string B = "example";
    std::cout<<BMsearch(B,A)<<"\n";
    return 0;
}
