//
//  sort.hpp
//  sort_sort_sort
//
//  Created by 李博 on 08/05/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#ifndef sort_h
#define sort_h

#include "Header.hpp"
#include "Heap.hpp"

// using namespace std;

// //__insertion_sort版本一的辅助函数
// template <class _RandomAccessIter, class _Tp>
// inline void __linear_insert(_RandomAccessIter __first, 
//                             _RandomAccessIter __last, _Tp*) {
//   _Tp __val = *__last;//记录尾元素
//   if (__val < *__first) {//尾元素比头元素还小
//       //将整个区间向右移一个位置
//     copy_backward(__first, __last, __last + 1);
//     *__first = __val;//令头元素等于原先的尾元素
//     //以上两行命令的功能相等于交换两个元素
//   }
//   else//尾元素不小于头元素
//     __unguarded_linear_insert(__last, __val);
// }
// //__insertion_sort以双层循环形式进行。外循环遍历整个序列，每次迭代决定出一个子区间；
// //内循环遍历子区间，将子区间内的每一个“逆转对”倒转过来，如果一旦不存在“逆转对”，表示排序完毕。
// //“逆转对”概念：指任何两个迭代器i和j，i<j,而*i>*j.
// //版本一
// template <class _RandomAccessIter>
// void __insertion_sort(_RandomAccessIter __first, _RandomAccessIter __last) {
//   if (__first == __last) return; //若区间为空，则退出
//   for (_RandomAccessIter __i = __first + 1; __i != __last; ++__i)//外循环，遍历整个区间
//       //[first,i)形成的子空间
//     __linear_insert(__first, __i, __VALUE_TYPE(__first));
// }
// 
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

template <>
class compare <long long> 
{
public:
	bool operator () (const long long &a,const long long &b) const
	{
		return a < b;
	}
};

template <>
class compare <size_t> 
{
public:
	bool operator () (const size_t &a,const size_t &b) const
	{
		return a < b;
	}
};

template <>
class compare <float> 
{
public:
	bool operator () (const float &a,const float &b) const
	{
		return a < b;
	}
};

template <>
class compare <double> 
{
public:
	bool operator () (const double &a,const double &b) const
	{
		return a < b;
	}
};

template <class Iterator>
struct iterator_traits
{
	typedef typename Iterator::value_type value_type;
};

template <class Iterator>
struct iterator_traits<Iterator*>
{
	typedef Iterator value_type;
};

template<class RandomIterator>
//版本一，重载小于符号。
inline void insertion_sort(RandomIterator first,RandomIterator last)
{
	using T = typename iterator_traits<RandomIterator>::value_type;
	if (first == last)
	{
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

template<class RandomIterator,class Compare>
//版本二，仿函数实现。
inline void insertion_sort(RandomIterator first,RandomIterator last,Compare comp)
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
			if (comp(*(itr),*(itr - 1)))
			{
				T val = *(itr);
				RandomIterator j = itr;
				while(j != first && comp(val,*(j-1)))
				{
					*(j) = *(j - 1);
                    j -- ;
				}
				*(j) = val;
			}
		}
	}
}

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

template <class RandomIterator,class Compare>
inline void bubble_sort(RandomIterator first,RandomIterator last,Compare comp)
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
				if (comp(*(j),*(j-1)))
				{
					std::swap(*(j),*(j-1));
					swapped = 1;
				}
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

template <class RandomIterator,class Compare>
void shell_sort(RandomIterator first,RandomIterator last,Compare comp)
{	
	using T = typename iterator_traits<RandomIterator>::value_type;
	RandomIterator jtr;
	for (int i = 0; i < gaps.size(); ++i)
	{
		int gap = gaps[i];
		for (RandomIterator itr = first + gap; itr < last; ++itr)
		{
			T val = *(itr);
			for (jtr = itr; jtr >= first + gap && comp(val,*(jtr - gap)); jtr -= gap)
			{
				*(jtr) = *(jtr - gap);
			}
			*(jtr) = val;
		}
	}
}

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
	// 	*(pos) = aux[k++];
	// }
	delete [] aux;
}

template <class RandomIterator,class Compare>
//迭代器的末尾位置始终处于最后一个元素的下一位
//迭代归并，自底向上计算
void merge_sort(RandomIterator first,RandomIterator last,Compare comp)
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
				aux[k++] = comp(*(pos + start1),*(pos + start2)) ? *(pos + start1++) : *(pos + start2++);
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
	// 	*(pos) = aux[k++];
	// }
	delete [] aux;
}

// long long seed = std::chrono::system_clock::now().time_since_epoch().count();
// std::default_random_engine generator((unsigned int)seed);

// template <class RandomIterator>
// class randomGet
// {
// public:
// 	inline int operator () (RandomIterator itr,const int &n) const
// 	{
// 		std::uniform_int_distribution<int> distribution(0,(int)n);
// 		auto dice = bind(distribution,generator);
// 		return int(dice());
// 	}
// };

// template <class RandomIterator>
// class median_of_three
// {
// public:
// 	inline int operator () (RandomIterator itr,const int &n) const
// 	{
// 		// std::uniform_int_distribution<int> distribution(1,n);
// 		// auto dice = bind(distribution,generator);
// 		// return size_t(dice());
// 		int mid = n / 2;
// 		RandomIterator a = itr;
// 		RandomIterator b = itr + mid;
// 		RandomIterator c = itr + n - 1;
// 		if (*(a) > *(b))
// 		{
// 			std::swap(*(a),*(b));
// 		}
// 		if (*(b) > *(c))
// 		{
// 			std::swap(*(b),*(c));
// 		}
// 		if (*(a) > (*b))
// 		{
// 			std::swap(*(a),*(b));
// 		}
// 		return n / 2;
// 	}
// };



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




#endif /* sort_h */
