# 跳跃表背后的随机算法思想

### 背景：Enhanced List

关于跳表（Skip list）的由来，首先要从链表（Linked list）说起。

![图片 1](http://p1.bpimg.com/567571/9aab25912db64d11.png)

链表是一种为了方便插入和删除而引入的数组的增强版，其存储空间为$O(N)$，插入和删除操作都非常给力，时间复杂度均为$O(1)$，但是插入和删除所必须要做的预备工作自然是找到所要插入和删除的位置，而对于链表（Linked list），其并未定义查找方法，而通过朴素查找，一个节点最多只能 reach 到它的下一个节点，这样的查找方式则是需要$O(N)$才能找到可能要删除的位置。

人们为了解决这个问题，提出了[Doubly Linked List](https://en.wikipedia.org/wiki/Doubly_linked_list)这种数据结构，这样查找算法的时间复杂度便被优化到了$O(\frac{N}{2})$. 这是一种典型的空间换时间（trade off）的思路。

![图片 2](http://p1.bqimg.com/567571/56e87e31ea4f0d4c.png)



更进一步的，在1990年，由 William Pugh 提出了[Skip List](https://en.wikipedia.org/wiki/Skip_list)这种基于[分治算法]()和[随机化算法 ](https://en.wikipedia.org/wiki/Randomized_algorithm)而产生的更优化的链表类数据结构。![图片 3](http://i1.piimg.com/567571/b2605a416bb30784.gif)

跳跃表原理上基于链表，每一个节点可以看做是原链表的节点中增加了一个高度的属性，且针对此属性还对应了相应的指针，其实把跳跃表转置 90° 后，再将各条链分散开一些，是不是看起来很像一颗 K 叉树？

> 它在工程中应用（额我虽然没怎么听说过，但是看起来真的很棒）在Redis和LevelDB（一个由Google实现的数据库）中。

### 时空复杂度

- 空间复杂度

  这个和跳跃表的最高高度有关，实际复杂度为$maxlevel * n$，但渐进的来看也就是$O(N)$的效率，十分的合理。

- 时间复杂度

  可以先看一看作者在论文中对于跳跃表的结点高度的描述。

  > In a skip list of 16 elements generated with $p = \frac{1}{2}$, we might happen to have 9 elements of level 1, 3 elements of level 2, 3 elements of level 3 and 1 element of level 14 (this would be very unlikely, but it could happen). How should we handle this?  If we use the standard algorithm and start our search at level 14, we will do a lot of useless work. 
  >
  > Where should we start the search?  Our analysis suggests that ideally we would start a search at the level L where we expect $\frac{1}{p}$ nodes. This happens when $L = \log_\frac{1}{p}{n}$. Since we will be referring frequently to this formula, we will use $L(n)$ to denote $\log_\frac{1}{p}{n}$.

  ​

  ![图片 4](http://p1.bqimg.com/567571/b4ef322c59676142.png)

  通过随机化的高度，我们将这个图分成了几个大组，[3, 6], [6, 25], [25, 26]。而其中每个大组由下分几个小组，我们在查找的过程中首先根据从大组向小组，一步一步的确定搜索的最终位置，而这个过程怎么去计算时间消耗呢？

  ​

### 实现与测试

##### 实现

我自己采取了习惯的OOP的设计方式，在了解了其结构特点，以及参考了网上许多源码之后，先确定了其存储结构为

```cpp
    struct skipNode
    {
        object data;
        skipNode *next[maxlevel];
        skipNode(const object &d = object())
        {
            data = d;
            for (int i = 0; i < maxlevel; ++i)
            {
                next[i] = nullptr;
            }
        }
    };
```

然后再针对这个数据结构的特点，我为其设计了（除了必须有的构造与析构函数之外）如下的对外的接口。

- find( const object &x ) 方法，find() 操作基于跳跃表的结构特点实现，时间消耗为$O(\log_2{N})$.

- insert( const object &x ,const bool mod = 0, const int &level ) 方法，同上。

  > 注：insert 方法为后面两个参数指定了默认参数，对外的用法为insert(x) 将x插入到相应的位置，而同样可以使用insert(x, 1 , 4)，表示开启debug模式，将x插入到位置，不使用随机层数，指定其层数为4。
  >
  > 通过这种做法，可以避免随机生成层数导致 bug 时有时无，无法复现的问题。

- erase( const object &x ) 方法，同上。

- empty( ) 方法，判断这个表是否为空。

- debug( ) 方法，主要应用于测试，其作用为打印出 skipList 的图示。

  ![图片 5](http://p1.bqimg.com/567571/e2be168330b04aed.png)

##### 测试

首先进行了一个 SimpleTest( )，在其中主要打印了如上图所示的跳跃表的图形表示，由于结点过多会造成排列混乱，只进行了简单的测试。

接下来进行的是时间复杂度的测试，在一个名为 TimePerfo( ) 的函数中进行，对三种结构 skip list, list（直接使用STL库函数）, Avl（自己以前编写的）设置变量为规模 n ,控制表的规模，对于三种结构分别生成从10000 - 100000大小的表，对于每个表都插入10000个元素，进行对比测试插入时间效率。

具体的测试方法为，我在 cpp 文件中将测试的规模与时间生成文本文件数据，在另外的 plot.py 文件中对这些数据进行了读入以及处理，然后调用 matplotlib 函数库进行了图形的绘制，最终结果如下。

![图片 6](http://p1.bqimg.com/567571/49a1836f1c2d0a5b.png)

![图片 7](http://i1.piimg.com/567571/dd6c06e33a40ebd1.png)

在插入的时间效率对比上，我们可以看出AVL和SkipList在插入效率上远远比List要快上许多，毕竟从理论分析上，前两者都是$O(\log_2{N})$的时间效率，而后者是$O(N)$的时间效率。



### 总结与分析

1. 本次实验首次使用py与cpp混合编译的方式遇到了很多的坑，最后还是放弃了，采用手动使用一个.txt文件作为中间件传送数据的方式。
2. 理论上跳跃表（Skip List）的时间效率应该会高过平衡二叉树（Avl Tree），但是两周都是自己实现的，在写代码的过程中我也觉得 Skip List 确实应该快一些，但是最终测试的结果是 Avl 胜出，看来上学期才是写代码的巅峰，刚开学手感略显生疏？2333333