//
//  main.cpp
//  Graph Plus
//
//  Created by 李博 on 11/04/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#include "Header.hpp"
#include "Biconnected_Component.hpp"
#include "Strong_Connected_Component.hpp"

using namespace std;

int main()
{
    freopen("/Users/luodian/Desktop/DSA/Graph Plus/Graph Plus/DATA/out.txt","w+",stdout);
    cout<<"Part I: Bcc Test\n";
    cout<<"*************************\n";
    Bcc B;
    B.getInfo("/Users/luodian/Desktop/DSA/Graph Plus/Graph Plus/DATA/bcc_in.txt");
    B.outputInfo();

    cout<<"\nPart II: Scc Test\n";
    Tarjan A;
    A.getInfo("/Users/luodian/Desktop/DSA/Graph Plus/Graph Plus/DATA/scc_in.txt");
    A.find_scc();
    A.outputInfo();


    cout<<"\n";
    KorosaJu C;
    C.getInfo("/Users/luodian/Desktop/DSA/Graph Plus/Graph Plus/DATA/scc_in.txt");
    C.find_scc();
    C.outputInfo();

    return 0;
}
