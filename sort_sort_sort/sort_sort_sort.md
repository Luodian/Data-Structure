#Sort sort sort !!!


对于在计算机的应用中，排序可以说是最广泛最基础但是却又不太引人注意的需求。一方面我们需要在大大小小的编程中对各式各样的元素，结构，类型等进行排序，而另一方面我们却又因为很多编程语言，操作系统的库中都有现成的排序函数而渐渐的忽视了排序的重要性。
很多时候一行`std::sort(v.begin(),v.end())`可以解决的问题，如果仔细剖解开来看，也是颇有些意味。

首先从各种排序函数开始。

## 平方以及亚平方级别排序算法
本次实验我实现了两种平方排序，一种亚平方级别排序算法，分别是冒泡排序和插入排序，以及希尔排序
以下分别是三种算法流程。
```cpp
template <class RandomIterator>
inline void bubble_sort(RandomIterator first,RandomIterator last)
{
    if (first == last)
    {
        return;
    }
    else
    {
        bool swapped = 1;
        for (RandomIterator itr = first; itr < last && swapped == 1; ++itr)
        {
            swapped = 0;
            for (RandomIterator j = first + 1; j < (first + (last - itr)); ++j)
            {
                if (*(j-1) > *(j))
                {
                    std::swap(*(j),*(j-1));
                    swapped = 1;
                }
            }
        }
    }
}

template<class RandomIterator>
//版本一，重载小于符号。
inline void insertion_sort(RandomIterator first,RandomIterator last)
{
    using T = typename iterator_traits<RandomIterator>::value_type;
    if (first == last)
    {
        //区间为空
        return;
    }
    else
    {   
        for (RandomIterator itr = first + 1; itr != last; ++itr)
        {
            if (*(itr) < *(itr - 1))
            {
                T val = *(itr);
                RandomIterator j = itr;
                while(j != first && *(j-1) > val)
                {
                    *(j) = *(j - 1);
                    j -- ;
                }
                *(j) = val;
            }
        }
    }
}

int gapsInt[] = {701, 301, 132, 57, 23, 10, 4, 1};
std::vector<int> gaps(gapsInt,gapsInt + sizeof(gapsInt) / sizeof(int));
//Using Marcin Ciura's gap sequence, with an inner insertion sort.
template <class RandomIterator>
void shell_sort(RandomIterator first,RandomIterator last)
{   
    using T = typename iterator_traits<RandomIterator>::value_type;
    RandomIterator jtr;
    for (int i = 0; i < gaps.size(); ++i)
    {
        int gap = gaps[i];
        for (RandomIterator itr = first + gap; itr < last; ++itr)
        {
            T val = *(itr);
            for (jtr = itr; jtr >= first + gap && *(jtr - gap) > val; jtr -= gap)
            {
                *(jtr) = *(jtr - gap);
            }
            *(jtr) = val;
        }
    }
}

```

对于这三组排序，我分别进行了从1000 ~ 100000随机数据的测试。
测试结果如下。

