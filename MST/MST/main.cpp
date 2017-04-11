//
//  main.cpp
//  MST
//
//  Created by 李博 on 09/04/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#include "python2.7/python.h"
#include "Header.hpp"
#include "Kruskal.hpp"
#include "Prim.hpp"

using namespace std;

void unit_test()
{
    // freopen("/Users/luodian/Desktop/DSA/MST/MST/DATA/in.txt","r",stdin);


    cout<<"When graph is a sparse graph\n\n";
    cout<<"*************************************************\n";
    cout<<"Now using Prim algorithm to generate mst: \n";
    Prim Prim_pattern;
    Prim_pattern.getInfo("/Users/luodian/Desktop/DSA/MST/MST/DATA/in.txt");

    cout<<"The graph info is as below: \n";
    Prim_pattern.outputInfo();

   	cout<<"\n\n*************************************************\n\n";
    cout<<"The minimal cost is : ";
    cout<<Prim_pattern.getAns()<<"\n";
    cout<<"The minimal spanning tree contains edge as below : \n";
    cout<<"Output as form of tuple(u,v,w)\n";
    Prim_pattern.outputEdge();
    Prim_pattern.saveInfo("/Users/luodian/Desktop/DSA/MST/MST/DATA/selected_edge.txt");
}

void time_test()
{
    cout<<"When the graph is a real dense graph\n\n";
    cout<<"If we still using prim to solve it ? \n";
    Prim Prim2_pattern;
    Prim2_pattern.getInfo("/Users/luodian/Desktop/DSA/MST/MST/DATA/bigdata.txt");
    clock_t t = clock();
    cout<<"The minimal cost is : ";
    cout<<Prim2_pattern.getAns()<<endl;
    t = clock() - t;
    cout<<"The time cost is : "<<float(t) / CLOCKS_PER_SEC<<"s. \n";

    cout<<"If we use kruskal to solve it ? \n";
    Kruskal K_pattern;
    K_pattern.getInfo("/Users/luodian/Desktop/DSA/MST/MST/DATA/bigdata.txt");
    cout<<"The minimal cost is : ";
    t = clock();
    cout<<K_pattern.getAns()<<endl;
    t = clock() - t;
    cout<<"The time cost is : "<<float(t) / CLOCKS_PER_SEC<<"s. \n";
}

void callPython()
{

    // Py_Initialize(); /*初始化python解释器,告诉编译器要用的python编译器*/
    // PyRun_SimpleString("import midSize"); 调用python文件
    // PyRun_SimpleString("midSize.__main__");/*调用python文件中的函数*/
    // Py_Finalize(); /*结束python解释器，释放资源*/
}
int main(int argc, const char * argv[])
{
    freopen("/Users/luodian/Desktop/DSA/MST/MST/DATA/out.txt","w",stdout);
	cout<<"Part I: Unit Test\n";
	unit_test();
	cout<<"Part II: Time Test\n";
	time_test();
    callPython();
    return 0;
}
