//
//  main.cpp
//  Huffman
//
//  Created by 李博 on 2016/11/22.
//  Copyright © 2016年 李博. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>

using namespace std;

struct HuffNode
{
	int weight;
	char node_element;
	int code;
	HuffNode* left;
	HuffNode* right;
	HuffNode(int w = 0)
	{
		weight = w;
		left = nullptr;
		right = nullptr;
		node_element  = '*';
		code = 0;
	}
};

class Compare
{
public:
	bool operator() (const HuffNode *lhs,const HuffNode *rhs) const
	{
		return lhs->weight > rhs->weight;
	}
};
// priority_queue <pair<char,int> , vector<pair<char,int>> , Compare> Piiq;

priority_queue<HuffNode*,vector<HuffNode * >,Compare> weight_heap;
vector<pair<char,int>> FrqArray;
map<char,int> code_map;

void init(int n)
{
	while(!weight_heap.empty())
	{
		weight_heap.pop();
	}
	FrqArray.clear();
	code_map.clear();
}

void ExertOnBuffer(string &buffer)
{
	for (int i = 0; i < buffer.size(); ++i)
	{
		if (buffer[i] == '_')
		{
			buffer[i] = ' ';
		}
		if (buffer[i] == ' ')
		{
			buffer[i] = '_';
		}
	}
}

HuffNode * Construct(vector<pair<char,int>> &Buf)
{
	int n = (int)Buf.size();
	for (int i = 0 ; i < n; ++i)
	{
		HuffNode *cur = new HuffNode;
		cur->weight = Buf[i].second;
		cur->node_element = Buf[i].first;
		weight_heap.emplace(cur);
	}
	HuffNode *root = nullptr;
	while(weight_heap.size() != 1)
	{
		HuffNode *p1,*p2,*parent;
		parent = new HuffNode;
		p1 = weight_heap.top();
		weight_heap.pop();
		p2 = weight_heap.top();
		weight_heap.pop();
		parent->left = p1;
		parent->right = p2;
        parent->weight = p1->weight+p2->weight;
		weight_heap.emplace(parent);
	}
	root = weight_heap.top();
	return root;
}

void Encode(HuffNode *root,int code)
{
	if (root == nullptr)
	{
		return;
	}
	root->code = code;
	if(root->right == nullptr)
	{
		code_map[root->node_element] = code;
	}
	Encode(root->left,code<<1);
	Encode(root->right,(code<<1)+1);
}

string dec2bin(int n)
{
	string ret;
	while(n != 0)
	{
		if (n & 1)
		{
			ret.push_back('1');
		}
		else
		{
			ret.push_back('0');
		}
		n = n >> 1;
	}
	//从树根往右为1，往左为0;
	for (int i = 0;i < ret.size() / 2; ++i)
	{
		swap(ret[i],ret[ret.size() - i - 1]);
	}
	return ret;
}

//将结点对应的字符如f的code = 10转换为1010这种可视化程度更高的编码。

void GetCode(map<char,string> &ret)
{
    ret.clear();
    map<char,int> :: iterator IT;
    for (IT = code_map.begin(); IT != code_map.end(); ++IT)
    {
    	string str_code = dec2bin((*IT).second);
    	ret.emplace((*IT).first,str_code);
    }
}

void Frequency(const string &buffer)
{
    int FrqTemp[300];
    memset(FrqTemp,0,sizeof(FrqTemp));
    FrqArray.clear();
	for (int i = 0; i < buffer.length(); ++i)
	{
		FrqTemp[(int)buffer[i]] ++;
	}
	for (int i = 0 ; i < 300; ++i)
	{
		if (FrqTemp[i] != 0)
		{
			pair<char,int> foo;
			foo = make_pair((char)(i),FrqTemp[i]);
			FrqArray.push_back(foo);
		}
	}
}

unsigned char Str2Bin(string str)  
{  
    int a = atoi(str.c_str());  
    int b = 1;  
    int ans = 0;  
    while(a != 0)  
    {  
        ans += a%10 * b;  
        b *= 2;  
        a /= 10;  
    }
    return (unsigned char)ans;  
}

void display(map<char,string> &buf)
{
    map<char,string>::iterator IT;
    int i = 1;
    for (IT = buf.begin(); IT != buf.end(); ++IT)
    {
    	++i;
    	if (i % 2 == 0)
    	{
    		cout<<"\n";
    	}
        cout<<"\t"<<(*IT).first<<" : "<<(*IT).second<<"\t\t";
    }
    cout<<"\n";
}

void display2(map<string,char> &buf)
{
	map<string,char>::iterator IT;
    for (IT = buf.begin(); IT != buf.end(); ++IT)
    {
        cout<<(*IT).first<<" "<<(*IT).second<<"\n";
    }
}

void ComPress(map<char,string> &CodePair,const string &text)
{	
	fstream osout;
	osout.open("out.dat",ios::out | ios::binary);
	fstream ou2Bin("out.bin",ios::out | ios::binary);
	if (!osout.is_open())
	{
		throw "Error Filename";
	}
	string buffer;
	buffer.clear();
	map<char,string>::iterator IT;
	for (IT = CodePair.begin(); IT != CodePair.end(); ++IT)
	{
		char char_code = (*IT).first;
		string code_str = (*IT).second;
		osout<<char_code<<code_str;
	}
	osout<<" ";
	for (int i = 0; i < text.size(); ++i)
	{
		string code_str = CodePair[text[i]];
		ou2Bin<<code_str;
		for (int j = 0; j < code_str.size(); ++j)
		{
			if (buffer.size() != 7)
			{
				buffer.push_back(code_str[j]);
			}
			else
			{
                j --;
				char PushToFile = Str2Bin(buffer);
				osout<<PushToFile;
				buffer.clear();
			}
		}
	}
	if (!buffer.empty())
	{
		char PushToFile = Str2Bin(buffer);
		osout<<PushToFile;
	}
	ou2Bin.close();
	osout.close();
}

