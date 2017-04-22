# 连通分量（Connected Component）

### 背景（Background）

首先，提起连通分量，不得不提起一个和这个名词无比相关的名字——Robert Endre Tarjan。

![](http://i1.piimg.com/567571/7bf46648892d6664.jpg)

他传奇的一生中发明了无数[算法](http://lib.csdn.net/base/datastructure)，统称为Tarjan算法。其中最著名的有三个，分别用来求解，无向图的双连通分量，有向图的强连通分量，最近公共祖先问题。

其中我们本次实验所讨论的算法为双连通分量（BCC）以及强连通分量（SCC）问题。

### BCC问题

对于一个连通图，如果任意两点至少存在两条点不重复路径，则称这个图为**点双连通**的（简称双连通）；如果任意两点至少存在两条边不重复路径，则称该图为**边双连通**的。点双连通图的定义等价于任意两条边都同在一个简单环中，而边双连通图的定义等价于任意一条边至少在一个简单环中。对一个无向图，点双连通的极大子图称为**点双连通分量**（简称双连通分量），边双连通的极大子图称为**边双连通分量**。

![](http://media.hihocoder.com/problem_images/20150718/14372154489431.png)

求解点双连通分量与边双连通分量其实和求解割点与桥密切相关，不同双连通分量最多只有一个公共点，即某一个割顶，任意一个割顶都是至少两个点双连通的公共点。不同边双连通分量没有公共点，而桥不在任何一个边双连通分量中，点双连通分量一定是一个边双连通分量。 

对于上图，$ 3-4$ 是一个桥，$3, 4$ 分别是两个割点。

#### Tarjan算法

由于对于一个连通图，割点就是删除之后使得图不再连通的点。那么如何求出一个图的所有割点呢？显然我们容易想到第一个朴素的解法：

尝试删除每个结点，然后用 DFS 判断连通分量是否增加，时间复杂度为$O(N * (N + M) $。

但是Tarjan提出了一个更优化的算法，他通过深挖 DFS 回退这一性质，可以在线性时间内求出所有的割点。

首先这个算法的实现依赖于一个时间顺序，即很多书中提到的 dfn 数组，这里我习惯用一个 pre[] 数组代替（刘汝佳紫书中使用这个），我们可以在对图进行 DFS 的时候对每个点进行clock标记，使用pre数组记录每个点的访问的先后顺序。

之后再进行一次边的分类，对于一个无向图，其每条边 $(u,v)$ 都会被访问两次，其中访问 $u$ 的时候一次，访问 $v$ 的时候一次，DFS 森林中的边我们将其称作树边（Tree edge），从后代指向祖先的边我们将其称作回退边（Back edge），在无向图中除了树边都是反向边。

割点和桥的判定条件：

__定理：在无向图$G$ 的 DFS 树中，非根结点 $u$ 是 $G$ 的割点当且仅当 $u$ 存在一个子结点 $v$ ，使得 $v$ 及其所有后代都没有反向边连回 $u$ 的祖先（连回 u 不算）__

方便起见，设 $low(u)$ 为 $u$ 及其后代能连回的最早的祖先的pre值，则定理中的条件就可以简写成结点 $u$ 存在一个子结点 $v$ 使得 $low(v) \geq pre(u).$

作为一种特殊的情况，如果 $v$ 的后代只能连回 $v$ 自己（即$low(v) > pre(u)$），只需要删除$(u,v)$一条边就可以让图G非连通了，满足这个条件的边称作桥，而如果上述式子的等号成立，则这个结点是一个割点。

#### 操作实现（Implement）

因此我们使用如下的代码便可以完成对割点的标记，以及对双连通分量的计算。

```cpp
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
```



#### 测试数据

我随机生成了一个20个点的图，对于这20个点的图进行了测试。

```cpp
Input:
20 29
18 20
10 16
……
```

测试结果如下：

```cpp
Output:
In this graph we can find: 8 cut vertexs
The cut vertex is : 3 8 9 10 11 12 14 18 
In this graph we can find: 12 biconnected component
In the 1th biconnected component, there are vertexs : 9 19 
In the 2th biconnected component, there are vertexs : 2 12 9 18 
In the 3th biconnected component, there are vertexs : 7 12 4 11 
In the 4th biconnected component, there are vertexs : 6 20 11 18 
In the 5th biconnected component, there are vertexs : 15 3 8 20 18 1 12 
In the 6th biconnected component, there are vertexs : 12 1 13 3 
In the 7th biconnected component, there are vertexs : 5 1 16 10 
In the 8th biconnected component, there are vertexs : 14 10 
In the 9th biconnected component, there are vertexs : 3 14 
In the 10th biconnected component, there are vertexs : 3 17 
In the 11th biconnected component, there are vertexs : 8 3 
In the 12th biconnected component, there are vertexs : 1 8 
```

 

数据可视化结果如下，其中割点专门使用颜色标记：

![](http://i2.muimg.com/567571/ce8e5b3c9d0cb9df.png)

#### 实际应用

求解割点的可以应用在诸如决策网络服务器放置位置相关的场景，因为对于割点，如果服务器放置在割点，那么服务器一旦瘫痪，则割点所连的连通分量会被断开，导致无法通信，网络瘫痪。因此我们在这种情况下通常选择先求出割点的位置，然后再保证每一个双连通分量中至少都有一个服务器即可。

类似的问题还有很多，诸如在地下矿道放置安全井用于逃生，在城市交通网络放置红绿灯，都需要考虑图的连通性。

图论问题的难点不在于算法，而在于抽象建模。

### SCC问题

和无向图的连通分量类似，有向图中也有『强连通分量』（Strongly Connected Component）的说法。如果把一个SCC集合看作是一个点（通常我们又把它叫做是缩点），那么这个图就会被简化成为一个DAG，我们还可以在这个DAG上进行更多的诸如动态规划这样的操作。

![](http://i1.piimg.com/567571/c0ba478d878b934b.jpg)

对于SCC问题，我们常用的有两种算法

#### Kosaraju 算法

对于上述的图，我们如果从 1 开始 DFS ，将得到只包含${G,H,I,J,K,L}$的一颗 DFS 树，如果从 1 开始 DFS ，将得到只包含${G,H,I,J,K,L}$ 的一颗 DFS 树，然后从 C 出发，得到$ {C,F}$ ，再从 D 出发可以得到 D，以此类推，每次可以得到一个 SCC。

但是很不幸的是，并不是每一次的 DFS 顺序都是可行的，如果选择了一个，如 A 点这样的起点进行 DFS ，那么最后会将整个图都包含进这颗 DFS 树中，也就是说，不明智的 DFS 把所有的 SCC 混在了一起。

很显然我们希望能够按照 SCC 图的逆序顺序进行DFS，而Kosaraju算法便是基于这个思想的，我们需要借助一个辅助的G2来存图的反向边。

#### 操作实现（Implement）

```cpp
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
```



#### Tarjan 算法

![](https://upload.wikimedia.org/wikipedia/commons/6/60/Tarjan%27s_Algorithm_Animation.gif)

 Tarjan算法依然借助于 DFS ，但是它不是靠遍历顺序来把不同的 SCC 分离到不同的 DFS 树中。

首先考虑强连通分量 C，设其中第一个被发现的点为 x ，则 C 中的其他点都是 x 的后代，我们希望在 x 访问完成时立即输出 C，这样，就可以在同一颗 DFS 树中区分所有的 SCC 了，因此问题的关键，是判断一个点是否为一个SCC 中最先被发现的点。

现在我们任选一结点开始进行深度优先搜索（若深度优先搜索结束后仍有未访问的结点，则再从中任选一点再次进行）。搜索过程中已访问的结点不再访问。搜索树的若干子树构成了图的强连通分量。结点按照被访问的顺序存入栈中。从搜索树的子树返回至一个结点时，检查该结点是否是某一强连通分量的根结点（见下）并将其从栈中删除。如果某结点是强连通分量的根，则在它之前出栈且还不属于其他强连通分量的结点构成了该结点所在的强连通分量。

#### 操作实现（Implement）

```cpp
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
```


#### 测试数据

```cpp
Input:
8 14
1 2
3 1
2 3
2 5
2 4
3 4
4 8
8 4
5 8
7 8
5 6
6 5
6 7
7 6
```



![](http://i4.buimg.com/567571/7a4a864d7879c7ce.png)



```cpp
Output:
In this graph, we can find: 3 strong connected component.
In the 1 th scc, there are vertexs : 1 3 2 
In the 2 th scc, there are vertexs : 5 6 7 
In the 3 th scc, there are vertexs : 4 8 
 
```



#### 实际应用

实际上现实生活中对于BCC的案例如果其边是无向的，那么也就可以转换成SCC的算法来进行求解，而BCC的案例在上面已经列举过了就不再赘述。这里再给出一个不太常见的有关等价性证明的SCC的应用。

在数学中我们通常需要完成若干个命题的等价性证明，比如有4个命题 $a, b, c, d$，我们可以证明 $a \leftrightarrow b , b \leftrightarrow c，c \leftrightarrow d$，但是这样就需要总共6次证明，而另一种证明方式则是证明$a \rightarrow b，b \rightarrow c，c \rightarrow d，d \rightarrow a$，只需要总共4次证明，如果想要证明 n 个问题全部等价，现在我们已经给出了m个关系，可以利用这m个关系建图。则这个情景就被抽象成了一个n个结点m条边的有向图，要求加最少的边使得这个图强连通，对于这样的问题我们可以进行一次缩点，得到一个DAG，接下来对这个DAG进行连边即可。



