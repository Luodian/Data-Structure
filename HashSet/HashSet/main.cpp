//
//  main.cpp
//  HashSet
//
//  Created by 李博 on 20/04/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#include "OpenHash.hpp"
#include "ProbHash.hpp"
#include "consisten_hash.hpp"

using namespace std;

void readCSV(const string &filepath ,vector< vector<string> > &vecMatrix)
{
	fstream inFile;
	inFile.open(filepath,ios::in);

    string value;
    vector<string> vecLine;
    vecLine.clear();
	while(inFile.good())
    {
    	getline(inFile,value);
        if (value == "")
        {
            break;
        }
    	stringstream SS(value);
        SS.clear();
        string info;
        vecLine.clear();
    	while(getline(SS,info,','))
    	{
            if (info[info.size()-1] == '\r')
            {
                info = info.substr(0,info.size()-1);
            }
    		vecLine.push_back(info);
    	}
    	vecMatrix.push_back(vecLine);
    }
    inFile.close();
}

void writeCSV(const string &filepath,vector< vector<string> > &vecMatrix)
{
	fstream outfile;
	outfile.open(filepath,ios::out | ios::trunc);
	for (int i = 0; i < vecMatrix.size(); ++i)
	{
		for (int j = 0; j < vecMatrix[i].size(); ++j)
		{
			if (j != vecMatrix[i].size() - 1)
			{
				outfile<<vecMatrix[i][j]<<",";
			}
			else
			{
				outfile<<vecMatrix[i][j]<<endl;
			}
		}
	}
}

struct foo_node
{
	size_t seqNum;
	string nameA,nameB;

	foo_node(size_t _seqNum = 0,string _nameA = string() ,string _nameB = string())
	{
		seqNum = _seqNum;
		nameA = _nameA;
		nameB = _nameB;
	}
	friend ostream& operator << (ostream &out,const foo_node &x)
	{
		out<<x.seqNum<<"-"<<x.nameA<<"-"<<x.nameB<<"\n";
		return out;
	}

	bool operator == (const foo_node &_a) const
	{
		return (_a.seqNum == seqNum || _a.nameA == nameA || _a.nameB == nameB);
	}
};

template<class KeyType>
class foo_hash
{
public:
	size_t operator () (const KeyType & x) const
	{
		size_t hashVal = 0;
        size_t seed = 31;
        string str = x.nameA + x.nameB;
        for (int i = 0; i < str.size(); ++i)
        {
            hashVal = hashVal * seed + str[i];
        }
        return ((hashVal & 0x7FFFFFFF));
	}
};


void ProbeSimpleTest()
{
	cout<<"1.Simple function test of Probe hash set.\n";

	ProbeSet::HashTable < string,string > A;
	A.insert("Scott Fitzgerald","The Great Gatsby");
	A.insert("Salinger", "The Catcher in the Rye");
	A.insert("Virginia Woolf","A Room of One's Own");

	cout<<"  The load factor is : "<<A.get_load_factor()<<endl;
    cout<<"  The size is: "<<A.getSize()<<endl;

	A.insert("Edith Warton","The Age of Innocence");
	A.insert("George Orwell","Shooting an Elephant");
	A.insert("John Milton","Lost Paradise");
	A.insert("Thomas Paine","Common Sense");
	A.insert("Earnest Hemmingway","The Old Man and the Sea");
	A.insert("Orhan Pamuk","My Name is Red");
	A.insert("James Joyce","Ulysses");

	cout<<"  The adjusted size is: "<<A.getSize()<<endl;
	cout<<"  The load factor is : "<<A.get_load_factor()<<endl;

	cout<<"\n";
	cout<<"  The value of James Joyce is :";
	cout<<A.contain("James Joyce")<<endl;

	cout<<"  The value of Earnest Hemmingway is :";
	cout<<A.contain("Earnest Hemmingway")<<endl;

}

