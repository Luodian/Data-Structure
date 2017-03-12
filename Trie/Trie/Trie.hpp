//
//  Trie.hpp
//
//  Created by 李博 on 11/03/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#ifndef Trie_hpp
#define Trie_hpp

#include <iostream>
#include <string>
#include <vector>
template<int sigma_size>
class Trie
{
private:
    struct TrieNode
    {
        int count;
        bool existed;
        TrieNode *child[sigma_size];
        TrieNode()
        {
            count = 0;
            existed = 0;
            for (int i = 0; i < sigma_size; ++i)
            {
                child[i] = nullptr;
            }
        }
    };
    TrieNode *head;
    void insert(TrieNode * &head,const std::string &key)
    {
        TrieNode *p = head;
        int id;
        for (int i = 0; i < key.size(); ++i)
        {
            id = key[i] - 'a';
            if (p->child[id] == nullptr)
            {
                p->child[id] = new TrieNode;
            }
            p = p->child[id];
            p->count ++;
        }
        p->existed = 1;
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
    int search(TrieNode * &head,const std::string &key)
    {
        TrieNode *p = head;
        int id;
        for (int i = 0; i < key.size(); ++i)
        {
            id = key[i] - 'a';
            p = p->child[id];
            if (p == nullptr)
            {
                return 0;
            }
        }
        return p->count;
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
    }
    ~Trie()
    {
        makeEmpty(head);
    }
    void insert(const std::string &key)
    {
        insert(head,key);
    }
    int search(const std::string &key)
    {
        return search(head,key);
    }
    bool empty()
    {
        return empty(head);
    }
};
#endif /* Trie_hpp */
