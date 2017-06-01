//
//  main.cpp
//  Patricia
//
//  Created by 李博 on 24/05/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#include "Header.hpp"
#include "patricia.hpp"
#include "Trie.hpp"


std::vector<std::string> string_buffer;
std::string ret;

void read_txt()
{
    std::fstream in;
    in.open("in.txt",std::ios::in);
    while(!in.eof())
    {
       in>>ret;
       for (int i = 0; i < ret.size(); ++i)
       {
            if (!isalpha(ret[i]))
            {
                ret.erase(i);
            }
       }
       if (ret.size() == 0)
       {
            continue;
       }
       // std::cout<<ret<<"\n";
       string_buffer.push_back(ret);
    }
}

clock_t patricia_insert()
{
    Radix::patricia_tree<std::string,int> a; 

    clock_t delta_t;
    delta_t = clock();
    for (int i = 0; i < string_buffer.size(); ++i)
    {
        a.insert(string_buffer[i],i + 1);
    }
    delta_t = clock() - delta_t;
    return delta_t;
}

clock_t patricia_find()
{
    Radix::patricia_tree<std::string,int> a;
    clock_t delta_t;
    std::string find1 = "Island";
    std::string find2 = "Kilimanjaro";
    for (int i = 0; i < string_buffer.size(); ++i)
    {
        a.insert(string_buffer[i],i+1);
    }
    delta_t = clock();
    a.find(find1);
    a.find(find2);
    delta_t = clock() - delta_t;
    return delta_t;
}

clock_t patricia_delete()
{
    Radix::patricia_tree<std::string,int> a;
    clock_t delta_t;
    std::string find1 = "Island";
    std::string find2 = "Kilimanjaro";
    for (int i = 0; i < string_buffer.size(); ++i)
    {
        a.insert(string_buffer[i],i+1);
    }
    delta_t = clock();
    a.remove(find1,8814);
    a.remove(find2,1);
    delta_t = clock() - delta_t;
    return delta_t;
}

clock_t trie_insert()
{
    Trie<52,std::string,int> a; 

    clock_t delta_t;
    delta_t = clock();
    for (int i = 0; i < string_buffer.size(); ++i)
    {
        a.insert(string_buffer[i],i + 1);
    }
    delta_t = clock() - delta_t;
    return delta_t;
}

clock_t trie_find()
{
    Trie<52,std::string,int> a; 

    clock_t delta_t;

    for (int i = 0; i < string_buffer.size(); ++i)
    {
        a.insert(string_buffer[i],i + 1);
    }
    std::string find1 = "Island";
    std::string find2 = "Kilimanjaro";
    delta_t = clock();
    a.search(find1);
    a.search(find2);
    delta_t = clock() - delta_t;
    return delta_t;
}

clock_t trie_delete()
{
    Trie<52,std::string,int> a; 

    clock_t delta_t;

    for (int i = 0; i < string_buffer.size(); ++i)
    {
        a.insert(string_buffer[i],i + 1);
    }

    std::string find1 = "Island";
    std::string find2 = "Kilimanjaro";

    delta_t = clock();
    a.remove(find1,8814);
    a.remove(find2,8762);
    delta_t = clock() - delta_t;

    return delta_t;
}

size_t trie_space()
{
    Trie<52,std::string,int> a;
    for (int i = 0; i < string_buffer.size(); ++i)
    {
        a.insert(string_buffer[i],i+1);
    }
    return a.space_size();
}

size_t patricia_space()
{
    Radix::patricia_tree<std::string,int> a;
    for (int i = 0; i < string_buffer.size(); ++i)
    {
        a.insert(string_buffer[i],i+1);
    }
    return a.space_size();
}


void f()
{
    read_txt();
    Trie<52,std::string,int> a; 

    for (int i = 0; i < string_buffer.size(); ++i)
    {
        a.insert(string_buffer[i],i + 1);
    }
    std::cout<<string_buffer[0]<<"\n";
    std::string find1 = "Island";
    std::string find2 = "Kilimanjaro";

    a.remove(find1,8814);
    std::cout<<a.search(find2);
}

