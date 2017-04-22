//
//  spfa.hpp
//  Shortest Path
//
//  Created by 李博 on 12/04/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#ifndef spfa_h
#define spfa_h

#include "Header.hpp"

using namespace std;

class spfa
{
private:
    // int Gm[maxn][maxn];
    struct edge
    {
        int u;
        int v;
        int w;
        edge(int uu = 0,int vv = 0,int ww = 0)
        {
            u = uu;
            v = vv;
            w = ww;
        }
    };

    vector<edge> G[maxn];
    vector<int> path;
    int parent[maxn];
    int dist[maxn];
    bool vis[maxn];
    int c[maxn];
    int n,m;
    void init()
    {
        memset(dist,0,sizeof(dist));
        memset(parent,0,sizeof(parent));
        path.clear();
        memset(vis,0,sizeof(vis));
        // memset(Gm,0,sizeof(Gm));
        for (int i = 0; i < maxn; ++i)
        {
            G[i].clear();
        }
    }
    bool FindPath(int s)
    {   
        queue<int> Q;
        for (int  i = 1; i <= n; ++i)
        {
            dist[i] = INF;
        }
        mem(c);
        Q.push(s);
        dist[s] = 0;
        vis[s] = 1;
        c[s] = 1;

        while(!Q.empty())
        {
            int x = Q.front();
            Q.pop();
            vis[x] = 0;
            for (int i = 0; i < G[x].size(); ++i)
            {
                edge nextEdge = G[x][i];
                int next = nextEdge.v;
                if (dist[next] > dist[x] + nextEdge.w)
                {
                    dist[next] = dist[x] + nextEdge.w;
                    if (!vis[next])
                    {
                        vis[next] = 1;
                        c[next] ++;
                        Q.push(next);
                        if (c[next] > n)
                        {
                            return 0;
                        }
                    }
                }
            }
        }
        return 1;
    }
    
public:
    spfa()
    {
        init();
    }
    ~spfa()
    {
        //
    }
    void getInfo(const string &filepath)
    {
        fstream infile;
        infile.open(filepath,ios::in);
        
        int u,v,w;
        infile>>n>>m;
        for (int i = 0; i < m; ++i)
        {
            infile>>u>>v>>w;
            // Gm[u][v] = w;
            G[u].push_back(edge(u,v,w));
        }
        infile.close();
    }
    bool findans()
    {
        return FindPath(1);
    }
    void outputInfo()
    {
        // cout<<"The adjacent matrix view is : \n";
        // for (int i = 1; i <= n; ++i)
        // {
        //     for (int j = 1; j <= n; ++j)
        //     {
        //         cout<<Gm[i][j]<<" ";
        //     }
        //     cout<<"\n";
        // }
        // cout<<"\n";
        cout<<"The edge side view is : \n";
        for (int i = 1; i <= n; ++i)
        {
            cout<<"For node "<<i<<" there's out edge : ";
            for (int j = 0; j < G[i].size(); ++j)
            {
                cout<<G[i][j].v<<" ";
            }
            cout<<"\n";
        }
        cout<<"\n";
    }
    int ans()
    {
        return dist[n];
    }
    
};
#endif /* spfa_h */
