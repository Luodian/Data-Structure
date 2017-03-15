//
//  main.cpp
//  PriorityQueue
//
//  Created by 李博 on 05/03/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#include "Heap.hpp"
#include "LeftistHeap.hpp"

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
    fstream readFile;
    readFile.open("data.txt",ios::in);
    int temp;
    for (int i = 0; i < 10000000; ++i)
    {
        readFile>>temp;
        datasheet.push_back(temp);
    }
}

clock_t UT_Heap_time_insert(int n)
{
    BinaryHeap<int> A;
    clock_t t = clock();
    for (int i = 0; i < n; ++i)
    {
        A.insert(datasheet[i]);
    }
    t = clock() - t;
    return t;
}

clock_t UT_LHeap_time_insert(int n)
{
    LeftistHeap<int> A;
    clock_t t = clock();
    for (int i = 0; i < n; ++i)
    {
        A.insert(datasheet[i]);
    }
    t = clock() - t;
    return t;
}   

void UT_Heap_Valid()
{
    vector<int> Init_vec;
    for (int i = 1; i <= 10; ++i)
    {
        Init_vec.push_back(i);
    }
    Init_vec.push_back(4);
    Init_vec.push_back(7);
    cout<<"   Validation of Heap\n";
    cout<<"********************************\n";
    cout<<"The init vector is : \n";
    for (int i = 0; i < Init_vec.size(); ++i)
    {
        if (i != Init_vec.size() - 1) 
        {
            cout<<Init_vec[i]<<" ";
        }
        else
        {
            cout<<Init_vec[i]<<"\n";
        }
    }
    BinaryHeap<int> A(Init_vec);
    cout<<"\nThe Answer After Heap Sort: \n";
    while(!A.empty())
    {
        cout<<A.front()<<" ";
        A.pop_front();
    }
    cout<<"\n\n";
}

void UT_LHeap_Valid()
{
    cout<<"\n Validation of LeftistHeap\n";
    cout<<"********************************\n";
    cout<<"The init vector is : \n";

    LeftistHeap<int> A;
    for (int i = 0 ;i < 10; ++i)
    {
        int num = RandomNum(20);
        cout<<num<<" ";
        A.insert(num);
    }

    cout<<"\n\nThe Answer After Heap Sort: \n";
    while(!A.empty())
    {
        cout<<A.front()<<" ";
        A.pop_front();
    }
    cout<<"\n\n";
}

void InsertPerfo()
{
    fstream writeFile;
    cout.setf(ios::fixed,ios::floatfield);
    cout.precision(6);
    writeFile.setf(ios::fixed,ios::floatfield);
    writeFile.precision(6);

    writeFile.open("Heap_insert.txt",ios::out | ios::trunc);
    cout<<"\nTime perfomance of Heap's insert\n";
    cout<<"*******************************************\n\n";
    clock_t delta_t;

    for (int i = 1;i <= 30; ++i)
    {
        int scale = i * 10000;
        delta_t = UT_Heap_time_insert(scale);
        writeFile<<i * 10000<<" "<<((float) delta_t / (CLOCKS_PER_SEC))<<"\n";
        cout<<i * 10000<<" "<<((float) delta_t / (CLOCKS_PER_SEC))<<"\n";
    }
    writeFile.close();

    writeFile.open("LeftHeap_insert.txt",ios::out | ios::trunc);
    cout<<"\nTime perfomance of LeftistHeap's insert\n";
    cout<<"*******************************************\n\n";

    for (int i = 1;i <= 30; ++i)
    {
        int scale = i * 10000;
        delta_t = UT_LHeap_time_insert(scale);
        writeFile<<i * 10000<<" "<<((float) delta_t / (CLOCKS_PER_SEC))<<"\n";
        cout<<i * 10000<<" "<<((float) delta_t / (CLOCKS_PER_SEC))<<"\n";
    }
    writeFile.close();
}

void CombinationPerfo()
{
    cout.setf(ios::fixed,ios::floatfield);
    cout.precision(6);

    BinaryHeap<int> A,B;
    LeftistHeap<int> LA,LB;
    for (int i = 0; i < 10000000; ++i)
    {
        A.insert(datasheet[i]);
        B.insert(datasheet[10000000 - 1 - i]);
    }
    for (int i = 0; i < 10000000; ++i)
    {
        LA.insert(datasheet[i]);
        LB.insert(datasheet[10000000 - 1 - i]);
    }
    clock_t H_t = clock();
    while(!B.empty())
    {
        int front = B.front();
        B.pop_front();
        A.insert(front);
    }
    H_t = clock() - H_t;

    clock_t LH_t = clock();
    LA.merge(LB);
    LH_t = clock() - LH_t;

    cout<<"\nTime Perfomance Test\n";
    cout<<"*********************************************\n";
    cout<<"Heap's merge time          |   "<<(float)(H_t) / (CLOCKS_PER_SEC)<<" s\n";
    cout<<"LeftistHeap's merge time   |   "<<(float)(LH_t) / (CLOCKS_PER_SEC)<<" s\n";
}