void OpenSimpleTest()
{
	cout<<"2.Simple function test of Open hash set.\n";
	OpenSet::HashTable < foo_node, string , foo_hash<foo_node> > A;
	vector< vector< string > > vecMatrix;

	readCSV("/Users/luodian/Desktop/软设实验分组.csv",vecMatrix);

	for (int i = 1; i < vecMatrix.size(); ++i)
	{
		stringstream ss;
		ss.clear();
		ss<<vecMatrix[i][0];
		int Tempnum;
		ss>>Tempnum;
		string TempA = vecMatrix[i][1];
		string TempB = vecMatrix[i][2];
        string ProjectName = vecMatrix[i][3];
		foo_node foo(Tempnum,TempA,TempB);
        A.insert(foo,ProjectName);
	}

	foo_node bar(13,"李博","武德浩");
	cout<<"  The project info of \"李博\",\"武德浩\" is : ";
	cout<<A.contain(bar)<<endl;

	cout<<"  Erase the info: "<<bar;
	A.remove(bar);
	vecMatrix.erase(vecMatrix.begin() + 11);
	// writeCSV("/Users/luodian/Desktop/软设实验分组.csv",vecMatrix);
	cout<<"  The project info of \"李博\",\"武德浩\" is : ";
	cout<<A.contain(bar)<<endl;
}

int RandomNum(int n)
{
    unsigned int seed = (unsigned int)chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(1,n);
    
    auto dice = bind(distribution,generator);
    int ret = dice();

    return ret;
}

vector<int> datasheet;
void generate_data(int n)
{
    datasheet.resize(n);
	for (int i = 0; i < n; ++i)
	{
		datasheet[i] = RandomNum(0x3f3f3f3f);
	}
}

//对开哈希表的插入效率测试
clock_t openhash_insert(int n)
{
	OpenSet::HashTable<int,int> A;
	clock_t ret = clock();
	for (int i = 0 ; i < n; ++i)
	{
		A.insert(datasheet[i],i);
	}
	ret = clock() - ret;
	return ret;
}

//在n个数据中查找m个元素
clock_t openhash_find(int n,int m)
{
	OpenSet::HashTable<int,int> A;
	for (int i = 0; i < n; ++i)
	{
		A.insert(datasheet[i],i);
	}
	clock_t ret = clock();
	for (int i = 0; i < m; ++i)
	{
		A.contain(datasheet[i]);
	}
	ret = clock() - ret;
	return ret;
}

//对闭哈希表的插入效率测试
clock_t probehash_insert(int n)
{
	ProbeSet::HashTable<int,int> A;
	clock_t ret = clock();
	for (int i = 0 ; i < n; ++i)
	{
		A.insert(datasheet[i],i);
	}
	ret = clock() - ret;
	return ret;
}

clock_t probehash_find(int n,int m)
{
	ProbeSet::HashTable<int,int> A;
	for (int i = 0; i < n; ++i)
	{
		A.insert(datasheet[i],i);
	}
	clock_t ret = clock();
	for (int i = 0; i < m; ++i)
	{
		A.contain(datasheet[i]);
	}
	ret = clock() - ret;
	return ret;
}

//针对冲突次数的记录
int BKDR_func_open_test(int n)
{
	string info;
	OpenSet::HashTable<string,int> A;
	stringstream ss;
	ss.clear();
	for (int i = 0; i < n; ++i)
	{
		ss.clear();
		ss<<datasheet[i];
		ss>>info;
		A.insert(info,datasheet[i]);
	}
	return A.getCrashCnt();
}

template<class KeyType>  
class hash_func
{
public:
	size_t operator () (const KeyType &str) const
	{  
	    if(str.size() == 0)   // 这是由本人添加，以保证空字符串返回哈希值0  
	        return 0;  
	   	size_t seed = 2166136261;  

	    for (int i = 0; i < str.size(); ++i)
	    {  
	    	size_t ch = size_t(str[i]);
	        seed *= 16777619;  
	        seed ^= ch;  
	    }  
	    return (seed & 0x7FFFFFFF);  
	}
};

