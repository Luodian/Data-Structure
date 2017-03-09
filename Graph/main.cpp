//
//  main.cpp
//  Expriment3-Graph
//
//  Created by 李博 on 2016/11/29.
//  Copyright © 2016年 李博. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include "Ortho.cpp"
#include "Tree.cpp"
using namespace std;

//邻接矩阵存储结构
int graph[maxn][maxn];
vector<int> DFSN,BFSN;
vector<int> BfsSq;
int CntForBfs;
int n,m;
bool VisForGraph[maxn];
bool VisForOLG[maxn];
string PreOrder;
vector<ArcTuple> TupleVec;

//邻接表存储结构
struct edge_info
{
	int v;
	int next;
	int weight;
	edge_info(int a = 0,int b = 0,int c = 0):v(a),next(b),weight(c){}
}Edge[maxn*maxn / 2];
int head[maxn];
bool VisForList[maxn];
int CntEdge;

void AddEdge(int u,int v,int w)
{	
	edge_info temp = {v,0,w};
	Edge[CntEdge] = temp;
	Edge[CntEdge].next = head[u];
	head[u] = CntEdge ++;
}

void ConstructList()
{
	CntEdge = 1;
	mem(head);
	mem(Edge);
	for (int i = 0; i < m; ++i)
	{
		int u,v,w;
		cin>>u>>v>>w;
		AddEdge(u,v,w);
	}
}

void ConstructGraph()
{
	mem(graph);
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

void DisplayList()
{
	for (int i = 1; i <= n; ++i)
	{
		cout<<"For Node "<<i<<" it has out nodes: \n";
		for (int j = head[i]; j != 0; j = Edge[j].next)
		{
			cout<<i<<"->"<<Edge[j].v<<": "<<Edge[j].weight<<"\n";
			int u = i;
			int v = Edge[j].v;
			int w = Edge[j].weight;
			ArcTuple foo(u,v,w);
			TupleVec.push_back(foo);
		}
		cout<<"\n";
	}
}


void GTConstructor()
{
	int Mxn = BFSN[BFSN.size() - 1];
	int rear = BfsSq.size() - 1,front = 1;
	int sequences = 2;
	while(front <= rear)
	{	
		int cur = front;
		cout<<"\nFor the root "<<cur<<" it has childs : ";
		for (int i = front; i <= rear; ++i)
		{
			if (BFSN[i] == sequences)
			{
				cout<<BfsSq[i]<<" ";
			}
		}
		cout<<"\n";
		front ++;
		sequences++;
		if (sequences > Mxn)
		{
			break;
		}
	}
}

void DisplayMatrix()
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
				cout<<"*"<<" ";
			}
		}
		cout<<"\n";
	}
}

//矩阵转换为邻接表
void Matrix2List(int n)
{
	vector<ArcTuple> TempUse;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			if (graph[i][j] != 0)
			{
				ArcTuple foo(i,j,graph[i][j]);
				TempUse.push_back(foo);
			}
		}
	}
    CntEdge = 1;
	for (int i = 0; i < TempUse.size(); ++i)
	{
		int u,v,w;
		tie(u,v,w) = TempUse[i];
		AddEdge(u,v,w);
	}
}

//邻接表转换成矩阵
void List2Matrix()
{
	for (int i = 1; i <= n; ++i)
	{
		for (int j = head[i]; j ; j = Edge[j].next)
		{
			graph[i][Edge[j].v] = Edge[j].weight;
		}
	}
}

