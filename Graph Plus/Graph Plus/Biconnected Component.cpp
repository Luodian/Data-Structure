//
//  main.cpp
//  Graph Plus
//
//  Created by 李博 on 04/04/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#include "Header.hpp"

using namespace std;
#define mem(x) memset(x,0,sizeof(x))
const int maxn = 15;
int Previs[maxn];
int isCut[maxn];
int BccNum[maxn];
int dfs_clock;
int bcc_cnt;
int cut_cnt;

vector<int> G[maxn];
vector<int> Bcc[maxn];
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
//Bcc用于存储对应的双联通分量

stack<Edge> S;
void init(int n)
{
	for (int i = 0; i <= n; ++i)
    {
    	Bcc[i].clear();
    }
    while(!S.empty())
    {
    	S.pop();
    }
	mem(Previs);
	mem(isCut);
	mem(BccNum);
	dfs_clock = bcc_cnt = cut_cnt = 0;
    for (int i = 0; i <= n; ++i)
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
				Bcc[bcc_cnt].clear();
				while(1)
				{
					Edge x = S.top();
					S.pop();
					//对割点似乎会被标记成最大的那个Bcc编号。
					if (BccNum[x.u] != bcc_cnt)
					{
						Bcc[bcc_cnt].push_back(x.u);
						BccNum[x.u] = bcc_cnt;
					}
					if (BccNum[x.v] != bcc_cnt)
					{
						Bcc[bcc_cnt].push_back(x.v);
						BccNum[x.v] = bcc_cnt;
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

void findBcc(int n)
{
	for (int i = 1; i <= n; ++i)
	{
		if (Previs[i] == 0)
		{
            if (G[i].size() == 0)
            {
                bcc_cnt ++;
                Bcc[bcc_cnt].push_back(i);
            }
			else
            {
                dfs(i,-1);
            }
		}
	}
}

void printA()
{
	cout<<"The graph A is:\n";
	cout<<"\t1 -------- 2\n";
	cout<<"\t| \\        |\n";
	cout<<"\t|   \\      |\n";
	cout<<"\t|     \\    |\n";
	cout<<"\t|       \\  |\n";
	cout<<"\t3 -------- 4\n";
	cout<<"\t|        / |\n";
	cout<<"\t|      /   |\n";
	cout<<"\t|    /     |\n";
	cout<<"\t|  /       |\n";
    cout<<"\t5          6\n";
}

void getInfo(int &n,int &m)
{
	cin>>n>>m;
	init(n);
	for (int i = 0; i < m; ++i)
	{
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
}

void feedans(int n)
{
	findBcc(n);
	cout<<"\nIn this graph we can find: "<<cut_cnt<<" cut vertexs\n";
	cout<<"The cut vertex is : ";
	for (int i = 1; i <= n; ++i)
	{
		if (isCut[i] == 1)
		{
			cout<<i<<" ";
		}
	}
	cout<<"\n";
	cout<<"In this graph we can find: "<<bcc_cnt<<" biconnected component\n";
	for (int i = 1; i <= bcc_cnt; ++i)
	{
		cout<<"In the "<<i<<"th biconnected component, there are vertexs : ";
		for (int j = 0; j < Bcc[i].size(); ++j)
		{
			cout<<Bcc[i][j]<<" ";
		}
		cout<<"\n";
	}
}

void printB()
{
	cout<<"\nThe graph B is:\n";
	cout<<"\t1 ------- 2\n";
	cout<<"\t|          \n";
	cout<<"\t|          \n";
	cout<<"\t|          \n";
	cout<<"\t3         4\n";
	cout<<"\t|  \\     \n";
	cout<<"\t|    \\   \n";
	cout<<"\t|      \\ \n";
	cout<<"\t5 ------- 6\n";
}


int main(int argc, const char * argv[]) 
{
	freopen("/Users/luodian/Desktop/in.txt","r",stdin);
	int n,m;
	getInfo(n,m);
	printA();
	feedans(n);

	getInfo(n,m);
	printB();
	feedans(n);
    return 0;
}
