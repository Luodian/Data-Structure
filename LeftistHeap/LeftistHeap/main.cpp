//
//  main.cpp
//  LeftistHeap
//
//  Created by 李博 on 13/03/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#include "Leftist.hpp"

int main()
{
    LeftistHeap<int> A;
    for (int i = 1; i <= 10; ++i)
    {
        A.insert(i);
    }
}
