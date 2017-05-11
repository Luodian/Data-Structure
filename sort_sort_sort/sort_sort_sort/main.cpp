//
//  main.cpp
//  sort_sort_sort
//
//  Created by 李博 on 08/05/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#include <iostream>
#include "Header.hpp"
#include "sort.hpp"

template <class T>
class display
{
public:
	void operator () (const T &x) const
	{
		std::cout<<x<<" ";
	}
};

template <class RandomIterator>
class leftiest
{
public:
	inline int operator () (RandomIterator itr, const int& left,const int &right) const
	{
		return left;
	}
};

template <class RandomIterator>
class randomGet
{
public:
	inline int operator () (RandomIterator itr,const int &left,const int &right) const
	{
        long long seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator((unsigned int)seed);
		std::uniform_int_distribution<int> distribution(left,right);
		auto dice = bind(distribution,generator);
		return int(dice());
	}
};

template <class RandomIterator>
class median_of_three
{
public:
	inline int operator () (RandomIterator itr,const int &left,const int &right) const
	{
		int mid = (right - left) / 2;
		RandomIterator a = itr;
		RandomIterator b = itr + mid;
		RandomIterator c = itr + right;
		if (*(a) > *(b))
		{
			std::swap(*(a),*(b));
		}
		if (*(b) > *(c))
		{
			std::swap(*(b),*(c));
		}
		if (*(a) > (*b))
		{
			std::swap(*(a),*(b));
		}
		return mid;
	}
};

