//
//  main.cpp
//  SkipList
//
//  Created by 李博 on 04/03/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <ctime>
#include <list>
#include <iomanip>
#include <random>

using namespace std;
constexpr static int INF = 0x3f3f3f3f;
constexpr static int maxlevel = 16;

template <typename object>
class skipList
{
private:
    struct skipNode
    {
        object data;
        skipNode *next[maxlevel];
        skipNode(const object &d = object())
        {
            data = d;
            for (int i = 0; i < maxlevel; ++i)
            {
                next[i] = nullptr;
            }
        }
    };
    int topLevel = 0;
    int size = 0;
    skipNode *header;
    void init()
    {
        topLevel = 0;
        size = 0;
        header = new skipNode(INF);
        skipNode* first = new skipNode(INF);
        //需要用max_limits
        for (int i = 0; i < maxlevel; ++i)
        {
            header->next[i] = first;
        }
    }
    // void clear()
    // {
    // 	while(!*(this).empty())
    // 	{
    // 		pop_back();
    // 	}
    // }
    int randLevel()
    {
        unsigned int seed = (unsigned int)chrono::system_clock::now().time_since_epoch().count();
        default_random_engine generator(seed);
        uniform_int_distribution<int> distribution(0,10);
        auto dice = bind(distribution,generator);
        int level = 0;
        for (int i = 0; i < maxlevel; ++i)
        {
            int num = dice();
            if (num < 5)
            {
                level ++;
            }
        }
        return level;
    }
    bool empty(const skipNode *header)
    {
        if(header->next[0] == nullptr)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    bool erase(skipNode *header,const int &key)
    {
        skipNode* update[maxlevel];
        skipNode* p = nullptr;
        skipNode* q = nullptr;
        p = header;
        for (int i = maxlevel - 1; i >= 0; --i)
        {
            update[i] = header;
        }
        for (int i = topLevel - 1; i >= 0; --i)
        {
            while((q=p->next[i]) && (p->next[i]->data < key))
            {
                p = p->next[i];
            }
            update[i] = p;
        }
        if (q != nullptr && q->data == key)
        {
            for (int i = 0; i < topLevel; ++i)
            {
                if (update[i]->next[i] == q)
                {
                    update[i]->next[i] = q->next[i];
                }
            }
            delete q;
            for (int i = topLevel - 1;i >= 0; --i)
            {
                if (header->next[i] == nullptr)
                {
                    topLevel --;
                }
            }
            return 1;
        }
        else
        {
            return 0;
        }
    }
    bool insert(const skipNode* head, const int &key,bool isDebug = 0,int l = 0)
    {
        int level;
        if (isDebug == 1)
        {
            level = l;
        }
        else
        {
            level = randLevel();
        }
        // cout<<level<<"\n";
        //node is wait for insertion
        skipNode* node = new skipNode;
        node->data = key;
        skipNode* Update[maxlevel];
        skipNode* p = header;
        skipNode* last = header;
        for (int i = 0; i < maxlevel; ++i)
        {
            Update[i] = header;
        }
        for (int i = topLevel - 1;i >= 0; --i)
        {
            while(p->next[i] != nullptr && key > p->next[i]->data)
            {
                p = p->next[i];
            }
            Update[i] = p;
        }
        last = p->next[0];
        if (level > topLevel)
        {
            for (int i = topLevel; i < level; ++i)
            {
                Update[i] = header;
            }
            topLevel = level;
        }
        if (last != nullptr && last->data != INF)
        {
            for (int i = 0; i < level; ++i)
            {
                node->next[i] = Update[i]->next[i];
                Update[i]->next[i] = node;
            }
        }
        else
        {
            for(int i = 0; i < level; ++i)
            {
                Update[i]->next[i] = node;
                node->next[i] = nullptr;
            }
        }
        return 1;
    }
    void printList(skipNode *head)
    {
        if (empty(header) == 1)
        {
            cout<<"null\n";
            return;
        }
        skipNode* p = head->next[0];
        vector<object> verify;
        verify.clear();
        while(p != nullptr)
        {
            verify.push_back(p->data);
            p = p->next[0];
        }
        for (int i = topLevel - 1; i >= 0; --i)
        {
            p = head->next[i];
            cout<<"level "<<i<<" head ";
            for (int j = 0; j < size; ++j)
            {
                if (p != nullptr && p->data == verify[j])
                {
                    cout<<p->data<<" ";
                    p = p->next[i];
                }
                else if (p != nullptr && p->data != verify[j])
                {
                    cout<<"- ";
                }
                else if (p == nullptr)
                {
                   cout<<"- ";
                }
            }
            cout<<"-> NULL.\n";
        }
    }
    bool find(skipNode *head,const object &key)
    {
        skipNode *p = nullptr;
        skipNode *q = nullptr;
        p = head;
        for (int i = topLevel - 1; i >= 0; --i)
        {
            while((q = p->next[i]) && key  >= q->next[i]->data)
            {
                if (q->data == key)
                {
                    return 1;
                }
                p = q;
            }
        }
        return 0;
    }
public:
    skipList()
    {
        init();
    }
    skipList(const skipList &rhs)
    {
        init();
        *(this) = rhs;
    }
    ~skipList()
    {
        // clear();
        delete header;
    }
    bool find(const object &key)
    {
        return find(header,key);
    }
    bool insert(const object& key,bool debug = 0, int level = 0)
    {
        if (insert(header,key,debug,level) == 1)
        {
            size ++;
            return 1;
        }
        else
        {
            return 0;
        }
    }
    bool empty()
    {
        return empty(header);
    }
    void erase(const int &key)
    {
        if (erase(header,key) == 1)
        {
            cout<<"Erase "<<key<<"\n";
            size --;
        }
        else
        {
            cout<<"Can't find "<<key<<"\n";
        }
    }
    void debug()
    {
        printList(header);
    }
};

int GenerateData()
{
    unsigned int seed = (unsigned int)chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(1,100000);
    auto dice = bind(distribution,generator);
    int ret = dice();
    return ret;
}

clock_t SKtest(int n)
{
    skipList<int> test;
    int temp;
    for (int i = 0; i < n; ++i)
    {
        temp = GenerateData();
        test.insert(temp);
    }
    clock_t t = clock();
    test.find(temp);
    t = clock() - t;
    return t;
}

clock_t ListTest(int n)
{
    list<int> test;
    int temp;
    for (int i = 0; i < n; ++i)
    {
        temp = GenerateData();
        test.push_back(temp);
    }
    temp = GenerateData();
    list<int> :: iterator itr;
    clock_t t = clock();
    for (itr = test.begin(); itr != test.end(); ++itr)
    {
        if (*(itr) == temp)
        {
            t = clock() - t;
            return t;
        }
    }
    t = clock() - t;
    return t;
}

void TimePerfo()
{
    fstream writeFile;
    writeFile.open("/Users/luodian/Desktop/#1/SkipList/SkipList/SkipList.txt",ios::out | ios::trunc);
    cout.setf(ios::fixed,ios::floatfield);
    cout.precision(6);
    writeFile.setf(ios::fixed,ios::floatfield);
    writeFile.precision(6);
    cout<<"\nTime perfomance of skip list in search\n";
    cout<<"*******************************************\n\n";
    for (int i = 1; i <= 100; ++i)
    {
        clock_t t = SKtest(i * 1000);
        writeFile<<i * 1000<<" "<<((float) t / (CLOCKS_PER_SEC))<<"\n";
        cout<<i * 1000<<" "<<((float) t / (CLOCKS_PER_SEC))<<"\n";
    }
    fstream writeList;
    writeList.open("/Users/luodian/Desktop/#1/SkipList/SkipList/List.txt",ios::out | ios::trunc);
    cout<<"\nTime perfomance of list in search\n";
    cout<<"*******************************************\n\n";
    for (int i = 1; i <= 100; ++i)
    {
        clock_t t = ListTest(i * 1000);
        writeList<<i * 1000<<" "<<((float) t / (CLOCKS_PER_SEC))<<"\n";
        cout<<i * 1000<<" "<<((float) t / (CLOCKS_PER_SEC))<<"\n";
    }
}

void SimpleTest()
{
    skipList<int> test;
    for (int i = 1; i <= 9; ++i)
    {
        test.insert(i);
    }
    test.debug();
}

int main()
{
    //Accelerate IO Stream
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    SimpleTest();
    TimePerfo();
    return 0;
}

