# 哈希表-空间与时间的博弈



> 有两个字典，分别存有 100 条数据和 10000 条数据，如果用一个不存在的 key 去查找数据，在哪个字典中速度更快？

有些计算机常识的读者都会立刻回答: “一样快，底层都用了哈希表，查找的时间复杂度为 O(1)”。然而实际情况真的是这样么？

### 哈希表概述

在讨论哈希表之前，先规范几个接下来会用到的概念。哈希表的本质是一个数组，数组中每一个元素称为一个箱子(bucket)，箱子中存放的是键值对。

哈希表的存储过程如下:

1. 根据 key 计算出它的哈希值 hash_code。
2. 假设箱子的个数为 n，那么这个键值对应该放在第 **(hash_code % n)** 个箱子中。
3. 如果该箱子中已经有了键值对，就使用开放寻址法或者拉链法解决冲突。

- 在使用拉链法解决哈希冲突时，每个箱子其实是一个链表，属于同一个箱子的所有键值对都会排列在链表中。

![pic](https://upload.wikimedia.org/wikipedia/commons/thumb/5/5a/Hash_table_5_0_1_1_1_1_0_LL.svg/1000px-Hash_table_5_0_1_1_1_1_0_LL.svg.png)



- 在使用开放寻址方式解决冲突的时候，会依据事先定义好的寻址方式（平方，线性等等方式）不断的向下一个位置寻找是否可以插入。

  ![](https://upload.wikimedia.org/wikipedia/commons/thumb/b/bf/Hash_table_5_0_1_1_1_1_0_SP.svg/760px-Hash_table_5_0_1_1_1_1_0_SP.svg.png)



### 负载因子 — 哈希表的时空平衡元素

哈希表还有一个重要的属性: 负载因子(load factor)，它用来衡量哈希表的 **空/满** 程度，一定程度上也可以体现查询的效率，计算公式为:

> 负载因子 = 总键值对数 / 箱子个数

负载因子越大，意味着哈希表越满，越容易导致冲突，性能也就越低。因此，一般来说，当负载因子大于某个常数(可能是 1，或者 0.75 等)时，哈希表将自动扩容。

哈希表在自动扩容时，一般会创建两倍于原来个数的箱子，因此即使 key 的哈希值不变，对箱子个数取余的结果也会发生改变，因此所有键值对的存放位置都有可能发生改变，这个过程也称为重哈希(rehash)。

哈希表的扩容并不总是能够有效解决负载因子过大的问题。假设所有 key 的哈希值都一样，那么即使扩容以后他们的位置也不会变化。虽然负载因子会降低，但实际存储在每个箱子中的链表长度并不发生改变，因此也就不能提高哈希表的查询性能。

基于以上总结，细心的读者可能会发现哈希表的两个问题:

1. 如果哈希表中本来箱子就比较多，扩容时需要重新哈希（rehash）并移动数据，性能影响较大。
2. 如果哈希函数设计不合理，哈希表在极端情况下会变成线性表，性能极低。

本次实验我针对这两个问题做了一些分析。

### 结构设计与代码实现

#### I. 泛型设计

在本次实验中，我参考了STL源码分析，以及数据结构与算法的C++实现，设计了一个简化版的类似于STL中的unordered_set的hash_set。

其简化了`class allocator`这个参数以及STL中为了考虑各种情况（编译环境等等）的各种类型复杂交错的定义。

> STL源码真的类似于天书

```cpp
	template <class KeyType>
	class hash_func
	{
	public:
		size_t operator () (const KeyType &x) const
		{
			return hash_func<underlying_type<KeyType>>()(x);
		}

		static_assert(is_enum<KeyType>(), "This type has no default hash function.");
	};
	template<>
	class hash_func <string>
	{
	public:
		size_t operator () (const string &str) const
		{ 	
			size_t hashVal = 0;
            size_t seed = 31;
            for (int i = 0; i < str.size(); ++i)
            {
                hashVal = hashVal * seed + str[i];
            }
            return size_t((hashVal & 0x7FFFFFFF));
		}
	};
	template <class KeyType,class ValueType,class HashFunc = hash_func<KeyType>,int Items = 1>
	class HashTable
      ……
```

在实现中，参考了STL中对于hashable和unhashable的类型区别，对于常见的，可行的hashable对象，我在类中使用了仿函数（类似于函数对象，不过是通过类封装的函数对象）以及特化类模板的方式定义了默认的hash方式，而对于unhashable的对象，则需要用户自己定义hash的方式。

在测试中，我使用了如下的方式演示了对于泛型的使用。

```cpp
struct foo_node
{
	size_t seqNum;
	string nameA,nameB;

	foo_node(size_t _seqNum = 0,string _nameA = string() ,string _nameB = string())
	{
		seqNum = _seqNum;
		nameA = _nameA;
		nameB = _nameB;
	}
	friend ostream& operator << (ostream &out,const foo_node &x)
	{
		out<<x.seqNum<<"-"<<x.nameA<<"-"<<x.nameB<<"\n";
		return out;
	}

	bool operator == (const foo_node &_a) const
	{
		return (_a.seqNum == seqNum || _a.nameA == nameA || _a.nameB == nameB);
	}
};

template<class KeyType>
class foo_hash
{
public:
	size_t operator () (const KeyType & x) const
	{
		size_t hashVal = 0;
        size_t seed = 31;
        string str = x.nameA + x.nameB;
        for (int i = 0; i < str.size(); ++i)
        {
            hashVal = hashVal * seed + str[i];
        }
        return ((hashVal & 0x7FFFFFFF));
	}
};

	//对象的定义如下
    OpenSet::HashTable < foo_node, string , foo_hash<foo_node> > A;
    foo_node bar(13,"李博","武德浩");
    A.insert(bar);
```

对于这个`hashtable`来说，它可以接收如`foo_node`这样的自定义类型，但是这个类型对于它来说是一个`unhashable`的对象（类中没有定义默认的`hash`函数），因此我使用了一个`foo_hash`的特化类模板给`foo_node`定义了它的`hash`函数（将`node`中的两个字符串连接到一起），然后进行`BKDR`的`hash`运算。

> 这个才叫真正的泛型好吗！只能传入string or int long long等等类型可能是假的泛型O_O

对于这个类来说，这样的实现方式，才能够使这个类能够作为一个泛型类被其他人使用。



#### II. 简单测试

```cpp
void ProbeSimpleTest()
{
	cout<<"1.Simple function test of Probe hash set.\n";

	ProbeSet::HashTable < string,string > A;
	A.insert("Scott Fitzgerald","The Great Gatsby");
	A.insert("Salinger", "The Catcher in the Rye");
	A.insert("Virginia Woolf","A Room of One's Own");

	cout<<"  The load factor is : "<<A.get_load_factor()<<endl;
    cout<<"  The size is: "<<A.getSize()<<endl;

	A.insert("Edith Warton","The Age of Innocence");
	A.insert("George Orwell","Shooting an Elephant");
	A.insert("John Milton","Lost Paradise");
	A.insert("Thomas Paine","Common Sense");
	A.insert("Earnest Hemmingway","The Old Man and the Sea");
	A.insert("Orhan Pamuk","My Name is Red");
	A.insert("James Joyce","Ulysses");

	cout<<"  The adjusted size is: "<<A.getSize()<<endl;
	cout<<"  The load factor is : "<<A.get_load_factor()<<endl;

	cout<<"\n";
	cout<<"  The value of James Joyce is :";
	cout<<A.contain("James Joyce")<<endl;

	cout<<"  The value of Earnest Hemmingway is :";
	cout<<A.contain("Earnest Hemmingway")<<endl;

}

void OpenSimpleTest()
{
	cout<<"2.Simple function test of Open hash set.\n";
	OpenSet::HashTable < foo_node, string , foo_hash<foo_node> > A;
	vector< vector< string > > vecMatrix;

	readCSV("/Users/luodian/Desktop/软设实验分组.csv",vecMatrix);

	for (int i = 1; i < vecMatrix.size(); ++i)
	{
		stringstream ss;
		ss.clear();
		ss<<vecMatrix[i][0];
		int Tempnum;
		ss>>Tempnum;
		string TempA = vecMatrix[i][1];
		string TempB = vecMatrix[i][2];
        string ProjectName = vecMatrix[i][3];
		foo_node foo(Tempnum,TempA,TempB);
        A.insert(foo,ProjectName);
	}

	foo_node bar(13,"李博","武德浩");
	cout<<"  The project info of \"李博\",\"武德浩\" is : ";
	cout<<A.contain(bar)<<endl;

	cout<<"  Erase the info: "<<bar;
	A.remove(bar);
	vecMatrix.erase(vecMatrix.begin() + 11);
	// writeCSV("/Users/luodian/Desktop/软设实验分组.csv",vecMatrix);
	cout<<"  The project info of \"李博\",\"武德浩\" is : ";
	cout<<A.contain(bar)<<endl;
}
```



结果如下

```cpp
1.Simple function test of Probe hash set.
  The load factor is : 0.428571
  The size is: 7
  The adjusted size is: 3079
  The load factor is : 0.00324781

  The value of James Joyce is :Ulysses
  The value of Earnest Hemmingway is :The Old Man and the Sea

2.Simple function test of Open hash set.
  The project info of "李博","武德浩" is : Patricia树（Patricia Tree）
  Erase the info: 13-李博-武德浩
  The project info of "李博","武德浩" is : Not found.
```

可以看到的是，在Probe hashtable的测试中，展示了Probe hashtable可以扩容的性质，即在load_factor达到0.5时，会自动的rehash，将表长扩大。

而在Open hashtable的测试中，我对于一个.CSV文件进行了读取，展示了如上的泛型性质，通过对`foo_node`的查找，返回了值`Patricia树（Patricia Tree）`

然后删除了这个键值对，并且重新写入了.CSV文件。

#### III. 性能测试

1. 开闭哈希表的插入性能测试

   在开闭哈希表中，我们分别使用了10000-1000000，间隔100组数据进行了插入性能的测试，rehash条件为平衡因子 > 0.5;

   ![insert_comparasion_whole](/Users/luodian/Desktop/DSA/HashSet/HashSet/insert_comparasion_whole.png)

   ![insert_comparasion](/Users/luodian/Desktop/DSA/HashSet/HashSet/insert_comparasion.png)

   可以看到的是，在插入元素较多的情况下，使用探测方式的闭哈希表的插入性能基本上呈线性增长的态势，其插入效率会变得非常的低，其主要的原因是在插入过程中，闭哈希表的结构会使得其表空间很快被占满，需要 rehash 的次数远远的多于开散列表，而每次rehash都是最坏$O(N)$的效率，因此在实际使用中，闭散列表可能并不占优势。

2. 开闭哈希表的查找性能测试

   在开闭哈希表中，我们分别使用了10000-1000000，间隔100组数据进行了查找性能的测试，每次查找10000个元素，rehash条件为平衡因子 > 0.5;

   ![find_comparasion](/Users/luodian/Desktop/DSA/HashSet/HashSet/find_comparasion.png)

   显然对于查找来说，由于不需要`rehash()`的过程，因此两种方式的查找效率都是$O(1 + \epsilon)$，两者均能够在常数时间内完成操作。

3. 两种散列表的两种hash function的**冲突次数**测试

   处理冲突，是哈希表实际中很重要的一个环节。

   1. 如果哈希表中本来箱子就比较多，扩容时需要重新哈希并移动数据，性能影响较大。
   2. 如果哈希函数设计不合理，哈希表在极端情况下会变成线性表，性能极低。

   而处理冲突的方式，第一取决于哈希表的结构，第二则取决于哈希表的哈希函数的选取。

   首先我使用了BKDR和FNV两种较为出名的字符串哈希函数进行了冲突次数测试。

   BKDR是一种经过数学证明的较为成熟的乘数哈希方式，而FNV则同样也是另一种较为成熟的位运算哈希方式，对于两种函数，BKDR更适用于短字符串的处理，而FNV则适用于相对较长的。

   1. Open hashtable 的测试

      ![Crash_count_open](/Users/luodian/Desktop/DSA/HashSet/HashSet/Crash_count_open.png)

      ​2. Probe hashtable 的测试![Crash_count_probe](/Users/luodian/Desktop/DSA/HashSet/HashSet/Crash_count_probe.png)

   在以上的两幅图可以看出，两种不同的hash函数，其均能够实现均匀一致的hash，但是对于不同的存储结构来说，明显的可以看出，Probe hashtable在冲突次数上远远地高于 Open hashtable。

#### IV. 一致性哈希问题的解决

一致性哈希[算法](http://lib.csdn.net/base/datastructure)在1997年由麻省理工学院提出的一种分布式哈希（DHT）实现算法，设计目标是为了解决因特网中的热点(Hot spot)问题，初衷和CARP十分类似。一致性哈希修正了CARP使用的简 单哈希算法带来的问题，使得分布式哈希（DHT）可以在P2P环境中真正得到应用。 
一致性hash算法提出了在动态变化的Cache环境中，判定哈希算法好坏的四个定义：


1、**平衡性**(Balance)：平衡性是指哈希的结果能够尽可能分布到所有的缓冲中去，这样可以使得所有的缓冲空间都得到利用。很多哈希算法都能够满足这一条件。 

2、**单调性**(Monotonicity)：单调性是指如果已经有一些内容通过哈希分派到了相应的缓冲中，又有新的缓冲加入到系统中。哈希的结果应能够保证原有已分配的内容可以被映射到原有的或者新的缓冲中去，而不会被映射到旧的缓冲集合中的其他缓冲区。 

3、**分散性**(Spread)：在分布式环境中，终端有可能看不到所有的缓冲，而是只能看到其中的一部分。当终端希望通过哈希过程将内容映射到缓冲上时，由于不同终端所见的缓冲范围有可能不同，从而导致哈希的结果不一致，最终的结果是相同的内容被不同的终端映射到不同的缓冲区中。这种情况显然是应该避免的，因为它导致相同内容被存储到不同缓冲中去，降低了系统存储的效率。分散性的定义就是上述情况发生的严重程度。好的哈希算法应能够尽量避免不一致的情况发生，也就是尽量降低分散性。 

4、**负载**(Load)：负载问题实际上是从另一个角度看待分散性问题。既然不同的终端可能将相同的内容映射到不同的缓冲区中，那么对于一个特定的缓冲区而言，也可能被不同的用户映射为不同 的内容。与分散性一样，这种情况也是应当避免的，因此好的哈希算法应能够尽量降低缓冲的负荷。

在分布式集群中，对机器的添加删除，或者机器故障后自动脱离集群这些操作是分布式集群管理最基本的功能。**如果采用常用的hash(object)%N算法，那么在有机器添加或者删除后，很多原有的数据就无法找到了**，这样严重的违反了单调性原则。

#### 上面说了这么多！最关键的一点其实是

我们把服务器看成是hash结点，把服务者(clients)看成是虚拟结点或者是可以映射到虚拟结点的处于环上的点。

![](http://img.blog.csdn.net/20160509140239739)

那么现在如果我们的一个服务器B如果Crash掉了，那么映射到B结点上的所有点都需要暂时被rehash()到别的结点，比如是 C 结点。

![](http://img.blog.csdn.net/20160509140308505)



且在这个过程中，由于我们这个hashtable是分布式存储的，我们可能无法做到对每一个分布的用户都去更新这个hash的映射关系，所以我们还要保证如果服务器B上线之后，那么被转移的结点还能够重新给hash回到B这个结点上，这样就能够保证哈希的一致性。

然而，在考虑将结点转移到C的时候，这可能又会造成一个“雪崩”的情况，即C节点由于承担了B节点的数据，所以C节点的负载会变高，C节点很容易也宕机，这样依次下去，这样造成整个集群都挂了。

为此，引入了“虚拟节点”的概念：即把想象在这个环上有很多“虚拟节点”，数据的存储是沿着环的顺时针方向找一个虚拟节点，每个虚拟节点都会关联到一个真实节点，如下图所使用：

![](http://img.blog.csdn.net/20160509140331640)

由于这些虚拟节点数量很多，在服务器B下线之后，我们将所有的结点重新的均匀分布，因此不会造成“雪崩”现象。

下面通过测试结果演示这个算法的实现。

```cpp
   The clients: 199.61.192.87 in server 202.104.236.1
   The clients: 131.208.40.65 in server 202.104.236.2
   The clients: 138.195.163.174 in server 202.104.236.1
   The clients: 228.16.75.161 in server 202.104.236.1
   The clients: 152.169.154.136 in server 202.104.236.0
   The clients: 242.245.66.123 in server 202.104.236.0
   The clients: 46.125.92.115 in server 202.104.236.2
   The clients: 249.232.189.232 in server 202.104.236.3
   The clients: 196.82.30.94 in server 202.104.236.1
   The clients: 0.219.57.85 in server 202.104.236.1

   The servers 0 th has node: 2 .
   The servers 1 th has node: 5 .
   The servers 2 th has node: 2 .
   The servers 3 th has node: 1 .

   The clients: 199.61.192.87 in server 202.104.236.3
   The clients: 131.208.40.65 in server 202.104.236.2
   The clients: 138.195.163.174 in server 202.104.236.2
   The clients: 228.16.75.161 in server 202.104.236.2
   The clients: 152.169.154.136 in server 202.104.236.0
   The clients: 242.245.66.123 in server 202.104.236.0
   The clients: 46.125.92.115 in server 202.104.236.2
   The clients: 249.232.189.232 in server 202.104.236.3
   The clients: 196.82.30.94 in server 202.104.236.3
   The clients: 0.219.57.85 in server 202.104.236.2

   The servers 0 th has node: 2 .
   The servers 1 th has node: 0 .
   The servers 2 th has node: 5 .
   The servers 3 th has node: 3 .

   The clients: 199.61.192.87 in server 202.104.236.1
   The clients: 131.208.40.65 in server 202.104.236.2
   The clients: 138.195.163.174 in server 202.104.236.1
   The clients: 228.16.75.161 in server 202.104.236.1
   The clients: 152.169.154.136 in server 202.104.236.0
   The clients: 242.245.66.123 in server 202.104.236.0
   The clients: 46.125.92.115 in server 202.104.236.2
   The clients: 249.232.189.232 in server 202.104.236.3
   The clients: 196.82.30.94 in server 202.104.236.1
   The clients: 0.219.57.85 in server 202.104.236.1

   The servers 202.104.236.0 has node: 2 .
   The servers 202.104.236.1 has node: 5 .
   The servers 202.104.236.2 has node: 2 .
   The servers 202.104.236.3 has node: 1 .
```

可以看到的是，一开始我们将 10 个`client`分别分配到 4 个`server`上，在`server 1`下线之后，我们重新将`client`分布到其他服务器上，且这个分布是均匀的，不会出现将 1 结点的访问全部交给 2 结点的情况。

然后我们又将`server 1`恢复，可以看到的是，结点1的所有信息又回来了，且与原来下线之前的信息完全一致。

这样就简单的实现了一次一致性哈希的过程。