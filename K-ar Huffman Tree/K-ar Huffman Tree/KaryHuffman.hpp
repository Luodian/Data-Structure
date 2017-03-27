//
//  KaryHuffman.h
//  K-ar Huffman Tree
//
//  Created by 李博 on 23/03/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#ifndef KaryHuffman_h
#define KaryHuffman_h

#include "Header.hpp"

using namespace std;

template<int Kary>
class HuffmanTree;
template<int Kary>
class compare;
constexpr static int maxKary = 128;

template <int Kary>
class HuffmanNode
{
public:
    friend class HuffmanTree<Kary>;
    friend class compare<Kary>;
    int weight;
    string code;
    char element;
    bool isNullNode;
    bool hasChar;
    vector<HuffmanNode<Kary> *> childs;
public:
    HuffmanNode(int w = 0)
    {
        weight = w;
        element = '*';
        childs.clear();
    }
};

template<int Kary>
class compare
{
public:
    bool operator() (const HuffmanNode<Kary> *lhs,const HuffmanNode<Kary> *rhs) const
    {
        return lhs->weight > rhs->weight;
    }
};

template <int Kary>
class HuffmanTree
{
private:
    HuffmanNode<Kary> *root;
    priority_queue<HuffmanNode<Kary>*,vector<HuffmanNode<Kary> *>,compare<Kary>> FrqHeap;
    
    //字母表-权值映射
    map<char,int> alphabet_Frq_map;

    map<int,char> Seq_char_map;
    map<char,int> Char_Seq_map;

    map<char,string> BinaryCodeTable;

    string Text;
    void init()
    {
        while(!FrqHeap.empty())
        {
            HuffmanNode<Kary> *p = FrqHeap.top();
            FrqHeap.pop();
            delete p;
        }
        root = nullptr;
        alphabet_Frq_map.clear();
        Seq_char_map.clear();
        Char_Seq_map.clear();
        BinaryCodeTable.clear();
        for (int i = 0; i <= 9; ++i)
        {
            Seq_char_map[i] = i + '0';
            Char_Seq_map[i + '0'] = i; 
        }
        for (int i = 10; i <= 35; ++i)
        {
            Seq_char_map[i] = (i - 10) + 'A';
            Char_Seq_map[(i - 10) + 'A'] = i;
        }
        for (int i = 36; i <= 63; ++i)
        {
            Seq_char_map[i] = (i - 36) +'a';
            Char_Seq_map[(i - 36) +'a'] = i;
        }
        root = nullptr;
    }
    void genWordFrq()
    {
        for (int i = 0; i < Text.size(); ++i)
        {
            if (Text[i] == ' ')
            {
                Text[i] = '_';
            }
            alphabet_Frq_map[Text[i]] ++;
        }
    }
    void genFrqHeap()
    {
        map<char,int>::iterator itr;
        for (itr = alphabet_Frq_map.begin(); itr != alphabet_Frq_map.end(); ++itr)
        {
            char temp_ch = itr->first;
            int temp_int = itr->second;
            
            //似乎这个地方有点问题
            HuffmanNode<Kary> *p = new HuffmanNode<Kary>;
            // if(p->weight == 0)
            // {
            //     cout<<"Before Assign"<<endl;
            // }
            p->weight = temp_int;
            p->element = temp_ch;
            p->hasChar = 1;
            // if(p->weight == 0)
            // {
            //     cout<<"Before Insert"<<endl;
            // }
            FrqHeap.emplace(p);
            // if(p->weight == 0)
            // {
            //     cout<<"Yes"<<endl;
            // }
            // showHeap();
        }
        //增加虚节点k - 1 - (n-1) % (k-1);
        int n = (int)alphabet_Frq_map.size();
        int NullNodes = (Kary - 1 - (n - 1) % (Kary-1));
        for (int i = 0; i < NullNodes; ++i)
        {
            HuffmanNode<Kary> *Hnode = new HuffmanNode<Kary>;
            Hnode->weight = 0;
            Hnode->isNullNode = 1;
            Hnode->hasChar = 0;
            FrqHeap.emplace(Hnode);
        }
    }
    void buildHuffmanTree()
    {   
        while(FrqHeap.size() != 1)
        {
            HuffmanNode<Kary> *parent = new HuffmanNode<Kary>;
            for (int i = 0; i < Kary; ++i)
            {
                HuffmanNode<Kary> *p = FrqHeap.top();
                FrqHeap.pop();
                parent->childs.push_back(p);
                parent->weight += (p->weight);
            }
            FrqHeap.emplace(parent);
        }
        root = FrqHeap.top();
    }
    void showHeap()
    {
        priority_queue<HuffmanNode<Kary>*,vector<HuffmanNode<Kary> *>,compare<Kary>> T = FrqHeap;
        while(!T.empty())
        {
            cout<<T.top()->weight<<" "<<T.top()->element<<" "<<T.top()<<endl;
            T.pop();
        }
        cout<<endl;
    }
    string accumulation;
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
        int BitLen = log2(Kary);
        if (ret.size() < BitLen)
        {   
            ret.push_back('0');
        }
        for (int i = 0;i < ret.size() / 2; ++i)
        {
            swap(ret[i],ret[ret.size() - i - 1]);
        }
        return ret;
    }
    void genCodeVec(HuffmanNode<Kary> *root,HuffmanNode<Kary> *father,int singleCode)
    {
        if(root == nullptr)
        {
            return;
        }
        if(father != nullptr)
        {
            root->code = father->code + Seq_char_map[singleCode];
        }
        if (root->childs.size() == 0 || root->hasChar == 1)
        {
            if (root->hasChar == 1)
            {
                for (int i = 0; i < root->code.size(); ++i)
                {
                    int decCode = Char_Seq_map[root->code[i]];
                    string StringCode = dec2bin(decCode);
                    BinaryCodeTable[root->element] = StringCode;
                }
            }
            return;
        }
        for (int i = 0; i < Kary; ++i)
        {
            if (root->childs.size() != 0)
            {
                genCodeVec(root->childs[i],root,i);
            }
        }
    }
    //这一步之后将编码存放于CodeTable<char,string>中。
    //接下来将Raw文本转码
    void TransferRawText()
    {
        for (int i = 0; i < Text.size(); ++i)
        {

        }
    }
    void makeEmpty(HuffmanNode<Kary> * &root)
    {
        if (root == nullptr)
        {
            return;
        }
        for (int i = 0; i < Kary; ++i)
        {
            if(root->childs.size() != 0)
                makeEmpty(root->childs[i]);
        }
        delete root;
    }
    
    string backTextArray[25];
    //用于存放多余的text
public:
    HuffmanTree()
    {
        init();
    }
    ~HuffmanTree()
    {
        makeEmpty(root);
    }
    void getString(const string &pattern)
    {
        Text = pattern;
    }
    void Encode(const string &pattern)
    {
        if (pattern.size() == 0)
        {
            cout<<"Please make sure the text is valid\n";
        }
        else
        {
            getString(pattern);
            genWordFrq();
            genFrqHeap();
            showHeap();
            //这之前可能有一些bug
            buildHuffmanTree();
            genCodeVec(root,nullptr,0);
        }
    }
    void getRootSize()
    {
        cout<<root->weight<<endl;
    }
};

#endif /* KaryHuffman_h */
