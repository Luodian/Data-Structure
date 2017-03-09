#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <stack>
#include <cmath>
#include <list>
#include "List.cpp"

using namespace std;


struct Term
{
    int Exp;
    double Coef;
    bool operator < (const Term &rhs) const
    {
        return Exp > rhs.Exp;
    }
    Term(double a = 0,int b = 0)
    {
        Exp = b;
        Coef = a;
    }
};

string StringToLower(string &name)
{
    for (int i = 0; i < name.size(); ++i)
    {
        if (isupper(name[i]))
        {
            name[i] = tolower(name[i]);
        }
    }
    return name;
}

int ExecuteString(const string &temp,int index,bool forward)
{
    int accumu = 0;
    stack<int> Contain;
    while (!Contain.empty())
    {
        Contain.pop();
    }
    if (forward == 1)
    {
        for (int i = index; i < temp.size() && (isdigit(temp[i])); ++i)
        {
            accumu += temp[i] - '0';
            accumu *= 10;
        }
    }
    else
    {
        for (int i = index; i >= 0 && (isdigit(temp[i])); -- i)
        {
            Contain.push(temp[i] - '0');
        }
        while (!Contain.empty())
        {
            int cache = Contain.top();
            accumu += (cache);
            Contain.pop();
            accumu *= 10;
        }
    }
    return (accumu / 10);
}

// queue <Term *> freenodes;
// Node Term[2000];
// void init()
// {
//    for (int i = 0; i < 2000; ++i)
//    {
//        freenodes.push(&Term[i]);
//    }
// }

// Node* newnode()
// {
//    Node *u = freenodes.front();
//    freenodes.pop();
//    return u;
// }

// Node* deletenode(Node *u)
// {
//    freenodes.push(u);
// }

void addterm(List<Term> &a,Term &b)
{
    List<Term> :: iterator itr;
    for (itr = a.begin(); itr != a.end(); ++itr)
    {
        if ((*itr).Exp > b.Exp)
        {
            continue;
        }
        else
        {
            break;
        }
    }
    if (itr == a.end())
    {
        a.insert(itr,b);
    }
    else if ((*itr).Exp == b.Exp)
    {
        (*itr).Coef += b.Coef;
    }
    else
    {
        a.insert(itr,b);
    }
}

List<Term> PolynomialsAdd(List<Term> &a,List<Term> &b)
{
    List<Term> :: iterator at = a.begin();
    List<Term> :: iterator bt = b.begin();
    Term newTerm;
    List<Term> Sum;
    while (at != a.end() && bt != b.end())
    {
        if ((*at).Exp == (*bt).Exp)
        {
            newTerm.Coef = (*at).Coef + (*bt).Coef;
            newTerm.Exp = (*at).Exp;
            Sum.push_back(newTerm);
            ++at;
            ++bt;
        }
        else if ((*at).Exp > (*bt).Exp)
        {
            newTerm.Coef = (*at).Coef;
            newTerm.Exp = (*at).Exp;
            Sum.push_back(newTerm);
            ++at;
        }
        else if((*at).Exp < (*bt).Exp)
        {
            newTerm.Coef = (*bt).Coef;
            newTerm.Exp = (*bt).Exp;
            Sum.push_back(newTerm);
            ++bt;
        }
    }
    while (at != a.end())
    {
        newTerm.Coef = (*at).Coef;
        newTerm.Exp = (*at).Exp;
        Sum.push_back(newTerm);
        ++at;
    }
    while (bt != b.end())
    {
        newTerm.Coef = (*bt).Coef;
        newTerm.Exp = (*bt).Exp;
        Sum.push_back(newTerm);
        ++bt;
    }
    return Sum;
}

//define that a - b
List<Term> PolynomialsSub(List<Term> &a,List<Term> &b)
{
    List<Term> :: iterator bt;
    for (bt = b.begin(); bt != b.end(); ++bt)
    {
        (*bt).Coef = -(*bt).Coef;
    }
    return PolynomialsAdd(a,b);
}

//store in Polynomials[2]
//a * b
List<Term> PolynomialsMutipy(List<Term> &a,List<Term> &b)
{
    List<Term>::iterator at;
    List<Term>::iterator bt;
    Term newTerm;
    List<Term> Ans;
    List<Term> Temp;
    Ans.clear();
    for (at = a.begin(); at != a.end(); ++at)
    {
        Temp.clear();
        for (bt = b.begin(); bt != b.end(); ++bt)
        {
            double CoefAns = (*at).Coef * (*bt).Coef;
            int ExpAns = (*at).Exp + (*bt).Exp;
            newTerm.Coef = CoefAns;
            newTerm.Exp = ExpAns;
            addterm(Temp,newTerm);
        }
        Ans = PolynomialsAdd(Temp, Ans);
    }
    return Ans;
}

void Display(List<Term> &a)
{
    if (a.size() == 0)
    {
        cout<<0;
    }
    List<Term> :: iterator itr;
    int countsize = 0;
    for (itr = a.begin(); itr != a.end(); ++itr)
    {
        countsize ++;
        if ((*itr).Coef == 0)
        {
            continue;
        }
        else if ((*itr).Exp == 0)
        {
            cout<<(*itr).Coef;
        }
        else
        {
            cout<<(*itr).Coef<<"x^"<<(*itr).Exp;
        }
        if(countsize != a.size())
        {
            cout<<" + ";
        }
    }
    cout<<"\n";
}

double CaculateValue(List<Term> &a,double x)
{
    double Ans = 0;
    List<Term> :: iterator itr;
    for (itr = a.begin(); itr != a.end(); ++itr)
    {
        Ans += (*itr).Coef * (pow(x,(*itr).Exp));
    }
    return Ans;
}

