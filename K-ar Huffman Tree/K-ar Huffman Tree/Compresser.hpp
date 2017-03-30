//
//  Compresser.hpp
//  K-ar Huffman Tree
//
//  Created by 李博 on 29/03/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#ifndef Compresser_h
#define Compresser_h
#include "Header.hpp"
#include "KaryHuffman.hpp"

class cpresser
{
private:
    string filePath;
    
    HuffmanTree<2> A;
    HuffmanTree<4> B;
    HuffmanTree<8> C;
    HuffmanTree<16> D;
    HuffmanTree<32> E;
    HuffmanTree<64> F;
    double minRatio;
    int minK;
public:
    void getPath(const string &path)
    {
        filePath = path;
    }
    void getMinimalK()
    {
        minRatio = 1;
        double curRatio;
        A.getFilePath(filePath);
        curRatio = A.getEstimateRatio();
        if (curRatio < minRatio && curRatio != 0)
        {
           minRatio = curRatio;
           minK = 2;
        }

        B.getFilePath(filePath);
        curRatio = B.getEstimateRatio();
        if (curRatio < minRatio && curRatio != 0)
        {
           minRatio = curRatio;
           minK = 4;
        }
        
        C.getFilePath(filePath);
        curRatio = C.getEstimateRatio();
        if (curRatio < minRatio && curRatio != 0)
        {
           minRatio = curRatio;
           minK = 8;
        }
        D.getFilePath(filePath);
        curRatio = D.getEstimateRatio();
        if (curRatio < minRatio && curRatio != 0)
        {
           minRatio = curRatio;
           minK = 16;
        }
        E.getFilePath(filePath);
        curRatio = E.getEstimateRatio();
        if (curRatio < minRatio && curRatio != 0)
        {
           minRatio = curRatio;
           minK = 32;
        }
        F.getFilePath(filePath);
        curRatio = F.getEstimateRatio();
        if (curRatio < minRatio && curRatio != 0)
        {
            minRatio = curRatio;
            minK = 64;
        }
        cout<<"The minimal k of this file is "<<minK<<endl;
        cout<<std::setprecision(2)<<std::fixed;
        cout<<"The estimate compress ratio is "<<minRatio * 100<<" %"<<endl;
    }
};

#endif /* Compresser_h */
