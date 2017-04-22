//
//  djikstra.hpp
//  Shortest Path
//
//  Created by 李博 on 11/04/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#ifndef djikstra_h
#define djikstra_h

#include "Header.hpp"

using namespace std;

class djikstra
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
	struct HeapNode
	{
		int d;
		int u;
		HeapNode(int _d = 0,int _u = 0)
		{
			d = _d;
			u = _u;
		}
		bool operator < (const HeapNode & rhs) const
		{
			return d > rhs.d;
		}
	};
	vector<edge> G[maxn];
	stack<int> reversePoint;
	vector<int> path;
	int parent[maxn];
	int dist[maxn];
	bool vis[maxn];
	int n,m;
	void init()
	{
		while(!reversePoint.empty())
		{
			reversePoint.pop();
		}
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
        priority_queue<HeapNode>  Q;
        for (int i = 0; i <= n; i++)
        {
            dist[i] = INF;
        }
        dist[s] = 0;
        memset(vis,0,sizeof(vis));
        Q.push(HeapNode(0,s));
        bool flag = 0;
        while (!Q.empty())
        {
        	if (Q.size() == 1000000)
        	{
        		flag = 1;
        		break;
        	}
            HeapNode x = Q.top();
            Q.pop();
            int u = x.u;
            if (!vis[u])
            {
                vis[u] = 1;
                for (int i = 0; i < G[u].size(); ++i)
                {
                    edge e = G[u][i];
                    if (dist[e.v] > dist[u] + e.w)
                    {
                        dist[e.v] = dist[u] + e.w;
                       	parent[e.v] = u;
                        //路径记录
                        //for (int j = p[n];j;j = p[edges[j].to])
                        //{
                        //  cout<<j.from<<endl;
                        //}
                        //通过这样的方式来访问路径。。感觉挺复杂的。。
                        Q.push(HeapNode(dist[e.v],e.v));
                    }
                }
            }
        }
        if (flag == 1)
        {
        	cout<<"Error, there may exists negative circle\n";
        	return 0;
        }
        else
        {
        	return 1;
        }
    }
    void getPath(int s,int t)
    {
        reversePoint.push(t);
        for (int i = parent[t]; i != s; i = parent[i])
        {
            reversePoint.push(i);
        }
        reversePoint.push(s);
        while(!reversePoint.empty())
        {
        	path.push_back(reversePoint.top());
        	reversePoint.pop();
        }
    }
    
public:
	djikstra()
	{
		init();
	}
	~djikstra()
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
	void printPath()
	{
		getPath(1,n);
    	cout<<"The Shortest Path Is : ";
		for (int i = 0; i < path.size(); ++i)
		{
			cout<<path[i]<<" ";
		}
		cout<<"\n";
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
        if (findans())
        {
	       	printPath();
	       	cout<<"The shortest cost is : "<<dist[n]<<".\n";
        }
        cout<<"\n";
    }
    int ans()
    {
    	return dist[n];
    }
};


#endif /* djikstra_h */
