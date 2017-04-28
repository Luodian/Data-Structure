//
//  consisten_hash.hpp
//  HashSet
//
//  Created by 李博 on 27/04/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#ifndef consisten_hash_h
#define consisten_hash_h

#include "Header.hpp"
using namespace std;

class ConsistentHash
{
public:
    ConsistentHash(size_t _node_num, size_t _virtual_node_num)
    {
    	node_num = _node_num;
    	virtual_node_num = _virtual_node_num;
    	init();
    }
    ~ConsistentHash()
    {
    	server_nodes.clear();
    }
    
    void init()
    {
	    for(int i = 0; i < node_num; ++i)
	    {
	        for(int j = 0; j < virtual_node_num; ++j)
	        {
	            stringstream node_key;
	            node_key<<"SHARD-"<<i<<"-NODE-"<<j;
	            uint32_t partition = murmur3_32(node_key.str().c_str(), strlen(node_key.str().c_str()));
	            server_nodes.insert(pair<uint32_t, size_t>(partition, i));
	        }
	    }
    }

    size_t GetServerIndex(const string &string_key)
    {
    	char *key = new char [string_key.size() + 1];
    	strcpy(key,string_key.c_str());
    	uint32_t partition = murmur3_32(key, strlen(key));

	    map<uint32_t, size_t>::iterator it = server_nodes.lower_bound(partition);//沿环的顺时针找到一个大于等于key的虚拟节点

	    if(it == server_nodes.end())//未找到
	    {
	        return server_nodes.begin()->second;
	    }
	    return it->second;
    }
    
    void remove(const size_t index)
    {
    	for(int j = 0; j < virtual_node_num; ++j)
	    {
	        stringstream node_key;
	        node_key<<"SHARD-"<<index<<"-NODE-"<<j;
	        uint32_t partition = murmur3_32(node_key.str().c_str(), strlen(node_key.str().c_str()));

	        map<uint32_t,size_t>::iterator it = server_nodes.find(partition);

	        if(it != server_nodes.end())
	        {
	            server_nodes.erase(it);
	        }
	    }
    }

    void add(const size_t index)
    {
    	for(int j = 0; j < virtual_node_num; ++j)
	    {
	        stringstream node_key;
	        node_key<<"SHARD-"<<index<<"-NODE-"<<j;
	        uint32_t partition = murmur3_32(node_key.str().c_str(), strlen(node_key.str().c_str()));
	        server_nodes.insert(pair<uint32_t, size_t>(partition, index));
	    }
    }

    string getIP()
	{
		string IP;
		unsigned int seed = (unsigned int)chrono::system_clock::now().time_since_epoch().count();
	    default_random_engine generator(seed);
	    uniform_int_distribution<int> distribution(0,255);
	    
	    auto dice = bind(distribution,generator);
	    size_t a = 0, b = 0, c = 0, d = 0;
	    a = dice();
	    b = dice();
	    c = dice();
	    d = dice();

	    stringstream ss;
	    ss.clear();
	    string aa,bb,cc,dd;

	    ss<<a;
	    ss>>aa;
	    ss.clear();

	    ss<<b;
	    ss>>bb;
	    ss.clear();

	    ss<<c;
	    ss>>cc;
	    ss.clear();

	    ss<<d;
	    ss>>dd;
	    ss.clear();

	    IP = aa + '.' + bb + '.' + cc + '.' + dd;
	    return IP;
	}

	uint32_t murmur3_32(const char *key, uint32_t len, uint32_t seed = 17) 
	{
		static const uint32_t c1 = 0xcc9e2d51;
		static const uint32_t c2 = 0x1b873593;
		static const uint32_t r1 = 15;
		static const uint32_t r2 = 13;
		static const uint32_t m = 5;
		static const uint32_t n = 0xe6546b64;
	 
		uint32_t hash = seed;
	 
		const int nblocks = len / 4;
		const uint32_t *blocks = (const uint32_t *) key;
		int i;
		for (i = 0; i < nblocks; i++) 
		{
			uint32_t k = blocks[i];
			k *= c1;
			k = (k << r1) | (k >> (32 - r1));
			k *= c2;
	 
			hash ^= k;
			hash = ((hash << r2) | (hash >> (32 - r2))) * m + n;
		}
	 
		const uint8_t *tail = (const uint8_t *) (key + nblocks * 4);
		uint32_t k1 = 0;
	 
		switch (len & 3) 
		{
		case 3:
			k1 ^= tail[2] << 16;
		case 2:
			k1 ^= tail[1] << 8;
		case 1:
			k1 ^= tail[0];
	 
			k1 *= c1;
			k1 = (k1 << r1) | (k1 >> (32 - r1));
			k1 *= c2;
			hash ^= k1;
		}
	 
		hash ^= len;
		hash ^= (hash >> 16);
		hash *= 0x85ebca6b;
		hash ^= (hash >> 13);
		hash *= 0xc2b2ae35;
		hash ^= (hash >> 16);
	 
		return hash;
	}
	void set_server_name(const size_t index,const string &name)
	{
		server_info[index] = name;
	}
	string get_server_name(size_t index)
	{
		return server_info[index];
	}
	private:
		map<size_t,string> server_info;
	    map<uint32_t,size_t> server_nodes;
	    map<size_t,string> clients_info;
	    size_t node_num;
	    size_t virtual_node_num;
	};

#endif /* consisten_hash_h */
