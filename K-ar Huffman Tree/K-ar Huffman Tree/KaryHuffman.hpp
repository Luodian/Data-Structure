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

    //给K进制编码映射1位char用于编码
    map<int,char> Seq_char_map;
    //对1位char反过来映射
    map<char,int> Char_Seq_map;

    //对字符集进行二进制编码
    map<char,string> BinaryCodeTable;

    //对二进制编码镜像用于解码。
    map<string,char> DecodeTable;

    double ratio;
    
    long long FileLen;
    char *Text;
    long long CompressedFileLen;
    char *CompressedText;
    
    string DecodeString;

    string suffix;
    string CurrentDir;

    int TrailingZero;
    void makeEncodeTable()
    {
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
        for (int i = 64; i <= 70; ++i)
        {
            Seq_char_map[i] = (i - 64) + ':'; 
            Char_Seq_map[(i - 64) +':'] = i;
        }
        for (int i = 71; i <= 76; ++i)
        {
            Seq_char_map[i] = (i - 71) + '[';
            Char_Seq_map[(i - 71) +'['] = i;
        }
    }
    void init()
    {
        while(!FrqHeap.empty())
        {
            HuffmanNode<Kary> *p = FrqHeap.top();
            FrqHeap.pop();
            delete p;
        }
        root = nullptr;

        DecodeString.clear();

        alphabet_Frq_map.clear();
        Seq_char_map.clear();
        Char_Seq_map.clear();

        BinaryCodeTable.clear();
        DecodeTable.clear();

        makeEncodeTable();
    }
    void genWordFrq()
    {
        for (int i = 0; i < FileLen; ++i)
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
        while (ret.size() < BitLen)
        {   
            ret.push_back('0');
        }
        for (int i = 0;i < ret.size() / 2; ++i)
        {
            swap(ret[i],ret[ret.size() - i - 1]);
        }
        return ret;
    }
    string CharZeroDec2bin(int n)
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
        int BitLen = 8;
        while (ret.size() < BitLen)
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
                    // cout<<root->element<<" "<<StringCode<<"\n";
                    if (BinaryCodeTable.find(root->element) == BinaryCodeTable.end())
                    {
                        BinaryCodeTable[root->element] = StringCode;
                        // cout<<root->element<<" Yes"<<"\n";
                    }
                    else
                    {
                        BinaryCodeTable[root->element] = BinaryCodeTable[root->element] +  StringCode;
                        // cout<<root->element<<" secodn"<<"\n";
                    }
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

    //生成镜像的DecodeTable;
    // void genDecodeTable()
    // {
    //     for (auto itr : BinaryCodeTable)
    //     {
    //         DecodeTable[itr.second] = itr.first;
    //     }
    // }
    unsigned char Str2Bin(string str)  
    {  
        //transfer c style str()
        int a = atoi(str.c_str());
        int b = 1;
        int ans = 0;
        while(a != 0)
        {
            ans += (a % 10 * b);
            b *= 2;
            a /= 10;
        }
        return (unsigned char)ans;
    }
    
    //这一步之后将编码存放于BinaryCodeTable<char,string>中。
    //接下来将Raw文本转码成compress文件
    void WriteCompressedFile(const string &filePath)
    {
        string buffer;
        fstream WriteFile;
        fstream BinaryWrite;
        fstream logFile;

        suffix.clear();
        string CompressedFilePath;

        for (int i = (int)filePath.size() - 1; i >= 0; --i)
        {
            if (filePath[i] == '.')
            {
                CompressedFilePath = filePath.substr(0,i);
                suffix = filePath.substr(i,filePath.size() - i);
                break;
            }
        }
        string DebugPath = CompressedFilePath + ".bin";
        string logPath = CompressedFilePath + ".log";

        logFile.open(logPath,ios::out | ios::trunc |  ios::binary);

        BinaryWrite.open(DebugPath,ios::out | ios::trunc | ios::binary);
        CompressedFilePath += ".compress";


        WriteFile.open(CompressedFilePath,ios::out| ios::trunc | ios::binary);

        logFile<<BinaryCodeTable.size()<<"\n";
        for (auto itr : BinaryCodeTable)
        {
            logFile<<itr.first<<" "<<itr.second<<"\n";        
        }
        logFile<<suffix<<"\n";
        vector<char> DebugBinary;
        //将文件写入DATA目录的.compress文件中
        DebugBinary.clear();
        //buffer用于存储01字符串，满8位清零。
        vector<char> WriteCharBuffer;
        WriteCharBuffer.clear();
        
        for (int i = 0; i < FileLen; ++i)
        {
            string StringCode = BinaryCodeTable[Text[i]];
            for (int j = 0; j < StringCode.size(); ++j)
            {
                if (buffer.size() == 8)
                {
                    unsigned char WriteChar = Str2Bin(buffer);
                    WriteCharBuffer.push_back(WriteChar);
                    for (int i = 0; i < 8; ++i)
                    {
                        DebugBinary.push_back(buffer[i]);
                    }
                    buffer.clear();
                }
                buffer.push_back(StringCode[j]);
            }
        }
        if (buffer.size() != 0)
        {
            TrailingZero = 0;
            for (int i = (int)buffer.size(); i < 8; ++i)
            {
                TrailingZero ++;
                buffer += "0";
            }
            unsigned char WriteChar = Str2Bin(buffer);
            for (int i = 0; i < buffer.size(); ++i)
            {
                DebugBinary.push_back(buffer[i]);
            }
            WriteCharBuffer.push_back(WriteChar);
        }
        
        logFile<<TrailingZero<<"\n";

        WriteFile.write(WriteCharBuffer.data(),WriteCharBuffer.size());
        
        BinaryWrite.write(DebugBinary.data(),DebugBinary.size());

        BinaryWrite.close();
        WriteFile.close();
    }
    void readLogFile(const string &CompressedFilePath)
    {
        DecodeTable.clear();
        fstream in;

        string logPath;

        for (int i = (int)CompressedFilePath.size() - 1; i >= 0; --i)
        {
            if (CompressedFilePath[i] == '.')
            {
                logPath = CompressedFilePath.substr(0,i);
                break;
            }
        }

        logPath += ".log";
        char sig;
        string CodeBuffer;
        string pairBuffer;
        suffix.clear();
        in.open(logPath,ios::in | ios::binary);
        if (in)
        {
            int tableSize;
            in>>tableSize;
            for (int i = 0; i < tableSize + 1; ++i)
            {
                getline(in,pairBuffer);
                if (pairBuffer.size() == 0)
                {
                    continue;
                }
                sig = pairBuffer[0];
                if (sig == ' ')
                {
                    pairBuffer = pairBuffer.substr(1,pairBuffer.size() - 1);
                    DecodeTable[pairBuffer] = '\n';
                    continue;
                }
                CodeBuffer = pairBuffer.substr(2,pairBuffer.size() - 2);
                DecodeTable[CodeBuffer] = sig;
            }
            in>>sig;
            in>>CodeBuffer;
            DecodeTable[CodeBuffer] = sig;
            in>>suffix;
            in>>TrailingZero;
        }
        else
        {
            cout<<"Log file doesn't exits\n";
            return;
        }
    }
    void DecodeCompressedText(const string &CompressedPath)
    {
        fstream readFile;
        readFile.open(CompressedPath,ios::in | ios::binary);
        fstream BinaryWrite;
        BinaryWrite.open("/Users/luodian/Desktop/DSA/K-ar Huffman Tree/K-ar Huffman Tree/DATA/Test.bin",ios::in | ios::binary);
        string DecodeFilePath;

        //读入编码表和后缀名，TrailingZero等信息。
        readLogFile(CompressedPath);

        for (int i = (int)CompressedPath.size() - 1; i >= 0; --i)
        {
            if (CompressedPath[i] == '.')
            {
                DecodeFilePath = CompressedPath.substr(0,i);
                break;
            }
        }

        DecodeFilePath += "_Decode";
        DecodeFilePath += suffix;

        fstream writeFile;
        writeFile.open(DecodeFilePath,ios::out | ios::trunc | ios::binary);
        string buffer;
        string DecodeBuffer;

        buffer.clear();
        DecodeBuffer.clear();
        
        if (readFile)
        {
            readFile.seekg(0,readFile.end);
            CompressedFileLen = readFile.tellg();
            readFile.seekg(0,readFile.beg);

            CompressedText = new char[CompressedFileLen];

            readFile.read(CompressedText,CompressedFileLen);
        }
        if (CompressedFileLen == 0)
        {
            cout<<"Compressed file doesn't exist\n";
        }
        for (int i = 0; i < CompressedFileLen; ++i)
        {
            int DecodeChar = (int)(CompressedText[i]);
            if (DecodeChar < 0)
            {
                DecodeChar += 256;
            }
            string BinaryDecodeString = CharZeroDec2bin(DecodeChar);
            DecodeBuffer += BinaryDecodeString;
        }
//        DecodeBuffer.clear();
//        long long BinaryWriteLen;
//        if (BinaryWrite)
//        {
//            BinaryWrite.seekg(0,BinaryWrite.end);
//            BinaryWriteLen = BinaryWrite.tellg();
//            DecodeBuffer.resize(BinaryWriteLen);
//            BinaryWrite.seekg(0,BinaryWrite.beg);
//            
//            BinaryWrite.read(DecodeBuffer.data(),BinaryWriteLen);
//        }
//        readFile.seekg(0,readFile.end);
//        CompressedFileLen = readFile.tellg();
//        readFile.seekg(0,readFile.beg);
//        
//        CompressedText = new char[CompressedFileLen];
//        
//        readFile.read(CompressedText,CompressedFileLen);
        int j = 0;
        string TempUse;

        vector<char> WriteBackBuffer;
        for (int i = 0; i < DecodeBuffer.size() - TrailingZero; ++i)
        {
            j = i;
            while(j < DecodeBuffer.size())
            {
                TempUse.push_back(DecodeBuffer[j++]);
                if (DecodeTable.find(TempUse) != DecodeTable.end())
                {
                    if (DecodeTable[TempUse] == '_')
                    {
                        WriteBackBuffer.push_back(' ');
                    }
                    else
                    {
                        WriteBackBuffer.push_back(DecodeTable[TempUse]);
                    }
                    TempUse.clear();
                    break;
                }
            }
            i = j - 1;
        }
        
        writeFile.write(WriteBackBuffer.data(),WriteBackBuffer.size());
        //专门特判TrailingZero的情况
//        j = (int)DecodeBuffer.size() - 8;
//        while(j < (DecodeBuffer.size() - TrailingZero))
//        {
//            TempUse.push_back(DecodeBuffer[j++]);
//            if (DecodeTable.find(TempUse) != DecodeTable.end())
//            {
//                if (DecodeTable[TempUse] == '_')
//                {
//                    writeFile<<" ";
//                }
//                else
//                {
//                    writeFile<<DecodeTable[TempUse];
//                }
//                TempUse.clear();
//            }
//        }
        readFile.close();
        writeFile.close();
    }

    void Encode()
    {
        if (FileLen == 0)
        {
            cout<<"Please make sure the text is valid\n";
        }
        else
        {
            genWordFrq();
            genFrqHeap();
            showHeap();

            buildHuffmanTree();
            genCodeVec(root,nullptr,0);
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
    void ComPressFile(const string &filePath)
    {
        if (filePath.size() == 0)
        {
            cout<<"Please make sure the address is valid\n";
            return;
        }
        fstream in;
        in.open(filePath,ios::in | ios::binary);
        if (in)
        {
            in.seekg(0,in.end);
            FileLen = in.tellg();
            in.seekg(0,in.beg);
            Text = new char[FileLen];
            in.read(Text,FileLen);
        }
        Encode();
        WriteCompressedFile(filePath);
        delete [] Text;
        in.close();
    }
    void Decode(const string &filePath)
    {
        DecodeCompressedText(filePath);
    }
    double getRatio()
    {
        return (double)CompressedFileLen  / (double)FileLen;
    }
    void debug(const string &filePath)
    {
        fstream out;
        out.open(filePath,ios::out | ios::trunc | ios::binary);
        for (auto itr : BinaryCodeTable)
        {
            if (itr.first == '\n')
            {
                out<<"Zn"<<" "<<itr.second<<"\n";
                continue;
            }
            out<<itr.first<<" "<<itr.second<<"\n";
        }
        out<<"\n";
        for (auto itr : DecodeTable)
        {
            if (itr.second == '\n')
            {
                out<<itr.first<<" "<<"Zn"<<"\n";
                continue;
            }
            out<<itr.first<<" "<<itr.second<<"\n";
        }
        out<<suffix<<"\n";
        out<<TrailingZero<<"\n";
    }
};

#endif /* KaryHuffman_h */
