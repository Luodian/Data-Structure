//
//  main.cpp
//  SkipList
//
//  Created by 李博 on 09/03/2017.
//  Copyright © 2017 李博. All rights reserved.
//
#include <iostream>
#include <fstream>
#include "SkipList.cpp"
#include "Avl.cpp"

using namespace std;

vector<int> datasheet;

int RandomNum(int n)
{
    unsigned int seed = (unsigned int)chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(1,n);
    
    auto dice = bind(distribution,generator);
    int ret = dice();
    return ret;
}

void GenerateData()
{
    for (int i = 0; i < 10000000; ++i)
    {
        datasheet.push_back(i);
    }
    return;
}
/*
 Function: test the time performance of skiplist's find operation
 Args: scale(n)
 Return: tik of machine(k)
 Expect log(n)'s performance
 */
clock_t sKipList_find(int n)
{
    skipList<int> test;
    clock_t t = clock();
    for (int i = 0; i < n; ++i)
    {
        test.insert(datasheet[i]);
    }
    t = clock() - t;
    return t;
}

/*
 Function: test the time performance of skiplist's insert operation
 Args: scale(n)
 Return: tik of machine(k)
 Except log(n) performance
 */

clock_t sKipList_insert(int n)
{
    skipList<int> test;
    for (int i = 0; i < n; ++i)
    {
        test.insert(datasheet[i]);
    }
    clock_t t = clock();
    for (int i = 1; i <= 10000; ++i)
    {
        int temp = RandomNum(n);
        test.insert(temp);
    }
    t = clock() - t;
    return t;
}

/*
 Function: test the time performance of list's insert operation
 Args: scale(n)
 Return: tik of machine(k)
 Except n performance
 */

clock_t List_insert(int n)
{
    list<int> test;
    list<int> :: iterator itr;
    for (int i = 0; i < n; ++i)
    {
        test.push_back(datasheet[i]);
    }
    clock_t t = clock();
    for (int i = 0; i < 10000; ++i)
    {
        int temp = RandomNum(n);
        if (test.size() == 0)
        {
            test.push_back(temp);
        }
        else
        {
            // 3 6 9 10
            // ^
            // 5
            bool inserted = 0;
            for (itr = test.begin(); itr != test.end(); itr++)
            {
                if (*(itr) > temp)
                {
                    test.insert(itr,temp);
                    inserted = 1;
                    break;
                }
            }
            if (!inserted)
            {
                test.push_back(temp);
            }
        }
    }
    t = clock() - t;
    return t;
}

clock_t Avl_insert(int n)
{
    AvlTree test;
    for (int i = 0; i < n; ++i)
    {
        test.insert(datasheet[i]);
    }
    clock_t t = clock();
    for (int i = 1; i <= 10000; ++i)
    {
        int temp = RandomNum(n);
        test.insert(temp);
    }
    t = clock() - t;
    return t;
}


void TimePerfo()
{
    //Prework
    fstream writeFile;
    writeFile.open("SkipList.txt",ios::out | ios::trunc);

    //set IO stream format
    cout.setf(ios::fixed,ios::floatfield);
    cout.precision(6);

    writeFile.setf(ios::fixed,ios::floatfield);
    writeFile.precision(6);
    clock_t delta_t;
    GenerateData();

    cout<<"\nTime perfomance of skip list's insert\n";
    cout<<"*******************************************\n\n";

    for (int i = 100; i <= 1000; i += 10)
    {
        delta_t = sKipList_insert(i * 100);
        writeFile<<i * 100<<" "<<((float) delta_t / (CLOCKS_PER_SEC))<<"\n";
        cout<<i * 100<<" "<<((float) delta_t / (CLOCKS_PER_SEC))<<"\n";
    }
    writeFile.close();

    writeFile.open("List.txt",ios::out | ios::trunc);
    cout<<"\nTime perfomance of list's insert\n";
    cout<<"*******************************************\n\n";

    for (int i = 100; i <= 1000; i += 10)
    {
        delta_t = List_insert(i * 100);
        writeFile<<i * 100<<" "<<((float) delta_t / (CLOCKS_PER_SEC))<<"\n";
        cout<<i * 100<<" "<<((float) delta_t / (CLOCKS_PER_SEC))<<"\n";
    }

    writeFile.close();
    writeFile.open("Avl.txt",ios::out | ios::trunc);
    cout<<"\nTime perfomance of Avltree's insert\n";
    cout<<"*******************************************\n\n";
    for (int i = 100; i <= 1000; i += 10)
    {
        delta_t = Avl_insert(i * 100);
        writeFile<<i * 100<<" "<<((float) delta_t / (CLOCKS_PER_SEC))<<"\n";
        cout<<i * 100<<" "<<((float) delta_t / (CLOCKS_PER_SEC))<<"\n";
    }
    writeFile.close();
}

void SimpleTest()
{
    skipList<int> test;
    for (int i = 1; i <= 9; ++i)
    {
        test.insert(i);
    }
    test.debug();
}

int main()
{
    //Accelerate IO Stream
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    SimpleTest();
    TimePerfo();
    return 0;
}

