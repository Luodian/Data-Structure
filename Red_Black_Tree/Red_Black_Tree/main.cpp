//
//  main.cpp
//  Red_Black_Tree
//
//  Created by 李博 on 24/04/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#include <iostream>
#include "RB_Tree.hpp"
#include "Avl.hpp"

using namespace std;

struct foo_node
{
	string info;
	int grades[5];
	int gradesSum;
	foo_node(string _info = string())
	{
		info = _info;
		memset(grades,0,sizeof(grades));
		gradesSum = 0;
	}
	friend ostream& operator << (ostream &out,const foo_node &rhs)
	{
		out<<"Name: "<<rhs.info<<"\n";
		for (int i = 0; i < 5; ++i)
		{
			out<<rhs.grades[i]<<" ";
		}
		out<<"\n";
		return out;
	}
	bool operator < (const foo_node &rhs) const
	{
		int accumulation = 0;
		int accumulation_rhs = 0;
		for (int i = 0; i < 5; ++i)
		{
			accumulation += grades[i];
		}
		for (int i = 0; i < 5; ++i)
		{
			accumulation_rhs += rhs.grades[i];
		}	

		return accumulation < accumulation_rhs;
	}
	bool operator == (const foo_node &rhs) const
	{
		return gradesSum == rhs.gradesSum;
	}
	bool operator != (const foo_node &rhs) const
	{
		return gradesSum != rhs.gradesSum;
	}
	void sumUp()
	{
		for (int i = 0; i < 5; ++i)
		{
			gradesSum += grades[i];
		}
	}
};

void FuncTest()
{
	cout<<"I. The first test is simple and function test.\n\n";
	cout<<"********************************************\n";
    RB::RedBlackTree<int,int> A;
    for (int i = 1; i <= 9; ++i)
    {
    	A.insert(i,i);
    }
    cout<<"The tree's image is like this: \n\n";
    A.printTree();
    cout<<"\n";
    cout<<"The value of 1 is : ";
    cout<<A.find(1)<<endl;

    cout<<"If we remove the key 2.\n";
    cout<<"The tree changes to : \n\n";
    A.Remove(2);
    A.printTree();
    cout<<"\n";

    cout<<"The max element of the RB tree is : ";
    cout<<A.findMax()<<endl;

    // cout<<"The minimal element of the RB tree is : ";
    // cout<<A.findMin()<<endl;
}

