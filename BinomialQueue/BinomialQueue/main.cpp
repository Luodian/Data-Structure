//
//  main.cpp
//  BinomialQueue
//
//  Created by 李博 on 03/04/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#include <iostream>
#include "BinomialQueue.hpp"

int main(int argc, const char * argv[])
{
    BinomialQueue<int> Bq;
    Bq.insert(1);
    Bq.insert(2);
    Bq.insert(3);
    
    BinomialQueue<int> Aq;
    Aq.insert(1);
    Aq.insert(4);
    Aq.insert(6);
    Aq.insert(10);
    
    Aq.insert(1);
    Aq.insert(2);
    Aq.insert(5);
    Aq.insert(3);
    Aq.insert(6);
    Aq.insert(7);
    Aq.insert(8);
    Aq.insert(12);
    Bq.merge(Aq);
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
