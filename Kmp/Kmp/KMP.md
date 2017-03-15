# KMP—快速字符串匹配

### 背景知识

字符串匹配是计算机的一个最基本的任务。

举例来说，有一个字符串"BBC ABCDAB ABCDABCDABDE"，我想知道，里面是否包含另一个字符串"ABCDABD"，以及它出现的具体位置。

各路文本处理软件都可以在极快的时间内针对大数据进行匹配，这其中KMP虽然不是最常用的，但似乎是最出名的，相对最常用的 BM 算法也更简单一些。

其中这个K是Knuth的缩写，超级的有名，当今世界的算法大神，提出了Algorithms 和 Data structure 的概念。

<div><center><img src="http://p1.bqimg.com/567571/dba8d798367a2d9e.jpg" alt="图 1" align=center /></div>



### 算法简述与效率分析

网上有很多关于 KMP 算法的分析，程序设计竞赛里也有很多以 KMP 为基础的题目，因此不再赘述其字符串匹配的滑动过程。

这里首先贴出阮一峰对于[KMP的讲解](http://www.ruanyifeng.com/blog/2013/05/Knuth–Morris–Pratt_algorithm.html)，我很早的时候接触过 KMP 算法，当时对 next 数组的求解十分疑惑，一度靠着背代码来做关于字符串匹配的题目。

而阮一峰先生对于这个问题的讲解，尤其是对于 next 数组的求解思路（这里的定义和其他地方的定义不太一样，但是却显得更好理解一些）可以显式的看出 next 数组求解也利用了 KMP 算法的思路，这是非常出彩的地方。

**而最重要的是！！！**

KMP 里面对于 next 数组的求解十分有效的体现了 KMP 的思想（这句话非常的有趣，其实用在递归这个地方也可以这么说，要学会递归首先你要学会递归233333）。

<div><center><img src="http://p1.bqimg.com/567571/71aca63073403524.gif" alt="图 1" align=center /></div>

但什么是 KMP 的思想呢？其实就是利用已经匹配过的信息（前后缀重合的程度），去避免重复匹配，而 next 数组的生成，也是利用了这个思想，所以这两部分的代码看起来几乎是一样的。

在计算 next 数组时，当我们已知P[q]和P[k]无法匹配时，我们难道需要把下面的串往后移动一位吗？想一想标准KMP是怎么做的？我们可以去参考 next[k-1] 的值，令 j = next[k-1]，去比对P[q]和P[j]是否相等，这个时候的滑动就利用起了P[1] ~P[k-1]的前后缀重合的信息，如果有重合，直接将前缀重合部分移动到后缀来匹配即可。



<div><center><img src="http://p1.bqimg.com/567571/b0eebabab0672687.png"  alt="图 1" align=center /></div>

<div><center><img src="http://p1.bqimg.com/567571/3ace184a393f359f.png"  alt="图 1" align=center /></div>



第二部分则是效率分析

```cpp
void makePatchTable(const std::string &pattern,std::vector<int> &PatchTable)
{
    int m = (int)pattern.size();
    PatchTable.resize(m);
    PatchTable[0] = 0;
    int k = 0;
    // i is index of suffix;
    // k is index of prefix;
    for (int i = 1; i < m; ++i)
    {
        while(k > 0 && pattern[i] != pattern[k])
        {
            k = pattern[k-1];
        }
        if (pattern[i] == pattern[k])
        {
            k ++;
        }
        PatchTable[i] = k;
    }
}
```

直接看代码，我们只用分析怎么处理 next 数组，处理 next 数组是对一个长度为 m 的Pattern串进行操作，因此在进行匹配的时候，其实可以看成是对于一个长度为 n 的Template串进行同样的操作。

在这里我们用 i 表示字符串后缀，用 k 表示字符串的前缀，可以看出，i 是不回退的，而显然，k = next[k-1]的回退异常的快。

在这里我们举一个最坏情况的例子，如AAAAAB这种情况，next数组值分别为01234，在计算B的next值时，其实一开始是这么对上的，（红圈处）。

![图片 5](http://i1.piimg.com/567571/ae47354ad9f15a6d.png)

此时 i 因为可以完全匹配，已经到了5的位置，在第5号位置无法匹配，导致在k向前回退的过程中，k最多会回退4次，最后计算出B的next值为0.

此时的时间消耗为5 + 4 = 9次，因此next数组计算时最坏情况为$O(2 * M) = O(M)$.

**因此KMP算法效率分析的核心思想就是**

**我们假设 T 串的下标为 i，P 串的下标为 q，首先 i 串不会回退，其次对于每一处的 i ，任意举例就可以发现 q = next[q-1] 可以在常数时间要么使 q = 0，要么使 T[i] == P[q]，而这两种情况都是可以使 KMP 中的 while 循环结束。**

因此实际匹配的过程为 $O(N)$，最终整体的复杂度为 $O(N + M)$.



### 测试与效率分析

#### 测试

本文中我分别给出了3组不同的测试数据。

分别使用了KMP，BM，Trie树，暴力前缀匹配，暴力后缀匹配，以及STL中内置的 find() 方法进行了对比测试。

> 其中Trie树只能应用于查找是否出现过，而不能找出出现的位置。

匹配结果分别如下。

1. 一篇长度为5W字左右的英文小说『乞力马扎罗的雪』，在其中插入了我的ID，Luodian，然后以Luodian作为模式串进行模式匹配。

   ![图片 6](http://i1.piimg.com/567571/4b5d740f7e43221a.png)

   ​


2. 一个随机生成的长度为1K左右的字符串，以某一个子串为模式串进行匹配。

   ![图片 6](http://p1.bpimg.com/567571/8b8dcb5ff88b1682.png)



3. 对于Bruteforce算法最坏情况，但是KMP可以表现良好的一种情况。

   即T = 'AAAA……（1e5个）B'，P = 'AAAAAB' 进行匹配。

   ![图片 7](http://i1.piimg.com/567571/d1c800e180257897.png)



#### 分析

对于最为普遍的文本类型数据的模式匹配，首先Trie树作为 $O(len)$ 的算法效率自然是最快的，而 KMP可以看出，由于其预处理的过程，效率其实较暴力匹配并没有更优，BM 算法通常情况下为 $O(N)$ 的效率，但是实际操作却可以比 KMP 快出3 - 5倍，因为其增加了一个好后缀的回退规则，而STL中string类的 find() 方法，推测其是使用的暴力匹配。

而在第二种情况，随机数据下，情况和第一种类似，仍然是 KMP 劣势，STL实现最优，暴力匹配和BM算法次之。

但是在第三种专门为了卡暴力匹配算法速度的字符串中，KMP便可以体现出其应用的场景，这里首先解释一下为什么基于后缀匹配的暴力匹配速度更快，因为在对于T = 'AAAA……（1e5个）B'，P = 'AAAAAB' 进行后缀匹配时，每次都会因为 'B' != 'A'，而造成P串的快速后退，因此在$O(N)$的时间内，就可以找到应有的位置。

而KMP则是$O(N+M)$的，因为在完成了 next 数组之后，对P串的每一次匹配失败都会造成T串向后移动一位，所以在实际匹配的过程中也是 $O(N)$ 的复杂度。

而对于基于前缀暴力匹配算法，因为每次都会识别到 'B' 这个位置才发现不匹配，因此时间复杂度是最坏情况下的$O(N*M)$.



#### 总结

虽然文本文件系统大量使用BM算法作为模式匹配的首选方法，但KMP也是蜜汁出名，我想可能是因为KMP算法的时间复杂度算是线性最优，因此即使相较于BF算法大多数情况下都不占优势，但是它最坏$O(N+M)$的特点，也可以让它成为一个很棒的模式匹配的方法。

但或许更重要的，是KMP中，求解 next 数组的那种思路，正如文章开头时的那个科赫曲线一般，从自身去导出自身，利用 next[k-1] 的信息，去生成next[k]的值，尽可能的减少匹配的次数。而后又将这种思想去应用在对于P串的匹配上，这是思维的一个闪光点，也是算法历史上的一道难得的光芒。



### 学以致用：Application

可以使用 next 数组的性质去完成一些很有趣的竞赛题目，这是一道我曾经看到过的竞赛题，当时还不太理解 next 数组所以就放弃了，现在我又去做的时候，由于完成了 KMP 算法，这道题就显得游刃有余了。

这是在利用 next 数组的一个性质，我们利用 next[i] 表示截止 i 位置时，出现的最大的前后缀重合长度，对于ABCAB，它的next值为2，所以我们可以得知，截止( i 从 0 开始 ) i = 4时，前缀A可以找到一次重合，前缀AB也可以找到一次重合，因此其Sum = 2，恰好和 next 数组值相等。 

HDU-3336

http://acm.hdu.edu.cn/showproblem.php?pid=3336



![pic](http://i1.piimg.com/567571/97874fba153117e5.png)



AC代码：

```cpp
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
```



### 他山之石：Reference

1. 阮一峰 (2013). "*字符串匹配的KMP算法*". Retrieved on 10th March, 2017 from:

   http://www.ruanyifeng.com/blog/2013/05/

   ​

   ​