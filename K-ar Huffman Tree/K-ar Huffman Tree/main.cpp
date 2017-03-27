//
//  main.cpp
//  K-ar Huffman Tree
//
//  Created by 李博 on 23/03/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#include "Header.hpp"
#include "KaryHuffman.hpp"

using namespace std;


int main(int argc, const char * argv[])
{
    HuffmanTree<4> A;
    A.Encode("LUODIANDIANDIAN");
    A.getRootSize();
    std::cout << "Hello, World!\n";
    return 0;
}