//邻接表转换成十字链表
void List2Ortho(OrthoGraph<int> &OLG,int n,int m)
{
	vector<ArcTuple> TupleVec;
	for (int i = 1; i < n; ++i)
	{
		for (int j = head[i]; j ; j = Edge[j].next)
		{
			int u = i;
			int v = Edge[j].v;
			int w = Edge[j].weight;
			ArcTuple foo(u,v,w);
			TupleVec.push_back(foo);
		}
	}
	OLG.Tuple2OLG(TupleVec);
}
void _DfsMatrix(int cur)
{
	if (VisForGraph[cur] == 1)
	{
		return;
	}
	VisForGraph[cur] = 1;
	DFSN.push_back(cur);
	cout<<cur<<" ";
	PreOrder.push_back(cur+'0');
	for (int i = 1; i <= n; ++i)
	{
		if(graph[cur][i] != 0 && VisForGraph[i] == 0)
		{
			_DfsMatrix(i);
		}
	}
}

void MutiPath(int cur)
{
	stack<int> Nodepool;
    if(!VisForGraph[cur])
    {
        cout<<cur<<" ";
        Nodepool.push(cur);
        VisForGraph[cur] = 1;
    }
	while (!Nodepool.empty())
	{
		cur = Nodepool.top();
		Nodepool.pop();
		for (int i = 1;i <= n; ++i)
		{
			if(!VisForGraph[i] && graph[cur][i] != 0)
			{
				Nodepool.push(i);
				VisForGraph[i] = 1;
				cout<<i<<" ";
				break;
			}
		}
	}
}

void OnePath(int cur)
{
    stack<int> Nodepool;
    if (!VisForGraph[cur])
    {
        cout<<cur<<" ";
        Nodepool.push(cur);
        VisForGraph[cur] = 1;
    }
    while(Nodepool.empty() != 1)
    {
    	cur = Nodepool.top();
    	int i;
    	for (i = 1; i <= n; ++i)
    	{
    		if (!VisForGraph[i] && graph[cur][i])
    		{
	    		Nodepool.push(i);
	    		VisForGraph[i] = 1;
	    		cout<<i<<" ";
    			break;
    		}
    	}
    	if (i == n + 1)
    	{
    		Nodepool.pop();
    	}
    }
}

void BfsMatrix(int cur)
{
	queue<int> Q;
	while(!Q.empty())
	{
		Q.pop();
	}
    bool flag = 0;
	if (!VisForGraph[cur])
	{
		cout<<cur<<" ";
		Q.push(cur);
		VisForGraph[cur] = 1;
		BfsSq.push_back(cur);
		BFSN.push_back(CntForBfs ++);
	}
	while(!Q.empty())
	{
		cur = Q.front();
		Q.pop();
        flag = 0;
		for (int i = 1; i <= n; ++i)
		{
			if (graph[cur][i] && !VisForGraph[i])
			{
                flag = 1;
				cout<<i<<" ";
				BfsSq.push_back(i);
				Q.push(i);
				BFSN.push_back(CntForBfs);
				VisForGraph[i] = 1;
			}
		}
		if (flag) CntForBfs ++;
	}
}
void TarversalInMatrix()
{
	cout<<"\n\n******** Now we are using three ways to travesal with matrix *********\n\n";
	mem(VisForGraph);
	PreOrder.clear();
	DFSN.clear();
    cout<<"Traversal with deep first way\n";
	cout<<"The sequences is: \n";
	for (int i = 1; i <= n; ++i)
	{
		if (VisForGraph[i] == 0)
		{
			_DfsMatrix(i);
			cout<<"\n";
		}
	}
	cout<<"The dfn number sequences is: \n";
	for (int i = 0; i < DFSN.size(); ++i)
	{
		cout<<DFSN[i]<<" ";
	}
    cout<<"\n\n";
    mem(VisForGraph);
    cout<<"Traversal with non-recursion deep first way\n";
	cout<<"The sequences is: \n";
    int ct = 1;
    for (int i = 1; i <= n; ++i)
    {
    	if (VisForGraph[i] == 0)
    	{
    		cout<<"The "<<ct++<<" th path is :";
    		MutiPath(i);
    		cout<<"\n";
    	}
    }
    cout<<"\n";
    mem(VisForGraph);
    BFSN.clear();
    CntForBfs = 1;
    cout<<"Breadth first way to traversal\n";
	cout<<"The sequences is: \n";
    BfsMatrix(1);
    cout<<"\n\n";
    cout<<"The bfsn number is: \n";
    for (int i = 0; i < BFSN.size(); ++i)
	{
		cout<<BFSN[i]<<" ";
	}
    cout<<"\n";
    GTConstructor();
}