![pic 1](http://opmza2br0.bkt.clouddn.com/17-5-11/4713782-file_1494501801042_16432.png)

从测试结果可以看到，冒泡排序和插入排序远远的慢于希尔排序。
对于冒泡以及插入排序，其时间效率为 $O(n^2)$.

而对于希尔排序，其排序时间复杂度基于选取的间隔，对于本次试验我选取的间隔，其理论时间复杂度为 $O(n^{1.37}).$

### 超线性（准线性）排序算法

本次实验我实现了三种排序算法，分别是堆排序，归并排序，快速排序（随机选取枢纽，默认选取最左边元素为枢纽元）。

具体实现如下

其中对于`quick_sort`的方法，可以对其传入相应位置的仿函数来进不同功能（random or leftist）的选取。

```cpp
template <class RandomIterator>
//迭代器的末尾位置始终处于最后一个元素的下一位
//迭代归并，自底向上计算
void merge_sort(RandomIterator first,RandomIterator last)
{
    using T = typename iterator_traits<RandomIterator>::value_type;
    RandomIterator pos = first;
    size_t len = last - first;
    T* aux = new T[len];
    for (size_t seg = 1;seg < len; seg += seg)
    {
        for (size_t start = 0; start < len; start += (2 * seg))
        {
            size_t low = start;
            size_t mid = std::min(start + seg,len);
            size_t high = std::min(start + 2 * seg,len);
            size_t k = low;
            size_t start1 = low;
            size_t end1 = mid;
            size_t start2 = mid;
            size_t end2 = high;
            while(start1 < end1 && start2 < end2)
            {
                aux[k++] = *(pos + start1) < *(pos + start2) ? *(pos + start1++) : *(pos + start2++);
            }
            while(start1 < end1)
            {
                aux[k++] = *(pos + start1 ++);
            }
            while(start2 < end2)
            {
                aux[k++] = *(pos + start2 ++);
            }
        }
        RandomIterator itr;
        size_t i;
        for (itr = first,i = 0; i < len; ++i)
        {
            *(itr++) = aux[i];
        }
    }

    // int k;
    // for (pos = first,k = 0; pos < last; ++pos)
    // {
    //  *(pos) = aux[k++];
    // }
    delete [] aux;
}

template <class RandomIterator,class mode_selector>
void quick_sort(RandomIterator pos,int left,int right,mode_selector mode_func)
{
    using T = typename iterator_traits<RandomIterator>::value_type;
    if (left < right)
    {
        int low = left;
        int high = right;
        int pivotPos = mode_func(pos,left,right);
        T key = *(pos + pivotPos);//取第一个元素为基准元
        std::swap(*(pos + left),*(pos + pivotPos));
        while(low < high)
        {
            while(low < high && !(*(pos + high) < key))
            {
                high --;
            }
            if (low < high)
            {
                *(pos + low) = *(pos + high);
                low ++;
            }
            else
            {
                break;
            }
            while(low < high && !(*(pos + low) > key))
            {
                low ++;
            }
            if (low < high)
            {
                *(pos + high) = *(pos + low); 
                high --;
            }
            else
            {
                break;
            }
        }
        *(pos + low) = key;
        quick_sort(pos,left,low - 1,mode_func);
        quick_sort(pos,low + 1,right,mode_func);
    }
}


template <class RandomIterator>
void heapsort(RandomIterator first,RandomIterator last)
{
    using T = typename iterator_traits<RandomIterator>::value_type;
    std::vector<T> aux;
    for (RandomIterator itr = first; itr < last; ++itr)
    {
        aux.push_back(*(itr));
    }
    BinaryHeap<T> heap(aux);
    RandomIterator itr = first;
    while(!heap.empty())
    {
        *(itr++) = heap.front();
        heap.pop_front();
    }
}

template <class RandomIterator,class mode_selector>
void quicksort(RandomIterator first,RandomIterator last,mode_selector mode_func)
{
    int left = 0;
    int right = last - first - 1;
    RandomIterator pos = first;
    quick_sort(pos,left,right,mode_func);
}

```


## 线性排序算法

对于线性排序算法，我选择了桶排序，基数排序，基于空间优化的桶排序三种算法进行实现。
具体代码如下

```cpp
template <class RandomIterator>
inline void bucket_sort(RandomIterator first,RandomIterator last,int maxLimit)
{
    RandomIterator pos = first;
    using T = typename iterator_traits<RandomIterator>::value_type;
    std::vector<T> bucket;
    bucket.resize(maxLimit);
    int len = last - first;
    for (int i = 0; i < len; ++i)
    {
        bucket[*(pos+i)] ++;
    }
    pos = first;
    for (int i = 0; i < maxLimit; ++i)
    {
        for (int j = 0; j < bucket[i]; ++j)
        {
            *(pos++) = i;
        }
    }
}

template <class RandomIterator>
void optimal_bucktet_sort(RandomIterator first,RandomIterator last)
{
    int maxInt = -0x3f3f3f3f;
    for (RandomIterator pos = first; pos < last; pos ++)
    {
        maxInt = std::max(maxInt,*(pos));
    }
    int divide = (maxInt+20) / 10;
    std::vector<int> aux[10];
    for (RandomIterator pos = first; pos < last; ++pos)
    {
        for (int bound = 0,hole = 0; hole < 10; bound += (divide),hole ++)
        {
            if (*(pos) <= bound)
            {
                aux[hole].push_back(*(pos));
                break;
            }
        }
    }
    for (int i = 0; i < 10; ++i)
    {
        std::sort(aux[i].begin(),aux[i].end());
    }
    RandomIterator pos = first;
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < aux[i].size(); ++j)
        {
            *(pos++) = aux[i][j];
        }
    }
}

std::string deciTostring(int maxRadix,int decimal)
{
    int decimal_backup = decimal;
    std::string ret;
    std::stack<char> reverse;
    while(decimal_backup)
    {
        reverse.push(decimal_backup % 10 + '0');
        decimal_backup /= 10;
    }
    while(reverse.size() < maxRadix)
    {
        reverse.push('0');
    }
    while(!reverse.empty())
    {
        ret.push_back(reverse.top());
        reverse.pop();
    }
    return ret;
}

int strTodeci(std::string str)
{
    int ret = 0;
    for (int i = 0; i < str.size(); ++i)
    {
        ret += (str[i] - '0');
        ret *= 10;
    }
    return ret / 10;
}

template <class RandomIterator>
void radix_sort(RandomIterator first,RandomIterator last,int maxRadix,clock_t &minus)
{
    minus = clock();
    std::vector<std::string> bucket[10];
    RandomIterator itr = first;
    std::vector<std::string> str_arr;
    minus = clock() - minus;
    while(itr != last)
    {
        str_arr.push_back(deciTostring(maxRadix,*(itr)));
        itr ++;
    }
    for (int i = maxRadix - 1; i >= 0; --i)
    {
        for (int j = 0; j < str_arr.size(); ++j)
        {
            bucket[str_arr[j][i] - '0'].push_back(str_arr[j]);
        }
        int k = 0;
        for (int i = 0; i < 10; ++i)
        {
            for (int j = 0; j < bucket[i].size(); ++j)
            {
                str_arr[k++] = bucket[i][j];
            }
            bucket[i].clear();
        }
    }
    itr = first;
    int k = 0;
    while(itr != last)
    {
        *(itr++) = strTodeci(str_arr[k++]);
    }
}
```

对于这三种算法，其效率都明显的较前两种方式快了许多。
在对比测试中，也加入了 `std::sort()` 进行横向测试。

测试数据总共分为100组，规模从小到大分别为10000 ~ 1000000

其中准线性排序算法和线性排序算法的横向测试结果如下。

![pic 2](http://opmza2br0.bkt.clouddn.com/17-5-11/90973979-file_1494505218935_d81e.png)

对于桶排序，其最坏情况下需要 $O(maxint)$ 的空间来保存中间状态，对于基数排序，其思路虽然并不如桶排序粗暴，但是其空间复杂度也已经达到了 $O(bit * n)$（而且其时间效率也较直接的桶排序慢了许多）。
对于最后一种基于空间优化的桶排序，实质上是根据数组中的最大值将数分成了很多区间，然后一边扫描之后分别决定数的位置，最后再对每个小桶进行一次基于交换的排序（如快速排序）。

实际上我们从以上的几种算法可以很明显的看出，对于线性排序算法的效率分析，其本质上是一次时间与空间的Trade off，时间效率越高，空间上的消耗也相应的会越大。

而相应的，线性排序更多的是基于将数位的特性转换为大小的关系，因此其并不方便对相应的排序进行泛型，而我想，这恐怕也就是STL里面并不提供线性排序的库函数的一个缘故吧。

## 快速排序枢纽元的选取

我们都知道，快速排序不是一种十分优化的排序方式，它的时间复杂度并不够稳定，对于默认选取最左枢纽元素时，因为其每次选取的枢纽元只能将一个元素划分出去，因此其对于有序情况时排序会退化至 $O(n^2)$。算法导论中对于这种情况进行了相应的讨论，且对快速排序提出了一种随机化优化的版本，并且证明了其期望下的时间复杂度为 $O(n \cdot \lg_2{n})$.

本次实验中我也对这种情形进行了测试。

对于两种不同选取枢纽元方式的快速排序，其测试结果如下。

对于随机数据结果如下

![pic 4](http://opmza2br0.bkt.clouddn.com/17-5-11/56085980-file_1494501800661_15295.png)

对于正向有序数据结果如下
![pic 3](http://opmza2br0.bkt.clouddn.com/17-5-11/37588278-file_1494501800924_163b1.png)

对于逆向有序数据结果如下

![pic 5](http://opmza2br0.bkt.clouddn.com/17-5-11/30617057-file_1494501800806_5533.png)

从测试的结果可以看出。

对于随机化数据，选取最左枢纽元的方式较为占优，因为其少了一个随机数据的过程，因此在常数时间内较随机化算法更有优势。

但是对于正向有序的数据，其结果证实了理论的分析，选取最左枢纽元的方式退化成了 $O(n^2)$ 的插入排序。

对于逆向有序的数据也是如此。

## 泛型设计与C++与STL的一些小结

本次实验我采用的是类似于STL中对于`std::sort()`的实现方式，是基于随机迭代器上实现的，其需要传入的参数分别为指针，随机迭代器。

对于指针操作可以针对于任意的数据，数据块，只要为一个指针数据即可。

对于随机迭代器，其支持的容器类型如下。

![pic 6](http://opmza2br0.bkt.clouddn.com/17-5-11/54770869-file_1494506739744_942.jpg)

另外，归功于C++中良好的设计，以及STL对于迭代器萃取这个技术的设计，我成功的实现了在函数内通过迭代器萃取的方式，推断出迭代器所指元素的类型，从而实现了真正的泛型，真正的利用了迭代器实现了算法（sort）与数据结构（container）的分离，避免了容器其他细节的暴露，从而实现了结构上的低耦合。

而更让人感到神奇的是，
STL中Traits特性与C++中特化类模板的巧妙结合，使得不论是类实例化模板，还是指针抑或指向常量的指针进行实例化模板，都保证了模板的交出的类型都是合乎程序需要的。

```cpp
//对常见的类型进行模板特化
//如果未定义，则需传入对应的functor
template <class T>
class compare
{
public:
    bool operator () (const T &a,const T &b) const
    {
        return compare<std::underlying_type<T>>()(a,b);
    }
    static_assert(std::is_enum<T>(), "This type has no default compare function.");
};

template <>
class compare <int> 
{
public:
    bool operator () (const int &a,const int &b) const
    {
        return a < b;
    }
};

template <>
class compare <long> 
{
public:
    bool operator () (const long &a,const long &b) const
    {
        return a < b;
    }
};
```

这十分完美的契合了迭代器的设计理念，也是我自学习C++以来，其六大组件除了`allocator`之外，其余均有接触，但一直都仅仅只知STL在用，我便模仿即可，却不知道STL为什么用，为什么这么用，而这次真正的了解到了STL设计思想的冰山一角，仅仅如此便让我感受到了无边的深邃与神妙。

这种如同朝圣一般的感受也坚定了我进一步去学习STL的步伐。

> STL在排序这一部分，不仅仅是上述的对于泛型的完美支持值得称赞，其内置的intro_sort算法部分的设计思想也是非常巧妙和值得学习的。

处于对STL的致敬，本次实验我实现的所有 `sort` 函数均可以与`vector,deque`容器进行无缝衔接，同时也支持数组的指针作为参数传入的方式。
如快速排序，调用的方式为`quicksort(v.begin(),v.end()))`，与stl中sort函数用法完全一致。

代码部分如下：

```cpp
    //int类型数组
    int int_arr[10] = {0,1,4,1,2,5,213,3214,21,14};
    //float类型数组
    float float_arr[10] = {0.1 ,2.2 ,3.2 ,4.1, 3.2, 41, 9.1, 10.123, 11.23, 12.89};
    //vector容器，int类型
    std::vector<int> vec_arr(int_arr,int_arr + 10);
    //deque容器，float类型
    std::deque<float> deque_arr(float_arr,float_arr + 10);

    std::cout<<"1.int* type sort.\n";
    std::cout<<"  The array before merge sort is: \n";
    std::cout<<"  ";
    std::for_each(int_arr,int_arr + 10,display<int>());
    std::cout<<"\n\n";

    //利用指针的方式调用
    merge_sort(int_arr,int_arr + 10);

    std::cout<<"  The array after merge sort is: \n";
    std::cout<<"  ";
    std::for_each(int_arr,int_arr + 10,display<int>());
    std::cout<<"\n\n";


    std::cout<<"2.vector type sort.\n";
    std::cout<<"  The array before merge sort is: \n";
    std::cout<<"  ";
    std::for_each(vec_arr.begin(),vec_arr.end(),display<int>());
    std::cout<<"\n\n";

    //利用迭代器的方式传参，传入vector容器的随机迭代器
    merge_sort(vec_arr.begin(),vec_arr.end());

    std::cout<<"  The array after merge sort is: \n";
    std::cout<<"  ";
    std::for_each(vec_arr.begin(),vec_arr.end(),display<int>());
    std::cout<<"\n\n";

    std::cout<<"3.float* type sort.\n";
    std::cout<<"  The array before merge sort is: \n";
    std::cout<<"  ";
    std::for_each(float_arr,float_arr + 10,display<float>());
    std::cout<<"\n\n";

    //利用指针的方式调用
    merge_sort(float_arr,float_arr + 10);

    std::cout<<"  The array after merge sort is: \n";
    std::cout<<"  ";
    std::for_each(float_arr,float_arr + 10,display<float>());
    std::cout<<"\n\n";

    std::cout<<"4.deque type sort.\n";
    std::cout<<"  The array before merge sort is: \n";
    std::cout<<"  ";
    std::for_each(deque_arr.begin(),deque_arr.end(),display<float>());
    std::cout<<"\n\n";

    //利用迭代器的方式传参，传入vector容器的随机迭代器
    merge_sort(deque_arr.begin(),deque_arr.end());

    std::cout<<"  The array after merge sort is: \n";
    std::cout<<"  ";
    std::for_each(deque_arr.begin(),deque_arr.end(),display<float>());
    std::cout<<"\n\n";
```

**可以见得其非常好的支持了多种容器，各种类型的排序需求。**


同样的，参考了STL中的实现方式。
对于每个函数我都制作了重载小于运算符和传入functor两个同名函数，根据具体的参数实现相应的函数重载。

```cpp

//__insertion_sort以双层循环形式进行。外循环遍历整个序列，每次迭代决定出一个子区间；
//内循环遍历子区间，将子区间内的每一个“逆转对”倒转过来，如果一旦不存在“逆转对”，表示排序完毕。
//“逆转对”概念：指任何两个迭代器i和j，i<j,而*i>*j.
//版本一
template <class _RandomAccessIter>
void __insertion_sort(_RandomAccessIter __first, _RandomAccessIter __last) {
  if (__first == __last) return; //若区间为空，则退出
  for (_RandomAccessIter __i = __first + 1; __i != __last; ++__i)//外循环，遍历整个区间
      //[first,i)形成的子空间
    __linear_insert(__first, __i, __VALUE_TYPE(__first));
}
//版本二
template <class _RandomAccessIter, class _Compare>
void __insertion_sort(_RandomAccessIter __first,
                      _RandomAccessIter __last, _Compare __comp) {
  if (__first == __last) return;
  for (_RandomAccessIter __i = __first + 1; __i != __last; ++__i)
    __linear_insert(__first, __i, __VALUE_TYPE(__first), __comp);
}

```
其中版本一是通过重载小于运算符的方式，版本二是使用仿函数的方式自定义比较方式（自己定义大小关系）
对每个排序函数，在`sort.hpp`文件中我也加入了对应的仿函数实现版本，在调用的过程中，对用户自定义类型进行排序的过程中，就有如下的测试结果。

```cpp
    struct node
    {
        std::string name;
        int a;
        int b;
        node (std::string _n = "",int _a = 0,int _b = 0)
        {
            name = _n;
            a = _a;
            b = _b;
        }
        bool operator < (const node & rhs) const
        {
            return a + b > (rhs.a + rhs.b);
        }
        friend std::ostream & operator << (std::ostream &out,const node &rhs)
        {
            out<<"  "<<rhs.name<<": ";
            out<<rhs.a<<" "<<rhs.b<<"\n";
            return out;
        }
    };

    //仿函数
    template <class T>
    class foo_compare
    {
    public:
        bool operator () (const T &node_a,const T&node_b) const
        {
            return node_a.a + node_a.b > node_b.a + node_b.b;
        }
    };

    std::vector<node> node_arr;
    node_arr.resize(4);
    node_arr[0] = node("武德浩",100,98);
    node_arr[1] = node("万丁",98,96);
    node_arr[2] = node("李博",66,66);
    node_arr[3] = node("张永顺",100,100);

    std::cout<<"5.custom type sort(Reload less operator).\n";
    std::cout<<"  The array before merge sort is: \n";
    for (int i = 0; i < 4; ++i)
    {
        std::cout<<node_arr[i];
    }
    std::cout<<"\n\n";

    //不使用仿函数，根据函数重载的规则，调用的是重载小于运算符的版本。
    merge_sort(node_arr.begin(),node_arr.end());

    std::cout<<"  The array after merge sort is: \n";
    for (int i = 0; i < 4; ++i)
    {
        std::cout<<node_arr[i];
    }
    std::cout<<"\n\n";

    node_arr[0] = node("武德浩",100,98);
    node_arr[1] = node("万丁",98,96);
    node_arr[2] = node("李博",66,66);
    node_arr[3] = node("张永顺",100,100);

    std::cout<<"6.custom type sort(convey compare functor).\n";
    std::cout<<"  The array before merge sort is: \n";
    for (int i = 0; i < 4; ++i)
    {
        std::cout<<node_arr[i];
    }
    std::cout<<"\n\n";

    //传入仿函数foo_compare作为比较函数
    merge_sort(node_arr.begin(),node_arr.end(),foo_compare<node>());

    std::cout<<"  The array after merge sort is: \n";
    for (int i = 0; i < 4; ++i)
    {
        std::cout<<node_arr[i];
    }
    std::cout<<"\n\n";
```
测试结果如下
```
5.custom type sort(Reload less operator).
  The array before merge sort is: 
  武德浩: 100 98
  万丁: 98 96
  李博: 66 66
  张永顺: 100 100


  The array after merge sort is: 
  张永顺: 100 100
  武德浩: 100 98
  万丁: 98 96
  李博: 66 66
  //顺哥最强！

6.custom type sort(convey compare functor).
  The array before merge sort is: 
  武德浩: 100 98
  万丁: 98 96
  李博: 66 66
  张永顺: 100 100


  The array after merge sort is: 
  张永顺: 100 100
  武德浩: 100 98
  万丁: 98 96
  李博: 66 66
```

###说完了，That's all.

