void MergeApp(int n)
{
    fstream writeFile;
    cout.setf(ios::fixed,ios::floatfield);
    cout.precision(6);
    writeFile.setf(ios::fixed,ios::floatfield);
    writeFile.precision(6);

    //generate 2 files and merge them;
    cout<<"\n*********************************************\n";
    cout<<"We start merge two files into one......\n";
    // cout<<"\n*********************************************\n";
    int num;
    writeFile.open("merge1.txt",ios::out | ios::trunc);
    for (int i = 0; i < n; ++i)
    {
        num = RandomNum(100);
        writeFile<<num<<" ";
    }
    writeFile.close();

    writeFile.open("merge2.txt",ios::out | ios::trunc);
    for (int i = 0; i < n; ++i)
    {
        int num = RandomNum(100);
        writeFile<<num<<" ";
    }

    writeFile.close();
    LeftistHeap<int> LA,LB;
    fstream readFile;
    readFile.open("merge1.txt",ios::in);
    for (int i = 0; i < n; ++i)
    {
        readFile>>num;
        LA.insert(num);
    }
    readFile.close();

    readFile.open("merge2.txt",ios::in);
    for (int i = 0; i < n; ++i)
    {
        readFile>>num;
        LB.insert(num);
    }
    readFile.close();

    clock_t delta_t = clock();
    LA.merge(LB);
    delta_t = clock() - delta_t;

    writeFile.open("Merged.txt",ios::out | ios::trunc);
    while(!LA.empty())
    {
        writeFile<<LA.front()<<" ";
        LA.pop_front();
    }
    writeFile.close();
    float t = (float)(delta_t) / (float)(CLOCKS_PER_SEC);
    cout<<"\n\nIt has merged |merge1.txt| and |merge2.txt| into |Merged.txt|.\n";
    cout<<"Used time = "<<t<<"s.\n\n";
}

void TopK(int n)
{
    cout<<"Find Top 10 elements in 100000000 elements\n";
    cout<<"*********************************************\n\n";
    fstream readFile;
    readFile.open("/Users/luodian/Desktop/DSA/PriorityQueue/PriorityQueue/data.txt",ios::in);
    BinaryHeap<int> BfTopK;
    BinaryHeap<int> optiTopK;
    int num;
    clock_t BfTopK_T = clock();

    for (int i = 0; i < n; ++i)
    {
        readFile>>num;
        BfTopK.insert(num);
    }

    BfTopK_T = clock() - BfTopK_T;
    cout<<"Top 10 using heap sort\n";
    int BfTopKSize = BfTopK.size();
    for (int i = 0; i < 10; ++i)
    {
        num = BfTopK.front();
        BfTopK.pop_front();
        cout<<num<<" ";
    }
    cout<<"\n\n";

    readFile.seekg(0,readFile.beg);
    clock_t OpTopK_T = clock();
    int Sk = -INF;
    for (int i = 0; i < 10; ++i)
    {
        readFile>>num;
        optiTopK.insert(num);
        Sk = max(num,Sk);
    }

    for (int i = 10; i < n; ++i)
    {
        readFile>>num;
        if (num < Sk)
        {
            optiTopK.insert(num);
            optiTopK.pop_max();
            Sk = optiTopK.find_max();
        }
    }
    OpTopK_T = clock() - OpTopK_T;

    cout<<"Top 10 using maintain a k heap\n";
    int optiTopKSize = optiTopK.size();
    for (int i = 0; i < 10; ++i)
    {
        num = optiTopK.front();
        cout<<num<<" ";
        optiTopK.pop_front();
    }
    cout<<"\n\n";

    cout<<"Comparasion Between two methods\n";
    // cout<<"***********************************\n";
    cout<<"        Method     |  "<<"  Space     |   "<<"   Time   \n";
    cout<<"       Heapsort    |   "<<BfTopKSize<<"   |    "<<(float)(BfTopK_T) / (float)(CLOCKS_PER_SEC)<<"s\n";
    cout<<"  Mantain a k heap |      "<<optiTopKSize<<"      |    "<<(float)(OpTopK_T) / (float)(CLOCKS_PER_SEC)<<"s\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    try
    {
        UT_Heap_Valid();
        UT_LHeap_Valid();
        cout<<"Waiting for reading data.........\n";
        GenerateData();
        cout<<"Data ready.\n";
        CombinationPerfo();
        InsertPerfo();
        MergeApp(10000000);
        TopK(10000000);
    }
    catch(flowType t)
    {
        if (t == Underflow)
        {
            cout<<"Underflow\n";
            exit(-1);
        }
        else
        {
            cout<<"Overflow\n";
            exit(-1);
        }
    }
}
