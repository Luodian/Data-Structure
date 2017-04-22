//
//  main.cpp
//  Shortest Path
//
//  Created by 李博 on 11/04/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#include "djikstra.hpp"
#include "floyd.hpp"
#include "spfa.hpp"

using namespace std;

void TestA()
{
	djikstra *A = new djikstra();
    A->getInfo("/Users/luodian/Desktop/DSA/Shortest Path/Shortest Path/DATA/in.txt");
    A->outputInfo();
    delete A;
}

void TestB()
{
    Floyd *B = new Floyd();
    B->getInfo("/Users/luodian/Desktop/DSA/Shortest Path/Shortest Path/DATA/in.txt");
    B->update();
    B->outputInfo();
    delete B;
}

void mediumData()
{
	djikstra *A = new djikstra();
	Floyd *B = new Floyd();

	clock_t t = clock();
    A->getInfo("/Users/luodian/Desktop/DSA/Shortest Path/Shortest Path/DATA/dense_graph_in.txt");
    A->findans();
    t = clock() - t;
    cout<<"\nDjikstra :\n";
    cout<<"The shortest path cost: "<<A->ans()<<".\n";
    cout<<"The time efficiency: "<<float(t) / CLOCKS_PER_SEC<<" s.\n";
    t = clock();
    B->getInfo("/Users/luodian/Desktop/DSA/Shortest Path/Shortest Path/DATA/dense_graph_in.txt");
    B->update();
    t = clock() - t;
    cout<<"\nFloyd :\n";
    cout<<"The shortest path cost: "<<B->ans()<<".\n";
    cout<<"The time efficiency: "<<float(t) / CLOCKS_PER_SEC<<" s.\n";
    delete A;
    delete B;
}

void bigDataTest()
{
	djikstra *A = new djikstra();
	spfa *B = new spfa();

	clock_t t = clock();
    A->getInfo("/Users/luodian/Desktop/DSA/Shortest Path/Shortest Path/DATA/Bigdata.txt");
    A->findans();
    t = clock() - t;

    cout<<"\nDjikstra :\n";
    cout<<"The shortest path cost: "<<A->ans()<<".\n";
    cout<<"The time efficiency: "<<float(t) / CLOCKS_PER_SEC<<" s.\n";

    t = clock();
    B->getInfo("/Users/luodian/Desktop/DSA/Shortest Path/Shortest Path/DATA/Bigdata.txt");
    B->findans();
    t = clock() - t;

    cout<<"\nSPFa :\n";
    cout<<"The shortest path cost: "<<B->ans()<<".\n";
    cout<<"The time efficiency: "<<float(t) / CLOCKS_PER_SEC<<" s.\n";

    delete A;
    delete B;

}

int main(int argc, const char * argv[]) 
{
	freopen("/Users/luodian/Desktop/DSA/Shortest Path/Shortest Path/DATA/out.txt","w",stdout);
	cout<<"1. Validation of Three algorithm\n\n";
    TestA();
    TestB();
    cout<<"\n2. Dense graph test\n\n";
    mediumData();
    cout<<"\n3. Bigdata test\n\n";
    bigDataTest();
    cout<<"\n";
    return 0;
}