void unit_test()
{
	std::vector<int> foo;
	std::vector<int> bar;
   	foo.resize(20);
   	std::fstream infile;
   	infile.open("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/in.txt",std::ios::in);
	for (int i = 0; i < foo.size(); ++i)
	{
		infile>>foo[i];
	}
	std::cout<<"I. Unit test.\n\n";
	std::cout<<"****************************************************\n";
	std::cout<<"1.Insertion sort.\n";
	std::cout<<"  The array before insertion sort is: \n";

	infile.close();

	bar = foo;
	std::cout<<"  ";
	std::for_each(bar.begin(),bar.end(),display<int>());
   	std::cout<<"\n\n";

   	// quicksort(bar.begin(),bar.end(),leftiest<std::vector<int>::iterator>());
   	// quicksort(bar.begin(),bar.end(),randomGet<std::vector<int>::iterator>());
   	// quicksort(bar.begin(),bar.end(),median_of_three<std::vector<int>::iterator>());
   	// heapsort(bar.begin(),bar.end());
   	insertion_sort(bar.begin(),bar.end());
   	// std::cout<<float(t) / float(CLOCKS_PER_SEC)<<"\n";
   	std::cout<<"  The array after insertion sort is: \n";
   	std::cout<<"  ";
   	std::for_each(bar.begin(),bar.end(),display<int>());
   	std::cout<<"\n\n";


   	bar = foo;
   	std::cout<<"2.Bubble sort.\n";
	std::cout<<"  The array before bubble sort is: \n";
	std::cout<<"  ";
   	std::for_each(bar.begin(),bar.end(),display<int>());
   	std::cout<<"\n\n";

   	bubble_sort(bar.begin(),bar.end());

   	std::cout<<"  The array after bubble sort is: \n";
   	std::cout<<"  ";
   	std::for_each(bar.begin(),bar.end(),display<int>());
   	std::cout<<"\n\n";

   	bar = foo;
   	std::cout<<"3.Shell sort.\n";
	std::cout<<"  The array before shell sort is: \n";
	std::cout<<"  ";
   	std::for_each(bar.begin(),bar.end(),display<int>());
   	std::cout<<"\n\n";
   	
   	shell_sort(bar.begin(),bar.end());

   	std::cout<<"  The array after shell sort is: \n";
   	std::cout<<"  ";
   	std::for_each(bar.begin(),bar.end(),display<int>());
   	std::cout<<"\n\n";

   	bar = foo;
   	std::cout<<"4.Merge sort.\n";
	std::cout<<"  The array before merge sort is: \n";
	std::cout<<"  ";
   	std::for_each(bar.begin(),bar.end(),display<int>());
   	std::cout<<"\n\n";
   	
   	bubble_sort(bar.begin(),bar.end());

   	std::cout<<"  The array after merge sort is: \n";
   	std::cout<<"  ";
   	std::for_each(bar.begin(),bar.end(),display<int>());
   	std::cout<<"\n\n";


   	bar = foo;
   	std::cout<<"5.Quick sort(Leftist).\n";
	std::cout<<"  The array before quick sort is: \n";
	std::cout<<"  ";
   	std::for_each(bar.begin(),bar.end(),display<int>());
   	std::cout<<"\n\n";
   	
   	quicksort(bar.begin(),bar.end(),leftiest<std::vector<int>::iterator>());

   	std::cout<<"  The array after quick sort is: \n";
   	std::cout<<"  ";
   	std::for_each(bar.begin(),bar.end(),display<int>());
   	std::cout<<"\n\n";

   	bar = foo;
   	std::cout<<"6.Quick sort(Random).\n";
	std::cout<<"  The array before bubble sort is: \n";
	std::cout<<"  ";
   	std::for_each(bar.begin(),bar.end(),display<int>());
   	std::cout<<"\n\n";
   	
   	quicksort(bar.begin(),bar.end(),randomGet<std::vector<int>::iterator>());

   	std::cout<<"  The array after quick sort is: \n";
   	std::cout<<"  ";
   	std::for_each(bar.begin(),bar.end(),display<int>());
   	std::cout<<"\n\n";

   	bar = foo;
   	std::cout<<"7.Heap sort.\n";
	std::cout<<"  The array before heap sort is: \n";
	std::cout<<"  ";
   	std::for_each(bar.begin(),bar.end(),display<int>());
   	std::cout<<"\n\n";
   	
   	heapsort(bar.begin(),bar.end());

   	std::cout<<"  The array after insertion sort is: \n";
   	std::cout<<"  ";
   	std::for_each(bar.begin(),bar.end(),display<int>());
   	std::cout<<"\n\n";

   	bar = foo;
   	std::cout<<"8.Bucket sort.\n";
	std::cout<<"  The array before bucket sort is: \n";
	std::cout<<"  ";
   	std::for_each(bar.begin(),bar.end(),display<int>());
   	std::cout<<"\n\n";
   	
   	bucket_sort(bar.begin(),bar.end(),20);

   	std::cout<<"  The array after bucket sort is: \n";
   	std::cout<<"  ";
   	std::for_each(bar.begin(),bar.end(),display<int>());
   	std::cout<<"\n\n";

   	bar = foo;
   	std::cout<<"9.Optimal bucket sort.\n";
	std::cout<<"  The array before optimal bucket sort is: \n";
	std::cout<<"  ";
   	std::for_each(bar.begin(),bar.end(),display<int>());
   	std::cout<<"\n\n";
   	
   	optimal_bucktet_sort(bar.begin(),bar.end());

   	std::cout<<"  The array after optimal bucket sort is: \n";
   	std::cout<<"  ";
   	std::for_each(bar.begin(),bar.end(),display<int>());
   	std::cout<<"\n\n";

   	bar = foo;
   	std::cout<<"10.radix sort.\n";
	std::cout<<"  The array before radix sort is: \n";
	std::cout<<"  ";
   	std::for_each(bar.begin(),bar.end(),display<int>());
   	std::cout<<"\n\n";
   	clock_t fill;
   	radix_sort(bar.begin(),bar.end(),3,fill);

   	std::cout<<"  The array after radix sort is: \n";
   	std::cout<<"  ";
   	std::for_each(bar.begin(),bar.end(),display<int>());
   	std::cout<<"\n\n";
}

int RandomNum(int n)
{
    unsigned int seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(0,n);
    
    auto dice = bind(distribution,generator);
    int ret = dice();

    return ret;
}

std::vector<int> datasheet;
void generate_data(int n)
{
    datasheet.resize(n);
	for (int i = 0; i < n; ++i)
	{
		datasheet[i] = RandomNum(10000);
	}
}

