//
//  Kruskal.hpp
//  MST
//
//  Created by 李博 on 09/04/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#ifndef Kruskal_h
#define Kruskal_h

#include "Header.hpp"

using namespace std;

class Kruskal
{
private:
    //领接矩阵存图
    int Gm[maxn][maxn];
    int n,m;

    //领接表存边
    struct edge
    {
        int u,v,w;
        edge(int uu = 0,int vv = 0,int ww = 0)
        {
            u = uu;
            v = vv;
            w = ww;
        }
        bool operator < (const edge &rhs) const
        {
            return w < rhs.w;
        }
    };
    vector<edge> Edges;
    vector<int> EdgeList[maxn];
    vector<edge> TreeEdge;

    int pre[maxn];

    void init()
    {
        for (int i = 0; i < maxn; ++i)
        {
            pre[i] = i;
        }
        Edges.clear();
        TreeEdge.clear();
        for (int i = 0; i < maxn; ++i)
        {
            EdgeList[i].clear();
        }
    }
    int find(int u)
    {
        return u == pre[u] ? u : pre[u] = find(pre[u]);
    }
public:
    Kruskal()
    {
        init();
    }
    ~Kruskal()
    {
        //pass;
    }
    unsigned long long getAns()
    {
        unsigned long long _sum = 0;
        sort(Edges.begin(),Edges.begin() + Edges.size());
        for (int i = 0; i < Edges.size(); ++i)
        {
            int u = Edges[i].u;
            int v = Edges[i].v;
            
            int fu = find(u);
            int fv = find(v);
            
            if (fu != fv)
            {
                _sum += Edges[i].w;
                pre[fu] = fv;
                TreeEdge.push_back(Edges[i]);
            }
            if (TreeEdge.size() == n - 1)
            {
                break;
            }
        }
        if (TreeEdge.size() != n - 1)
        {
            cout<<"Can't find a mst.\n";
            return 0;
        }
        else
        {
            return _sum;
        }
    }

    void getInfo(const string &filepath)
    {
        fstream infile;
        infile.open(filepath,ios::in);

        infile>>n>>m;
        for (int i = 0; i < m; ++i)
        {
            int u,v,w;
            infile>>u>>v>>w;
            Gm[u][v] = Gm[v][u] = w;
            EdgeList[u].push_back(v);
            EdgeList[v].push_back(u);
            edge e(u,v,w);
            Edges.push_back(e);
        }
        infile.close();
    }

    void outputInfo()
    {
        cout<<"The adjacent matrix view is : \n";
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                cout<<Gm[i][j]<<" ";
            }
            cout<<"\n";
        }
        cout<<"The edge side view is : \n";
        for (int i = 0; i < n; ++i)
        {
            cout<<"For node "<<i<<" there's out edge : ";
            for (int j = 0; j < EdgeList[i].size(); ++j)
            {
                cout<<EdgeList[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    void saveInfo(const string &filepath)
    {
        fstream outfile;
        outfile.open(filepath,ios::out);
        if (!outfile.is_open())
        {
            cout<<"Open failed\n";
        }
        else
        {
            int u,v,w;
            outfile<<"The selected edge is: \n";
            for (int i = 0; i < TreeEdge.size(); ++i)
            {
                u = TreeEdge[i].u;
                v = TreeEdge[i].v;
                w = TreeEdge[i].w;
                outfile<<u<<" "<<v<<" "<<w<<"\n";
            }
        }
    }
};

#endif /* Kruskal_h */
