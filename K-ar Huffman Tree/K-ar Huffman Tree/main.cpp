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
    string filePath = "/Users/luodian/Desktop/DSA/K-ar Huffman Tree/K-ar Huffman Tree/DATA/Prq.exec";
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
    
    HuffmanTree<8> A;
    A.getFilePath(filePath);

    A.ComPressFile();
    cout<<std::setprecision(2)<<std::fixed;
    cout<<"The real compress ratio is "<<A.getRealRatio() * 100<<" %"<<endl;

    cout<<"Compress is done\n";

    
    HuffmanTree<8> B;
    B.Decode(getCmprSuffix(filePath));


    return 0;
}