clock_t single_test(int n,int mode)
{
	std::vector<int> bar;
	bar = datasheet;
	clock_t t = clock();
	if (mode == 1)
	{
		insertion_sort(bar.begin(),bar.begin() + n + 1);
	}
	else if (mode == 2)
	{
		bubble_sort(bar.begin(),bar.begin() + n + 1);
	}
	else if (mode == 3)
	{
		shell_sort(bar.begin(),bar.begin() + n + 1);		
	}
	else if (mode == 4)
	{
		merge_sort(bar.begin(),bar.begin() + n + 1);		
	}
	else if (mode == 5)
	{
		quicksort(bar.begin(),bar.begin() + n + 1,leftiest<std::vector<int>::iterator>());		
	}
	else if (mode == 6)
	{
		quicksort(bar.begin(),bar.begin() + n + 1,randomGet<std::vector<int>::iterator>());		
	}
	else if (mode == 7)
	{
		heapsort(bar.begin(),bar.begin() + n + 1);		
	}
	else if (mode == 8)
	{		
		bucket_sort(bar.begin(),bar.begin() + n + 1,10000);		
	}
	else if (mode == 9)
	{
		optimal_bucktet_sort(bar.begin(),bar.begin() + n + 1);		
	}
	// else if (mode == 10)
	// {
	// 	radix_sort(bar.begin(),bar.begin() + n + 1,6);		
	// }
	else if (mode == 11)
	{
		std::sort(bar.begin(),bar.begin() + n + 1);
	}
	t = clock() - t;
	return t;
}

