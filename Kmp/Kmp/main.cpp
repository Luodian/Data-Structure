//
//  main.cpp
//  Kmp
//
//  Created by 李博 on 05/03/2017.
//  Copyright © 2017 李博. All rights reserved.
//
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

void makePatchTable(const string &pattern,vector<int> &PatchTable)
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

bool kmp(const string &Template,const string &Pattern, vector<int> &PatchTable)
{
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
            cout<<"Finded in :"<<(i - m + 1)<<"\n";
            finded = 1;
        }
    }
    if (finded == 0)
    {
        cout<<"Can't find this Pattern\n";
        return 0;
    }
    else
    {
        return 1;
    }
}

string randomSome()
{
    
}

int main()
{
    vector<int> PatchTable;
    string Template = "ABABBXAXX";
    string Pattern = "AXX";
    kmp(Template,Pattern,PatchTable);
}

