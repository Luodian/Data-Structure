#include <vector>
#include <iostream>
#include <cstring>
#include <stack>
#include <queue>
using namespace std;
const int maxn = 20;
typedef tuple<int,int,int> ArcTuple;
#define mem(x) memset(x,0,sizeof(x))
template <typename Ojbect>
class OrthoGraph
{
private:
	bool VisForOLG[maxn];
	struct ArcBox
	{
		int u,v;
		ArcBox *headlink;
		ArcBox *taillink;
		int weight;
	};
	struct VexNode
	{
		Ojbect data;
		ArcBox *firstIn;
		ArcBox *firstOut;
	};
	struct OLGraph
	{
		VexNode xlist[maxn];
		int vexnum;
		int arcnum;
	};
	OLGraph *G;
	void AddEdge(int u,int v,int w,ArcBox * &TempArc)
	{
		TempArc->u = u;
		TempArc->v = v;
		TempArc->weight = w;
		TempArc->headlink = G->xlist[v].firstIn;
		TempArc->taillink = G->xlist[u].firstOut;
		G->xlist[v].firstIn = TempArc;
		G->xlist[u].firstOut = TempArc;
	}
	void CreateOLGraph(OLGraph * &G)
	{	
		cout<<"Please Input Tuple Like (u,v,w) to Construct A Graph\n";
		for (int i = 1; i < G->vexnum; ++i)
		{
			G->xlist[i].data = i;
			G->xlist[i].firstOut = nullptr;
			G->xlist[i].firstIn = nullptr;
		}
		for (int i = 0; i < G->arcnum; ++i)
		{
			int u,v,w;
			cin>>u>>v>>w;
			ArcBox *TempArc = new ArcBox;
			AddEdge(u,v,w,TempArc);
		}
	}
	void Tuple2OLG(vector<ArcTuple> &WaitArc,OLGraph * &G)
	{
		for (int i = 1; i < G->vexnum; ++i)
		{
			G->xlist[i].data = i;
			G->xlist[i].firstOut = nullptr;
			G->xlist[i].firstIn = nullptr;
		}
		for (int i = 0; i < WaitArc.size(); ++i)
		{
			int u,v,w;
			tie(u,v,w) = WaitArc[i];
			ArcBox *TempArc = new ArcBox;
			AddEdge(u,v,w,TempArc);
		}
	}
	vector<ArcTuple> & OrthoList2Matrix(OLGraph * &G,vector<ArcTuple> &ret)
	{
		for (int i = 1; i <= G->vexnum; ++i)
		{
			for (ArcBox* j = G->xlist[i].firstOut;j != nullptr; j = j->taillink)
			{
				int u = j->u;
				int v = j->v;
				int w = j->weigh;

				ArcTuple foo(u,v,w);
				ret.push_back(foo);
			}
		}
		return ret;
	}
	void DFSOLG(int cur)
	{
		if (VisForOLG[cur])
		{
			return;
		}
		VisForOLG[cur] = 1;
		cout<<cur<<" ";
		for (ArcBox *j = G->xlist[cur].firstOut; j != nullptr; j = j->taillink)
		{
			if (!VisForOLG[j->v])
			{
				DFSOLG(j->v);
			}
		}
	}
	void NonReDFS(int cur)
	{
		stack<int> Nodepool;
		if(!VisForOLG[cur])
		{
			cout<<cur<<" ";
			Nodepool.push(cur);
			VisForOLG[cur] = 1;
		}
		else
		{
			while(!Nodepool.empty())
			{
				cur = Nodepool.top();
				Nodepool.pop();
				for (ArcBox *j = G->xlist[cur].firstOut; j != nullptr; j = j->taillink)
				{
					if (!VisForOLG[j->v])
					{
						cout<<j->v<<" ";
						Nodepool.push(j->v);
						VisForOLG[j->v] = 1;
						break;
					}
				}
			}
		}
	}
	void _BfsXlist(int cur)
	{
		queue<int> Q;
		if (!VisForOLG[cur])
		{
			Q.push(cur);
			VisForOLG[cur] = 1;
			cout<<cur<<" ";
		}
		while(!Q.empty())
		{
			cur = Q.front();
			Q.pop();
			for (ArcBox *j = G->xlist[cur].firstOut; j != nullptr; j = j->taillink)
			{
				if (!VisForOLG[j->v])
				{
					cout<<j->v<<" ";
					Q.push(j->v);
					VisForOLG[j->v] = 1;
				}
			}
		}
	}
public:
	OrthoGraph(int n,int m)
	{
		G = new OLGraph;
		G->vexnum = n;
		G->arcnum = m;
	}
	~OrthoGraph()
	{
		delete G;
	}
	void CreateOLGraph()
	{
		CreateOLGraph(G);
	}
	void Tuple2OLG(vector<ArcTuple> &WaitArc)
	{
		Tuple2OLG(WaitArc,G);
	}
	vector<ArcTuple> & OrthoList2Matrix(vector<ArcTuple> &ret)
	{
		return OrthoList2Matrix(G,ret);
	}
	void DisplayOLG()
	{
		for (int i = 1; i <= G->vexnum; ++i)
		{
			cout<<"For Node "<<i<<" it has in nodes: \n";
            ArcBox *j = new ArcBox;
			for (j = G->xlist[i].firstIn;j != nullptr; j = j->headlink)
			{
				cout<<j->u<<" -> "<<i<<": "<<j->weight<<"\n";
			}
			cout<<"\n";
		}
	}
	void TraversalOLG()
	{
		mem(VisForOLG);
		cout<<"\n\n******** Now we are using three ways to travesal with xlist *********\n\n";
	    cout<<"Traversal this graph \n";
		cout<<"The sequences is :";
		for (int i = 1; i <= G->vexnum; ++i)
		{
			if (!VisForOLG[i])
			{
				DFSOLG(i);
			}
		}
		cout<<"\n\n";
		cout<<"Traversal this xlist without recursion \n";	
		cout<<"The sequences is: ";
		mem(VisForOLG);
		for (int i = 1; i <= G->vexnum; ++i)
		{
			NonReDFS(i);
		}
		cout<<"\n\n";
		mem(VisForOLG);
		cout<<"Traversal this xlist \n";
		cout<<"The sequences is: ";
		for (int i = 1; i <= G->vexnum; ++i)
		{
			_BfsXlist(i);
		}
		cout<<"\n\n";
	}
};