int FNV_func_open_test(int n)
{
	string info;
	OpenSet::HashTable<string,int,hash_func <string> > A;
	stringstream ss;
	ss.clear();
	for (int i = 0; i < n; ++i)
	{
		ss.clear();
		ss<<datasheet[i];
		ss>>info;
		A.insert(info,datasheet[i]);
	}
	return A.getCrashCnt();
}

int BKDR_func_probe_test(int n)
{
	string info;
	ProbeSet::HashTable<string,int> A;
	stringstream ss;
	ss.clear();
	for (int i = 0; i < n; ++i)
	{
		ss.clear();
		ss<<datasheet[i];
		ss>>info;
		A.insert(info,datasheet[i]);
	}
	return A.getCrashCnt();
}

int FNV_func_probe_test(int n)
{
	string info;
	ProbeSet::HashTable< string,int,hash_func<string> > A;
	stringstream ss;
	ss.clear();
	for (int i = 0; i < n; ++i)
	{
		ss.clear();
		ss<<datasheet[i];
		ss>>info;
		A.insert(info,datasheet[i]);
	}
	return A.getCrashCnt();
}

void Time_perfo_test()
{
	cout<<"3. Here is big data time test.\n";
	generate_data(1000000);

	cout<<"\n Part I: Hash set insert test.\n\n";
	fstream OpenFile;
    OpenFile.open("Open_insert.txt",ios::out | ios::trunc);

    fstream ProbeFile;
    ProbeFile.open("Probe_insert.txt",ios::out | ios::trunc);

    OpenFile.setf(ios::fixed,ios::floatfield);
    OpenFile.precision(6);

    ProbeFile.setf(ios::fixed,ios::floatfield);
    ProbeFile.precision(6);

    cout.setf(ios::fixed,ios::floatfield);
    cout.precision(6);

	clock_t deltaProbe;
	clock_t delta_Open;
	for (int i = 1; i <= 100; ++i)
	{
		deltaProbe = probehash_insert(i * 10000);
		delta_Open = openhash_insert(i * 10000);
		OpenFile<<i * 10000<<" "<<((float) deltaProbe / (CLOCKS_PER_SEC))<<"\n";
		ProbeFile<<i * 10000<<" "<<((float) delta_Open / (CLOCKS_PER_SEC))<<"\n";
		cout<<"   Open: "<<i * 10000<<" "<<((float) delta_Open / (CLOCKS_PER_SEC))<<"\n";
		cout<<"   Probe: "<<i * 10000<<" "<<((float) deltaProbe / (CLOCKS_PER_SEC))<<"\n";
	}

	ProbeFile.close();
	OpenFile.close();

	cout<<"\n Part II: Hash set find test.\n\n";
    OpenFile.open("Open_find.txt",ios::out | ios::trunc);
    ProbeFile.open("Probe_find.txt",ios::out | ios::trunc);

	for (int i = 1; i <= 100; ++i)
	{
		deltaProbe = probehash_find(i * 10000,10000);
		delta_Open = openhash_find(i * 10000,10000);
		OpenFile<<i * 10000<<" "<<((float) deltaProbe / (CLOCKS_PER_SEC))<<"\n";
		ProbeFile<<i * 10000<<" "<<((float) delta_Open / (CLOCKS_PER_SEC))<<"\n";
		cout<<"  Open: "<<i * 10000<<" "<<((float) delta_Open / (CLOCKS_PER_SEC))<<"\n";
		cout<<"  Probe: "<<i * 10000<<" "<<((float) deltaProbe / (CLOCKS_PER_SEC))<<"\n";
	}

	ProbeFile.close();
	OpenFile.close();

	cout<<"\n Part III: Openset Hash function crash test.\n\n";
	OpenFile.open("BKDR_open_crash.txt",ios::out | ios::trunc);
    ProbeFile.open("FNV_open_crash.txt",ios::out | ios::trunc);

    int BKDR;
    int FNV;
    for (int i = 1; i <= 100; ++i)
    {
		BKDR = BKDR_func_open_test(i * 10000);
		FNV = FNV_func_open_test(i * 10000);
		OpenFile<<i * 10000<<" "<<BKDR<<"\n";
		ProbeFile<<i * 10000<<" "<<FNV<<"\n";
		cout<<"   BKDR: "<<i * 10000<<" "<<BKDR<<"\n";
		cout<<"   FNV: "<<i * 10000<<" "<<FNV<<"\n";
    }

	ProbeFile.close();
	OpenFile.close();

	cout<<"\n Part IV: Probe Hash function crash test.\n\n";
	OpenFile.open("BKDR_probe_crash.txt",ios::out | ios::trunc);
    ProbeFile.open("FNV_probe_crash.txt",ios::out | ios::trunc);

    for (int i = 1; i <= 100; ++i)
    {
		BKDR = BKDR_func_probe_test(i * 10000);
		FNV = FNV_func_probe_test(i * 10000);
		OpenFile<<i * 10000<<" "<<BKDR<<"\n";
		ProbeFile<<i * 10000<<" "<<FNV<<"\n";
		cout<<"  BKDR: "<<i * 10000<<" "<<BKDR<<"\n";
		cout<<"  FNV: "<<i * 10000<<" "<<FNV<<"\n";
    }

	ProbeFile.close();
	OpenFile.close();
}

