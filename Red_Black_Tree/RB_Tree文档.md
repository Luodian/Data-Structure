# 红黑树 — 你为什么这么复杂！

### 简述

红黑树（英语：Red–black tree）是一种自平衡二叉查找树，是在计算机科学中用到的一种数据结构，典型的用途是实现关联数组。它是在1972年由鲁道夫·贝尔发明的，他称之为"对称二叉B树"，它现代的名字是在Leo J. Guibas和Robert Sedgewick于1978年写的一篇论文中获得的。

它是复杂的，但它的操作有着良好的最坏情况运行时间，并且在实践中是高效的：它可以在O(log n)时间内做查找，插入和删除，这里的n是树中元素的数目。

红黑树和AVL树一样都对插入时间、删除时间和查找时间提供了最好可能的最坏情况担保（接近于问题的下限）。这不只是使它们在时间敏感的应用如实时应用（real time application）中有价值，而且使它们有在提供最坏情况担保的其他数据结构中作为建造板块的价值；例如，在计算几何中使用的很多数据结构都可以基于红黑树。

### 理论分析

红黑树是每个节点都带有颜色属性的二叉查找树，颜色为红色或黑色。在二叉查找树强制一般要求以外，对于任何有效的红黑树我们增加了如下的额外要求：

1. 节点是红色或黑色。
2. 根是黑色。
3. 所有叶子都是黑色（叶子是NIL节点）。
4. 每个红色节点必须有两个黑色的子节点。（从每个叶子到根的所有路径上不能有两个连续的红色节点。）
5. 从任一节点到其每个叶子的所有简单路径都包含相同数目的黑色节点。

下面是一个具体的红黑树的图例：