void time_perfomance_test()
{
    clock_t delta_t;
    std::fstream out;
    std::fstream in;
    in.open("in.txt",std::ios::in);
    out.open("patricia_out.txt",std::ios::out | std::ios::trunc);

    out.setf(std::ios::fixed,std::ios::floatfield);
    out.precision(6);
    out.tie(nullptr);

    std::cout.setf(std::ios::fixed,std::ios::floatfield);
    std::cout.precision(6);
    std::cout.tie(nullptr);
    in.tie(nullptr);

    read_txt();

    delta_t = 0;
    for (int i = 0; i < 100; ++i)
    {
        delta_t += patricia_insert();
    }
    delta_t /= 10;
    out<<"Patricia insert: "<<((float) delta_t / (CLOCKS_PER_SEC))<<"\n";
    std::cout<<"Patricia insert: "<<((float) delta_t / (CLOCKS_PER_SEC))<<"\n";
    
    delta_t = 0;
    for (int i = 0; i < 100; ++i)
    {
        delta_t += patricia_find();
    }
    delta_t /= 10;

    out<<"Patricia find: "<<((float) delta_t / (CLOCKS_PER_SEC))<<"\n";
    std::cout<<"Patricia find: "<<((float) delta_t / (CLOCKS_PER_SEC))<<"\n";

    delta_t = 0;
    for (int i = 0; i < 100; ++i)
    {
        delta_t += patricia_delete();
    }
    delta_t /= 10;

    out<<"Patricia delete: "<<((float) delta_t / (CLOCKS_PER_SEC))<<"\n";
    std::cout<<"Patricia delete: "<<((float) delta_t / (CLOCKS_PER_SEC))<<"\n";

    out.close();
    out.open("trie_out.txt",std::ios::out | std::ios::trunc);

    delta_t = 0;
    for (int i = 0; i < 100; ++i)
    {
        delta_t += trie_insert();
    }
    delta_t /= 10;

    out<<"Trie insert: "<<((float) delta_t / (CLOCKS_PER_SEC))<<"\n";
    std::cout<<"Trie insert: "<<((float) delta_t / (CLOCKS_PER_SEC))<<"\n";

    delta_t = 0;
    for (int i = 0; i < 100; ++i)
    {
        delta_t += trie_find();
    }
    delta_t /= 10;

    out<<"Trie find: "<<((float) delta_t / (CLOCKS_PER_SEC))<<"\n";
    std::cout<<"Trie find: "<<((float) delta_t / (CLOCKS_PER_SEC))<<"\n";

    delta_t = 0;
    for (int i = 0; i < 100; ++i)
    {
        delta_t += trie_delete();
    }
    delta_t /= 10;

    out<<"Trie delete: "<<((float) delta_t / (CLOCKS_PER_SEC))<<"\n";
    std::cout<<"Trie delete: "<<((float) delta_t / (CLOCKS_PER_SEC))<<"\n";

    out<<"Patricia space: "<<patricia_space()<<" bits.\n";
    std::cout<<"Patricia space: "<<patricia_space()<<" bits.\n";

    out<<"Trie space: "<<trie_space()<<" bits.\n";
    std::cout<<"Trie space: "<<trie_space()<<" bits.\n";
    
}

void simple_perfomance_test()
{
    // Radix::patricia_tree<std::string, int> test;
    // test.insert("aa",1);
    // test.insert("ff",2);
    // test.insert("aaaa",3);
    // // test.insert("aaaa",5);
    // test.insert("aaa",4);
    // test.insert("abc",6);
    // test.insert("abd",7);
    // test.insert("dafda",19);
    // // test.insert("81",21);
    // // test.remove("81",232);
    // test.insert("afada",232);
    // test.remove("afada",232);
    // test.find("afada");
    Trie<52,std::string,int> a;
    a.insert("aa",2);
    std::cout<<a.search("aa")<<"\n";
    a.remove("aa",2);
    a.insert("fafa",3);
    std::cout<<a.search("fafa")<<"\n";
    a.remove("fafa",3);
    std::cout<<a.search("fafa")<<"\n";
    a.insert("FA",1);
    // test.remove("abc",31);
    // test.find("81");
    // test.f();
}

void prefix_test()
{
    Radix::patricia_tree<std::string,int> a;
    a.insert("toilet",1);
    a.insert("tea",2);
    a.insert("ted",3);
    a.insert("tee",4);
    a.insert("teeth",5);
    a.insert("bbbbb",6);
    a.insert("bbba",7);
    a.insert("bbb",8);
    a.insert("bbbb",9);
    a.insert("bb",10);
    std::vector<std::string> ret = a.prefix_search("te");
    for (int i = 0; i < ret.size(); ++i)
    {
        std::cout<<ret[i]<<std::endl;
    }
}
int main(int argc, const char * argv[])
{
    // freopen("out.txt","w",stdout); 
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    prefix_test();
    // time_perfomance_test();
    // f();
    // simple_perfomance_test();
    return 0;
}
