//
//  ProbHash.hpp
//  HashSet
//
//  Created by 李博 on 22/04/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#ifndef ProbHash_h
#define ProbHash_h

#include "Header.hpp"
using namespace std;

namespace ProbeSet
{
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
        explicit HashTable(const size_t size = 7)
        {
            makeEmpty();
            currentSize = 0;
            crashCnt = 0;
            HashArray.resize(size);
        }
        ~HashTable()
        {
            //
        }
        ValueType contain(const KeyType &x)
        {
            bool found = isActive(findPos(x));
            if (found == 1)
            {
                return HashArray[findPos(x)].value;
            }
            else
            {
                cout<<"Not Found\n";
                return 0;
            }
        }
        void makeEmpty()
        {
            for (int i = 0; i < HashArray.size() ; ++i)
            {
                HashArray[i].info = EMPTY;
            }
        }
        bool insert(const KeyType &x,const ValueType &v)
        {
            size_t currentPos = findPos(x);
            if (isActive(currentPos))
            {
                return 0;
            }
            HashArray[currentPos] = HashEntry(x,v,ACTIVED);
            currentSize ++;
            if (get_load_factor() > 0.5)
            {
                rehash();
            }
            return true;
        }
        bool remove(const KeyType &x)
        {
            size_t currentPos = findPos(x);
            if (!isActive(currentPos))
            {
                return false;
            }
            HashArray[currentPos].info = DELETED;
            HashArray[currentPos].element.clear();
            currentSize --;
            return true;
        }

        size_t getSize() const
        {
            return HashArray.size();
        }

        double get_load_factor()
        {
            return (double)currentSize / (double)HashArray.size();
        }
        int getCrashCnt()
        {
            return crashCnt;
        }
    private:
        HashFunc fn;
        enum EntryType{ACTIVED,EMPTY,DELETED};
        struct HashEntry
        {
            KeyType element;
            ValueType value;
            EntryType info;
            HashEntry(const KeyType &e = KeyType(), const ValueType &v = ValueType(),EntryType i = EMPTY)
            {
                element = e;
                value = v;
                info = i;
            }
        };
        int crashCnt;

        vector<HashEntry> HashArray;
        size_t currentSize;
        const size_t prime_list[22] = {
            3079,       6151,           12289,      24593,
            49157,      98317,          196613,     393241,     786443,
            1572869,    3145739,        6291469,    12582917,   25165842,
            50331553,   100663319,      201326611,  402653189,  805306457,
            1610612741, 3221225473ul,   4294967291ul
        };

        size_t nextPrime()
        {   
            if (HashArray.size() == 4294967291)
            {
                cout<<"Reach to max table size\n";
                exit(0);
                return 0;
            }
            else
            {
                for (int i = 0; i < 22; ++i)
                {
                    if (prime_list[i] > HashArray.size())
                    {
                        return prime_list[i];
                    }
                }
            }
            return 0;
        }
        void rehash()
        {
            vector<HashEntry> oldArray = HashArray;
            HashArray.resize(nextPrime());
            for (int j = 0; j < HashArray.size(); ++j)
            {
                HashArray[j].info = EMPTY;
            }

            currentSize = 0;
            for (int i = 0; i < oldArray.size(); ++i)
            {
                if (oldArray[i].info == ACTIVED)
                {
                    insert(oldArray[i].element,oldArray[i].value);
                }
            }
        }
        bool isActive(size_t currentPos) const
        {
            return HashArray[currentPos].info == ACTIVED;
        }

        size_t findPos(const KeyType &x)
        {
            size_t offset = 1;
            size_t currentPos = myhash(x);
            while (HashArray[currentPos].info != EMPTY && HashArray[currentPos].element != x)
            {
                crashCnt ++;
                currentPos += offset;
                offset += 2;
                if (currentPos >= HashArray.size())
                {
                    currentPos -= HashArray.size();
                }
            }
            return currentPos;
        }

        size_t myhash(const KeyType &x) const
        {
            size_t hash_pos = fn(x);
            return hash_pos % (HashArray.size());
        }
    };
}

#endif /* ProbHash_h */