void Generic_test()
{
	cout<<"II. The second test is a generic test.\n\n";
	cout<<"********************************************\n";

	foo_node head_node("null");
	head_node.gradesSum = -INF;
	RB::RedBlackTree<foo_node,int> A(head_node);
	foo_node Kim("Kim");
	Kim.grades[0] = 87;
	Kim.grades[1] = 89;
	Kim.grades[2] = 88;
	Kim.grades[3] = 71;
	Kim.grades[4] = 99;
	Kim.sumUp();

	foo_node Tom("Tom");
	Tom.grades[0] = 83;
	Tom.grades[1] = 86;
	Tom.grades[2] = 68;
	Tom.grades[3] = 71;
	Tom.grades[4] = 89;
	Tom.sumUp();

	foo_node Frank("Frank");
	Frank.grades[0] = 84;
	Frank.grades[1] = 84;
	Frank.grades[2] = 83;
	Frank.grades[3] = 72;
	Frank.grades[4] = 91;
	Frank.sumUp();

	A.insert(Kim,Kim.gradesSum);
	A.insert(Tom,Tom.gradesSum);
	A.insert(Frank,Frank.gradesSum);

	cout<<"The sum of grades for Tom is :";
	cout<<A.find(Tom)<<endl;
	cout<<"The maxium grades for all is : ";
	cout<<A.findMax()<<endl;
	cout<<"\n";

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
void generateData(int n)
{
	datasheet.clear();
	datasheet.resize(n);
	for (int i = 0; i < n; ++i)
	{
		datasheet[i] = RandomNum(0x3f3f3f3f);
	}
}

clock_t avl_insert_test(int n)
{
	AVL::AvlTree A;
	for (int i = 0; i < n; ++i)
	{
		A.insert(i);
	}
	clock_t ret = clock();
    for (int i = 1; i <= 10000; ++i)
    {
        int temp = RandomNum(0x3f3f3f3f);
        A.insert(temp);
    }
	ret = clock() - ret;
	return ret;
}

clock_t RB_insert_test(int n)
{
	RB::RedBlackTree<int,int> A;
	for (int i = 1; i <= n; ++i)
	{
		A.insert(i,i);
	}
	clock_t ret = clock();
    for (int i = 1; i <= 10000; ++i)
    {
        int temp = RandomNum(0x3f3f3f3f);
        A.insert(temp);
    }
	ret = clock() - ret;

	return ret;
}

//在n个数据中查找m次的cost
clock_t RB_find_test(int n,int m)
{
	RB::RedBlackTree<int,int> A;
	for (int i = 0; i < n; ++i)
	{
		A.insert(datasheet[i],i);
	}

	clock_t ret = clock();
	for (int i = 0; i < m; ++i)
	{
		A.find(datasheet[i]);
	}
	ret = clock() - ret;
	return ret;
}

clock_t avl_find_test(int n,int m)
{
	AVL::AvlTree A;
	for (int i = 0; i < n; ++i)
	{
		A.insert(datasheet[i]);
	}

	clock_t ret = clock();
	for (int i = 0; i < m; ++i)
	{
		A.find(datasheet[i]);
	}
	ret = clock() - ret;
	return ret;
}

void Time_test()
{
	cout<<"III. The third test is time performance test.\n";
	cout<<"********************************************\n\n";

	cout<<"Part I: Random data insert test.\n\n";

	generateData(1000000);
	//needed 400M memory;
	//so it may cause memory leaks;
	fstream RBTreeFile;
    RBTreeFile.open("RBTree_insert_random.txt",ios::out | ios::trunc);

    fstream AvlFile;
    AvlFile.open("AVLTree_insert_random.txt",ios::out | ios::trunc);

    RBTreeFile.setf(ios::fixed,ios::floatfield);
    RBTreeFile.precision(6);

    AvlFile.setf(ios::fixed,ios::floatfield);
    AvlFile.precision(6);

    cout.setf(ios::fixed,ios::floatfield);
    cout.precision(6);

	clock_t delta_t_avl;
	clock_t delta_t_rb;
	for (int i = 1; i <= 100; ++i)
	{
		delta_t_avl = avl_insert_test(i * 10000);
		delta_t_rb = RB_insert_test(i * 10000);
		RBTreeFile<<i * 10000<<" "<<((float) delta_t_avl / (CLOCKS_PER_SEC))<<"\n";
		AvlFile<<i * 10000<<" "<<((float) delta_t_rb / (CLOCKS_PER_SEC))<<"\n";
		cout<<"RB: "<<i * 10000<<" "<<((float) delta_t_rb / (CLOCKS_PER_SEC))<<"\n";
		cout<<"AVL: "<<i * 10000<<" "<<((float) delta_t_avl / (CLOCKS_PER_SEC))<<"\n";
	}

	AvlFile.close();
	RBTreeFile.close();

	cout<<"\nPart II: Random data find test.\n\n";
    RBTreeFile.open("RBTree_search_random.txt",ios::out | ios::trunc);
    AvlFile.open("AVLTree_search_random.txt",ios::out | ios::trunc);

	for (int i = 1; i <= 100; ++i)
	{
		delta_t_avl = avl_find_test(i * 10000,1000);
		delta_t_rb = RB_find_test(i * 10000,1000);
		RBTreeFile<<i * 10000<<" "<<((float) delta_t_rb / (CLOCKS_PER_SEC))<<"\n";
		AvlFile<<i * 10000<<" "<<((float) delta_t_avl / (CLOCKS_PER_SEC))<<"\n";
		cout<<"RB: "<<i * 10000<<" "<<((float) delta_t_rb / (CLOCKS_PER_SEC))<<"\n";
		cout<<"AVL: "<<i * 10000<<" "<<((float) delta_t_avl / (CLOCKS_PER_SEC))<<"\n";
	}

	AvlFile.close();
	RBTreeFile.close();

	cout<<"\nPart III: Sequntial data insert test.\n\n";
	RBTreeFile.open("RBTree_insert_sequntial.txt",ios::out | ios::trunc);
    AvlFile.open("AVLTree_insert_sequntial.txt",ios::out | ios::trunc);
    for (int i = 0; i < 1000000; ++i)
    {
    	datasheet[i] = i + 1;
    }

    for (int i = 1; i <= 100; ++i)
    {
		delta_t_avl = avl_insert_test(i * 10000);
		delta_t_rb = RB_insert_test(i * 10000);
		RBTreeFile<<i * 10000<<" "<<((float) delta_t_rb / (CLOCKS_PER_SEC))<<"\n";
		AvlFile<<i * 10000<<" "<<((float) delta_t_avl / (CLOCKS_PER_SEC))<<"\n";
		cout<<"RB: "<<i * 10000<<" "<<((float) delta_t_rb / (CLOCKS_PER_SEC))<<"\n";
		cout<<"AVL: "<<i * 10000<<" "<<((float) delta_t_avl / (CLOCKS_PER_SEC))<<"\n";
    }

	AvlFile.close();
	RBTreeFile.close();

	cout<<"\nPart IV: Sequntial data find test.\n\n";
	RBTreeFile.open("RBTree_find_sequntial.txt",ios::out | ios::trunc);
    AvlFile.open("AVLTree_find_sequntial.txt",ios::out | ios::trunc);
    for (int i = 0; i < 1000000; ++i)
    {
    	datasheet[i] = i + 1;
    }

    for (int i = 1; i <= 100; ++i)
    {
		delta_t_avl = avl_find_test(i * 10000,1000);
		delta_t_rb = RB_find_test(i * 10000,1000);
		RBTreeFile<<i * 10000<<" "<<((float) delta_t_rb / (CLOCKS_PER_SEC))<<"\n";
		AvlFile<<i * 10000<<" "<<((float) delta_t_avl / (CLOCKS_PER_SEC))<<"\n";
		cout<<"RB: "<<i * 10000<<" "<<((float) delta_t_rb / (CLOCKS_PER_SEC))<<"\n";
		cout<<"AVL: "<<i * 10000<<" "<<((float) delta_t_avl / (CLOCKS_PER_SEC))<<"\n";
    }
    
	AvlFile.close();
	RBTreeFile.close();
}

int main(int argc, const char * argv[]) 
{
	freopen("out.txt","w",stdout);
	FuncTest();
	Generic_test();
	Time_test();
    return 0;
}
