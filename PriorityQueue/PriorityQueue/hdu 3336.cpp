#include <iostream>
#include <cstdio>
#include <iomanip>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <bitset>
#include <numeric>
#include <set>
#include <list>
#include <map>

using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
#define lower_bound LB
#define upper_bound UB
#define mem(a,x) memset(a,x,sizeof(a))
#define IT iterator
#define test puts("OK")
#define lowbit(x) x & -x
#define PRQ priority_queue
#define PB push_back
#define gcd(a,b) _gcd(a,b)
const double PI = acos(-1.0);
const double eps = 1e-8;
const int INF = 0x3f3f3f3f;

const int maxn = 200000 + 10;
const int MOD = 10007;

int nextValue[maxn];
string P;

void makeNext()
{
	nextValue[0] = 0;
	int k = 0;
	for (int i = 1; i < P.size(); ++i)
	{
		while(k > 0 && P[k] != P[i])
		{
			k = nextValue[k-1];
		}
		if (P[k] == P[i])
		{
			k ++;
		}
		nextValue[i] = k;
	}
}

int main()
{
	#ifndef ONLINE_JUDGE
		freopen("/Users/luodian/Desktop/in.txt","r",stdin);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
	{
		int len;
		cin>>len;
		cin>>P;
		mem(nextValue,0);
		makeNext();
		long long ans = 0;
		ans = (P.size() + nextValue[P.size() - 1]);
		for (int i = 1; i < P.size() - 1; ++i)
		{
			if (nextValue[i] != 0 && nextValue[i] != (nextValue[i + 1] - 1))
			{
				ans += nextValue[i];
			}
		}
		cout<<ans % MOD<<endl;
	}
	return 0;
}