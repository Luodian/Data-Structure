//
//  floyd.hpp
//  Shortest Path
//
//  Created by 李博 on 11/04/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#ifndef floyd_h
#define floyd_h


#include "Header.hpp"
using namespace std;


class Floyd
{
private:
	int Gm[105][105];
	int dp[105][105];
	int Asist[105][105];
	int n,m;
	void init()
	{
		n = 0;
		m = 0;
		mem(Gm);
		mem(dp);
		mem(Asist);
	}
public:
	Floyd()
	{
		init();
	}
	~Floyd()
	{
		//
	}
	void update()
	{
		for (int i = 1; i <= n; ++i)
		{
			for (int j = 1; j <= n; ++j)
			{
				Asist[i][j] = 0;
                if (Gm[i][j])
                {
                	dp[i][j] = Gm[i][j];
                }
                else
                {
                	dp[i][j] = INF;
                }
			}
		}
		for (int k = 1; k <= n; ++k)
		{
			for (int i = 1; i <= n; ++i)
			{
				for (int j = 1; j <= n; ++j)
				{
					if (dp[i][j] > dp[i][k] + dp[k][j])
					{
						dp[i][j] = dp[i][k] + dp[k][j];
						Asist[i][j] = k;
					}
				}
			}
		}
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
			Gm[u][v] = w;
		}
		infile.close();
	}
	void printPath(int a,int b)
	{
		if (Asist[a][b] == 0)
		{
			cout<<b<<" ";
            return;
		}
		printPath(a,Asist[a][b]);
		printPath(Asist[a][b],b);
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
        cout<<"\n";
        cout<<"The shortest path is : ";
        cout<<1<<" ";
        printPath(1,n);
        cout<<"\n";
		cout<<"The minimal cost is : "<<dp[1][n]<<".\n";
	}
	int ans()
	{
		return dp[1][n];
	}
};


#endif /* floyd_h */
