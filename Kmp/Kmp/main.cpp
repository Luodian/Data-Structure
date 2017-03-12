//
//  main.cpp
//  Kmp
//
//  Created by 李博 on 05/03/2017.
//  Copyright © 2017 李博. All rights reserved.
//
#include "Kmp.hpp"
#include "Trie.hpp"
#include "BoyerMoore.hpp"
#include "BFsuffix.hpp"

void TestPerfo(std::string &Template,std::string &Pattern,bool IOallowed = 0)
{
	// inital IO stream
    Trie<60> bigTree;
    if (IOallowed == 1)
    { 
        std::fstream readFile;
        readFile.open("/Users/luodian/Desktop/DSA/Kmp/Kmp/in.txt",std::ios::in);
        Pattern = "Luodian";
        std::string cat_buffer;
        while(!readFile.eof())
        {
            cat_buffer.clear();
            readFile>>cat_buffer;
            std::string TrieBuffer = cat_buffer;
            for (int i = 0; i < TrieBuffer.size(); ++i)
            {
                if (!isalpha(TrieBuffer[i]))
                {
                    TrieBuffer.erase(i,1);
                }
            }
            bigTree.insert(TrieBuffer);
            cat_buffer += " ";
            Template += cat_buffer;
        }
    }
    //set IO stream format
    std::cout.setf(std::ios::fixed,std::ios::floatfield);
    std::cout.precision(6);

    //simple interface
    std::cout<<"\n\n**********************************************\n";
    std::cout<<"           Length of Template : "<<Template.size()<<"\n";
    std::cout<<"           Length of Pattern : "<<Pattern.size()<<"\n";
    std::cout<<"           Pattern :";
    for (int i = 0; i < 10; ++i)
    {
        std::cout<<Pattern[i];
    }
    std::cout<<"\n";
    std::cout<<"**********************************************\n\n";
    std::cout<<"Validating Test: \n";

    //validation test
    std::cout<<"KMP's result         |  ";
    clock_t kmp_t = clock();
    int kmp_finded = 0;
    for (int i = 1; i <= 1000; ++i)
    {
        kmp_finded = kmp(Template, Pattern);
    }
    kmp_t = clock() - kmp_t;

    if (kmp_finded)
    {
        std::cout<<"Found in "<<kmp_finded<<"    |  Yes found it\n";
    }
    else
    {
        std::cout<<"  |   Sorry can't found\n";
    }

    std::cout<<"BoyerMoore's result  |  ";
    clock_t bm_t = clock();
    int bm_found = 0;
    for (int i = 1;i <= 1000; ++i)
    {
        bm_found = BMsearch(Template,Pattern);
    }
    bm_t = clock() - bm_t;

    if (bm_found)
    {
        std::cout<<"Found in "<<bm_found<<"    |  Yes found it\n";
    }
    else
    {
        std::cout<<"  |   Sorry can't found\n";
    }

    clock_t trie_t;
    if (IOallowed == 1)
    {
        std::cout<<"Trie's result        |  ";

        int trie_found = 0;
        trie_t = clock();
        for (int i = 1; i <= 1000; ++i) 
            trie_found = bigTree.search(Pattern);
        trie_t = clock() - trie_t;
        if (trie_found)
        {
            std::cout<<"Just found it     |  Yes found it\n";
        }
        else
        {
            std::cout<<"  |   Sorry can't found\n";
        }
    }

    std::cout<<"BF suffix's result   |  ";
    clock_t bf_t = clock();
    int bf_found = 0;
    for(int i = 1;i <= 1000; ++i) 
        bf_found = Brutesuffix(Pattern,Template);
    bf_t = clock() - bf_t;

    if (bf_found)
    {
        std::cout<<"Found in "<<bf_found<<"    |  Yes found it\n";
    }
    else
    {
        std::cout<<"  |   Sorry can't found\n";
    }

    std::cout<<"BF prefix's result   |  ";
    clock_t bfp_t = clock();
    int bfp_found = 0;
    for (int i = 1;i <= 1000; ++i) 
        bfp_found = BrutePrefix(Pattern,Template);
    bfp_t = clock() - bfp_t;
    if (bfp_found)
    {
        std::cout<<"Found in "<<bfp_found<<"    |  Yes found it\n";
    }
    else
    {
        std::cout<<"  |   Sorry can't found\n";
    }

    std::cout<<"STL find()'s result  |  ";
    clock_t strstr_t = clock();
    int strstr_found = 0;
    for (int i = 1;i <= 1000; ++i)    
        strstr_found = Template.find(Pattern);
    strstr_t = clock() - strstr_t;

    if (strstr_found)
    {
        std::cout<<"Found in "<<strstr_found<<"    |  Yes found it\n";
    }
    else
    {
        std::cout<<"  |   Sorry can't found\n";
    }

    //time perfomance
    std::cout<<"\nTime Perfomance Test\n";
    std::cout<<"KMP's time         |  "<<float(kmp_t) / 1000<<"  clocks.\n";
    std::cout<<"BoyerMoore's time  |  "<<float(bm_t) / 1000<<"  clocks.\n";
    if (IOallowed == 1)
    {
        std::cout<<"Trie's time        |  "<<float(trie_t) / 1000<<"  clocks.\n";
    }
    std::cout<<"BF suffix's time   |  "<<float(bf_t) / 1000<<"  clocks.\n";
    std::cout<<"BF prefix's time   |  "<<float(bfp_t) / 1000<<"  clocks.\n";
    std::cout<<"STL function's time|  "<<float(strstr_t) / 1000<<"  clocks.\n";

}





