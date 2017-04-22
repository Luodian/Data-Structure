//
//  main.cpp
//  Graph Plus
//
//  Created by 李博 on 04/04/2017.
//  Copyright © 2017 李博. All rights reserved.
//
#ifndef Bcc_h
#define Bcc_h
#include "Header.hpp"

using namespace std;

class Bcc
{
private:
	int Gm[maxn][maxn];
	int n,m;
	int Previs[maxn];
	int isCut[maxn];
	int bccNum[maxn];
	int dfs_clock;
	int bcc_cnt;
	int cut_cnt;

	vector<int> G[maxn];
	vector<int> bcc[maxn];

	struct Edge
	{
		int u;
		int v;
		Edge(int input_u = 0,int input_v = 0)
		{
			u = input_u;
			v = input_v;
		}
	};
	//bcc用于存储对应的双联通分量
	stack<Edge> S;
	void init()
	{
		n = 0;
		m = 0;
		for (int i = 0; i < maxn; ++i)
	    {
	    	bcc[i].clear();
	    }
	    while(!S.empty())
	    {
	    	S.pop();
	    }
		mem(Previs);
		mem(isCut);
		mem(bccNum);
		dfs_clock = bcc_cnt = cut_cnt = 0;
	    for (int i = 0; i < maxn; ++i)
	    {
	        G[i].clear();
	    }
	}

	int dfs(int u,int fa)
	{
		int lowu = Previs[u] = ++dfs_clock;
		int child = 0;
		for (int i = 0; i < G[u].size(); ++i)
		{
			int v = G[u][i];
			Edge e(u,v);
			if (Previs[v] == 0)
			{
				S.push(e);
				child ++;
				int lowv = dfs(v,u);
				//割点的判断条件
				//>时为桥
				//=时u-v为割点
				if (lowv >= Previs[u])
				{
					if (isCut[u] == false)
					{
						isCut[u] = true;
						cut_cnt ++;
					}
					bcc_cnt++;
					bcc[bcc_cnt].clear();
					while(1)
					{
						Edge x = S.top();
						S.pop();
						//对割点似乎会被标记成最大的那个bcc编号。
						if (bccNum[x.u] != bcc_cnt)
						{
							bcc[bcc_cnt].push_back(x.u);
							bccNum[x.u] = bcc_cnt;
						}
						if (bccNum[x.v] != bcc_cnt)
						{
							bcc[bcc_cnt].push_back(x.v);
							bccNum[x.v] = bcc_cnt;
						}
						if (x.u == u && x.v == v)
						{
							break;
						}
					}
				}
			}
			//存在反向边v->u的情况。
			else if (Previs[v] < Previs[u] && v != fa)
			{
				S.push(e);
				//用反向边更新自己。
				lowu = min(lowu,Previs[v]);
			}
		}
		//特判最开始访问的点。
		if (fa < 0 && child == 1)
		{
			isCut[u] = 0;
	        cut_cnt --;
		}
		return lowu;
	}
	void findbcc(int n)
	{
		for (int i = 1; i <= n; ++i)
		{
			if (Previs[i] == 0)
			{
	            if (G[i].size() == 0)
	            {
	                bcc_cnt ++;
	                bcc[bcc_cnt].push_back(i);
	            }
				else
	            {
	                dfs(i,-1);
	            }
			}
		}
	}
public:
	Bcc()
	{
		init();
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
			Gm[u][v] = Gm[v][u] = 1;
			G[u].push_back(v);
			G[v].push_back(u);
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
		findbcc(n);
		cout<<"\nIn this graph we can find: "<<cut_cnt<<" cut vertexs\n";
		cout<<"The cut vertex is : ";
		vector<int> ret;
		ret.clear();
		for (int i = 1; i <= n; ++i)
		{
			if (isCut[i] == 1)
			{
				cout<<i<<" ";
				ret.push_back(i);
			}
		}
		cout<<"\n";
		cout<<"In this graph we can find: "<<bcc_cnt<<" biconnected component\n";
		for (int i = 1; i <= bcc_cnt; ++i)
		{
			cout<<"In the "<<i<<"th biconnected component, there are vertexs : ";
			for (int j = 0; j < bcc[i].size(); ++j)
			{
				cout<<bcc[i][j]<<" ";
			}
			cout<<"\n";
		}
	}
};

#endif 
