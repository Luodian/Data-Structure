//
//  main.cpp
//  K-ar Huffman Tree
//
//  Created by 李博 on 23/03/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#include "Header.hpp"
#include "KaryHuffman.hpp"
#include "Compresser.hpp"

using namespace std;



int main(int argc, const char * argv[])
{
    cpresser cp;
    string filePath;
    cout<<"*****************************************************************************\n";
    cout<<"*                                                                           *\n";
    cout<<"*                   Welcom to the little compress program                   *\n";
    cout<<"*		                                                                   *\n";
    cout<<"*                This program is based on huffman coding theory             *\n";
    cout<<"*****************************************************************************\n";

    cout<<"The file path is : "<<filePath<<"\n";
    cp.getPath(filePath);
    cp.getMinimalK();
    
    HuffmanTree<8> A;
    A.getFilePath(filePath);

    cout<<
    A.ComPressFile();
    cout<<std::setprecision(2)<<std::fixed;
    cout<<"The real compress ratio is "<<A.getRealRatio() * 100<<" %"<<endl;

    cout<<"Compress is done\n";

    cout<<""
    
    HuffmanTree<8> B;
    B.Decode("/Users/luodian/Desktop/DSA/K-ar Huffman Tree/K-ar Huffman Tree/DATA/第四周讲义及题解.compress");
    return 0;
}
