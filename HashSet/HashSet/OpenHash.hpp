//
//  OpenHash.hpp
//  HashSet
//
//  Created by 李博 on 22/04/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#ifndef OpenHash_h
#define OpenHash_h

#include "Header.hpp"
using namespace std;


namespace OpenSet
{

	// template <class KeyType,class ValueType,class HashFunc = _string_func<KeyType>(),int Items = 1> class HashTable;

	//对字符串的默认哈希函数
	
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

	//对各种整数的哈希函数
	template <>
	class hash_func <short>
	{
	public:
		size_t operator () (const short& x) const
		{
			return static_cast<size_t>(x);
		}
	};

	template <>
	class hash_func <int>
	{
	public:
		size_t operator () (const int& x) const
		{
			return static_cast<size_t>(x);
		}
	};

	template <>
	class hash_func<long>
	{
	public:
		size_t operator () (const long& x) const
		{
			return static_cast<size_t>(x);
		}
	};

	template <>
	class hash_func<long long>
	{
	public:
		size_t operator () (const long long& x) const
		{
			return static_cast<size_t>(x);
		}
	};

	template <>
	class hash_func<size_t>
	{
	public:
		size_t operator () (const size_t& x) const
		{
			return x;
		}
	};

	template <>
	class hash_func<double>
	{
	public:
		size_t operator () (const double& x) const
		{
			return static_cast<size_t>(x);
		}
	};

	template <class KeyType,class ValueType,class HashFunc = hash_func<KeyType>,int Items = 1>
	class HashTable
	{
	public:
	    explicit HashTable(const size_t size = 3079)
	    {
	    	// if (typeid(KeyType) == typeid(string))
	    	// {
	    	// 	//default using BKDR
	    	// 	fn = str_hash_BKDR<KeyType>();
	    	// }
	    	// else if (typeid(KeyType) == typeid(short))
	    	// {
	    	// 	fn = short_hash<KeyType>();
	    	// }
	    	// else if (typeid(KeyType) == typeid(int))
	    	// {
	    	// 	fn = int_hash<KeyType>();
	    	// }
	    	// else if (typeid(KeyType) == typeid(long))
	    	// {
	    	// 	fn = long_hash<KeyType>();
	    	// }
	    	// else if (typeid(KeyType) == typeid(long long))
	    	// {
	    	// 	fn = longlong_hash<KeyType>();
	    	// }
	    	makeEmpty();
	    	currentSize = 0;
	    	crashCnt = 0;
	    	theList.resize(size);
	    }
	    ValueType contain(const KeyType &x) const
	    {
	       	const list< pair<KeyType,ValueType> > &whichList = theList[myhash(x)];
	        for (auto itr : whichList)
	        {
	        	if (itr.first == x)
	        	{
	        		return itr.second;
	        	}
	        }
	        cout<<"Not found.\n";
	        return ValueType();
	    }
	    bool contain(const KeyType &x,const ValueType &y) const
	    {
	       	const list< pair<KeyType,ValueType> > &whichList = theList[myhash(x)];
	        for (auto itr : whichList)
	        {
	        	if (itr.first == x && itr.second == y)
	        	{
	        		return 1;
	        	}
	        }
	        return 0;
	    }
	    void makeEmpty()
	    {
	        for (int i = 0; i < theList.size(); ++i)
	        {
	            theList[i].clear();
	        }
	    }
	    bool insert(const KeyType &x,const ValueType &y)
	    {
	    	pair<KeyType,ValueType> Pkv;
	    	Pkv.first = x;
	    	Pkv.second = y;
	        list< pair<KeyType,ValueType> > &whichList = theList[myhash(x)];

	        if (find(whichList.begin(),whichList.end(),Pkv) != whichList.end())
	        {
	            return 0;
	        }
	        whichList.push_back(Pkv);
	        currentSize ++;
	        if (get_load_factor() > 0.5)
	        {
	            rehash();
	        }
	        return 1;
	    }

	    bool insert(const pair<KeyType,ValueType> &x)
	    {
	        list< pair<KeyType,ValueType> > &whichList = theList[myhash(x.first)];

	        if (find(whichList.begin(),whichList.end(),x) != whichList.end())
	        {
	            return 0;
	        }
	        if (whichList.size() != 0)
	        {
	        	crashCnt ++;
	        }
	        whichList.push_back(x);
	        currentSize++;
	        if (get_load_factor() > 0.5)
	        {
	            rehash();
	        }
	        return 1;
	    }
        
	    bool remove(const KeyType &x,const ValueType &y = ValueType())
	    {
	    	pair<KeyType,ValueType> Pkv;
	    	Pkv.first = x;
	    	Pkv.second = y;
	        list < pair<KeyType,ValueType> > &whichList = theList[ myhash(x) ];

	        typename list < pair<KeyType,ValueType> > :: iterator itr;
	        for (itr = whichList.begin(); itr != whichList.end(); ++itr)
	        {
	        	if (itr->first == x)
	        	{
	        		break;
	        	}
	        }
	        if (itr == whichList.end())
	        {
	            return 0;
	        }
	        whichList.erase(itr);
	        --currentSize;
	        return 1;
	    }

        double get_load_factor()
        {
            return (double)currentSize / (double)theList.size();
        }

	    size_t getSize() const
	    {
	    	return theList.size();
	    }
	    int getCrashCnt() const
	    {
	    	return crashCnt;
	    }
	    
	private:
		HashFunc defalut_func;
	    vector<list< pair<KeyType,ValueType> > > theList;

	    int currentSize;
	    int crashCnt;
	    const size_t prime_list[22] = {
            3079,       6151,           12289,      24593,
            49157,      98317,          196613,     393241,     786443,
            1572869,    3145739,        6291469,    12582917,   25165842,
            50331553,   100663319,      201326611,  402653189,  805306457,
            1610612741, 3221225473ul,   4294967291ul
        };

        size_t nextPrime()
        {   
            if (theList.size() == 4294967291ul)
            {
                cout<<"Reach to max table size\n";
                exit(0);
                return 0;
            }
            else
            {
                for (int i = 0; i < 22; ++i)
                {
                    if (prime_list[i] > theList.size())
                    {
                        return prime_list[i];
                    }
                }
            }
            return 0;
        }

	    void rehash()
	    {
	    	vector< list< pair<KeyType,ValueType> > > oldLists = theList;

	    	theList.resize(nextPrime());

	    	for (int i = 0; i < theList.size(); ++i)
	    	{
	    		theList[i].clear();
	    	}

	    	currentSize = 0;
	    	for (int i = 0; i < oldLists.size(); ++i)
	    	{
	    		typename list< pair<KeyType,ValueType> >::iterator itr = oldLists[i].begin();
	    		while(itr != oldLists[i].end())
	    		{
	    			insert(*itr++);
	    		}
	    	}
	    }

        size_t myhash(const KeyType &x) const
        {
        	size_t hash_pos;
        	hash_pos = defalut_func(x);
        	return hash_pos % (theList.size());
        }
	};

}
#endif /* OpenHash_h */