![](https://upload.wikimedia.org/wikipedia/commons/thumb/6/66/Red-black_tree_example.svg/900px-Red-black_tree_example.svg.png)



这些约束确保了红黑树的关键特性：从根到叶子的最长的可能路径不多于最短的可能路径的两倍长。结果是这个树大致上是平衡的。因为操作比如插入、删除和查找某个值的最坏情况时间都要求与树的高度成比例，这个在高度上的理论上限允许红黑树在最坏情况下都是高效的，而不同于普通的二叉查找树。

因此我们可以得出其各种操作的理论实践分析：

操作		Average		Worst Case
Space		$O(n)$		$O(n)$
Search		$O(log n)$		$O(log n)$
Insert		$O(log n)$		$O(log n)$
Delete		$O(log n)$		$O(log n)$

#### 然而最关键的并不是这个！

我认为最关键的是，红黑树作为一种这么复杂的数据结构（插入需要判断4种情况，删除需要判断5种情况），为什么能够在 Linux 2.2 版本中顶替掉AVL树作为其维护内核进程调度和内存管理的数据结构？其必然有其优越之处。

首先我们尝试着分析一下AVL树。

AVL是一种高度平衡的二叉树，所以通常的结果是，维护这种高度平衡所付出的代价比从中获得的效率收益还大，因为在一次不成功的删除或者插入，可能会造成从叶子节点一直旋转到根节点，不仅是对于时间的消耗，其对于栈空间的消耗也是$0(\log_2(N)$的.

而红黑树只是追求局部而不是非常严格整体平衡，以复杂的操作换取了最多三次的旋转维护，从而在针对插入和删除的效率上其比上AVL是一个非常不错的数据结构。

但是同样，AVL树高度的绝对平衡所带来的优势便是查找的常数效率更高，AVL是严格的$\Theta(\log_2(N))$的查找效率，但是对于红黑树，其查找的效率依赖于$O(h)，h为树的最大深度$.

### 数据测试

1. 简单测试与泛型测试

   ```cpp
   void FuncTest()
   {
   	cout<<"I. The first test is simple and function test.\n\n";
   	cout<<"********************************************\n";
       RB::RedBlackTree<int,int> A;
       for (int i = 1; i <= 9; ++i)
       {
       	A.insert(i,i);
       }
       cout<<"The tree's image is like this: \n\n";
       A.printTree();
       cout<<"\n";
       cout<<"The value of 1 is : ";
       cout<<A.find(1)<<endl;

       cout<<"If we remove the key 2.\n";
       cout<<"The tree changes to : \n\n";
       A.Remove(2);
       A.printTree();
       cout<<"\n";

       cout<<"The max element of the RB tree is : ";
       cout<<A.findMax()<<endl;

       // cout<<"The minimal element of the RB tree is : ";
       // cout<<A.findMin()<<endl;
   }

   void Generic_test()
   {
   	cout<<"II. The second test is a generic test.\n\n";
   	cout<<"********************************************\n";

   	foo_node head_node("null");
   	head_node.gradesSum = -INF;
   	RB::RedBlackTree<foo_node,int> A(head_node);
   	foo_node Kim("Kim");
   	Kim.grades[0] = 87;
   	Kim.grades[1] = 89;
   	Kim.grades[2] = 88;
   	Kim.grades[3] = 71;
   	Kim.grades[4] = 99;
   	Kim.sumUp();

   	foo_node Tom("Tom");
   	Tom.grades[0] = 83;
   	Tom.grades[1] = 86;
   	Tom.grades[2] = 68;
   	Tom.grades[3] = 71;
   	Tom.grades[4] = 89;
   	Tom.sumUp();

   	foo_node Frank("Frank");
   	Frank.grades[0] = 84;
   	Frank.grades[1] = 84;
   	Frank.grades[2] = 83;
   	Frank.grades[3] = 72;
   	Frank.grades[4] = 91;
   	Frank.sumUp();

   	A.insert(Kim,Kim.gradesSum);
   	A.insert(Tom,Tom.gradesSum);
   	A.insert(Frank,Frank.gradesSum);

   	cout<<"The sum of grades for Tom is :";
   	cout<<A.find(Tom)<<endl;
   	cout<<"The maxium grades for all is : ";
   	cout<<A.findMax()<<endl;
   	cout<<"\n";

   }
   ```

   输出结果如下：

   ```cpp
   I. The first test is simple and function test.

   ********************************************
   The tree's image is like this: 

            9 RED
         8 BLACK
            7 RED
      6 BLACK
         5 BLACK
   4 BLACK
         3 BLACK
      2 BLACK
         1 BLACK

   The value of 1 is : 1
   If we remove the key 2.
   The tree changes to : 

            9 RED
         8 BLACK
            7 RED
      6 RED
         5 BLACK
   4 BLACK
      3 BLACK
         1 RED

   The max element of the RB tree is : 9
   II. The second test is a generic test.

   ********************************************
   The sum of grades for Tom is :397
   The maxium grades for all is : 434
   ```

   对于泛型测试，我定义了foo_node，其中包含了人名以及五科的分数，将foo_node结点作为参数传入，通过重载小于运算符的方式实现了结点之间的比较，完成了泛型的功能。

   > 虽然系统对于很多常见的类型都进行了重载小于运算符，但是对于不可比的类型，我们必须通过为其重载小于运算符的方式，才能使得红黑树知道两个结点的大小关系。
   >
   > 同理，STL中的map也是这样实现的，当我们随意传入node时，它会提示我们为node类型不可比较，需要为node传入compare的仿函数参数才行。
   >
   > ```cpp
   > template <class _Key, class _Value, class _KeyOfValue, class _Compare,
   >           class _Alloc = __STL_DEFAULT_ALLOCATOR(_Value) >
   > ```
   >
   > STL中map的定义如上，其中第四个参数就是compare函数，当然也可以通过重载 < 运算符的方式解决这个问题，只是在内部比较那里有细微的区分。

2. 下面是针对于 10000 - 1000000 随机数据区间，总共100组数据的插入操作

![insert_random_whole](/Users/luodian/Desktop/DSA/Red_Black_Tree/Red_Black_Tree/insert_random_whole.png)

![insert_random](/Users/luodian/Desktop/DSA/Red_Black_Tree/Red_Black_Tree/insert_random.png)

​	可以看到的是，红黑树在插入的测试上的确是略优于AVL树的。



3. 下面是针对于 10000 - 1000000 有序数据，总共100组数据的插入操作。

![insert_sequntial_whole](/Users/luodian/Desktop/DSA/Red_Black_Tree/Red_Black_Tree/insert_sequntial_whole.png)

在这里我们可以看到的是，AVL树要快于红黑树，推测应该是AVL在此种情况下似乎只会不断的针对LL和RR型不平衡进行在叶子节点处的单旋转，因此平均只需要1次旋转。



4. 下面是针对于 10000 - 1000000 随机数据，总共100组数据的查找操作。

![search_random_whole](/Users/luodian/Desktop/DSA/Red_Black_Tree/Red_Black_Tree/search_random_whole.png)

5. 下面是针对于 10000 - 1000000 线性数据，总共100组数据的查找操作。

![search_sequntial_whole](/Users/luodian/Desktop/DSA/Red_Black_Tree/Red_Black_Tree/search_sequntial_whole.png)对于随机数据和有序数据的查找，实质是一样的，对于我们将树建好之后，其查找效率只会受到高度的影响，

正如上面说到的，AVL是严格的$\Theta(\log_2(N))$，对于红黑树，其查找的效率为$O(h)，h为树的最大深度$.

因此我们可以看到在图表中也能够反映出来，AVL的效率在常数时间内是要高于红黑树的。