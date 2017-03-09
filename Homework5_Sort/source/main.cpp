//
//  main.cpp
//  Homework5_Sort
//
//  Created by 李博 on 2016/12/19.
//  Copyright © 2016年 李博. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;


void ShowUp(vector<int> &v)
{
    for (int i = 0; i < v.size(); ++i)
    {
        cout<<v[i]<<" ";
        if (!(i%20) && (i != 0))
        {
            cout<<"\n";
        }
    }
    cout<<"\n";
}

void quicksort(vector<int> &vi, int left,int right)
{
    if (left < right)
    {
        int high = right;
        int low = left;
        int key = vi[low];
        while(low < high)
        {
            while(low < high && vi[high] >= key)
            {
                high --;
            }
            if (low < high)
            {
                vi[low] = vi[high];
                low ++;
            }
            else
            {
                break;
            }
            while(low < high && vi[low] <= key)
            {
                low ++;
            }
            if (low < high)
            {
                vi[high] = vi[low];
                high --;
            }
        }
        vi[low] = key;
        quicksort(vi,left,low - 1);
        quicksort(vi,low + 1,right);
    }
}

void Random(vector<int> &vi,int n)
{
    vi.clear();
    int seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(1,100);
    auto dice = bind(distribution,generator);
    for (int i = 0; i < n; ++i)
    {
        vi.push_back(dice());
    }
}

void swap(int &a,int &b)
{
    int c = a;
    a = b;
    b = c;
}

void bubble_sort(vector<int> &vi)
{
    for (int i = 0; i < vi.size() - 1; ++i)
    {
        for (int j = 0; j < vi.size() - i - 1; ++j)
        {
            if (vi[j] > vi[j+1])
            {
                swap(vi[j],vi[j+1]);
            }
        }
    }
}
void TimePerformance(vector<int> &vi,int n)
{
    cout<<"   n = "<<n<<"\n";
    Random(vi,n);
    clock_t t = clock();
    bubble_sort(vi);
    t = clock() - t;
    fstream nout,bubble,quick;
    
    nout.open("n.txt", ios_base::app);
    nout<<n<<"\n";
    
    bubble.open("bubble.txt",ios_base::app);
    bubble<<fixed<<setprecision(6)<<(float(t) / CLOCKS_PER_SEC)<<"\n";
    
    cout<<"   The time of bubble sort in "<<n<<" numbers is : "<<fixed<<setprecision(6)<<(float(t) / CLOCKS_PER_SEC)<<"s\n";
    t = clock();
    quicksort(vi,0,vi.size() - 1);
    t = clock() - t;
    cout<<"   The time of quick sort in "<<n<<" numbers is : "<<fixed<<setprecision(6)<<(float(t) / CLOCKS_PER_SEC)<<"s\n";
    
    quick.open("quick.txt",ios_base::app);
    quick<<fixed<<setprecision(6)<<(float(t) / CLOCKS_PER_SEC)<<"\n";
    cout<<"\n";
    nout.close();
    bubble.close();
    quick.close();
}

int BinarySearch(vector<int> &vi,int key,int left,int right)
{
    while(left < right)
    {
        int mid = left + ((right - left) >> 1);
        if (vi[mid] == key)
        {
            return mid;
        }
        else if (key < vi[mid])
        {
            right = mid;
        }
        else
        {
            left = mid + 1;
        }
    }
    return -1;
}

int Recursion_search(vector<int> &vi,int key,int low,int high)
{
    if(low <= high)
    {
        int mid = (low + high) >> 1;
        if(vi[mid] == key)
        {
            return mid;
        }
        else if(vi[mid] > key)
        {
            return Recursion_search(vi,key,low, mid-1);
        }
        else if(vi[mid] < key)
        {
            return Recursion_search(vi,key,mid+1, high);
        }
        else
        {
            return -1;
        }
    }
    return -1;
}

void CallBsearch(vector<int> &vi,int n)
{
    Random(vi,n);
    quicksort(vi,0,vi.size()-1);
    int seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(0,100);
    auto dice = bind(distribution,generator);
    int element = dice();
    // cout<<element<<endl;
    cout<<"\n  We are going to non_recur_search: "<<element<<" in "<<n<<" numbers array.\n";
    clock_t t = clock();
    int index = BinarySearch(vi,element,0,n);
    t = clock() - t;
    if (index != -1)
    {
        cout<<"   it's position is : "<<index<<" !\n";
    }
    else
    {
        cout<<"  we cannot find this element\n";
    }
    cout<<"  The time of non_recursion search is : "<<fixed<<setprecision(6)<<(float)t/CLOCKS_PER_SEC<<"s\n";
    fstream sequence;
    sequence.open("sequence.txt",ios::app);
    sequence<<n<<"\n";
    fstream timer;
    timer.open("timer.txt",ios::app);
    timer<<fixed<<setprecision(6)<<(float)t/CLOCKS_PER_SEC<<"\n";
    cout<<"\n  We are going to use recursion_search: "<<element<<" in "<<n<<" numbers array.\n";
    t = clock();
    index = Recursion_search(vi,element,0,n);
    t = clock() - t;
    if (index != -1)
    {
        cout<<"   it's position is : "<<index<<" !\n";
    }
    else
    {
        cout<<"  we cannot find this element\n";
    }
    cout<<"  The time of recursion search is : "<<fixed<<setprecision(6)<<(float)t/CLOCKS_PER_SEC<<"s\n";
    fstream recur;
    recur.open("recur.txt",ios::app);
    recur<<fixed<<setprecision(6)<<(float)t/CLOCKS_PER_SEC<<"\n";
    if (index != -1)
    {
        cout<<"   it's position is : "<<index<<" !\n";
    }
    else
    {
        cout<<"  we cannot find this element\n";
    }
}

int main(int argc, const char * argv[])
{
    vector<int> Prepare;
    Random(Prepare,10);
    cout<<"1.Now we have generated 10 random numbers: \n";
    ShowUp(Prepare);
    cout<<"\n";
    // cout<<"\nSorting ......\n";
    cout<<"2.The answer after bubble sort is : \n";
    bubble_sort(Prepare);
    ShowUp(Prepare);
    cout<<"\n";
    cout<<"3.The answer after quick sort is : \n";
    quicksort(Prepare,0,Prepare.size() - 1);
    ShowUp(Prepare);
    cout<<"\n";
    cout<<"4.Now we are testing the time performance \n\n";
    for (int i = 1000; i <= 4000; i += 100)
    {
    	TimePerformance(Prepare,i);
    }
    for (int i = 100000; i <= 500000; i += 10000)
    {
    	CallBsearch(Prepare,i);
    }
    // CallBsearch(Prepare,10000000);
    // Prepare.clear();
    // Prepare.push_back(1);
    // Prepare.push_back(3);
    // Prepare.push_back(6);
    // Prepare.push_back(8);
    // Prepare.push_back(11);
    // ShowUp(Prepare);
    // cout<<Recursion_search(Prepare,3,0,5)<<"\n";
    return 0;
}