void time_test(int threold)
{
	generate_data(1000000);

    std::cout<<"II.Time perfomance of random data test.\n";
   	std::cout<<"****************************************************\n";

	std::fstream infile;
    infile.open("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/RandomData/n^2_insertion_sort.txt",std::ios::out | std::ios::trunc);

    infile.setf(std::ios::fixed,std::ios::floatfield);
    infile.precision(6);

    std::cout.setf(std::ios::fixed,std::ios::floatfield);
    std::cout.precision(6);

    clock_t delta;
    for (int i = 1; i <= threold; ++i)
    {
    	delta = single_test(i * 1000,1);
		infile<<i * 1000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
		std::cout<<"   Insertion sort: "<<i * 1000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
    }

	std::cout<<"\n";
    infile.close();

    infile.open("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/RandomData/n^2_bubble_sort.txt",std::ios::out | std::ios::trunc);
    for (int i = 1; i <= threold; ++i)
    {
    	delta = single_test(i * 500,2);
		infile<<i * 1000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
		std::cout<<"   Bubble sort: "<<i * 1000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
    }

	std::cout<<"\n";
    infile.close();

    infile.open("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/RandomData/sub_square_shell_sort.txt",std::ios::out | std::ios::trunc);
    for (int i = 1; i <= threold; ++i)
    {
    	delta = single_test(i * 10000,3);
		infile<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
		std::cout<<"   Shell sort: "<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
    }
    std::cout<<"\n";
    infile.close();

    infile.open("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/RandomData/sup_linear_merge_sort.txt",std::ios::out | std::ios::trunc);
    for (int i = 1; i <= threold; ++i)
    {
    	delta = single_test(i * 10000,4);
		infile<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
		std::cout<<"   Merge sort: "<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
    }
    std::cout<<"\n";
    infile.close();

    infile.open("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/RandomData/sup_linear_quick_sort_lefist.txt",std::ios::out | std::ios::trunc);
    for (int i = 1; i <= threold; ++i)
    {
    	delta = single_test(i * 10000,5);
		infile<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
		std::cout<<"   Quick sort(leftiest): "<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
    }
    std::cout<<"\n";
    infile.close();

    infile.open("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/RandomData/sup_linear_quick_sort_random.txt",std::ios::out | std::ios::trunc);
    for (int i = 1; i <= threold; ++i)
    {
    	delta = 0;
    	for (int j = 0; j < 10; ++j)
    	{
    		delta += single_test(i * 10000,6);
    	}
    	delta /= 10;
		infile<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
		std::cout<<"   Quick sort(random): "<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
    }
    std::cout<<"\n";
    infile.close();

    infile.open("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/RandomData/sup_linear_heap_sort.txt",std::ios::out | std::ios::trunc);
    for (int i = 1; i <= threold; ++i)
    {
    	delta = single_test(i * 10000,7);
		infile<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
		std::cout<<"   Heap sort: "<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
    }
    std::cout<<"\n";
    infile.close();

    infile.open("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/RandomData/linear_bucket_sort.txt",std::ios::out | std::ios::trunc);
    for (int i = 1; i <= threold; ++i)
    {
    	delta = single_test(i * 10000,8);
		infile<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
		std::cout<<"   Bucket sort: "<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
    }
    std::cout<<"\n";
    infile.close();

    infile.open("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/RandomData/linear_bucket_optimal_sort.txt",std::ios::out | std::ios::trunc);
    for (int i = 1; i <= threold; ++i)
    {
    	delta = single_test(i * 10000,9);
		infile<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
		std::cout<<"   Bucket optimal(space) sort: "<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
    }
    std::cout<<"\n";
    infile.close();

    infile.open("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/RandomData/linear_radix_sort.txt",std::ios::out | std::ios::trunc);
    for (int i = 1; i <= threold; ++i)
    {
    	// delta = single_test(i * 10000,10);
    	std::vector<int> bar(datasheet.begin(),datasheet.begin() + i * 10000 + 1);
    	clock_t minus;
    	delta = clock();
    	radix_sort(bar.begin(),bar.end(),6,minus);
    	delta = clock() - delta;
    	delta -= (minus);
    	delta /= 10;
		infile<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
		std::cout<<"   Radix sort: "<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
    }
    std::cout<<"\n";
    infile.close();

    infile.open("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/RandomData/linear_stl_sort.txt",std::ios::out | std::ios::trunc);
    for (int i = 1; i <= threold; ++i)
    {
    	delta = single_test(i * 10000,11);
		infile<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
		std::cout<<"   Stl sort: "<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
    }
    std::cout<<"\n";
    infile.close();

   	std::cout<<"III.Time perfomance of sequential data test.\n";
   	std::cout<<"****************************************************\n";
   	for (int i = 0; i < 1000000; ++i)
   	{
   		datasheet[i] = i;
   	}

 //    for (int i = 1; i <= threold; ++i)
 //    {
 //    	delta = single_test(i * 1000,1);
	// 	infile<<i * 1000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
	// 	std::cout<<"   Insertion sort: "<<i * 1000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
 //    }

	// std::cout<<"\n";
 //    infile.close();

 //    infile.open("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/SequntialData/n^2_bubble_sort.txt",std::ios::out | std::ios::trunc);
 //    for (int i = 1; i <= threold; ++i)
 //    {
 //    	delta = single_test(i * 500,2);
	// 	infile<<i * 1000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
	// 	std::cout<<"   Bubble sort: "<<i * 1000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
 //    }

	// std::cout<<"\n";
 //    infile.close();

 //    infile.open("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/SequntialData/sub_square_shell_sort.txt",std::ios::out | std::ios::trunc);
 //    for (int i = 1; i <= threold; ++i)
 //    {
 //    	delta = single_test(i * 10000,3);
	// 	infile<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
	// 	std::cout<<"   Shell sort: "<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
 //    }
 //    std::cout<<"\n";
 //    infile.close();

 //    infile.open("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/SequntialData/sup_linear_merge_sort.txt",std::ios::out | std::ios::trunc);
 //    for (int i = 1; i <= threold; ++i)
 //    {
 //    	delta = single_test(i * 10000,4);
	// 	infile<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
	// 	std::cout<<"   Merge sort: "<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
 //    }
 //    std::cout<<"\n";
 //    infile.close();

    infile.open("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/SequntialData/sup_linear_quick_sort_lefist.txt",std::ios::out | std::ios::trunc);
    for (int i = 1; i <= threold; ++i)
    {
    	delta = single_test(i * 1000,5);
		infile<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
		std::cout<<"   Quick sort(leftiest): "<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
    }
    std::cout<<"\n";
    infile.close();

    infile.open("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/SequntialData/sup_linear_quick_sort_random.txt",std::ios::out | std::ios::trunc);
    for (int i = 1; i <= threold; ++i)
    {
    	delta = 0;
    	for (int j = 0; j < 10; ++j)
    	{
    		delta += single_test(i * 10000,6);
    	}
    	delta /= 10;
		infile<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
		std::cout<<"   Quick sort(random): "<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
    }
    std::cout<<"\n";
    infile.close();

  //   infile.open("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/SequntialData/sup_linear_heap_sort.txt",std::ios::out | std::ios::trunc);
  //   for (int i = 1; i <= threold; ++i)
  //   {
  //   	delta = single_test(i * 10000,7);
		// infile<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
		// std::cout<<"   Heap sort: "<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
  //   }
  //   std::cout<<"\n";
  //   infile.close();

  //   infile.open("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/SequntialData/linear_bucket_sort.txt",std::ios::out | std::ios::trunc);
  //   for (int i = 1; i <= threold; ++i)
  //   {
  //   	delta = single_test(i * 10000,8);
		// infile<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
		// std::cout<<"   Bucket sort: "<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
  //   }
  //   std::cout<<"\n";
  //   infile.close();

  //   infile.open("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/SequntialData/linear_bucket_optimal_sort.txt",std::ios::out | std::ios::trunc);
  //   for (int i = 1; i <= threold; ++i)
  //   {
  //   	delta = single_test(i * 10000,9);
		// infile<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
		// std::cout<<"   Bucket optimal(space) sort: "<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
  //   }
  //   std::cout<<"\n";
  //   infile.close();

  //   infile.open("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/SequntialData/linear_radix_sort.txt",std::ios::out | std::ios::trunc);
  //   for (int i = 1; i <= threold; ++i)
  //   {
  //   	delta = single_test(i * 10000,10);
		// infile<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
		// std::cout<<"   Radix sort: "<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
  //   }
  //   std::cout<<"\n";
  //   infile.close();

    infile.open("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/SequntialData/linear_stl_sort.txt",std::ios::out | std::ios::trunc);
    for (int i = 1; i <= threold; ++i)
    {
    	delta = single_test(i * 10000,11);
		infile<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
		std::cout<<"   Stl sort: "<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
    }
    std::cout<<"\n";
    infile.close();

   	std::cout<<"IV.Time perfomance of reverse sequential data test.\n";
   	std::cout<<"****************************************************\n";
   	for (int i = 0; i < 1000000; ++i)
   	{
   		datasheet[i] = 1000000 - i;
   	}

 //    for (int i = 1; i <= threold; ++i)
 //    {
 //    	delta = single_test(i * 1000,1);
	// 	infile<<i * 1000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
	// 	std::cout<<"   Insertion sort: "<<i * 1000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
 //    }

	// std::cout<<"\n";
 //    infile.close();

 //    infile.open("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/ReverseSequntialData/n^2_bubble_sort.txt",std::ios::out | std::ios::trunc);
 //    for (int i = 1; i <= threold; ++i)
 //    {
 //    	delta = single_test(i * 500,2);
	// 	infile<<i * 1000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
	// 	std::cout<<"   Bubble sort: "<<i * 1000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
 //    }

	// std::cout<<"\n";
 //    infile.close();

 //    infile.open("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/ReverseSequntialData/sub_square_shell_sort.txt",std::ios::out | std::ios::trunc);
 //    for (int i = 1; i <= threold; ++i)
 //    {
 //    	delta = single_test(i * 10000,3);
	// 	infile<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
	// 	std::cout<<"   Shell sort: "<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
 //    }
 //    std::cout<<"\n";
 //    infile.close();

 //    infile.open("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/ReverseSequntialData/sup_linear_merge_sort.txt",std::ios::out | std::ios::trunc);
 //    for (int i = 1; i <= threold; ++i)
 //    {
 //    	delta = single_test(i * 10000,4);
	// 	infile<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
	// 	std::cout<<"   Merge sort: "<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
 //    }
 //    std::cout<<"\n";
 //    infile.close();

    infile.open("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/ReverseSequntialData/sup_linear_quick_sort_lefist.txt",std::ios::out | std::ios::trunc);
    for (int i = 1; i <= threold; ++i)
    {
    	delta = single_test(i * 1000,5);
		infile<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
		std::cout<<"   Quick sort(leftiest): "<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
    }
    std::cout<<"\n";
    infile.close();

    infile.open("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/ReverseSequntialData/sup_linear_quick_sort_random.txt",std::ios::out | std::ios::trunc);
    for (int i = 1; i <= threold; ++i)
    {
    	delta = 0;
    	for (int j = 0; j < 10; ++j)
    	{
    		delta += single_test(i * 10000,6);
    	}
    	delta /= 10;
		infile<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
		std::cout<<"   Quick sort(random): "<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
    }
    std::cout<<"\n";
    infile.close();

  //   infile.open("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/ReverseSequntialData/sup_linear_heap_sort.txt",std::ios::out | std::ios::trunc);
  //   for (int i = 1; i <= threold; ++i)
  //   {
  //   	delta = single_test(i * 10000,7);
		// infile<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
		// std::cout<<"   Heap sort: "<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
  //   }
  //   std::cout<<"\n";
  //   infile.close();

  //   infile.open("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/ReverseSequntialData/linear_bucket_sort.txt",std::ios::out | std::ios::trunc);
  //   for (int i = 1; i <= threold; ++i)
  //   {
  //   	delta = single_test(i * 10000,8);
		// infile<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
		// std::cout<<"   Bucket sort: "<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
  //   }
  //   std::cout<<"\n";
  //   infile.close();

  //   infile.open("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/ReverseSequntialData/linear_bucket_optimal_sort.txt",std::ios::out | std::ios::trunc);
  //   for (int i = 1; i <= threold; ++i)
  //   {
  //   	delta = single_test(i * 10000,9);
		// infile<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
		// std::cout<<"   Bucket optimal(space) sort: "<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
  //   }
  //   std::cout<<"\n";
  //   infile.close();

  //   infile.open("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/ReverseSequntialData/linear_radix_sort.txt",std::ios::out | std::ios::trunc);
  //   for (int i = 1; i <= threold; ++i)
  //   {
  //   	delta = single_test(i * 10000,10);
		// infile<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
		// std::cout<<"   Radix sort: "<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
  //   }
  //   std::cout<<"\n";
  //   infile.close();

    infile.open("/Users/luodian/Desktop/DSA/sort_sort_sort/sort_sort_sort/ReverseSequntialData/linear_stl_sort.txt",std::ios::out | std::ios::trunc);
    for (int i = 1; i <= threold; ++i)
    {
    	delta = single_test(i * 10000,11);
		infile<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
		std::cout<<"   Stl sort: "<<i * 10000<<" "<<((float) delta / (CLOCKS_PER_SEC))<<"\n";
    }
    std::cout<<"\n";
    infile.close();
}

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

