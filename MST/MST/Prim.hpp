//
//  Prim.hpp
//  MST
//
//  Created by 李博 on 10/04/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#ifndef Prim_h
#define Prim_h

#include "Header.hpp"

using namespace std;

class Prim
{
private:
	int Gm[maxn][maxn];
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
		bool operator < (const edge &rhs) const
		{ 
			return w > rhs.w;
		}
	};
	vector<edge> G[maxn];
	vector<edge> TreeEdge;
	bool vis[maxn];
	int n,m;

	void init()
	{
		memset(vis,0,sizeof(vis));
		memset(Gm,0,sizeof(Gm));
		TreeEdge.clear();
		for (int i = 0; i < maxn; ++i)
		{
			G[i].clear();
		}
	}

public:
	Prim()
	{
		init();
	}
	~Prim()
	{
		//pass
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
			Gm[u][v] = Gm[v][u] = w;
			G[u].push_back(edge(u,v,w));
			G[v].push_back(edge(v,u,w));
		}
		infile.close();
	}

	unsigned long long getAns()
	{
		priority_queue<edge> Q;
		while(!Q.empty())
		{
			Q.pop();
		}
		for (int i = 0; i < G[1].size(); ++i)
		{
			edge E;
            E.u = 1;
			E.v = G[1][i].v;
			E.w = G[1][i].w;
			Q.push(E);
		}
		vis[1] = 1;
		int _cnt = 0;
		long long _sum = 0;
		while(!Q.empty())
		{
			edge E = Q.top();
			Q.pop();
			if (vis[E.v] == 1)
			{
				continue;
			}
			vis[E.v] = 1;
			_cnt ++;
			_sum += E.w;
			TreeEdge.push_back(E);
			for (int i = 0; i < G[E.v].size(); ++i)
			{
				edge nextEdge = G[E.v][i];
				if (vis[nextEdge.v] == 0)
				{
					Q.push(nextEdge);
				}
			}	
		}
		if (_cnt != n - 1)
		{
			cout<<"Can't find a mst.\n";
			return 0;
		}
		else
		{
			return _sum;
		}
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
            for (int j = 0; j < G[i].size(); ++j)
            {
                cout<<G[i][j].v<<" ";
            }
            cout<<"\n";
        }
    }

    void outputEdge()
    {
        int u,v,w;
        for (int i = 0; i < TreeEdge.size(); ++i)
        {
            u = TreeEdge[i].u;
            v = TreeEdge[i].v;
            w = TreeEdge[i].w;
            if (i != TreeEdge.size() - 1)
            {
            	cout<<u<<" "<<v<<" "<<w<<"\n";
            }
            else
            {
            	cout<<u<<" "<<v<<" "<<w;;
            }
        }
        cout<<"\n";
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
            outfile<<TreeEdge.size()<<"\n";
            for (int i = 0; i < TreeEdge.size(); ++i)
            {
                u = TreeEdge[i].u;
                v = TreeEdge[i].v;
                w = TreeEdge[i].w;
                if (i != TreeEdge.size() - 1)
                {
                	outfile<<u<<" "<<v<<" "<<w<<"\n";
                }
                else
                {
                	outfile<<u<<" "<<v<<" "<<w;;
                }
            }
        }
    }

};


#endif /* Prim_h */
