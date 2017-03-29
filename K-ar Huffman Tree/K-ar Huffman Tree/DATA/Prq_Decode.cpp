#include <iostream>
#include <cstdio>
#include <fstream>
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
#define lower bound LB
#define upper bound UB
#define mem(a,x) memset(a,x,sizeof(a))
#define IT iterator
#define test puts("OK")
#define lowbit(x) x & -x
#define PRQ priority queue
#define PB push back
#define gcd(a,b)  gcd(a,b)
const double PI = acos(-1.0);
const double eps = 1e-8;
const int INF = 0x3f3f3f3f;

int main()
{
    #ifndef ONLINE JUDGE
        freopen("/Users/luodian/Desktop/in.txt","r",stdin);
    #endif
    ios::sync with stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    fstream in;
    in.open("/Users/luodian/Desktop/第四周讲义及题解.html",ios::in | ios::binary);
    if (in)
    {
        in.seekg(0,in.end);
        int length = in.tellg();
        in.seekg(0,in.beg);
        char *buffer = new char[length];

        in.read(buffer,length);
        
        fstream out;
        out.open("/Users/luodian/Desktop/copy.html",ios::out | ios::binary);

        out.write(buffer,length);

        delete [] buffer;
    }
    return 0;
}