template <class T>
class foo_compare
{
public:
	bool operator () (const T &node_a,const T&node_b) const
	{
		return node_a.a + node_a.b > node_b.a + node_b.b;
	}
};
void generic_test()
{
   	std::cout<<"V.Generic sorting test.\n";
   	std::cout<<"****************************************************\n";
	int int_arr[10] = {0,1,4,1,2,5,213,3214,21,14};
	float float_arr[10] = {0.1 ,2.2 ,3.2 ,4.1, 3.2, 41, 9.1, 10.123, 11.23, 12.89};
	std::vector<int> vec_arr(int_arr,int_arr + 10);
	std::deque<float> deque_arr(float_arr,float_arr + 10);

   	std::cout<<"1.int* type sort.\n";
	std::cout<<"  The array before merge sort is: \n";
	std::cout<<"  ";
   	std::for_each(int_arr,int_arr + 10,display<int>());
   	std::cout<<"\n\n";

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

   	merge_sort(deque_arr.begin(),deque_arr.end());

   	std::cout<<"  The array after merge sort is: \n";
   	std::cout<<"  ";
   	std::for_each(deque_arr.begin(),deque_arr.end(),display<float>());
   	std::cout<<"\n\n";

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
}

int main(int argc, const char * argv[]) 
{
	freopen("out.txt","w",stdout);	
	unit_test();
	// time_test(100);
	generic_test();
   	return 0;
}
