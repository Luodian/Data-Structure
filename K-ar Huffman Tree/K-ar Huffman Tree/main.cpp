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
   	A.ComPressFile("/Users/luodian/Desktop/DSA/K-ar Huffman Tree/K-ar Huffman Tree/DATA/Prq.cpp");
    A.Decode("/Users/luodian/Desktop/DSA/K-ar Huffman Tree/K-ar Huffman Tree/DATA/Prq.compress");
    A.debug("/Users/luodian/Desktop/DSA/K-ar Huffman Tree/K-ar Huffman Tree/DATA/Raw.debug");
    cout<<A.getRatio()<<endl;
    return 0;
}
