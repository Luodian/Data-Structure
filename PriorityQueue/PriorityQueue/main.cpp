//
//  main.cpp
//  PriorityQueue
//
//  Created by 李博 on 05/03/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

enum flowType{Underflow,Overflow};
constexpr static int maxSize = 124860;

template <typename object>
class BinaryHeap
{
public:
    explicit BinaryHeap(int capacity = 100)
    //必须显式的调用构造函数
    {
        array.clear();
        array.resize(capacity);
    }
    explicit BinaryHeap(const vector<object> &items):array(items.size() + 10),currentSize(items.size())
    {
        for (int i = 0; i < items.size(); ++i)
        {
            array[i+1] = items[i];
        }
        buildHeap();
    }
    bool empty() const
    {
        if (currentSize == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    // const object & finMin() const;
    void push(const object & x)
    {
        if (currentSize > maxSize)
        {
            flowType t = Overflow;
            throw t;
        }
        if (currentSize == array.size() - 1)
        {
            array.resize(array.size() * 2);
        }
        int hole = ++currentSize;
        for (; hole > 1 && x < array[hole / 2]; hole /= 2)
        {
            array[hole] = array[hole / 2];
        }
        array[hole] = x;
    }
    void pop_front()
    {
        if (empty())
        {
            flowType t = Underflow;
            throw t;
        }
        array[1] = array[currentSize --];
        PercolateDown(1);
    }
    object top()
    {
        object minItem;
        if (empty())
        {
            flowType t = Underflow;
            throw t;
        }
        minItem = array[1];
        array[1] = array[currentSize];
        PercolateDown(1);
        return minItem;
    }
    // void makeEmpty();
    
private:
    int currentSize;
    vector<object> array;
    void buildHeap()
    {
        for (int i = currentSize / 2; i > 0; --i)
        {
            PercolateDown(i);
        }
    }
    void PercolateDown(int hole)
    {
        int child;
        object temp = array[hole];
        for (; hole * 2 <= currentSize; hole = child)
        {
            child = hole * 2;
            if (child != currentSize && array[child + 1] < array[child])
            {
                child ++;
            }
            if (array[child] < temp)
            {
                array[hole] = array[child];
            }
            else
            {
                break;
            }
        }
        array[hole] = temp;
    }
};

int main()
{
    try
    {
        BinaryHeap<int> A;
        A.push(1);
        A.push(2);
        int min = A.top();
        cout<<min<<endl;
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
