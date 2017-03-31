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

string getCmprSuffix(const string &path)
{
	string ret;
	ret = path;
	for (int i = ret.size() - 1; i  >= 0; --i)
	{
		if (ret[i] == '.')
		{
			ret = ret.substr(0,i) + ".compress";
			break;
		}
	}
	return ret;
}


int main(int argc, const char * argv[])
{

    cpresser cp;
    string filePath = "/Users/luodian/Desktop/DSA/K-ar Huffman Tree/K-ar Huffman Tree/DATA/N叉哈夫曼树.doc";
    
    cout<<"*****************************************************************************\n";
    cout<<"*                                                                           *\n";
    cout<<"*                   Welcom to the little compress program                   *\n";
    cout<<"*		                                                                    *\n";
    cout<<"*                This program is based on huffman coding theory             *\n";
    cout<<"*                                                                           *\n";
    cout<<"*****************************************************************************\n\n";

    cout<<"The file path is : "<<filePath<<"\n";
    cp.getPath(filePath);
    cp.getMinimalK();
    
    HuffmanTree<4> A,B;
    A.getFilePath(filePath);
    
    cout<<"Compressing........"<<endl;
    A.ComPressFile();
    A.debug("/Users/luodian/Desktop/DSA/K-ar Huffman Tree/K-ar Huffman Tree/DATA/in.debug");
    cout<<std::setprecision(2)<<std::fixed;
    
    cout<<"Compress is done.\n";
    cout<<"The actual compress ratio is "<<A.getRealRatio() * 100<<" %"<<"\n\n";

    cout<<"Decode file from "<<getCmprSuffix(filePath)<<"\n";
    
    cout<<"Decoding......\n";
    
    string CmprSuffxiPath = getCmprSuffix(filePath);
    A.Decode("/Users/luodian/Desktop/DSA/K-ar Huffman Tree/K-ar Huffman Tree/DATA/N叉哈夫曼树.compress");
    
    cout<<"Decode is done.\n";
    return 0;
}
