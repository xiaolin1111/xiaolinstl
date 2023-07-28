#include "list.h"
#include <iostream>
using namespace linstl;
using namespace std;
int main()
{
    list<int> l;
    for(int i = 0;i<5;i++)
    {
        l.push_back(i);
    }
    list<int>::iterator iter=l.begin();
    for(;iter!=l.end();iter++)
    {
        cout<<*iter<<" ";
    }
    cout<<endl;
    l.reserve();
    list<int>::iterator iter2=l.begin();
    for(;iter2!=l.end();iter2++)
    {
        cout<<*iter2<<" ";
    }
    cout<<endl;
    
    l.emplace_back(7);
    iter2 = l.begin();
    cout<<endl;
    for(;iter2!=l.end();iter2++)
    {
        cout<<*iter2<<" ";
    }
    cout<<endl;
    l.sort(l.begin(),l.end());
    iter2=l.begin();
    for(;iter2!=l.end();iter2++)
    {
        cout<<*iter2<<" ";
    }
    cout<<endl;
    list<int> l2({1,2,3,4,5,6,7,8,9,10});
    auto iter3 = l2.begin();
    for(;iter3!=l2.end();iter3++)
    {
        cout<<*iter3<<" ";
    }
    cout<<endl;
    auto iter4 = l2.cbegin();
    for(;iter4!=l2.cend();iter4++)
    {
        cout<<*iter4<<" ";
    }
    cout<<endl;
    cout<<l2.size();
    cout<<endl;
    l2.clear();
    cout<<l2.size();

    return 0;


}