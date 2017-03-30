//
//  main.cpp
//  Threading Plus
//
//  Created by 李博 on 17/03/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#include "Threading.hpp"


const int maxn = 10005;
vector<int> Tree[maxn];
vector<bool> vis;
int pre[maxn];

void init(int n)
{
    vis.clear();
    vis.resize(maxn);
    for (int i = 0; i < maxn; ++i)
    {
        Tree[i].clear();
    }
    for (int i = 0; i < n; ++i)
    {
        pre[i] = i;
    }
}

int find(const int &x)
{
    return pre[x] == x ? x : pre[x] = find(pre[x]);
}

//dfs的过程建树
void dfs(int cur,int father)
{
    if (vis[cur] == 1)
    {
        return;
    }
    else
    {
        for (int i = 0; i < cur.size(); ++i)
        {
            int next = Tree[cur][i];

        }
    }
}

//m为传入边数的参数
//n为传入点的参数
//注意 m <= (n*n)/2;
void genUfs(int n,int m)
{
    fstream out;
    out.open("/Users/luodian/Desktop/out.txt",ios::out | ios::binary);

    unsigned int seed = (unsigned int)chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(0,10000);
    auto dice = bind(distribution,generator);
    set<pair<int,int>> EdgeSet;

    EdgeSet.clear();
    while(EdgeSet.size() != m)
    {
        int u = dice();
        int v = dice();
        out<<u<<" "<<v<<"\n";

        pair<int,int> foo;
        foo = make_pair(u,v);
        //没有自环，没有重边
        if (u != v && EdgeSet.find(foo) != EdgeSet.end())
        {
            EdgeSet.insert(foo);
        }
    }

    init();
    //UFS去环，保证是一颗无根树
    for (auto itr : EdgeSet)
    {
        int u = itr.first;
        int v = itr.second;
        int fu = find(u);
        int fv = find(v);
        if (fv != fu)
        {
            fv = pre[fu];
            pair<int,int> foo;
            foo = make_pair(u,v);
            EdgeSet.erase(foo);
        }
    }

    //建立无根树
    for (auto itr : EdgeSet)
    {
        int u = itr.first;
        int v = itr.second;
        Tree[u].push_back(v);
        Tree[v].push_back(u);
    }

}



int main(int argc, const char * argv[])
{

    genUfs(2,3);
    ThreadingTree<char> pre,post;
    // cout<<"**************************************\n";
    // 
    cout<<"Create Tree from preorder: "; 
    string order = "ABDH##I##E##CF#J##G##";

    pre.ThreadingPreTree(order);

    cout<<order<<"\n\n";

    cout<<"The tree is : \n\n";

    pre.Display();


    cout<<"Treading tree to preorder traversal: ";
    pre.ThreadingPreTree(order);
    pre.PreOrder();
    cout<<"\n";

    cout<<"Treading tree to post order traversal: ";
    post.ThreadingPostTree(order);
    post.PostOrder();
    cout<<"\n";
    return 0;
}
