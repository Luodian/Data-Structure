//
//  main.cpp
//  Homwork4
//
//  Created by 李博 on 2016/12/14.
//  Copyright © 2016年 李博. All rights reserved.
//

#include <iostream>
#include <queue>
#include <vector>
#include <stack>

using namespace std;

#define mem(x) memset(x,0,sizeof(x))
typedef pair<int, int> pii;
const int maxn = 200;
const int inf = 0x3f3f3f3f;
int graph[maxn][maxn];
int Asist[maxn][maxn];
int backup[maxn][maxn];
int ClosureGraph[maxn][maxn];
int n,m;

void InputGraph()
{
	mem(graph);
	mem(backup);
	mem(Asist);
	mem(ClosureGraph);
	cin>>n>>m;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			int u,v,w;
			cin>>u>>v>>w;
			graph[u][v] = w;
		}
	}
}

void PrintMatrix()
{
	for (int i = 1; i <= n; ++i)
	{
		cout<<"\t";
		for (int j = 1; j <= n; ++j)
		{
			if(graph[i][j] != 0)
			{
				cout<<graph[i][j]<<" ";
			}
			else
			{
				cout<<graph[i][j]<<" ";
			}
		}
		cout<<"\n";
	}
}

void copy()
{
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			if (graph[i][j] != 0)
			{
				backup[i][j] = graph[i][j];
			}
			else
			{
				backup[i][j] = inf;
			}
		}
	}
}

void Floyd()
{
	copy();
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			Asist[i][j] = 0;
		}
	}
	for (int k = 1; k <= n; ++k)
	{
		for (int i = 1; i <= n; ++i)
		{
			for (int j = 1; j <= n; ++j)
			{
				if (backup[i][j] > backup[i][k] + backup[k][j])
				{
					backup[i][j] = backup[i][k] + backup[k][j];
					Asist[i][j] = k;
				}
			}
		}
	}
	cout<<"  This is minimal distance matrix: \n\n";
	for (int i = 1;i <= n; ++i)
	{
		cout<<"\t";
		for (int j = 1; j <= n; ++j)
		{
			if(backup[i][j] != inf) cout<<backup[i][j]<<" ";
			else
			{
				cout<<0<<" ";
			}
		}
		cout<<"\n";
	}
	cout<<"\n  This is minimal path matrix: \n\n";
	for (int i = 1;i <= n; ++i)
	{
		cout<<"\t";
		for (int j = 1; j <= n; ++j)
		{
			cout<<Asist[i][j]<<" ";
		}
		cout<<"\n";
	}
	stack<int> Recor;
	Recor.push(n);
	for (int i = Asist[1][n]; i != 0; i = Asist[1][i])
	{
		Recor.push(i);
	}
	Recor.push(1);
	cout<<"\n  Recorded path is : ";
	while(!Recor.empty())
	{
		cout<<Recor.top()<<" ";
		Recor.pop();
	}
	cout<<"\n";
}

void closure()
{
	mem(ClosureGraph);
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			if (graph[i][j] != 0)
			{
				ClosureGraph[i][j] = 1;
			}
		}
	}
	for (int k = 1; k <= n; ++k)
	{
		for (int i = 1;i <= n; ++i)
		{
			for (int j = 1; j <= n; ++j)
			{
				if (ClosureGraph[i][k] != 0 && ClosureGraph[k][j] != 0)
				{
					ClosureGraph[i][j] = 1;
				}
			}
		}
	}
	for (int i = 1;i <= n; ++i)
	{
		cout<<"\t";
		for (int j = 1; j <= n; ++j)
		{
			cout<<ClosureGraph[i][j]<<" ";
		}
		cout<<"\n";
	}
}

struct Edge
{
    int from,to,dist;
    Edge(int u,int v,int w):from(u),to(v),dist(w){}
};

