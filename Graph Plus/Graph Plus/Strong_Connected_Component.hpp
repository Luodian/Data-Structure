//
//  Strong Connected Component.h
//  Graph Plus
//
//  Created by 李博 on 11/04/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#ifndef Strong_Connected_Component_h
#define Strong_Connected_Component_h
#include "Header.hpp"

using namespace std;

class Tarjan
{
private:
	int graph[maxn][maxn];
	int n,m;
	vector<int> G[maxn];
	int pre[maxn];
	int sccno[maxn];
	vector<int> scc[maxn];
	int dfs_clock;
	int scc_cnt;
	stack<int> backPoint;
	void init()
	{
		for (int i = 0; i < maxn; ++i)
		{
			scc[i].clear();
			G[i].clear();
		}
		mem(pre);
		mem(sccno);
		mem(graph);
		dfs_clock = 0;
		scc_cnt = 0;
		while(!backPoint.empty())
		{
			backPoint.pop();
		}
	}
	int dfs(int u)
	{
		int lowlinku = pre[u] = ++dfs_clock;
		backPoint.push(u);
		for (int i = 0; i < G[u].size(); ++i)
		{
			int v = G[u][i];
			if (!pre[v])
			{
				int lowlinkv = dfs(v);
				lowlinku = min(lowlinku,lowlinkv);
			}
			//存在可以回退的点
			else if (!sccno[v])
			{
				lowlinku = min(lowlinku,pre[v]);
			}
		}
		if (lowlinku == pre[u])
		{
			scc_cnt ++;
			scc[scc_cnt].clear();
			while(1)
			{
				int x = backPoint.top();
                backPoint.pop();
				sccno[x] = scc_cnt;
				scc[scc_cnt].push_back(x);
				if (x == u)
				{
					break;
				}
			}
		}
		return lowlinku;
	}
public:
	Tarjan()
	{
		init();
	}
	~Tarjan()
	{
		//
	}
	void find_scc()
	{
		dfs_clock = scc_cnt = 0;
		mem(sccno);
		mem(pre);
		for (int i = 1; i <= n; ++i)
		{
			if (!pre[i])
			{
				dfs(i);
			}
		}
	}
	void getInfo(const string &filepath)
	{
		fstream infile;
		infile.open(filepath,ios::in);
		infile>>n>>m;
		for (int i = 0; i < m; ++i)
		{
			int u,v;
			infile>>u>>v;
			graph[u][v] = 1;
			G[u].push_back(v);
		}
	}
	void outputInfo()
	{
		cout<<"In this graph, we can find: "<<scc_cnt<<" strong connected component.\n";
		for (int i = 1; i <= scc_cnt; ++i)
		{
			cout<<"In the "<<i<<" th scc, there are vertexs : ";
			for (int j = 0; j < scc[i].size(); ++j)
			{
				cout<<scc[i][j]<<" ";
			}
			cout<<"\n";
		}
	}
	void saveInfo(const string &filepath)
	{
		fstream outfile;
		outfile.open(filepath,ios::out);
		outfile<<n<<m<<"\n";
		outfile<<scc_cnt<<"\n";
		for (int i = 1; i <= scc_cnt; ++i)
		{
			for (int j = 0; j < scc[i].size(); ++j)
			{
				if (j != scc[i].size() - 1)
				{
					outfile<<scc[i][j]<<" ";
				}
				else
				{
					outfile<<scc[i][j]<<"\n";
				}
			}
		}
	}
};

class KorosaJu
{

private:
	int Gm[maxn][maxn];
	int n,m;
	vector<int> G[maxn];

	//存反向边
	vector<int> G2[maxn];

	vector<int> reverse;
	vector<int> scc[maxn];
	int vis[maxn];
	int sccno[maxn];
	int scc_cnt;

	void init()
	{
		for (int i = 0; i < maxn; ++i)
		{
			G[i].clear();
			G2[i].clear();
			scc[i].clear();
		}
		reverse.clear();
        reverse.push_back(0);
		mem(vis);
		mem(sccno);
		scc_cnt = 0;
	}
	void dfs1(int u)
	{
		if (vis[u])
		{
			return;
		}
		vis[u] = 1;
		for (int i = 0; i < G[u].size(); ++i)
		{
			dfs1(G[u][i]);
		}
		reverse.push_back(u);
	}
	void dfs2(int u)
	{
		if (sccno[u])
		{
			return;
		}
		sccno[u] = scc_cnt;
		scc[scc_cnt].push_back(u);
		for (int i = 0; i < G2[u].size(); ++i)
		{
			dfs2(G2[u][i]);
		}
	}
public:
	KorosaJu()
	{
		init();
	}
	~KorosaJu()
	{
		
	}
	void find_scc()
	{
		scc_cnt = 0;
		reverse.clear();
        reverse.push_back(0);
		mem(vis);
		mem(sccno);
		for (int i = 1; i <= n; ++i)
		{
			dfs1(i);
		}
		for (int i = n; i >= 1; --i)
		{
			if (!sccno[reverse[i]])
			{
				scc_cnt ++;
				dfs2(reverse[i]);
			}
		}
	}

	void getInfo(const string &filepath)
	{
		fstream infile;
		infile.open(filepath,ios::in);
		infile>>n>>m;
		for (int i = 0; i < m; ++i)
		{
			int u,v;
			infile>>u>>v;
			Gm[u][v] = 1;
			G[u].push_back(v);
			G2[v].push_back(u);
		}
	}

	void outputInfo()
	{
		
        cout<<"The adjacent matrix view is : \n";
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                cout<<Gm[i][j]<<" ";
            }
            cout<<"\n";
        }
        cout<<"The edge side view is : \n";
        for (int i = 1; i <= n; ++i)
        {
            cout<<"For node "<<i<<" its adjacent nodes are : ";
            for (int j = 0; j < G[i].size(); ++j)
            {
                cout<<G[i][j]<<" ";
            }
            cout<<"\n";
        }
        cout<<"\n";
		cout<<"In this graph, we can find: "<<scc_cnt<<" strong connected component.\n";
		for (int i = 1; i <= scc_cnt; ++i)
		{
			cout<<"In the "<<i<<" th scc, there are vertexs : ";
			for (int j = 0; j < scc[i].size(); ++j)
			{
				cout<<scc[i][j]<<" ";
			}
			cout<<"\n";
		}
	}

	void saveInfo(const string &filepath)
	{
		fstream outfile;
		outfile.open(filepath,ios::out);
		outfile<<n<<m<<"\n";
		outfile<<scc_cnt<<"\n";
		for (int i = 1; i <= scc_cnt; ++i)
		{
			for (int j = 0; j < scc[i].size(); ++j)
			{
				if (j != scc[i].size() - 1)
				{
					outfile<<scc[i][j]<<" ";
				}
				else
				{
					outfile<<scc[i][j]<<"\n";
				}
			}
		}
	}
};

#endif /* Strong_Connected_Component_h */
