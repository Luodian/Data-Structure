//
//  Trie.hpp
//
//  Created by 李博 on 11/03/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#ifndef Trie_hpp
#define Trie_hpp

#include "Header.hpp"

template<int sigma_size,class K,class V>
class Trie
{
private:
    struct TrieNode
    {
        int count;
        bool existed;
        V value;
        TrieNode *child[sigma_size];
        TrieNode()
        {
            count = 0;
            existed = 0;
            value = V();
            for (int i = 0; i < sigma_size; ++i)
            {
                child[i] = nullptr;
            }
        }
    };
    size_t node_count;
    std::map<char,int> index_map;
    TrieNode *head;
    void insert(TrieNode * &head,const K &key,const V &value)
    {
        TrieNode *p = head;
        int id;
        for (int i = 0; i < key.size(); ++i)
        {
            id = index_map[key[i]];
            if (p->child[id] == nullptr)
            {
                p->child[id] = new TrieNode;
                node_count ++;
            }
            p = p->child[id];
            p->count ++;
        }
        p->value = value;
        p->existed = 1;
    }
    bool isfreeNode(TrieNode *p)
    {
        for (int i = 0; i < sigma_size; ++i)
        {
            if (p->child[i] != nullptr)
            {
                return false;
            }
        }
        return true;
    }
    bool isleaf(TrieNode *p)
    {
        return p->value != V();
    }
    bool remove(TrieNode *p,const K &key,const V &value,int idx,int len)
    {
        if (p)
        {
            if (idx == len)
            {
                if (p->value != V())
                {
                    p->value = V();
                    if (isfreeNode(p))
                    {
                        return true;
                    }
                    return false;
                }
            }
            else
            {
                int k = index_map[key[idx]];
                if (remove(p->child[k],key,value,idx + 1,len))
                {
                    delete p->child[k];
                    p->child[k] = nullptr;
                    return (!isleaf(p) && isfreeNode(p));
                }
            }
        }
        return false;
    }
    bool empty(TrieNode * &head)
    {
        for (int i = 0; i < sigma_size; ++i)
        {
            if (head->child[i] == nullptr)
            {
                return 1;
            }
        }
        return 0;
    }
    V search(TrieNode * &head,const std::string &key)
    {
        TrieNode *p = head;
        int id;
        for (int i = 0; i < key.size(); ++i)
        {
            id = index_map[key[i]];
            p = p->child[id];
            if (p == nullptr)
            {
                return V();
            }
        }
        return p->value;
    }
    void makeEmpty(TrieNode * &t)
    {
        for (int i = 0; i < sigma_size; ++i)
        {
            if (t->child[i] != nullptr)
            {
                makeEmpty(t->child[i]);
            }
        }
        delete t;
    }
    void init(TrieNode * &p)
    {
        p = new TrieNode;
    }   
public:
    Trie()
    {
        init(head);
        index_map.clear();
        for (int i = 0; i < 26; ++i)
        {
            index_map[i + 'a'] = i;
            index_map[i + 'A'] = i + 26;
        }
        node_count = 0;
    }
    ~Trie()
    {
        makeEmpty(head);
    }
    void insert(const K &key,const V &value)
    {
        insert(head,key,value);
    }
    V search(const K &key)
    {
        return search(head,key);
    }
    bool empty()
    {
        return empty(head);
    }
    void remove(const K &key,const V &value)
    {
        if (search(key) != value)
        {
            throw "key and value can not match.\n";
        }
        else
        {
            remove(head,key,value,0,key.size());
        }
    }
    size_t space_size()
    {
        return node_count * (4 + 1 + 4 + 52 * 8) * 8;
    }
};
#endif /* Trie_hpp */
