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
    Prim *Prim_pattern = new Prim();
    Prim_pattern->getInfo("/Users/luodian/Desktop/DSA/MST/MST/DATA/in.txt");

    cout<<"The graph info is as below: \n";
    Prim_pattern->outputInfo();

   	cout<<"\n\n*************************************************\n\n";
    cout<<"The minimal cost is : ";
    cout<<Prim_pattern->getAns()<<"\n";
    cout<<"The minimal spanning tree contains edge as below : \n";
    cout<<"Output as form of tuple(u,v,w)\n";
    Prim_pattern->outputEdge();
    Prim_pattern->saveInfo("/Users/luodian/Desktop/DSA/MST/MST/DATA/selected_edge.txt");
}

void time_test()
{
    cout<<"When the graph is a real dense graph\n";
    cout<<"(1000 nodes, 392582 edges.)\n";
    cout<<"If we still using prim to solve it ? \n";
    Prim *Prim2_pattern = new Prim();
    Prim2_pattern->getInfo("/Users/luodian/Desktop/DSA/MST/MST/DATA/densedata.txt");
    cout<<"The minimal cost is : ";
    clock_t t = clock();
    cout<<Prim2_pattern->getAns()<<endl;
    t = clock() - t;
    cout<<"The time cost is : "<<float(t) / CLOCKS_PER_SEC<<"s. \n";

    cout<<"\nIf we use kruskal to solve it ? \n";
    Kruskal *K_pattern = new Kruskal;
    K_pattern->getInfo("/Users/luodian/Desktop/DSA/MST/MST/DATA/densedata.txt");
    cout<<"The minimal cost is : ";
    t = clock();
    cout<<K_pattern->getAns()<<endl;
    t = clock() - t;
    cout<<"The time cost is : "<<float(t) / CLOCKS_PER_SEC<<"s. \n";
}

void midTest()
{
    Kruskal *K = new Kruskal();

    K->getInfo("/Users/luodian/Desktop/DSA/MST/MST/DATA/middata.txt");
    cout<<"The minimal cost is : ";
    clock_t t = clock();
    cout<<K->getAns()<<endl;
    t = clock() - t;
    cout<<"\n";
    cout<<"The time cost is : "<<float(t) / CLOCKS_PER_SEC<<"s. \n";
}

int main(int argc, const char * argv[])
{
 //    freopen("/Users/luodian/Desktop/DSA/MST/MST/DATA/out.txt","w",stdout);
	// cout<<"Part I: Unit Test\n";
	// unit_test();
 //    cout<<"\nPart II: Mid Test\n";
 //    midTest();
	// cout<<"\nPart III: Time Test\n";
	// time_test();
 //    // callPython();
    
    Kruskal *k = new Kruskal;
    k->getInfo("/Users/luodian/Desktop/weight_no_direction_MTG.txt");
    cout<<k->getAns()<<endl;

    Prim *p = new Prim;
    p->getInfo("/Users/luodian/Desktop/weight_no_direction_MTG.txt");
    cout<<p->getAns()<<endl;
    return 0;
}