void _DfsList(int cur)
{
	if (VisForList[cur] == 1)
	{
		return;
	}
	VisForList[cur] = 1;
	cout<<cur<<" ";
	for (int j = head[cur];j;j = Edge[j].next)
	{
		if (!VisForList[Edge[j].v])
		{
			_DfsList(Edge[j].v);
		} 
	}
}

void _NonReDfsInList(int cur)
{
	stack<int> Nodepool;
    if(!VisForList[cur])
    {
        cout<<cur<<" ";
        Nodepool.push(cur);
        VisForGraph[cur] = 1;
    }
	while (!Nodepool.empty())
	{
		cur = Nodepool.top();
		Nodepool.pop();
		for (int j = head[cur];j != 0;j = Edge[j].next)
		{
			if(!VisForList[Edge[j].v])
			{
				Nodepool.push(Edge[j].v);
				VisForList[Edge[j].v] = 1;
				cout<<Edge[j].v<<" ";
				break;
			}
		}
	}
}

void _BfsList(int cur)
{
	queue<int> Q;
	while(!Q.empty())
	{
		Q.pop();
	}
	if (VisForList[cur] == 0)
	{
		Q.push(cur);
		cout<<cur<<" ";
		VisForList[cur] = 1;
	}
	while(!Q.empty())
	{
		cur = Q.front();
		for (int j = head[cur]; j ; j = Edge[j].next)
		{
			if (!VisForList[Edge[j].v])
			{
				Q.push(Edge[j].v);
				VisForList[Edge[j].v] = 1;
				cout<<Edge[j].v<<" ";
			}
		}
        Q.pop();
	}
}


void TraversalInList(int cur)
{
	mem(VisForList);
	cout<<"\n\n******** Now we are using three ways to travesal with list *********\n\n";
    cout<<"Traversal with deep first way\n";
	cout<<"The sequences is :";
	for (int i = 1; i <= n; ++i)
	{
		if (VisForList[i] == 0)
		{
			_DfsList(i);
		}
	}
	cout<<"\n\n";
    cout<<"Traversal with deep first way and without recursion\n";
	cout<<"The sequences is: ";
	mem(VisForList);
	for (int i = 1; i <= n; ++i)
	{
		if (VisForList[i] == 0)
		{
			_NonReDfsInList(i);
		}
	}
	cout<<"\n\n";
	mem(VisForList);
    cout<<"Breadth first way to traversal\n";
	cout<<"The breadth firstsequences is: ";
	for (int i = 1; i <= n; ++i)
	{
		if (!VisForList[i])
		{
			_BfsList(i);
		}
	}
	cout<<"\n\n";
}

int main(int argc, const char * argv[])
{

	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout<<"Please Input The Vexnum:n and Arcnum:m :";
	cin>>n>>m;
	cout<<"\n";
	cout<<"***** First we construct a graph in matrix ****\n\n";
	ConstructGraph();
    DisplayMatrix();
    TarversalInMatrix();
    cout<<"\n***** Then we transfer this matrix to adjacent list ****\n\n";
    Matrix2List(n);
    DisplayList();
    TraversalInList(1);

    cout<<"\n***** Last we transfer this adjacent list to xlist ****\n\n";
    OrthoGraph<int> OLG(n,m);
    List2Ortho(OLG,n,m);
    cout<<"The form of xlist is like this\n\n";
    OLG.DisplayOLG();
    OLG.TraversalOLG();
    // BinaryTree<int> DfsTree;
    // DfsTree.CreateBTree(PreOrder);
    // DfsTree.Display();
    return 0;
}
