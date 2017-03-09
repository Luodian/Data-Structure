//
//  main.cpp
//  Infix
//
//  Created by 李博 on 2016/11/5.
//  Copyright © 2016年 李博. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstring>
#include <stack>
#include <vector>
#include <map>

using namespace std;

bool is_operator(const char &op)
{
    string container;
    container.push_back(op);
    if(container[0] == '+' || container[0] == '-' || container[0] == '*' || container[0] == '/'
       || container[0] == '^' || container[0] == '&'|| container[0] == '%'|| container[0] == '(' || container[0] == ')'
       || container[0] == '|')
    {
        return 1;
    }
    return 0;
}

template <typename object>
void watch_stack(stack<object> &st)
{
    if(st.empty())
    {
        return;
    }
    vector<object> contaniner;
    while(!st.empty())
    {
        contaniner.push_back(st.top());
        st.pop();
    }
    cout<<"Stack state(from buttom to top): ";
    for (int i = contaniner.size() - 1; i >= 0; --i)
    {
        cout<<contaniner[i]<<" ";
    }
    //retore stack;
    for(int i = contaniner.size() - 1; i >= 0; --i)
    {
        st.push(contaniner[i]);
    }
    cout<<"\n";
}

int CheckPri(const char &op)
{
    string container;
    container.push_back(op);
    if (container[0] == '+' || container[0] == '-')
    {
        return 1;
    }
    else if (container[0] == '*' || container[0] == '/')
    {
        return 2;
    }
    else
    {
        return 3;
    }
}

string Execute(const string &infix)
{
    stack<char> stack_container;
    string ret;
    bool FindLeftBracket = 0;
    for (int i = 0; i < infix.size(); ++i)
    {
        if (FindLeftBracket && infix[i] == ')')
        {
            while(!stack_container.empty() && stack_container.top() != '(')
            {
                ret.push_back(stack_container.top());
                stack_container.pop();
            }
            stack_container.pop();
            cout<<"Poping until left bracket\n";
            watch_stack(stack_container);
            cout<<"\n";
        }
        else if (is_operator(infix[i]))
        {
            watch_stack(stack_container);
            cout<<"\n";
            if(stack_container.empty() == 0 && infix[i] != '(' && infix[i] != ')' && CheckPri(infix[i]) < CheckPri(stack_container.top()))
            {
                while(!stack_container.empty() && (stack_container.top() != '(' && CheckPri(infix[i]) <= CheckPri(stack_container.top())))
                {
                    ret.push_back(stack_container.top());
                    stack_container.pop();
                }
                cout<<"Poping until meet a upper operator\n";
                watch_stack(stack_container);
                cout<<"\n";
            }
            if(infix[i] == '(')
            {
                FindLeftBracket = 1;
            }
            stack_container.emplace(infix[i]);
        }
        else
        {	
            ret.push_back(infix[i]);
        }
    }
    while(stack_container.empty() == 0)
    {
        ret.push_back(stack_container.top());
        stack_container.pop();
    }
    return ret;
}

double caculate(map<char,double> &KeyMap,const string &PostfixString)
{
    stack<double> PostStack;
    double ans = 0;
    for (int i = 0; i < PostfixString.size();++i)
    {
        if(isalpha(PostfixString[i]))
        {
            PostStack.push(KeyMap[PostfixString[i]]);
        }
        else if(is_operator(PostfixString[i]))
        {
            watch_stack(PostStack);
            double B = PostStack.top();
            PostStack.pop();
            double A = PostStack.top();
            PostStack.pop();
            cout<<"Poping A = "<<A<<" and B = "<<B<<"\n";
            if (PostfixString[i] == '*')
            {
                ans = A * B;
                PostStack.push(ans);
                cout<<"Pushing A * B to stack\n";
                watch_stack(PostStack);
            }
            else if (PostfixString[i] == '-')
            {
                ans  = A - B;
                PostStack.push(ans);
                cout<<"Pushing A - B to stack\n";
                watch_stack(PostStack);
            }
            else if (PostfixString[i] == '+')
            {
                ans  = A + B;
                PostStack.push(ans);
                cout<<"Pushing A + B to stack\n";
                watch_stack(PostStack);
            }
            else if (PostfixString[i] == '/')
            {
                ans = (double)A / B;
                PostStack.push(ans);
                cout<<"Pushing A / B to stack\n";
                watch_stack(PostStack);
            }
            cout<<"\n";
        }
    }
    if(PostStack.size() == 1)
    {
        return ans;
    }
    else
    {
        cout<<"Invalid Postfix\n";
        return 0;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    string infix;
    string postfix;
    map<char,double> KeyMap;
    // cout<<"Please input a valid infix expression: ";
    cin>>infix;
    cout<<"Your infx expression is: "<<infix<<"\n";
    // string test = Execute("a+b*c+(c*a+d)*b");
    postfix = Execute(infix);
    cout<<"\n";
    cout<<"The postfix expression is: ";
    cout<<postfix<<"\n\n";
    int n_vr;
    cin>>n_vr;
    for (int i = 0; i < n_vr; ++i)
    {
        char key = 'a' + i;
        int value;
        cin>>value;
        cout<<key<<"'s value is: "<<value<<"\n";
        KeyMap.emplace(key,value);
    }
    cout<<"\n";
    double ans = caculate(KeyMap,postfix);
    cout<<"\n";
    cout<<"The postfix expression is: ";
    cout<<postfix<<"\n\n";
    cout<<"According to postfix, its value is: "<<ans<<"\n\n";
}
