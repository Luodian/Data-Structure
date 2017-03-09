#include <iostream>
#include <fstream>
#include <algorithm>
#include <stack>
#include <string>
#include "List.cpp"

using namespace std;

class Polynomial
{
private:
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
	List<Term> _self;
	queue <Term *> Freenode;
	Term Node[500];
public:
	Polynomial()
	{
		List<Term> Polynomial;
		for (int i = 0 ; i < 500; ++i)
		{
			Freenode.push_back(&Node[i]);
		}

	}
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
	List<Term> operator + (List<Term> &a)
	{
	    List<Term> :: iterator at = a.begin();
	    List<Term> :: iterator bt = (*this).begin();
	    Term newTerm;
	    List<Term> Sum;
	    while (at != a.end() && bt != (*this).end())
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
	    while (bt != (*this).end())
	    {
	        newTerm.Coef = (*bt).Coef;
	        newTerm.Exp = (*bt).Exp;
	        Sum.push_back(newTerm);
	        ++bt;
	    }
	    return Sum;
	}
	List<Term> operator - (List<Term> &b)
	{
	    List<Term> :: iterator bt;
	    for (bt = b.begin(); bt != b.end(); ++bt)
	    {
	        (*bt).Coef = -(*bt).Coef;
	    }
	    return PolynomialsAdd((*this),b);
	}
	friend ostream & operator <<(ostream &os,List<Term> &a)
	{
		if (a.size() == 0)
	    {
	        os<<0;
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
	            os<<(*itr).Coef;
	        }
	        else
	        {
	            os<<(*itr).Coef<<"x^"<<(*itr).Exp;
	        }
	        if(countsize != a.size())
	        {
	            os<<" + ";
	        }
	    }
	    os<<"\n";
	    return os;
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
	List<Term> operator / (List<Term> &p2)
	{
	    List<Term> quotient;
	    List<Term> remainder;
	    while ((*this)).begin().Exp >= (*(p2.begin())).Exp)
	    {
	        double temp_coef = (*this).begin().Coef / (*(p2.begin())).Coef;
	        int temp_exp = (*this).begin().Exp - (*(p2.begin())).Exp;
	        List<Term> temp;
	        temp.clear();
	        Term newTerm(temp_coef,temp_exp);
	        temp.push_back(newTerm);
	        addterm(quotient,newTerm);
	        temp = PolynomialsMutipy(temp,p2);
	        *this = PolynomialsSub(*this,temp);
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
	List<Term> operator % (List<Term> &p2)
	{
	    List<Term> remainder = (*this);
	    List<Term> temp;
	    temp = try_divide(*this, p2);
	    check_poly(temp);
	    temp = PolynomialsMutipy(temp, p2);
	    remainder = PolynomialsSub(remainder, temp);
	    check_poly(remainder);
	    return remainder;
	}
	void InputPoly(List<Term> &a)
	{
	    int t_a;
	    cout<<"Please Input The Number Of Terms in: ";
	    cin>>t_a;
	    for (int i = 0; i < t_a; ++i)
	    {
	        double coef;
	        int exp;
	        Term newTerm;
	        cout<<i+1<<"."<<"Coef = :";
	        cin>>coef;
	        cout<<i+1<<"."<<"Exp = :";
	        cin>>exp;
	        newTerm.Coef = coef;
	        newTerm.Exp = exp;
	        addterm(a,newTerm);
	    }
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
};

int main()
{

}