struct Diji
{
    int Edge_size;
    int Node_size;
    struct HeapNode
    {
        int w,u;
        bool operator < (const HeapNode & rhs) const
        {
            return w > rhs.w;
        }
    };
    vector <Edge> edges;//用于保存边的具体信息。
    vector <int> G[maxn];
    bool vis[maxn];
    int dist[maxn];
    int parent[maxn];
    void init(int n)
    {
        this->Node_size = n;
        mem(parent);
        for (int i = 0; i <= n; i++)
        {
            G[i].clear();
        }
        edges.clear();
    }
    void AddEdge(int from,int to,int dist)
    {
        edges.push_back(Edge(from,to,dist));
        Edge_size = (int)edges.size();//边的计数器
        G[from].push_back(Edge_size-1);//m-1代表边号
    }
    void FindPath(int s)
    {
        priority_queue<pii,vector<pii>,greater<pii>>  Q;
        for (int i = 0; i <= n; i++)
        {
            dist[i] = inf;
        }
        dist[s] = 0;
        memset(vis,0,sizeof(vis));
        Q.push(make_pair(dist[s],s));
        while (!Q.empty())
        {
            pii x = Q.top();
            Q.pop();
            int u = x.second;
            if (!vis[u])
            {
                vis[u] = 1;
                for (int i = 0; i < G[u].size(); ++i)
                {
                    Edge & e = edges[G[u][i]];
                    if (dist[e.to] > dist[u] + e.dist)
                    {
                        dist[e.to] = dist[u] + e.dist;
                        parent[e.to] = e.from;
                        //路径记录
                        //for (int j = p[n];j;j = p[edges[j].to])
                        //{
                        //  cout<<j.from<<endl;
                        //}
                        //通过这样的方式来访问路径。。感觉挺复杂的。。
                        Q.push(make_pair(dist[e.to],e.to));
                    }
                }
            }
        }
    }
    void ShowPath(int s,int t)
    {
    	cout<<"  The Shortest Path Is : ";
        stack<int> path;
        path.push(t);
        for (int i = parent[t]; i != s; i = parent[i])
        {
            path.push(i);
        }
        path.push(s);
        while(!path.empty())
        {
        	cout<<path.top()<<" ";
        	path.pop();
        }
        cout<<"\n";
    }
}my;

void InputList()
{
	cin>>n>>m;
	my.init(n);
	for (int i = 0; i < m; ++i)
	{
		int u,v,w;
		cin>>u>>v>>w;
		my.AddEdge(u,v,w);
	}
}


//找出每个节点对于ed的最短路径
void Use_Diji_mu2one(int ed)
{
	for (int i = 1; i <= n; ++i)
	{
		if (i != ed)
		{
			mem(my.dist);
			mem(my.parent);
			my.FindPath(i);
			if (my.dist[ed] != inf) 
			{
				cout<<"  From source "<<i<<" to "<<ed<<" the minimal distance is : "<<my.dist[ed]<<"\n";
				cout<<"  The path is:";
				my.ShowPath(i,ed);
				cout<<"\n";
			}
			else
			{
				cout<<"  From source "<<i<<" to "<<ed<<" there is no connected path\n";
			}
		}
	}
	cout<<"\n";
}

void Use_Diji_o2o(int st,int ed)
{
	mem(my.dist);
	mem(my.parent);
	my.FindPath(st);
	if (my.dist[ed] != inf) 
	{
		cout<<"  From source "<<st<<" to "<<ed<<" the minimal distance is : "<<my.dist[ed]<<"\n";
		cout<<"  The path is:";
		my.ShowPath(st,ed);
		cout<<"\n";
	}
	else
	{
		cout<<"  From source "<<st<<" to "<<ed<<" there is no connected path\n";
	}
}

int main(int argc, const char * argv[]) 
{
	freopen("/Users/luodian/Desktop/Codes/DSA/Homwork4/Homwork4/in.txt","r",stdin);
	InputList();
    InputGraph();
	cout<<"******** We have read the graph and construct a adjacent matrix as follow ********\n\n";
	PrintMatrix();
	cout<<"\n1.Use Dijikstra Find Single Point Shortest Path and Record it\n\n";
	my.FindPath(1);
	cout<<"  From Source "<<1<<" to "<<n<<" the minimal distance is : "<<my.dist[n]<<"\n";
    my.ShowPath(1,10);
    cout<<"\n2.Use Floyd method Find MultiPoint's Shortest Path and Record it\n\n";
    Floyd();
	cout<<"\n3.Use Dijikstra method to Find MultiPoint To One Point Shortest Path \n\n";
	Use_Diji_mu2one(9);
	cout<<"\n4.Use Dijikstra method to Find One To One Point Shortest Path \n\n";
	Use_Diji_o2o(3,9);
	cout<<"\n5.Use Floyd_warshall Method To Caculate Closure Matrix\n\n";
	closure();
    return 0;
}