void consistHash_test()
{
	ConsistentHash hasher(4,100);
    vector<int> servers;
    servers.resize(4);
    hasher.set_server_name(0,"202.104.236.0");
	hasher.set_server_name(1,"202.104.236.1");
	hasher.set_server_name(2,"202.104.236.2");
	hasher.set_server_name(3,"202.104.236.3");

	string ips[55];

    for (int i = 0; i < 10; ++i)
    {
    	string ip = hasher.getIP();
    	ips[i] = ip;
    	size_t index = hasher.GetServerIndex(ip);
    	cout<<"   The clients: "<<ip<<" in server "<<hasher.get_server_name(index)<<"\n";
    	servers[index] ++;
    }

    cout<<"\n";
    for (int i = 0; i < servers.size(); ++i)
    {
    	cout<<"   The servers "<<i<<" th has node: "<<servers[i]<<" .\n";
    }
    cout<<"\n";
    hasher.remove(1);

    for (int i = 0; i < 4; ++i)
    {
    	servers[i] = 0;
    }

    for (int i = 0; i < 10; ++i)
    {
    	string ip = ips[i];
    	size_t index = hasher.GetServerIndex(ip);
    	cout<<"   The clients: "<<ip<<" in server "<<hasher.get_server_name(index)<<"\n";
    	servers[index] ++;
    }
    cout<<"\n";
    for (int i = 0; i < servers.size(); ++i)
    {
    	cout<<"   The servers "<<i<<" th has node: "<<servers[i]<<" .\n";
    }
    cout<<"\n";
    hasher.add(1);
    for (int i = 0; i < 4; ++i)
    {
    	servers[i] = 0;
    }
    for (int i = 0; i < 10; ++i)
    {
    	string ip = ips[i];
    	size_t index = hasher.GetServerIndex(ip);
    	cout<<"   The clients: "<<ip<<" in server "<<hasher.get_server_name(index)<<"\n";
    	servers[index] ++;
    }
    cout<<"\n";
    for (int i = 0; i < servers.size(); ++i)
    {
    	cout<<"   The servers "<<hasher.get_server_name(i)<<" has node: "<<servers[i]<<" .\n";
    }
    cout<<"\n";
}

int main(int argc, const char * argv[]) 
{
	// freopen("out.txt","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // ProbeSimpleTest();
    // cout<<"\n";
    // OpenSimpleTest();
    // cout<<"\n";
    // Time_perfo_test();
    // cout<<"\n";
    consistHash_test();
    cout<<"\n"; 
    return 0;
}