int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string Pattern,Template;
	TestPerfo(Template,Pattern,1);
    Template = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAFDLDAJFDLAJLGJDLAJLDAJLKGJELA;JEIOQUREQOJGLJDLFA;JFDL;AJFDA;LJGD;ALJFDA;JFDAL;JFDAL;FDJA;LFDJAKL;FDAJ;DAJFDL;AJFKDL;AJL;DAJFD;AJFKDL;AJGHDKLAJFDAL;JFDJKLDFJKFAJL;FAJKFDKJIFRIIJRFIJFIJFIJFFIFRJIRFJIFRJIFIJOFIJORFIJRFKLFDJKDFLKJFAKL;FLJK;AJDFNAJJFDJIOQJIOEIOTRQIUUITPQOPIURJRGJIOGOIJFIOJIJFVI.FIIJIFIJFJKLFJAKLFJDAKLFJDLA;JGL;AHFEQJGJQKFEQIOUTRQTJ[Q;GFJDALK;GA;LKFJDAH;QJGLFAFJEIO;QJIOEQUREQPTQPOHERQQCNPRCRUPENVQRNQVJJF;FJOIQ;FQJ;FQ;JFQJORE[QTU[QREJOQT;FJAL;FGH;FAJFKD;LAJGL;AJGL;AJFDL;AGLK;AHGLK;AJFDLAK;JFHOQPGHQOPRUEIOQ[RUEO[QUTQ[RUE[QUTQ[UGHQ;FJEQ;JQLG;QH;EQF[QJG[OUQOTUEOQI[TUEIQWYTQOPHEQKFHSZ,NC;KQGHGAL;SJFLKAJGHFA;HGONOINVEOQINVPUREQNVUINVEPOQUNVREIOPQUENVOQRIPNVUEPQNVRQW VEWQNVOREUQWVONREWOVQUNQRUPUEQVNREQO EQWNV[RPEQIR[QVNEQR[PVNRQOV REWQIOFNLA;FJKLA;NVLA;HGIAOERYGQVUPNERQVQEPEUQVREUQCMUERQPFJLAS;FNJ;QHFUOPUFOPEQRU[QUTDAOFJAJLKFJDAL;GOCFEQ[ORIEUTOPQTRWCIJFLAD;KJF;GHOQFOQ[RJEQIOPGHRA;FLJDA;FJSKLA;JFDLKA;JFLD;ASDFAJFDA;FJDA;LJFD;AJFDL;ASJFDLSA;JFDKSLA;JFDKL;SADFKSA;FJDSLAK;FJLKAS;HGL;AFJKDSA;[][][][][][][][][[][][][][][[][[[[]ABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBIIIIIIIIOOOOKKKLLJJJUUHHIIOOOPPPEIIIIREWPPRWOPREOWPREOPWROEPWROEPWOREEPPPPRWPREWOREWOREWR[[[[[[OEPWOREPWOEPWTIEWTEIOPIPWITR[WITR[WTIR[WTIR[WTIRWTRWTRWTRWTRWTNRKWGJRW&&**(())*";
    Pattern = "&&**(())*";

    TestPerfo(Template,Pattern);

    Template.clear();
    for (int i = 0; i < 100000; ++i)
    {
        Template.push_back('A');
    }
    Template.push_back('B');
    Pattern.clear();
    for (int i = 0; i < 1000; ++i)
    {
        Pattern.push_back('A');
    }
    Pattern.push_back('B');
    TestPerfo(Template,Pattern);


}