bool isCode(const char &element)
{
	if (element == '1' || element == '0')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Decoder(string filename,map<char,string> &CodePair)
{
	//通过读in文件建立CodePair
    fstream in;
    in.open(filename,ios::in | ios::binary);
	if (!in.is_open())
	{
		throw "Error Filename";
	}
	string TempUse;
	in>>TempUse;
	for (int i = 0; i < TempUse.size(); ++i)
	{
		if(!isCode(TempUse[i]))
		{
			int j = i + 1;
			string str_code;
			while(isCode(TempUse[j]) && j < TempUse.size())
			{
				str_code.push_back(TempUse[j++]);
			}
			CodePair[TempUse[i]] = str_code;
            i = j - 1;
		}
	}
	fstream BinIn;
	filename.replace(filename.end() - 3,filename.end(),"bin");
	BinIn.open(filename,ios::in | ios::binary);
	string BinBuffer;
	string BinTemp;
	BinBuffer.clear();
	BinTemp.clear();
	//AAAA DFA 
	//FAA AAA
	while(!BinIn.eof())
	{
		BinIn>>BinTemp;
		BinBuffer += BinTemp;
	}
    //display(CodePair);
	string text;
    text.clear();
	string temp;
    temp.clear();
	while(!in.eof())
	{
		in>>temp;
		text += temp;
	}
	// cout<<text<<endl;
    string BinaryCode;
    BinaryCode.clear();
    for (int i = 0; i < text.size(); ++i)
    {
    	int deci;
        deci = (int)text[i];
       	TempUse = dec2bin(deci);
       	if (TempUse.size() != 7 && i != text.size() - 1)
       	{
       		while(TempUse.size() != 7)
       		{
                TempUse.insert(TempUse.begin(),'0');
       		}
       	}
       	BinaryCode += TempUse;
    }
    BinaryCode = BinBuffer;
   	//翻转原有的map成为char,string类型的map便于翻译;
    string backspace;
   	map<string,char> DeMap;
   	map<char,string>::iterator IT;
   	fstream out;
    out.open("decoder.txt",ios::out | ios::binary);
   	for(IT = CodePair.begin(); IT != CodePair.end(); ++IT)
   	{
   		DeMap[(*IT).second] = (*IT).first;
   	}
    TempUse.clear();
    for (int i = 0; i < BinaryCode.size(); ++i)
    {
    	int j = i;
    	while(j < BinaryCode.size())
    	{
    		TempUse.push_back(BinaryCode[j++]);
    		if(DeMap.find(TempUse) != DeMap.end())
    		{
    			if (DeMap[TempUse] != '_')
    			{
                    char watch = DeMap[TempUse];
                    cout<<watch;
    			}
    			else
    			{
    				cout<<" ";
    			}
                TempUse.clear();
                break;
    		}
    	}
        i = j - 1;
    }
    in.close();
    out.close();
    BinIn.close();
}	



int main(int argc, const char * argv[]) 
{
	string longbuffer;
 	fstream in;
 	in.open("in.txt",ios::in);
 	string cat_longbuffer;
 	while(!in.eof())
 	{	
 		cat_longbuffer.clear();
 		in>>cat_longbuffer;
 		cat_longbuffer += " ";
 		longbuffer += cat_longbuffer;
 	}
    ExertOnBuffer(longbuffer);
    Frequency(longbuffer);
    cout<<"********* Welcome To The Huffman En-De coder System *********\n";

    cout<<"********* Successfully Analyze this txt **********\n\n";
    cout<<"\tChar\t\tFrequentness\t\tFrequency\n";
	cout<<setiosflags(ios::fixed);
    for (int i = 0; i < FrqArray.size(); ++i)
    {
    	cout<<"\t"<<FrqArray[i].first<<"\t\t"<<FrqArray[i].second<<"\t\t\t"<<setprecision(2)<<((double)FrqArray[i].second/longbuffer.size())*100<<"\%\t\n";
    }
    HuffNode *root = new HuffNode;
	root = Construct(FrqArray);
    Encode(root,1);
    map<char,string> CodePair,DecodePair;
    GetCode(CodePair);
    cout<<"************ According To Priority Code Rule *************\n\n";
    display(CodePair);

    cout<<"\n************ Now we try to encode the .dat file ************\n";
    try
    {
    	cout<<"\n************ Here is the out.dat file ************\n\n";
	    ComPress(CodePair,longbuffer);
	   	fstream ShowDat;
	   	ShowDat.open("out.dat",ios::in);
	   	string cat_temp;
	   	string Total;
	   	while(!ShowDat.eof())
	   	{
	   		cat_temp.clear();
	   		ShowDat>>cat_temp;
	   		Total += cat_temp;
	   	}
	   	cout<<Total<<"\n";
	   	int AfterComp = Total.size();
	   	int BforeComp = longbuffer.size();
	    cout<<"\n************ Here is the decoder.txt file ************\n\n";
    	Decoder("out.dat",DecodePair);
    	cout<<"\n";

    	cout<<"\n********** The Compress ratio is : "<<((double)(AfterComp) / BforeComp) * 100<<"%\n\n";
    }
    catch(const char *msg)
    {
    	cerr<<msg<<"\n";
    }
    return 0;
}