void check_poly(List<Term> &p1)
{
    for (List<Term> :: iterator itr = p1.begin(); itr != p1.end(); ++itr)
    {
        if ((*itr).Coef == 0)
        {
            p1.erase(itr);
        }
    }
}

List<Term> try_divide(List<Term> &p1,List<Term> &p2)
{
    List<Term> quotient;
    List<Term> remainder;
    while ((*(p1.begin())).Exp >= (*(p2.begin())).Exp)
    {
        double temp_coef = (*(p1.begin())).Coef / (*(p2.begin())).Coef;
        int temp_exp = (*(p1.begin())).Exp - (*(p2.begin())).Exp;
        List<Term> temp;
        temp.clear();
        Term newTerm(temp_coef,temp_exp);
        temp.push_back(newTerm);
        addterm(quotient,newTerm);
        temp = PolynomialsMutipy(temp,p2);
        p1 = PolynomialsSub(p1,temp);
        for (List<Term> :: iterator itr = p1.begin(); itr != p1.end(); ++itr)
        {
            if ((*itr).Coef == 0)
            {
                p1.erase(itr);
            }
        }
    }
    return quotient;
}

List<Term> try_mod(List<Term> &p1,List<Term> &p2)
{
    List<Term> remainder = p1;
    List<Term> temp;
    temp = try_divide(p1, p2);
    check_poly(temp);
    temp = PolynomialsMutipy(temp, p2);
    remainder = PolynomialsSub(remainder, temp);
    check_poly(remainder);
    return remainder;
}


List<Term> DeepCopy(List<Term> &source)
{
    List<Term> ret;
    ret.clear();
    List<Term>::iterator itr;
    for (itr = source.begin();itr != source.end(); ++itr)
    {
        ret.push_back(Term((*itr).Coef,(*itr).Exp));
    }
    return ret;
}

void Extract()
{
    string a = "x^23+12x^3+343x^32";
    vector<Term> Vi;
    List<Term> ret;
    vector<int> StorePlus;
    for (int i = 0; i < a.size(); ++i)
    {
        if (a[i] == '+')
        {
            StorePlus.push_back(i);
        }
    }
    Term newTerm;
    double Coef = 0;
    int Exp = 0;
    stringstream transfer;
    transfer.clear();
    string substring;
    int prev = 0;
    int idx = 0;
    for (int i = 0; i < StorePlus.size(); ++i)
    {
        transfer.clear();
        bool FindX = 0;
        for (int j = prev; j < StorePlus[i]; ++j)
        {
            if (a[j] == 'x')
            {
                FindX = 1;
                idx = j;
                break;
            }
        }
        if (FindX)
        {
            if (idx == 0)
            {
                Coef = 1;
                if(a[idx+1] == '^')
                {
                    if(i + 1 < StorePlus.size())
                    {
                        substring = a.substr(idx+2,StorePlus[i]-idx-2);
                    }
                    else
                    {
                        substring = a.substr(idx + 2,a.size()-idx - 2);
                    }
                    transfer.clear();
                    transfer<<substring;
                    transfer>>Exp;
                }
                else
                {
                    Exp = 1;
                }
            }
            else
            {
                if(a[idx-1] == '+')
                {
                    Coef = 1;
                }
                else
                {
                    substring = a.substr(StorePlus[i-1]+1,idx - StorePlus[i-1] - 1);
                    transfer.clear();
                    transfer<<substring;
                    transfer>>Coef;
                }

                if(a[idx+1] == '^')
                {
                    if(i + 1 < StorePlus.size())
                    {
                        substring = a.substr(idx+2,StorePlus[i]-idx-2);
                    }
                    else
                    {
                        substring = a.substr(idx + 2,a.size()-idx - 2);
                    }
                    transfer.clear();
                    transfer<<substring;
                    transfer>>Exp;
                }
                else
                {
                    Exp = 1;
                }
            }
            newTerm.Coef = Coef;
            newTerm.Exp = Exp;
            Vi.push_back(newTerm);
        }
        else
        {
            substring = a.substr(prev,idx - prev + 1);
            transfer<<substring;
            transfer>>Coef;
            Exp = 0;
            newTerm.Coef = Coef;
            newTerm.Exp = Exp;
            Vi.push_back(newTerm);
        }
        prev = StorePlus[i] + 1;
    }
    //处理最后一项。
    int last = (int)StorePlus.size() - 1;
    int last_index = StorePlus[last];
    bool FindX = 0;
    for (int i = last_index; i < a.size(); ++i)
    {
    	if(a[i] == 'x')
    	{
    		FindX = 1;
    		idx = i;
    		break;
    	}
    }
    if(FindX)
    {
    	if(a[idx-1] == '+')
    	{
    		Coef = 1;
    	}
    	else
    	{
    		substring = a.substr(last_index + 1,idx - last_index - 1);
            stringstream ss;
            ss.clear();
            ss<<substring;
            ss>>Coef;
    	}

    	if(a[idx+1] == '^')
    	{
    		substring = a.substr(idx+2,a.size() - idx - 2);
            stringstream ss;
            ss.clear();
    		ss<<substring;
    		ss>>Exp;
    	}
    	else
    	{
    		Exp = 1;
    	}
    	newTerm.Coef = Coef;
    	newTerm.Exp = Exp;
    	Vi.push_back(newTerm);
    }
    
}

// void InputPoly(List<Term> &a)
// {
//     cout<<"Please Input Your New Polynomials: ";
//     string poly;
//     cin>>poly;
//     a = Extract(poly);
//     cout<<"You Have Inserted A Polynomials: ";
//     Display(a);
//     cout<<"\n";
// }


int main()
{
    Extract();
    return 0;
}
