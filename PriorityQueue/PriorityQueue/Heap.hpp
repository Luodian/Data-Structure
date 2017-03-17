//
//  Heap.hpp
//  PriorityQueue
//
//  Created by 李博 on 13/03/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#ifndef Heap_h
#define Heap_h

#include "Header.hpp"

using namespace std;

constexpr static int maxSize = 124860000;

template <typename object>
class BinaryHeap
{
public:
    explicit BinaryHeap(int capacity = 20)
    //必须显式的调用构造函数
    {
        currentSize = 0;
        array.clear();
        array.resize(capacity);
    }

    //根据vector<object>数组进行建堆
    explicit BinaryHeap(const vector<object> &items)
    {
        array.clear();
        array.resize(items.size() + 10);
        currentSize = (int)items.size();
        for (int i = 0; i < items.size(); ++i)
        {
            array[i+1] = items[i];
        }
        buildHeap();
    }
    //currentSize是一个private变量，外部不能调用
    //外部通过empty()函数判断树是否为空
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
    
    //插入元素x到最后一个结点，然后依次实现上滤的过程
    void insert(const object & x)
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

    //出队头结点，将最后一个元素放到头结点，执行下滤的操作。
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

    //返回头结点，最大堆或者是最小堆
    object front()
    {
        object minItem;
        if (empty())
        {
            flowType t = Underflow;
            throw t;
        }
        minItem = array[1];
        return minItem;
    }

    //对除叶节点之外的元素执行下滤操作，时间复杂度为O(N);
    void bulidHeap(const vector<object> &items)
    {
        array.resize(items.size() + 10);
        currentSize = items.size();
        array.clear();
        for (int i = 0; i < items.size(); ++i)
        {
            array[i+1] = items[i];
        }
        buildHeap();
    }
    int size()
    {
        return currentSize;
    }

    //为了topK算法写的一个弹出最大堆中最小元素的，很非主流的方法。
    void pop_max()
    {
        int maxElement = -INF;
        int indexMax = 1;
        for (int i = currentSize / 2; i <= currentSize; ++i)
        {
            if (array[i] > maxElement)
            {
                maxElement = array[i];
                indexMax = i;
            }
        }
        swap(array[indexMax],array[currentSize]);
        array[currentSize] = 0;
        currentSize --;
        buildHeap();
    }
    object find_max()
    {
        int maxElement = -INF;
        for (int i = currentSize / 2; i <= currentSize; ++i)
        {
            maxElement = max(maxElement,array[i]);
        }
        return maxElement;
    }
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
            if (child < currentSize && array[child + 1] < array[child])
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
#endif /* Heap_h */
